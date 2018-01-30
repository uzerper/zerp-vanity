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

#include "../sha512.hpp"
#include "../ec.hpp"

#include <iostream>

namespace uzerper {

bignum_const get_private_generator(uint8_t const *entropy) {
  
  sha512_ctx_const ctx{create_sha512_ctx()->add(entropy, 16)};
  
  bignum_const secp256k1_order{secp256k1()->get_order()};
  
  uint32_t i{0};
  
  bignum_const candidate;
  
  while (true) {
    
    candidate = ctx->add(i)->finalize()->slice(0,32)->to_bignum();
    
    if (!candidate->is_zero() 
      && *candidate < *secp256k1_order) break;
    
    i++;
    
  }
  
  return candidate;
  
}

}