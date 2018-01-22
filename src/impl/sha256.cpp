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
#include "../sha256.hpp"

namespace uzerper {
 
bin_const sha256(uint8_t const *data, size_t size) {
  
  bin_impl_ptr rv{std::make_shared<bin_impl>(SHA256_DIGEST_LENGTH)};
  
  SHA256(data, size, rv->data.data());
  
  return std::move(rv);
  
}

sha256_ctx_iface::~sha256_ctx_iface() = default;

class sha256_ctx_impl;

using sha256_ctx_impl_ptr = std::shared_ptr<sha256_ctx_impl>;

class sha256_ctx_impl: public sha256_ctx_iface {
  
public:
  
  ~sha256_ctx_impl() {
    memset(&ctx, 0, sizeof(ctx));
  }
  
  sha256_ctx_const add(uint8_t const *data, size_t size) const override {
    
    sha256_ctx_impl_ptr rv{std::make_shared<sha256_ctx_impl>()};
    
    SHA256_CTX *rv_ctx(&rv->ctx);
    
    memcpy(rv_ctx, &ctx, sizeof(ctx));
    
    if (SHA256_Update(rv_ctx, data, size) != 1) {
      throw std::runtime_error("Error updating SHA-256 context");
    }
    
    return rv;
  }
  
  bin_const finalize() const override {
    
    bin_impl_ptr rv{std::make_shared<bin_impl>(SHA256_DIGEST_LENGTH)};
    
    SHA256_CTX final_ctx;
    
    memcpy(&final_ctx, &ctx, sizeof(ctx));
    
    if (SHA256_Final(rv->data.data(), &final_ctx) != 1) {
      throw std::runtime_error(std::string("Error finalizing SHA-256 context"));
    }
    
    return rv;
  }
  
  SHA256_CTX ctx;
  
};

sha256_ctx_const create_sha256_ctx() {
  
  sha256_ctx_impl_ptr rv{std::make_shared<sha256_ctx_impl>()};
  
  if (SHA256_Init(&rv->ctx) != 1) {
    throw std::runtime_error("Error initializing SHA-256 context");
  }
  
  return rv;
  
}
  
}