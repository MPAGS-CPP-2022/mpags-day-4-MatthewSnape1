//! Unit Tests for MPAGSCipher PlayfairCipher Class
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "PlayfairCipher.hpp"

//Test if applycipher will move letters right correctly and wrap-around in encryption
TEST_CASE("Playfair Cipher move right test + wrap-around for encryption", "[playfair]")
{
    PlayfairCipher cc{"testkey"};
    REQUIRE(cc.applycipher("KY", CipherMode::Encrypt) == "YT");
}

//Test if applycipher will move letters left correctly and wrap-around in decryption
TEST_CASE("Playfair Cipher move left + wrap-around test for decryption", "[playfair]")
{
    PlayfairCipher cc{"testkey"};
    REQUIRE(cc.applycipher("YT", CipherMode::Decrypt) == "KY");
}

//Test if applycipher will move letters down correctly and wrap-around in encryption
TEST_CASE("Playfair Cipher move down + wrap-around test for decryption", "[playfair]")
{
    PlayfairCipher cc{"testkey"};
    REQUIRE(cc.applycipher("PW", CipherMode::Encrypt) == "WS");
}

//Test if applycipher will move letters up correctly and wrap-around in decryption
TEST_CASE("Playfair Cipher move up + wrap-around test for decryption", "[playfair]")
{
    PlayfairCipher cc{"testkey"};
    REQUIRE(cc.applycipher("WS", CipherMode::Decrypt) == "PW");
}

//Test if applycipher will exchange corners of rectange correctly in encryption
TEST_CASE("Playfair Cipher exchange corner test for encryption", "[playfair]")
{
    PlayfairCipher cc{"testkey"};
    REQUIRE(cc.applycipher("TZ", CipherMode::Encrypt) == "YU");
}

//Test if applycipher will exchange corners of rectange correctly in decryption
TEST_CASE("Playfair Cipher exchange corner test for decryption", "[playfair]")
{
    PlayfairCipher cc{"testkey"};
    REQUIRE(cc.applycipher("YU", CipherMode::Decrypt) == "TZ");
}

//Test if applycipher will add X between repeated letters in encryption
TEST_CASE("Playfair Cipher add X betwwen repeat letters", "[playfair]")
{
    PlayfairCipher cc{"testkey"};
    REQUIRE(cc.applycipher("TT", CipherMode::Encrypt) == "KUYU");
}

//Test if applycipher will add Q between repeated Xs in encryption
TEST_CASE("Playfair Cipher add Q betwwen repeated Xs", "[playfair]")
{
    PlayfairCipher cc{"testkey"};
    REQUIRE(cc.applycipher("XX", CipherMode::Encrypt) == "KXZU");
}
