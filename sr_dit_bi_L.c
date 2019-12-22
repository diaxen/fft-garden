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


/* An iterative breadth-first implementation of the DIT Split-Radix
   FFT. The algorithm relies on lookup table for butterflies
   scheduling.

   Unlike the skodras92 Split-Radix variant, this algorithm do not
   group all butterflies sharing the same twiddles in the stage.
*/

void
fft(unsigned N, complex double * restrict out,
    const complex double * restrict in)
{
  unsigned log2_N = 31 - clz32(N);

  /* stage 0 */
  for (unsigned j = 0, i = 0; i < N; i += 2)
    {
      unsigned i0 = sr_input_lut[i / 2];

      if (sr_sched_off[j] * 2 > i)
        {
          out[i    ] = in[i0];
          out[i + 1] = in[i0 + N / 2];
        }
      else
        {
          ct_dit_bf2_0(1, N / 2, out + i, in + i0);
          j++;
        }
    }

  /* stage >= 1 */
  if (log2_N > 1)
    for (unsigned s = 1; s < log2_N; s++)
      {
        unsigned c = sr_sched_cnt[s];

        for (unsigned i = 0; i < c; i++)
          {
            complex double *o = out + (sr_sched_off[i] << (s + 1));
            unsigned t = log2_N - s - 1;
            unsigned os = 1 << (s - 1);

            for (unsigned k = 0; k < os; k++)
              sr_dit_bf4(os, o + k,
                     get_twiddle(k << t, log2_N),
                     get_twiddle_sr(k << t, log2_N));
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
