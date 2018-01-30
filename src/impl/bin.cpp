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
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include "bin_impl.hpp"
#include "bignum_impl.hpp"

namespace uzerper {
  
bin_iface::~bin_iface() = default;

bin_impl::~bin_impl() {
  memset(data.data(), 0, data.size());
}

bin_impl::bin_impl(size_t n)
  : data(n) {}

uint8_t const *bin_impl::begin() const {
  return data.data();
}
    
size_t bin_impl::size() const {
  return data.size();
}

std::string bin_impl::to_hex() const {

  std::stringstream ss;
  
  ss << std::setfill('0') << std::hex;
  
  for (uint8_t const d: data) {
    ss << std::setw(2) << (int)d;
  }
  
  std::string const s{ss.str()};
  
  return std::move(s);
    
}

bignum_const bin_impl::to_bignum() const {
  
  bignum_impl_ptr rv{std::make_shared<bignum_impl>(BN_bin2bn(data.data(), data.size(), nullptr))};
  
  if (!rv->bn) {
    throw std::runtime_error("Error creating bignum");
  }
  
  return rv;
}

bin_const bin_impl::slice(size_t start, size_t end) const {
  
  size_t const s(std::min(start, data.size()));
  size_t const e(std::min(end, data.size()));
  
  if (s >= e) return std::make_shared<bin_impl>(0);
  
  size_t const length{e - s};
  
  bin_impl_ptr rv{std::make_shared<bin_impl>(length)};
  
  memcpy(rv->data.data(), data.data() + s, length);
  
  return rv;
}
  
}
