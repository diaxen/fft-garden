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


#define MIN_COUNT 4
#define MAX_COUNT 4096

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "fft.h"

void print_cpx(complex double t)
{
  printf("(%lf, %lf)", creal(t), cimag(t));
}

void print_cpx_array(complex double *t, unsigned count)
{
  for (unsigned i = 0; i < count; i++)
    print_cpx(t[i]);
  printf("\n");
}

/* simple FFT used as reference implementation */
static void simple_dft(unsigned size, complex double *output,
		       const complex double *input,
		       unsigned stride /* = 1*/)
{
  unsigned half = size >> 1;

  if (!half)
    {
      output[0] = input[0];
    }
  else
    {
      simple_dft(half, output       , input         , stride << 1);
      simple_dft(half, output + half, input + stride, stride << 1);

      for (unsigned i = 0; i < half; i++)
	{
	  complex double a = output[i];
	  complex double b = output[i + half];

	  double angle = 2 * M_PI * i / size;
	  complex double tw = conj(cexp(angle * I));
	  complex double c = b * tw;

	  output[i] = a + c;
	  output[i + half] = a - c;
	}
    }
}

int main()
{
  for (int count = MIN_COUNT; count <= MAX_COUNT; count *= 2)
    {
      complex double s[count];	/* input */
      complex double t[count];	/* tested implementation output */
      complex double r[count];	/* reference output */

      /* random input */
      for (unsigned i = 0; i < count; i++)
	s[i] = (drand48() - .5) + I * (drand48() - .5);

      /* run fft under test */
      fft_init(count);

      /* run reference fft */
      simple_dft(count, r, s, 1);

#ifdef INPLACE
      fft(count, s);
      memcpy(t, s, sizeof(s));
#else
      fft(count, t, s);
#endif

      fft_cleanup();

      /* compare outputs */
      for (unsigned i = 0; i < count; i++)
	if (cabs(t[i] - r[i]) > 0.0001)
	  {
	    printf("LEN: %u\n", count);
	    printf("INPUT: ");
	    print_cpx_array(s, count);
	    printf("FFT: ");
	    print_cpx_array(t, count);
	    printf("REF: ");
	    print_cpx_array(r, count);
	    abort();
	  }

      printf("Ok %u\n", count);
    }
}
