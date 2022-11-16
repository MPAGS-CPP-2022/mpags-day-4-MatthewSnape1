#include "PlayfairCipher.hpp"

#include <iostream>
#include <string>
#include <algorithm>
#include <map>

PlayfairCipher::PlayfairCipher(const std::string& key){

    setkey(key);

}

void PlayfairCipher::setkey(const std::string& key) {

    // store the original key
    key_ = key;

    std::cout<< key_ << std::endl;

    key_ += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    std::transform(key_.begin(), key_.end(), key_.begin(), ::toupper );

    //remove non alphanumeric characters

    auto rem_iter = std::remove_if(key_.begin(), key_.end(), 
    
        [] (char c) { return !std::isalpha(c);});

    key_.erase(rem_iter,key_.end());

    // Change J -> I (not working)

    std::transform(key_.begin(),key_.end(), key_.begin(), 
        [] (char c) 
        {
            if (c == 'J') return 'I';
            return c;
        
        }
        
    );

    std::string dup_char = {""};

    //Remove duplicated letters (not working?)

    auto dup_det = [&] (char c){
        if (dup_char.find(c) == std::string::npos)
        {
                dup_char += c;
                return false;
        } 
        else 
        {
                return true;
        }

    };
    
    auto rem_iter2 = std::remove_if(key_.begin(),key_.end(), dup_det);
    key_.erase(rem_iter2, key_.end());

    std::cout << key_ << std::endl;

    using str2cord_map = std::map<std::string,std::pair<int,int>>;

    using cord2str_map = std::map<std::pair<int,int>,std::string>;

    str2cord_map map1;

    cord2str_map map2;

    int x = 1;

    int y = 1;

    for (size_t i = 0; i < key_.length();i++)
    {
        std::pair<int, int > cord{y,x};

        std::pair<std::string,std::pair<int,int>> p0{std::string{key_[i]},cord};

        std::pair<std::pair<int,int>,std::string> p1{cord,std::string{key_[i]}};

        map1.insert( p0 );

        map2.insert( p1 );

        x++;

        switch (x){
            case 6:
                x = 1;
                y++;
        }


    }

    //Store the coords of each letter

    // Store the playfair cihper key map

}

std::string PlayfairCipher::applycipher(const std::string& inputText,
                        const CipherMode /*cipherMode*/) const{

    // Change J → I

    // If repeated chars in a digraph add an X or Q if XX

    // if the size of input is odd, add a trailing Z

    // Loop over the input in Digraphs

    // - Find the coords in the grid for each digraph
    // - Apply the rules to these coords to get 'new' coords
    // - Find the letter associated with the new coords
    return inputText;

}
