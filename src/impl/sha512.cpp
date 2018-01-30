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
#include <cstring>
#include <openssl/sha.h>
#include "bin_impl.hpp"
#include "../sha512.hpp"

namespace uzerper {
 
bin_const sha512(uint8_t const *data, size_t size) {
  
  bin_impl_ptr rv{std::make_shared<bin_impl>(SHA512_DIGEST_LENGTH)};
  
  SHA512(data, size, rv->data.data());
  
  return std::move(rv);
  
}

sha512_ctx_iface::~sha512_ctx_iface() = default;

class sha512_ctx_impl;

using sha512_ctx_impl_ptr = std::shared_ptr<sha512_ctx_impl>;

class sha512_ctx_impl: public sha512_ctx_iface {
  
public:
  
  ~sha512_ctx_impl() {
    memset(&ctx, 0, sizeof(ctx));
  }
  
  sha512_ctx_const add(uint8_t const *data, size_t size) const override {
    
    sha512_ctx_impl_ptr rv{std::make_shared<sha512_ctx_impl>()};
    
    SHA512_CTX *rv_ctx(&rv->ctx);
    
    memcpy(rv_ctx, &ctx, sizeof(ctx));
    
    if (SHA512_Update(rv_ctx, data, size) != 1) {
      throw std::runtime_error("Error updating SHA-512 context");
    }
    
    return rv;
  }
  
  sha512_ctx_const add(uint32_t data) const override {
    
    uint8_t buf[4] = {
      static_cast<uint8_t>((data >> 24) & 0xFF),
      static_cast<uint8_t>((data >> 16) & 0xFF),
      static_cast<uint8_t>((data >> 8) & 0xFF),
      static_cast<uint8_t>(data & 0xFF),
    };
    
    return add(buf, 4);
    
  }
  
  bin_const finalize() const override {
    
    bin_impl_ptr rv{std::make_shared<bin_impl>(SHA512_DIGEST_LENGTH)};
    
    SHA512_CTX final_ctx;
    
    memcpy(&final_ctx, &ctx, sizeof(ctx));
    
    if (SHA512_Final(rv->data.data(), &final_ctx) != 1) {
      throw std::runtime_error(std::string("Error finalizing SHA-512 context"));
    }
    
    return rv;
  }
  
  SHA512_CTX ctx;
  
};

sha512_ctx_const create_sha512_ctx() {
  
  sha512_ctx_impl_ptr rv{std::make_shared<sha512_ctx_impl>()};
  
  if (SHA512_Init(&rv->ctx) != 1) {
    throw std::runtime_error("Error initializing SHA-512 context");
  }
  
  return rv;
  
}
  
}