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
#include "sr_bf.h"
#include "ct_bf.h"

/* A recursive implementation of the DIT Split-Radix FFT */

static void
sr_dit_dr(unsigned log2_N,
	  const complex double * restrict in,
	  complex double * restrict out,
	  unsigned l, unsigned i)
{
  unsigned is = 1 << (log2_N - l);
  unsigned os = 1 << (l - 2);
  unsigned t = log2_N - l;

  switch (l)
    {
    case 1:                     /* size 2 base case  */
      ct_dit_bf2_0(1, is, out, in + i);
      break;

    case 2:                     /* size 4 base case  */
      // sr_dit_dr(log2_N, in, out, 1, i);
      ct_dit_bf2_0(1, is * 2, out, in + i);

      out[2] = in[i + is];
      out[3] = in[i + 3 * is];
      sr_dit_bf4_0(1, out);
      break;

    default:
      sr_dit_dr(log2_N, in, out, l - 1, i);
      sr_dit_dr(log2_N, in, out + os * 2, l - 2, i + is);
      sr_dit_dr(log2_N, in, out + 3 * os, l - 2, i + 3 * is);

      unsigned k;
      sr_dit_bf4_0(os, out);
      sr_dit_bf4_pi4(os, out + os / 2);

      for (k = 1; k < os / 2; k++)
	{
	  complex double w1 = get_twiddle(k << t, log2_N);
	  complex double w3 = get_twiddle_sr(k << t, log2_N);
	  sr_dit_bf4(os, out + k, w1, w3);
	  sr_dit_bf4(os, out + os - k, conj(w1 * I), -conj(w3 * I));
	}
    }
}

void
fft(unsigned N, complex double * restrict out,
    const complex double * restrict in)
{
  unsigned log2_N = 31 - __builtin_clz(N);
  sr_dit_dr(log2_N, in, out, log2_N, 0);
}

void fft_init(unsigned N)
{
  twiddles_sr_init(N / 8, N);
}

void fft_cleanup()
{
  twiddles_cleanup();
}
