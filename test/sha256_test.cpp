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

#include "catch.hpp"
#include <sha256.hpp>

static std::size_t const SHA_INPUT_1_LEN{112};
static uint8_t const sha_input_1[SHA_INPUT_1_LEN + 1] = 
  "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";

TEST_CASE("One shot SHA-256 1") {
  
  using namespace uzerper;
 
  std::string s{sha256(sha_input_1, SHA_INPUT_1_LEN)->to_hex()};
  
  REQUIRE(s == "cf5b16a778af8380036ce59e7b0492370b249b11e8f07a51afac45037afee9d1");
}

TEST_CASE("add/finalize SHA-256 1") {
  
  using namespace uzerper;
  
  sha256_ctx_const ctx{create_sha256_ctx()};
  
  std::string s{ctx->add(sha_input_1, 42)->add(sha_input_1 + 42, SHA_INPUT_1_LEN - 42)->finalize()->to_hex()};
  
  REQUIRE(s == "cf5b16a778af8380036ce59e7b0492370b249b11e8f07a51afac45037afee9d1");
}
