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

#include "forward_decl.hpp"
#include "bin.hpp"

namespace uzerper {
  
class bignum_iface {
  
public:
  
  virtual ~bignum_iface();
  
  virtual bin_const to_bin() const = 0;
  
  virtual int compare(bignum_iface const &rhs) const = 0;
  
  virtual bool is_zero() const = 0;
  
};

bignum_const create_bignum(uint8_t const *data, size_t size);

bool operator<(bignum_iface const &lhs, bignum_iface const &rhs);
bool operator<=(bignum_iface const &lhs, bignum_iface const &rhs);
bool operator==(bignum_iface const &lhs, bignum_iface const &rhs);
bool operator!=(bignum_iface const &lhs, bignum_iface const &rhs);
bool operator>(bignum_iface const &lhs, bignum_iface const &rhs);
bool operator>=(bignum_iface const &lhs, bignum_iface const &rhs);


}