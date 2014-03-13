/* -*- c++ -*- */
/* 
 * Copyright 2014 Alexandru Csete OZ9AEC.
 * 
 * License: GPLv3
 *
 */

#ifndef DATVEXPRESS_SINK_C_IMPL_H
#define DATVEXPRESS_SINK_C_IMPL_H

#include <datvexpress/sink_c.h>
#include "hw/express.h"

#define BUFLEN 65536

namespace gr {
    namespace datvexpress {

        class sink_c_impl : public sink_c
        {
        public:
            sink_c_impl();
            ~sink_c_impl();

            int work(int noutput_items,
                     gr_vector_const_void_star &input_items,
                     gr_vector_void_star &output_items);

            // public API functions documented in datvexpress/sink_c.h
            void set_freq(double freq);
            double get_freq(void) const;
            void set_level(int level);
            int  get_level(void) const;
            void set_sample_rate(double rate);
            double get_sample_rate(void) const;
            void set_iq_cal(short ical, short qcal);
 
        private:
            scmplx output_buffer[BUFLEN];  // FIXME: Can be smaller?

            double m_freq;  /*!< RF frequency [Hz] */
            double m_rate;  /*!< Sample rate [sps] */
            int m_interp;   /*!< Interpolation rate for the current sample rate. */
            int m_filter;   /*!< Filter selection 0 to 3 (or 1 to 4)? */
            int m_level;    /*!< TX output level from 0 to 46. */
            
       };

    }
}

#endif

