/* -*- c++ -*- */
/* 
 * Copyright 2014 Alexandru Csete OZ9AEC.
 * 
 * License: GPLv3
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <gnuradio/io_signature.h>

#include "sink_c_impl.h"
#include "hw/express.h"

namespace gr {
    namespace datvexpress {

        sink_c::sptr sink_c::make()
        {
            return gnuradio::get_initial_sptr(new sink_c_impl());
        }

        /* Private constructor */
        sink_c_impl::sink_c_impl()
          : gr::sync_block("sink_c",
                           gr::io_signature::make(1, 1, sizeof(gr_complex)),
                           gr::io_signature::make(0, 0, sizeof(short)))
        {
            m_level = 0;
            m_filter = 3;
            m_freq = 434.115e6;

            // Initialise DATV-Express board
            int retcode = express_init();
            switch (retcode)
            {
            case EXP_OK:
                fprintf(stderr, "DATV-Express intialised\n");
                express_set_freq(m_freq);
                m_interp = express_set_sr(2048000);
                express_set_interp_and_filter(m_interp, m_filter);
                express_set_level(m_level);
                break;

            case EXP_FAIL:
            case EXP_MISS:
                throw std::runtime_error("DATV-Express Hardware not found");
                break;

            case EXP_IHX:
                throw std::runtime_error("FX2 firmware file not found");
                break;

            case EXP_RBF:
                throw std::runtime_error("FPGA firmware file not found");
                break;

            case EXP_CONF:
                throw std::runtime_error("Error configuring DATV-Express hardware");
                break;

            default:
                throw std::runtime_error("express_init() returned unknown return code");
                break;
            }

        }

        sink_c_impl::~sink_c_impl()
        {
            express_deinit();
        }

        int sink_c_impl::work(int noutput_items,
                              gr_vector_const_void_star &input_items,
                              gr_vector_void_star &output_items)
        {
            const gr_complex *in = (const gr_complex *) input_items[0];
            (void) output_items[0];

            int num = noutput_items > BUFLEN ? BUFLEN : noutput_items;

            if (noutput_items > BUFLEN)
            {
                fprintf(stderr, "Got more samples that we have room for: %d\n",
                                noutput_items);
            }

            // float-complex to short-complex conversion (FIXME: use VOLK)
            for (int i = 0; i < num; i++)
            {
                output_buffer[i].re = (short)(32767.0f * in[i].real());
                output_buffer[i].im = (short)(32767.0f * in[i].imag());
            }

            // Send samples to board.
            // Returns 0 if OK; otherwise error comming from libusb_submit_transfer()
            if (express_write_samples(output_buffer, num))
            {
                fprintf(stderr, "Error writing samples\n");
            }

            return num;
        }

        // set frequency
        void sink_c_impl::set_freq(double freq)
        {
            if (freq < 100.0e6)
                m_freq = 100.0e6;
            else if (freq > 2.45e9)
                m_freq = 2.45e9;
            else
                m_freq = freq;

            express_set_freq(m_freq);
        }

        // get frequency
        double sink_c_impl::get_freq() const
        {
            return m_freq;
        }

        // set output level
        void sink_c_impl::set_level(int level)
        {
            if (level < 0)
                m_level = 0;
            else if (level > 46)
                m_level = 46;
            else
                m_level = level;

            express_set_level(m_level);
        }

        // get output level
        int  sink_c_impl::get_level() const
        {
            return m_level;
        }

        // set sample rate
        void sink_c_impl::set_sample_rate(double rate)
        {
            if (rate < 1.0e6)
                m_rate = 1.0e6;
            else if (rate > 10.0e6)
                m_rate = 10.0e6;
            else
                m_rate = rate;

            // set sample rate and update interpolation+filter
            m_interp = express_set_sr(m_rate);
            express_set_interp_and_filter(m_interp, m_filter);
        }

        // get sample rate
        double sink_c_impl::get_sample_rate() const
        {
            return m_rate;
        }

        void sink_c_impl::set_iq_cal(short ical, short qcal)
        {
            express_load_calibration(ical, qcal);
        }
        

    } // namespace datvexpress
} // namespace gr

