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


/* Butterflies for the Split-Radix FFT */

#ifndef _SR_BF_H_
#define _SR_BF_H_

#include <complex.h>
#include <math.h>

#ifndef CMPLX
# define CMPLX(a, b) (complex double){a, b}
#endif

static inline void
sr_dit_bf4(unsigned s,
       complex double * restrict out,
       complex double w1, complex double w3)
{
  complex double a = out[0];
  complex double b = out[s];
  complex double c = out[s * 2];
  complex double d = out[s * 3];
  out[0]     = a +     (w1 * c + w3 * d);
  out[s]     = b - I * (w1 * c - w3 * d);
  out[s * 2] = a -     (w1 * c + w3 * d);
  out[s * 3] = b + I * (w1 * c - w3 * d);
}

static inline void
sr_dit_bf4_pi4(unsigned s,
           complex double * restrict out)
{
  complex double a = out[0];
  complex double b = out[s];
  complex double c = out[s * 2];
  complex double d = out[s * 3];

  double rc   = M_SQRT1_2 * creal(c);
  double rd   = M_SQRT1_2 * creal(d);
  double ic   = M_SQRT1_2 * cimag(c);
  double id   = M_SQRT1_2 * cimag(d);
  double wcr  = ic + rc;
  double wci  = ic - rc;
  double wdr  = -rd + id;
  double wdi  = -rd - id;
  double rsu  = wcr + wdr;
  double rsb  = wcr - wdr;
  double isu  = wci + wdi;
  double isb  = wci - wdi;

  out[0]     = CMPLX(creal(a) + rsu, cimag(a) + isu);
  out[s]     = CMPLX(creal(b) + isb, cimag(b) - rsb);
  out[s * 2] = CMPLX(creal(a) - rsu, cimag(a) - isu);
  out[s * 3] = CMPLX(creal(b) - isb, cimag(b) + rsb);
}

static inline void
sr_dit_bf4_0(unsigned s,
         complex double * restrict out)
{
  complex double a = out[0];
  complex double b = out[s];
  complex double c = out[s * 2];
  complex double d = out[s * 3];

  double rsu = creal(c) + creal(d);
  double rsb = creal(c) - creal(d);
  double isu = cimag(c) + cimag(d);
  double isb = cimag(c) - cimag(d);

  out[0]     = CMPLX(creal(a) + rsu, cimag(a) + isu);
  out[s]     = CMPLX(creal(b) + isb, cimag(b) - rsb);
  out[s * 2] = CMPLX(creal(a) - rsu, cimag(a) - isu);
  out[s * 3] = CMPLX(creal(b) - isb, cimag(b) + rsb);
}

#endif
