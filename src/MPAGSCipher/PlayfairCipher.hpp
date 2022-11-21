#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

#include <string>
#include <map>
#include "CipherMode.hpp"

class PlayfairCipher{
    public: 
        explicit PlayfairCipher(const std::string& key);

        void setkey(const std::string& key);

        std::string applycipher (const std::string& inputText,
                        const CipherMode cipherMode) const ;

    private:
        std::string key_{""};

        using map1 =  std::map<std::string,std::pair<int,int>>;

        map1 str2cord_map_;

        using map2 =  std::map<std::pair<int,int>,std::string>;

        map2 cord2str_map_;


};

#endif