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
#include "cp_bf.h"

static void
cp_dit_dr(unsigned log2_N,
	  const complex double * restrict in,
	  complex double * restrict out,
	  unsigned l, unsigned i)
{
  unsigned is = 1 << (log2_N - l);
  unsigned os = 1 << (l - 2);
  unsigned mask = (1 << log2_N) - 1;
  unsigned i0 = i & mask;
  unsigned t = log2_N - l;

  switch (l)
    {
#if 0
    case 0:			/* size 1 base case  */
      out[0] = in[i];
      break;
#endif

    case 1: {			/* size 2 base case  */
      unsigned i1 = i0 ^ is;
      complex double a = in[i0];
      complex double b = in[i1];
      out[0] = a + b;
      out[1] = a - b;
      break;
    }

    case 2: {			/* size 4 base case  */
      //      cp_dit_dr(log2_N, in, out, 1, i);
      unsigned i1 = i0 ^ (1 << (log2_N - 1));
      complex double a = in[i0];
      complex double b = in[i1];
      out[0] = a + b;
      out[1] = a - b;

      out[2] = in[(i + is) & mask];
      out[3] = in[(i - is) & mask];
      cp_dit_bf_0(1, out);
      break;
    }

    default:
      cp_dit_dr(log2_N, in, out, l - 1, i);
      cp_dit_dr(log2_N, in, out + 2 * os, l - 2, i + is);
      cp_dit_dr(log2_N, in, out + 3 * os, l - 2, i - is);

      unsigned k;
      cp_dit_bf_0(os, out);

      for (k = 1; k < os / 2; k++)
	cp_dit_bf(os, out + k, get_twiddle(k << t, log2_N));

      cp_dit_bf_pi4(os, out + k);

      for (k += 1; k < os; k++)
	cp_dit_bf(os, out + k, get_twiddle(k << t, log2_N));
    }
}

void
fft(unsigned N, complex double * restrict out,
    const complex double * restrict in)
{
  unsigned log2_N = 31 - __builtin_clz(N);
  cp_dit_dr(log2_N, in, out, log2_N, 0);
}

void fft_init(unsigned N)
{
  twiddles_init(N / 4, N);
}

void fft_cleanup()
{
  twiddles_cleanup();
}
