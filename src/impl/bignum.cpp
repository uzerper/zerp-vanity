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

#include <stdexcept>
#include "bignum_impl.hpp"
#include "bin_impl.hpp"

namespace uzerper {
 
bignum_iface::~bignum_iface() = default;

bignum_impl::bignum_impl()
  : bn(nullptr) {}
  
bignum_impl::bignum_impl(BIGNUM *bn)
  : bn(bn) {}

bignum_impl::~bignum_impl() {
  if (bn) {
    BN_clear(bn);
    BN_free(bn);
  }
}

bin_const bignum_impl::to_bin() const {
  
  int const N{BN_num_bytes(bn)};
  
  bin_impl_ptr rv{std::make_shared<bin_impl>(N)};
  
  if (BN_bn2bin(bn, rv->data.data()) != N) {
    throw std::runtime_error("Error converting bignum to binary");
  }
  
  return rv;
  
}

int bignum_impl::compare(bignum_iface const &rhs) const {
  
  bignum_impl const &rhs_impl{static_cast<bignum_impl const &>(rhs)};
  
  return BN_cmp(bn, rhs_impl.bn);
  
}

bignum_const create_bignum(uint8_t const *data, size_t size) {
  
  bignum_impl_ptr rv{std::make_shared<bignum_impl>(
    BN_bin2bn(data, size, NULL)
  )};
  
  if (!rv->bn) {
    throw std::runtime_error("Error creating bignum from buffer");
  }
  
  return rv;
}

bignum_ctx::bignum_ctx() {
  
  ctx = BN_CTX_new();
  
  if (!ctx) {
    throw std::runtime_error("Error creating bignum context");
  }
}
  
bignum_ctx::~bignum_ctx() {
  
  BN_CTX_free(ctx);
  
}
  
BN_CTX *bignum_ctx::operator()() {
  return ctx;
}
  
}