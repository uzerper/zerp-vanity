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

#include <memory>
#include "bin.hpp"

namespace uzerper {
 
bin_const sha256(uint8_t const *data, size_t size);

class sha256_ctx_iface;

using sha256_ctx = std::shared_ptr<sha256_ctx_iface>;

using sha256_ctx_const = std::shared_ptr<sha256_ctx_iface const>;

class sha256_ctx_iface {
  
public:
  
  virtual ~sha256_ctx_iface();
  
  virtual sha256_ctx_const add(uint8_t const *data, size_t size) const = 0;
  
  virtual bin_const finalize() const = 0;
  
};

sha256_ctx_const create_sha256_ctx();
  
}