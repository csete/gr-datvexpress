/* -*- c++ -*- */
/* 
 * Copyright 2014 Alexandru Csete OZ9AEC.
 * 
 * License: GPLv3
 *
 */
#ifndef DATVEXPRESS_SINK_C_H
#define DATVEXPRESS_SINK_C_H

#include <datvexpress/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
    namespace datvexpress {

        /*!
         * \brief DATV-Express sink block
         * \ingroup datvexpress
         *
         * \details
         * This class implements a sink block foir the DATV-Express wide band
         * transmitter board.
         *
         * For more info about the DATV-Express project see the website:
         * http://datv-express.com/ 
         */
        class DATVEXPRESS_API sink_c : virtual public gr::sync_block
        {
        public:
            typedef boost::shared_ptr<sink_c> sptr;

            /*!
             * \brief Return a shared_ptr to a new instance of datvexpress::sink_c.
             *
             * To avoid accidental use of raw pointers, datvexpress::sink_c's
             * constructor is in a private implementation class.
             * datvexpress::sink_c::make is the public interface for creating new
             * instances.
             */
            static sptr make();

            /*! \brief Set oputput level.
             *  \param level The output level between 0 and 46.
             *
             * \todo Confirm range.
             */
            virtual void set_level(int level) = 0;

            /*! \brief Get output level
             *  \returns The current output level between 0 and 46.
             */
            virtual int  get_level(void) const = 0;

            /*! \brief Set RF frequency.
             *  \param freq The desired RF frequency in Hz.
             *
             * The valid range of DATV-Express is 100 MHz to 2.45 GHz.
             */
            virtual void set_freq(double freq) = 0;

            /*! \brief Get RF frequency.
             *  \return The current RF frequency in Hz.
             *
             * \note This functions returns a cached frequency and not a
             *       frequency read from the device.
             */
            virtual double get_freq(void) const = 0;

            /*! \brief Set sample rate.
             *  \param rate The desired sample rate between 1.0 and 10.0 Msps.
             *  \note The hardware is optimized for 2-6 Msps.
             */
            virtual void set_sample_rate(double rate) = 0;

            /*! \brief Get sample rate.
             *  \returns The current sample rate in samples / second.
             */
            virtual double get_sample_rate(void) const = 0;

            /*! \brief Set I/Q calibration. */
            virtual void set_iq_cal(short ical, short qcal) = 0;
        };

    }
}

#endif /* INCLUDED_DATVEXPRESS_SINK_C_H */

