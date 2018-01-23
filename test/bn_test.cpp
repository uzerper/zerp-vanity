//------------------------------------------------------------------------------
/*
    Copyright 2018 uzerper (zona.eloon@gmail.com)

    Permission to use, copy, modify, and/or distribute this software for any
    purpose with or without fee is hereby granted, provided that the above 
    copyright notice and this permission notice appear in all copies.

    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES 
    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF 
    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR 
    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES 0x02};
static uint8_t BN3[4] = {0xFF, 0x34, 0x21, 0x03};

    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN 
    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF 
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#include "catch.hpp"
#include <bignum.hpp>

static uint8_t BN1[4] = {0xFF, 0x34, 0x21, 0x01};
static uint8_t BN2[4] = {0xFF, 0x34, 0x21, 0x02};
static uint8_t BN3[4] = {0xFF, 0x34, 0x21, 0x03};

TEST_CASE("Bignum compare 1") {
  
  using namespace uzerper;
  
  bignum_const bn1{create_bignum(BN1, 4)};
  bignum_const bn2{create_bignum(BN2, 4)};
  bignum_const bn3{create_bignum(BN3, 4)};
  
  REQUIRE(bn1->to_bin()->to_hex() == "ff342101");
  REQUIRE(bn2->to_bin()->to_hex() == "ff342102");
  REQUIRE(bn3->to_bin()->to_hex() == "ff342103");
  
  // compare
  
  REQUIRE(bn1->compare(*bn1) == 0);
  REQUIRE(bn1->compare(*bn2) == -1);
  REQUIRE(bn1->compare(*bn3) == -1);
  
  REQUIRE(bn2->compare(*bn1) == 1);
  REQUIRE(bn2->compare(*bn2) == 0);
  REQUIRE(bn2->compare(*bn3) == -1);
  
  REQUIRE(bn3->compare(*bn1) == 1);
  REQUIRE(bn3->compare(*bn2) == 1);
  REQUIRE(bn3->compare(*bn3) == 0);
  
  // <
  
  REQUIRE(!(*bn1 < *bn1));
  REQUIRE(*bn1 < *bn2);
  REQUIRE(*bn1 < *bn3);

  REQUIRE(!(*bn2 < *bn1));
  REQUIRE(!(*bn2 < *bn2));
  REQUIRE(*bn2 < *bn3);
  
  REQUIRE(!(*bn3 < *bn1));
  REQUIRE(!(*bn3 < *bn2));
  REQUIRE(!(*bn3 < *bn3));
  
  // <=
  
  REQUIRE(*bn1 <= *bn1);
  REQUIRE(*bn1 <= *bn2);
  REQUIRE(*bn1 <= *bn3);

  REQUIRE(!(*bn2 <= *bn1));
  REQUIRE(*bn2 <= *bn2);
  REQUIRE(*bn2 <= *bn3);
  
  REQUIRE(!(*bn3 <= *bn1));
  REQUIRE(!(*bn3 <= *bn2));
  REQUIRE(*bn3 <= *bn3);
  
  // ==
  
  REQUIRE(*bn1 == *bn1);
  REQUIRE(!(*bn1 == *bn2));
  REQUIRE(!(*bn1 == *bn3));

  REQUIRE(!(*bn2 == *bn1));
  REQUIRE(*bn2 == *bn2);
  REQUIRE(!(*bn2 == *bn3));
  
  REQUIRE(!(*bn3 == *bn1));
  REQUIRE(!(*bn3 == *bn2));
  REQUIRE(*bn3 == *bn3);

  // !=
  
  REQUIRE(!(*bn1 != *bn1));
  REQUIRE(*bn1 != *bn2);
  REQUIRE(*bn1 != *bn3);

  REQUIRE(*bn2 != *bn1);
  REQUIRE(!(*bn2 != *bn2));
  REQUIRE(*bn2 != *bn3);
  
  REQUIRE(*bn3 != *bn1);
  REQUIRE(*bn3 != *bn2);
  REQUIRE(!(*bn3 != *bn3));

  // >
  
  REQUIRE(!(*bn1 > *bn1));
  REQUIRE(!(*bn1 > *bn2));
  REQUIRE(!(*bn1 > *bn3));

  REQUIRE(*bn2 > *bn1);
  REQUIRE(!(*bn2 > *bn2));
  REQUIRE(!(*bn2 > *bn3));
  
  REQUIRE(*bn3 > *bn1);
  REQUIRE(*bn3 > *bn2);
  REQUIRE(!(*bn3 > *bn3));

  // >=
  
  REQUIRE(*bn1 >= *bn1);
  REQUIRE(!(*bn1 >= *bn2));
  REQUIRE(!(*bn1 >= *bn3));

  REQUIRE(*bn2 >= *bn1);
  REQUIRE(*bn2 >= *bn2);
  REQUIRE(!(*bn2 >= *bn3));
  
  REQUIRE(*bn3 >= *bn1);
  REQUIRE(*bn3 >= *bn2);
  REQUIRE(*bn3 >= *bn3);

  
}