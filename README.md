# zerp-vanity

## Overview

This is a project for understanding and experimenting with Ripple addresses. The goal is to "roll my own" to a fairly large degree, and to generate Ripple vanity addresses.

## Background

Ripple addresses are generated deterministically from a random seed. The seed is an array of 16 bytes, and should be generated with a cryptographically secure random number generator.

When you use `generateAddress` in `ripple-lib`, or `wallet-propose` in `rippled`, the "secret" in the returned wallet is the random seed. It is encoded with [Base58Check](https://en.wikipedia.org/wiki/Base58) using Ripple's Base58 alphabet, with the prefix 33. I.e. to encode a seed, compute

`33 || seed || SHA256( SHA256( 33 || seed ) )`,

and convert it to Base58, using the alphabet `rpshnaf39wBUDNEGHJKLM4PQRST7VWXYZ2bcdeCg65jkm8oFqi1tuvAxyz`.

To generate an address, you start by computing the private generator. Private generator candidates are

`SHA512( seed || i )[0..15], i = 0,1,...`,

i.e. the first 16 bytes of the SHA-512 digest resulting from the seed concatenated with i (which is a big endian unsigned 32 bit integer). The private generator is the non-zero candidate with the lowest i that is less than the secp256k1 order.

## Progress

Currently, I am experimenting with an idea I have of very opaque, memory and thread safe C++ interfaces, applied on the proven but not very safe OpenSLL crypto API.

### Working

* Random number generator
* SHA256 / SHA512
* secp256k1 order
* Bignum comparison
* Ripple Base58Check

### Roadmap

* Address generation
 * Elliptic curve point multiplication
* Parallelization
* GPU acceleration?