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
#include <openssl/ec.h>
#include <openssl/obj_mac.h>
#include "../ec.hpp"
#include "bignum_impl.hpp"

namespace uzerper {
 
ec_curve_iface::~ec_curve_iface() = default;
  
class ec_curve_impl;

using ec_curve_impl_ptr = std::shared_ptr<ec_curve_impl>;

class ec_curve_impl: public ec_curve_iface {
  
public:
  
  ec_curve_impl()
  : group(nullptr) {}
  
  ec_curve_impl(EC_GROUP *group)
  : group(group) {}
  
  ~ec_curve_impl() {
    if (group) {
      EC_GROUP_clear_free(group);
    }
  }
  
  bignum_const get_order() const override {
    
    bignum_impl_ptr rv{std::make_shared<bignum_impl>(BN_new())};
    
    if (!rv->bn) {
      throw std::runtime_error("Error creating bignum");
    }
    
    bignum_ctx ctx;
    
    if (EC_GROUP_get_order(group, rv->bn, ctx()) != 1) {
      throw std::runtime_error("Error getting elliptic curve order");
    }
    
    return rv;
  }
  
  EC_GROUP *group;
  
};

ec_curve_const secp256k1() {
 
  ec_curve_impl_ptr rv{std::make_shared<ec_curve_impl>(
    EC_GROUP_new_by_curve_name(NID_secp256k1)
  )};
  
  if (!rv->group) {
    throw std::runtime_error("Error creating elliptic curve group");
  }
  
  return rv;
}
  
}