#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

#include <string>
#include <map>
#include "CipherMode.hpp"

/**
 * \file PlayfairCipher.hpp
 * \brief Contains the declaration of the PlayfairCipher class
 */

/**
 * \class PlayfairCipher
 * \brief Encrypt or decrypt text using the Playfair cipher with the given key
 */

class PlayfairCipher{
    public: 
        /**
        * \brief Take a Phrase to use for the Playfair Cipher key
        *
        * \param key the phrase to use in the cipher
        */
        explicit PlayfairCipher(const std::string& key);

        /**
        * \brief Use the supplied phrase to set the key
        *
        * \param key the phrase to set the key
        * \return the key created from the phrase
        */
        void setkey(const std::string& key);

        /**
        * \brief Apply the cipher to the provided text
        *
        * \param inputText the text to encrypt or decrypt
        * \param cipherMode whether to encrypt or decrypt the input text
        * \return the result of applying the cipher to the input text
        */

        std::string applycipher (const std::string& inputText,
                        const CipherMode cipherMode) const ;

    private:
        //key_ stores the key map
        std::string key_{""};
        // defines a map to go from the letter to key map coordinate
        using map1 =  std::map<std::string,std::pair<int,int>>;
        map1 str2cord_map_;
        // defines a map to go from keymap coordinate to letter
        using map2 =  std::map<std::pair<int,int>,std::string>;
        map2 cord2str_map_;


};

#endif