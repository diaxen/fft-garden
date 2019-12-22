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
#include "cp_input_lut.h"
#include "cp_bf.h"


void
fft(unsigned N, complex double * restrict out,
    const complex double * restrict in)
{
  unsigned log2_N = 31 - clz32(N);

  /* stage 0 */
  for (unsigned j = 0, i = 0; i < N; i += 2)
    {
      unsigned i0 = cp_input_lut[i / 2];
      unsigned i1 = i0 ^ (N >> 1);

      if (sr_sched_off[j] * 2 > i)
        {
          out[i    ] = in[i0];
          out[i + 1] = in[i1];
        }
      else
        {
          complex double a = in[i0];
          complex double b = in[i1];
          out[i    ] = a + b;
          out[i + 1] = a - b;
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
          cp_dit_bf_0(1, out + o);
        }
    }

  /* stage 2 */
  if (log2_N > 2)
    {
      unsigned c = sr_sched_cnt[2];
      for (unsigned i = 0; i < c; i++)
        {
          unsigned o = sr_sched_off[i] << 3;

          cp_dit_bf_pi4(2, out + o + 1);
          cp_dit_bf_0(2, out + o);
        }
    }

  /* stage >= 3 */
  if (log2_N > 3)
    for (unsigned s = 3; s < log2_N; s++)
      {
        unsigned c = sr_sched_cnt[s];
	unsigned os = 1 << (s - 1);

	for (unsigned i = 0; i < c; i++)
	  {
	    unsigned o = sr_sched_off[i] << (s + 1);
	    cp_dit_bf_0(os, out + o);
	  }

	for (unsigned k = 1; k < os; k++)
	  {
	    unsigned t = log2_N - s - 1;
	    complex double w = get_twiddle(k << t, log2_N);

	    for (unsigned i = 0; i < c; i++)
	      {
		unsigned o = sr_sched_off[i] << (s + 1);
		cp_dit_bf(os, out + o + k, w);
	      }
	  }
      }
}

void fft_init(unsigned N)
{
  twiddles_init(N / 4, N);

  cp_input_lut_init(N);
  sr_sched_lut_init(N);
}

void fft_cleanup()
{
  sr_sched_lut_cleanup();
  cp_input_lut_cleanup();
  twiddles_cleanup();
}
