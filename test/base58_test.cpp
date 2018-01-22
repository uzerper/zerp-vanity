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
#include <stdexcept>
#include "catch.hpp"
#include <base58.hpp>

TEST_CASE("Base58 1") {
  
  using namespace uzerper;
 
  uint8_t const bin[16] = {1, 150, 248, 42, 147, 130, 238, 49, 225, 174, 75, 100, 164, 193, 9, 15};
  
  std::string enc{base58_encode(bin, 16, base58_encoding::bitcoin)};
  
  REQUIRE(enc == "CPNeCdtwNEzAgfQYKQL3Q");
  
  auto t1{base58_decode(enc.data(), enc.size(), base58_encoding::bitcoin)};
  
  REQUIRE(memcmp(bin, t1.data(), 16) == 0);
}

TEST_CASE("Base58 2") {
  
  using namespace uzerper;
 
  uint8_t const bin[16] = {0, 0, 0, 83, 64, 210, 117, 237, 230, 172, 46, 68, 217, 36, 240, 200};
  
  std::string enc{base58_encode(bin, 16, base58_encoding::bitcoin)};
  
  REQUIRE(enc == "1117wC6ZfPgYpu3yVk9pB");
  
  auto t1{base58_decode(enc.data(), enc.size(), base58_encoding::bitcoin)};
  
  REQUIRE(memcmp(bin, t1.data(), 16) == 0);
}

TEST_CASE("Invalid base58") {
  
  using namespace uzerper;
 
  try {
    auto t1{base58_decode("1234567890", 10, base58_encoding::bitcoin)};
    
    REQUIRE(false);
  }
  catch (std::runtime_error &e) {
    REQUIRE(e.what() == std::string("invalid base 58 character '0'"));
  }
  
}