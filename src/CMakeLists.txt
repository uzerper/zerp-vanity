find_package(OpenSSL REQUIRED)

include_directories(${OPENSSL_INCLUDE_DIR})

add_library(zerp-vanity impl/base58.cpp impl/bignum.cpp impl/bin.cpp impl/rand.cpp impl/sha256.cpp
  impl/sha512.cpp)

add_subdirectory(impl)