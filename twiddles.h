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


/* Twiddle factors generation

  - When the NO_TW macro is defined, no twiddle factor table is
    used. In this case, the cexp function is called to compute the
    twiddles on the fly.

  - When the SHORT_TW macro is defined, the size of the table is
    limited to N/8 entries and additional processing is required when
    accessing the twiddles.
 */

#ifndef _TWIDDLES_H_
#define _TWIDDLES_H_

#include <assert.h>
#include <complex.h>
#include <math.h>
#include <stdint.h>

void twiddles_init(unsigned l, unsigned N);
void twiddles_sr_init(unsigned l, unsigned N);
void twiddles_cleanup();

#ifndef CMPLX
# define CMPLX(a, b) (complex double){a, b}
#endif
#ifndef CMPLXF
# define CMPLXF(a, b) (complex float){a, b}
#endif

extern complex double *twiddles;
extern complex double *twiddles_sr;

static inline complex double
get_twiddle(unsigned i, unsigned log2_N)
{
#if defined(NO_TW)
  return cexp(-2 * M_PI * I * i / (1 << log2_N));

#elif defined(SHORT_TW)
  unsigned m = 1 << (log2_N - 3);
  unsigned q = i & (m - 1);

  i >>= log2_N - 3;

  if (i & 1)
    q = m - q;

  /*
     i == 0 : ( r,  i)
     i == 1 : (-i, -r)
     i == 2 : ( i, -r)
     i == 3 : (-r,  i)
  */

  switch (sizeof(twiddles[0]))
    {
    case 16: {
      union {
        double d;
        uint64_t u;
      } vr, vi;

      uint64_t nw = (i ^ (i >> 1)) & 1;
      uint64_t *x = (uint64_t*)(twiddles + q);
      vi.u = x[nw ^ 1] ^ (nw << 63);
      vr.u = x[nw] ^ ((i & 1ULL) << 63);

      return CMPLX(vr.d, vi.d);
    }

    case 8: {
      union {
        float d;
        uint32_t u;
      } vr, vi;

      uint32_t nw = (i ^ (i >> 1)) & 1;
      uint32_t *x = (uint32_t*)(twiddles + q);
      vi.u = x[nw ^ 1] ^ (nw << 31);
      vr.u = x[nw] ^ ((i & 1) << 31);

      return CMPLXF(vr.d, vi.d);
    }

    }

#else

  return twiddles[i];

#endif
}

/* used for second twiddle of split radix, returns twiddle(i * 3) */
static inline complex double
get_twiddle_sr(unsigned i, unsigned log2_N)
{
#if defined(NO_TW)
  return cexp(-2 * M_PI * I * 3 * i / (1 << log2_N));

#elif defined(SHORT_TW)
  i *= 3;
  complex double tw = get_twiddle(i, log2_N);
  /* angle can be greater then pi */
  if (i >> (log2_N - 1))
    tw = -tw;
  return tw;
#else

  return twiddles_sr[i];
#endif
}

/* used for last twiddle of radix4 because angle can be greater than pi */
static inline complex double
get_twiddle_mr(unsigned i, unsigned log2_N)
{
  complex double tw = get_twiddle(i, log2_N);
#if defined(SHORT_TW)
  if (i >> (log2_N - 1))
    tw = -tw;
#endif
  return tw;
}

#endif
