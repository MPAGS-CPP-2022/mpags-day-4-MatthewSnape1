#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

#include <string>
#include "CipherMode.hpp"

class PlayfairCipher{
    public: 
        explicit PlayfairCipher(const std::string& key);

        void setkey(const std::string& key);

        std::string applycipher (const std::string& inputText,
                        const CipherMode cipherMode) const ;

    private:
        std::string key_{""};


};

#endif