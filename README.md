# FFT Garden

FFT Garden is a collection of Fast Fourier Transform algorithms
implemented in the C programming language.

The project aims to provide easy to read and easy to study code for
various FFT algorithms. Most of the proposed algorithms are described
in the literature.

## Algorithms

There are many designs choice that can be made when designing an FFT
algorithm. When combined, this yield a very large number of variants.
The collection of 44 algorithms provided here cover a small portion of
the FFT design space. The source files naming reflect the implemented
algorithm variants as described below.

Let's consider three aspects of FFT algorithms:

 * The butterfly design:
   * Cooley-Tukey Radix-2 FFT `[ct]`
   * Mixed Radix 2/4 FFT `[mr]`
   * Split-Radix FFT `[sr]`
   * Conjugate Pair FFT `[cp]`

 * The decimation:
   * Decimation In Time `[dit]`
   * Decimation In Frequency `[dif]`

 * The traversal and algorithm structure:
   * Breadth-First Iterative `[bi]`
   * Depth-First Recursive `[dr]`
   * Depth-First Iterative `[di]`

More variants can be devised by considering the following
additional properties:

 * Butterflies using the same twiddles can be grouped by stage `[G]`.
 * Butterflies using the same twiddles can be grouped by block `[S]`.
 * Input reordering and/or butterfly scheduling may rely on lookup tables `[L]`.
 * Butterfly functions may be simplified for some twiddle factor values `[P]`.
 * The size of the twiddle table may be reduced to N/8 entries `[F]`.
 * Some algorithms can be made to work in-place `[N]`.

## Contributing

Many more algorithms could be added. In particular:

 * Only power of 2 size algorithms are proposed.
 * Most proposed algorithms use decimation in time.
 * Most proposed algorithms are out-of-place.
 * Other butterfly designs could be included.

Pull requests are welcome.

## License

The project source code is licensed under the CC0 creative commons license.

## Author

* **Alexandre Becoulet** - Initial work as part of the paper *A Depth-First Iterative Algorithm for the Conjugate Pair Fast Fourier Transform*
