/*
    Written in 2019 by Alexandre Becoulet <alexandre.becoulet@free.fr>

    To the extent possible under law, the author(s) have dedicated all
    copyright and related and neighboring rights to this software to
    the public domain worldwide. This software is distributed without
    any warranty.

    You should have received a copy of the CC0 Public Domain
    Dedication along with this software. If not, see
    http://creativecommons.org/publicdomain/zero/1.0/
*/


#include "fft.h"
#include "twiddles.h"
#include "sr_sched_lut.h"
#include "sr_input_lut.h"
#include "sr_bf.h"
#include "ct_bf.h"


/* Based on implementation of the DIT Split-Radix FFT proposed in the
   1992 paper "Efficient computation of the Split-Radix FFT".

   This is essentially a breadth first approach with inner loops
   arranged so that all butterflies with the same twiddles are
   processed before moving to the next twiddles value. This make the
   algorithm walk through blocks of butterflies several times.

   Unlike the burrus84 split-radix FFT, this one relies on lookup
   tables for butterflies scheduling.

   The original algorithm has been modified to use simplified
   butterfly functions for special angles 0 and pi/4.
*/

void
fft(unsigned N, complex double * restrict out,
    const complex double * restrict in)
{
  unsigned log2_N = 31 - clz32(N);

  /* stage 0 */
  for (unsigned j = 0, is = 0; is < N; is += 2)
    {
      unsigned i0 = sr_input_lut[is / 2];

      if (sr_sched_off[j] * 2 > is)
        {
          out[is    ] = in[i0];
          out[is + 1] = in[i0 + N / 2];
        }
      else
        {
          ct_dit_bf2_0(1, N / 2, out + is, in + i0);
          j++;
        }
    }

  /* stage 1 */
  if (log2_N > 1)
    {
      unsigned c = sr_sched_cnt[1];
      for (unsigned i = 0; i < c; i++)
        {
          unsigned o = sr_sched_off[i] << 2;
          sr_dit_bf4_0(1, out + o);
        }
    }

  /* stage 2 */
  if (log2_N > 2)
    {
      unsigned c = sr_sched_cnt[2];
      for (unsigned i = 0; i < c; i++)
        {
          unsigned o = sr_sched_off[i] << 3;

          sr_dit_bf4_0(2, out + o);
          sr_dit_bf4_pi4(2, out + o + 1);
        }
    }

  /* stage >= 3 */
  if (log2_N > 3)
    for (unsigned k = 3; k < log2_N; k++)
      {
        unsigned t = log2_N - k - 1;
        unsigned n2 = 1 << (k - 1);
        unsigned n4 = 1 << (k - 2);

        unsigned c = sr_sched_cnt[k];
        for (unsigned i = 0; i < c; i++)
          {
            unsigned o = sr_sched_off[i] << (k + 1);

            sr_dit_bf4_0(n2, out + o);
            sr_dit_bf4_pi4(n2, out + o + n4);
          }

        for (unsigned j0 = 1; j0 < n4; j0++)
          {
            complex double w1 = get_twiddle(j0 << t, log2_N);
            complex double w3 = get_twiddle_sr(j0 << t, log2_N);
            unsigned c = sr_sched_cnt[k];

            for (unsigned i = 0; i < c; i++)
              {
                unsigned o = sr_sched_off[i] << (k + 1);
                sr_dit_bf4(n2, out + o + j0, w1, w3);
              }

            unsigned j1 = j0 + n4;
            w1 = get_twiddle(j1 << t, log2_N);
	    w3 = get_twiddle_sr(j1 << t, log2_N);

            for (unsigned i = 0; i < c; i++)
              {
                unsigned o = sr_sched_off[i] << (k + 1);
                sr_dit_bf4(n2, out + o + j1, w1, w3);
              }
	  }
      }
}

void fft_init(unsigned N)
{
  twiddles_sr_init(N / 4, N);
  sr_input_lut_init(N);
  sr_sched_lut_init(N);
}

void fft_cleanup()
{
  sr_sched_lut_cleanup();
  sr_input_lut_cleanup();
  twiddles_cleanup();
}
