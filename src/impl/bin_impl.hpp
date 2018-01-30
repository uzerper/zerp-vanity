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

#include <vector>
#include "../bin.hpp"

namespace uzerper {
  
class bin_impl;

using bin_impl_ptr = std::shared_ptr<bin_impl>;
 
class bin_impl: public bin_iface {

public:
  
  bin_impl(size_t n);
  
  ~bin_impl();
  
  uint8_t const *begin() const override;
    
  size_t size() const override;
  
  std::string to_hex() const override;
  
  bignum_const to_bignum() const override;
  
  bin_const slice(size_t start, size_t end) const override;
  
  std::vector<uint8_t> data;
  
};
  
}