find_package(OpenSSL REQUIRED)

include_directories(${OPENSSL_INCLUDE_DIR} "..\\src\\")

add_executable(zerp-vanity_test ripple_test.cpp sha512_test.cpp sha256_test.cpp rand_test.cpp zerp-vanity_test.cpp base58_test.cpp
  ec_test.cpp bn_test.cpp)

target_link_libraries(zerp-vanity_test zerp-vanity ${OPENSSL_CRYPTO_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

enable_testing()

add_test(all zerp-vanity_test)