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

#pragma once

#include <openssl/bn.h>
#include "../bignum.hpp"

namespace uzerper {
  
class bignum_impl;

using bignum_impl_ptr = std::shared_ptr<bignum_impl>;
  
class bignum_impl: public bignum_iface {
  
public:
  
  bignum_impl();
  
  bignum_impl(BIGNUM *bn);
  
  ~bignum_impl();
  
  bin_const to_bin() const override;
  
  BIGNUM *bn;
  
};

class bignum_ctx {
  
public:
  
  bignum_ctx();
  
  ~bignum_ctx();
  
  BN_CTX *operator()();
  
private:
  
  BN_CTX *ctx;
};
  
}