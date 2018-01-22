//------------------------------------------------------------------------------
/*
    Copyright 2018 uzerper (zona.eloon@gmail.com)

    Permission to use, copy, modify, and/or distribute this software for any
    purpose with or without fee is hereby granted, provided that the above 
    copyright notice and this permission notice appear in all copies.

    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES 
    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF 
    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR 
    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES 
    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN 
    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF 
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#include <cstring>
#include "../base58.hpp"

namespace uzerper {

using alphabet = struct {
  uint8_t const length;
  char const *letters;
};

static const alphabet bitcoin_alphabet{  
  58,
  "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz"
};

static const alphabet ripple_alphabet{  
  58,
  "rpshnaf39wBUDNEGHJKLM4PQRST7VWXYZ2bcdeCg65jkm8oFqi1tuvAxyz"
};

static std::string encode_base_x(uint8_t const *b256, std::size_t b256_length, alphabet const &a, uint8_t *bx) {
  
  uint8_t const base{a.length};
  // count number of leading zeros
  std::size_t n_leading_zeros{0};
  while ( (n_leading_zeros < b256_length) && (b256[n_leading_zeros] == 0) ) { 
    n_leading_zeros++;
  }
  
  std::size_t i{n_leading_zeros};    

  uint32_t carry{0};
  std::size_t bx_length{0};
  
  while (i < b256_length) {
    
    std::size_t j{0};
    carry = b256[i];
    
    while (!((carry == 0) && (j == bx_length))) {
      if (j == bx_length) {
	bx[j] = 0;
	bx_length++;
      }
      else {
	carry += bx[j] * 256;
      }
      
      bx[j] = carry % base;
      carry /= base;	
      
      j++;
    }
    
    i++;
    
  }
  
  std::string rv;
  rv.resize(n_leading_zeros + bx_length);
  
  for (i = 0; i < n_leading_zeros; i++) {
    rv[i] = a.letters[0];
  }
  
  for (uint8_t *it{bx + bx_length - 1}; it >= bx; it--, i++) {
    rv[i] += a.letters[*it];
  }
  
  return std::move(rv);
  
}

static std::vector<uint8_t> decode_base_x(char const *bx, std::size_t bx_length, alphabet const &a, uint8_t *b256) {
  
  uint8_t const base{a.length};
  // count number of leading zeros
  std::size_t n_leading_zeros{0};
  while ( (n_leading_zeros < bx_length) && (bx[n_leading_zeros] == a.letters[0]) ) { 
    n_leading_zeros++;
  }
  
  std::size_t i{n_leading_zeros};    

  uint32_t carry{0};
  std::size_t b256_length{0};
  
  while (i < bx_length) {
    
    std::size_t j{0};
    carry = strchr(a.letters, bx[i]) - a.letters;
    
    while (!((carry == 0) && (j == b256_length))) {
      if (j == b256_length) {
	b256[j] = 0;
	b256_length++;
      }
      else {
	carry += b256[j] * base;
      }
      
      b256[j] = carry % 256;
      carry /= 256;	
      
      j++;
    }
    
    i++;
    
  }
  
  std::vector<uint8_t> rv(n_leading_zeros + b256_length);

  for (i = 0; i < n_leading_zeros; i++) {
    rv[i] = 0;
  }
  
  for (uint8_t *it{b256 + b256_length - 1}; it >= b256; it--, i++) {
    rv[i] += *it;
  }
    
  return std::move(rv);
  
}

static alphabet const &select_alphabet(base58_encoding encoding) {
  switch (encoding) {
    case base58_encoding::bitcoin:
      return bitcoin_alphabet;
    case base58_encoding::ripple:
    default:
      return ripple_alphabet;
  };
}

std::string base58_encode(uint8_t const *b256, std::size_t b256_length, base58_encoding encoding) {
  
  std::size_t const b58_length{(b256_length * 137)/100 + 1}; // log(256)/log(58) rounded up
  std::vector<uint8_t> b58(b58_length);
  
  return std::move(encode_base_x(b256, b256_length, select_alphabet(encoding), b58.data()));
  
}

std::vector<uint8_t> base58_decode(char const *b58, std::size_t b58_length, base58_encoding encoding) {
  
  std::size_t const b256_length{(b58_length * 733)/1000 + 1}; // log(58)/log(256) rounded up
  std::vector<uint8_t> b256(b256_length);
  
  return std::move(decode_base_x(b58, b58_length, select_alphabet(encoding), b256.data()));
}

}