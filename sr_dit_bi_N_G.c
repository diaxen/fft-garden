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
#include "bit_reverse.h"

/* Based on implementation of the DIT Split-Radix FFT proposed in the
   1984 paper "On Computing the Split-Radix FFT". Translated from
   Fortran to C.

   This is essentially a breadth first approach with inner loops
   arranged so that all butterflies with the same twiddles are
   processed before moving to the next twiddles value. This makes the
   algorithm walk through blocks of butterflies several times.

   The skodras92 algorithm uses a similar approach, relying on lookup
   tables to replace the two innermost nested loops by a single loop.
*/

static void
burrus84_fft(complex double * restrict inout,
	     unsigned n, unsigned m)
{
  BIT_REVERSE_SWAP_LOOP(i, j, n, {
      double complex t = inout[i];
      inout[i] = inout[j];
      inout[j] = t;
  });

  /* length two transforms */

  for (unsigned is = 0, id = 4; is < n; )
    {
      for (unsigned i0 = is; i0 < n; i0 += id)
	ct_dit_bf2_0(1, 1, inout + i0, inout + i0);
      is = 2 * id - 2;
      id = 4 * id;
    }

  if (m < 2)
    return;

  /* L shaped butterflies */

  for (unsigned k = 2; k <= m; k++)
    {
      unsigned n2 = 1 << k;
      unsigned n4 = n2 >> 2;

      for (unsigned j = 0; j < n4; j++)
	{
	  unsigned t = j << (m - k);
	  complex double w1 = get_twiddle(t, m);
	  complex double w3 = get_twiddle_sr(t, m);

	  for (unsigned is = j, id = 2 << k; is < n; )
	    {
	      for (unsigned i0 = is; i0 < n; i0 += id)
		sr_dit_bf4(n4, inout + i0, w1, w3);
	      is = 2 * id - n2 + j;
	      id = 4 * id;
	    }
	}
    }
}

void
fft(unsigned N, complex double * restrict inout)
{
  unsigned log2_N = 31 - __builtin_clz(N);
  burrus84_fft(inout, N, log2_N);
}

void fft_init(unsigned N)
{
  twiddles_sr_init(N / 4, N);
}

void fft_cleanup()
{
  twiddles_cleanup();
}
