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

/* This file provides various bit reversal loops used by
   some FFT algorithms */

#ifndef _BIT_REVERSE_H_
#define _BIT_REVERSE_H_

#define BIT_REVERSE_SWAP_LOOP(i, j, N, ...)		\
do {							\
  unsigned _N = (N);					\
  for (unsigned _i = 0, _j = 0; _i < _N - 1; _i++)	\
    {							\
      if (_i < _j)					\
	{						\
	  unsigned i = _j, j = _i;			\
	  __VA_ARGS__;					\
	}						\
      unsigned _k;					\
      for (_k = _N / 2; _k <= _j; _k /= 2)		\
        _j = _j - _k;					\
      _j = _j + _k;					\
    }							\
} while (0)

/*

  In order to increment a bit-reversed counter in software, I devised
  the following approach that I was not able to find described
  elsewhere:

  When a counter is incremented, the least significant bit clear is
  toggled as well as all one bits on the right. This means that being
  able to toggle a group of trailing bits in an integer is enough to
  implement a counter. The number of trailing bits to toggle on each
  step is given by the binary carry sequence. By applying this to the
  leading bits instead, we directly obtain a bit-reversed counter.

  mask = N - 1;
  for (i = r = 0; i < N; i++) {
    r ^= (~mask >> (32 - clz32(i ^ (i + 1)))) & mask;
    print(i, r);
  }

*/

/*
  BIT_REVERSE_LOOP(i, j, 4, ... )

    (0, 0) (1, 2) (2, 1) (3, 3)

  BIT_REVERSE_LOOP(i, j, 8, ... )

    (0, 0) (1, 4) (2, 2) (3, 6)
    (4, 1) (5, 5) (6, 3) (7, 7)

  BIT_REVERSE_LOOP(i, j, 16, ... )

    (0, 0) (1, 8) (2, 4) (3, 12)
    (4, 2) (5, 10) (6, 6) (7, 14)
    (8, 1) (9, 9) (10, 5) (11, 13)
    (12, 3) (13, 11) (14, 7) (15, 15)
*/

#define BIT_REVERSE_LOOP(i, j, N, ...)			\
do {							\
  unsigned _N = (N);					\
  unsigned _m = _N - 1;					\
  for (unsigned j = 0, i = 0; i < _N; )			\
    {							\
      __VA_ARGS__;					\
      /* increment a bit reversed counter */		\
      unsigned _k = i + 1;				\
      j ^= (~_m >> (32 - __builtin_clz(i ^ _k))) & _m;	\
      i = _k;						\
    }							\
} while (0)

/*
  BIT_REVERSE2_LOOP(i, j, 4, ... )

    (0, 0) (2, 1)

  BIT_REVERSE2_LOOP(i, j, 8, ... )

    (0, 0) (2, 2) (4, 1) (6, 3)

  BIT_REVERSE2_LOOP(i, j, 16, ... )

    (0, 0) (2, 4) (4, 2) (6, 6)
    (8, 1) (10, 5) (12, 3) (14, 7)
*/

#define BIT_REVERSE2_LOOP(i, j, N, ...)			\
do {							\
  unsigned _N = (N);					\
  unsigned _m = _N / 2 - 1;				\
  for (unsigned j = 0, i = 0; i < _N; )			\
    {							\
      __VA_ARGS__;					\
      /* increment a bit reversed counter */		\
      unsigned _k = i + 2;				\
      j ^= (~_m >> (31 - __builtin_clz(i ^ _k))) & _m;	\
      i = _k;						\
    }							\
} while (0)

/*
  BIT_REVERSE4_LOOP(i, j, 16, ... )

    (0, 0) (4, 2) (8, 1) (12, 3)

  BIT_REVERSE4_LOOP(i, j, 32, ... )

    (0, 0) (4, 4) (8, 2) (12, 6)
    (16, 1) (20, 5) (24, 3) (28, 7)
*/

#define BIT_REVERSE4_LOOP(i, j, N, ...)			\
do {							\
  unsigned _N = (N);					\
  unsigned _m = _N / 4 - 1;				\
  for (unsigned j = 0, i = 0; i < _N; )			\
    {							\
      __VA_ARGS__;					\
      /* increment a bit reversed counter */		\
      unsigned _k = i + 4;				\
      j ^= (~_m >> (30 - __builtin_clz(i ^ _k))) & _m;	\
      i = _k;						\
    }							\
} while (0)

/*
  BIT_REVERSE42_LOOP(i, j, 16, ... )

    (0, 0) (4, 1) (8, 2) (12, 3)

  BIT_REVERSE42_LOOP(i, j, 32, ... )

    (0, 0) (4, 8) (8, 1) (12, 9)
    (16, 2) (20, 10) (24, 3) (28, 11)
*/

#define BIT_REVERSE42_LOOP(i, j, N, ...)		\
  BIT_REVERSE4_LOOP(i, _r, N, {				\
      /* undo bit reversal inside pairs */		\
      unsigned j = (_r & 0x55555555) << 1 |		\
		   (_r & 0xaaaaaaaa) >> 1;		\
    __VA_ARGS__;					\
  })

#endif
