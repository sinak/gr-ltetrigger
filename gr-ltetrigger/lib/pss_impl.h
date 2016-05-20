/* -*- c++ -*- */
/*
 * Copyright 2016 <+YOU OR YOUR COMPANY+>.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_LTETRIGGER_PSS_IMPL_H
#define INCLUDED_LTETRIGGER_PSS_IMPL_H

#include <string> /* string */

#include <srslte/srslte.h>

#include <ltetrigger/pss.h>


namespace gr {
  namespace ltetrigger {

    class pss_impl : public pss
    {
    private:
      struct tracking_t
      {
        bool id[3] = {false};
        int score[3] = {0};
        int countdown[3] = {0};
        bool any() const { return id[0] | id[1] | id[2]; }
      } static d_tracking;

      static const int slot_length = 960;
      static const int half_frame_length = 10 * slot_length;
      static const int full_frame_length = 2 * half_frame_length;
      static const int symbol_sz = 128;

      const pmt::pmt_t tracking_port_id = pmt::intern("tracking_lost");

      void incr_score(tracking_t &tracking);
      void decr_score(tracking_t &tracking);

      srslte_pss_synch_t d_pss;
      float d_psr = 0;
      double d_psr_sum = 0.0;
      int d_psr_nsummed = 0;
      float d_psr_max = 0.0;
      int d_peak_pos = 0;

      int d_N_id_2;
      float d_psr_threshold;
      int d_track_after_n_frames;
      int d_track_every_n_frames;

    public:
      pss_impl(int N_id_2,
               float psr_threshold,
               int track_after,
               int track_every);
      ~pss_impl();

      int general_work(int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items);
    };

  } // namespace ltetrigger
} // namespace gr

#endif /* INCLUDED_LTETRIGGER_PSS_IMPL_H */
