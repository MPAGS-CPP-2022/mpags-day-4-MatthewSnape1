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

    //using str2cord_map = std::map<std::string,std::pair<int,int>>;

    //using cord2str_map = std::map<std::pair<int,int>,std::string>;

    //str2cord_map map1;

    //cord2str_map map2;

    size_t x = 1;

    size_t y = 1;

    for (size_t i = 0; i < key_.length();i++)
    {
        std::pair<int, int > cord{y,x};

        std::pair<std::string,std::pair<int,int>> p0{std::string{key_[i]},cord};

        std::pair<std::pair<int,int>,std::string> p1{cord,std::string{key_[i]}};

        std::cout << p0.first << " " << p0.second.first << ":" << p0.second.second << std::endl; 

        str2cord_map_.insert( p0 );

        cord2str_map_.insert( p1 );

        x++;

        switch (x){
            case 6:
                x = 1;
                y++;
        }


    }

}

std::string PlayfairCipher::applycipher(const std::string& inputText,
                        const CipherMode /*cipherMode*/) const{

    std::string outText{""};

    std::string digraph{""};

    outText += inputText[0];

    for (size_t i=1;i<inputText.length();i++)
    {
        if (inputText[i] != inputText[i-1])
        {
            outText += inputText[i];
        }
        else if (inputText[i] != 'X')
        {
            outText += "X";
            outText += inputText[i];
        }
        else
        {
            outText += "Q";
            outText += inputText[i];
        }
    }
        // if the size of input is odd, add a trailing Z
    if (outText.length()%2 == 1)
    {
        outText += "Z";
    }

    // Create digraphs

    std::pair<int,int> newcord1{0,0};
    std::pair<int,int> newcord2{0,0};
    //finding new coordinates
    for (size_t i = 0;i<outText.length();i+=2)
    {
        std::cout << "Looking at " << outText[i] << outText[i+1] << std::endl;
        auto it1 = str2cord_map_.find(std::string{outText[i]});
        std::cout << "found " << std::string{outText[i]} << " at " << (*it1).second.first << ":" << (*it1).second.second << std::endl;
        auto it2 = str2cord_map_.find(std::string{outText[i+1]});
        std::cout << "found " << std::string{outText[i+1]} << " at " << (*it2).second.first << ":" << (*it2).second.second << std::endl;
        
        if ((*it1).second.first == (*it2).second.first){
            newcord1.first = (*it1).second.first;
            newcord1.second = ((*it1).second.second%5)+1;
            std::cout << "new cord for " << outText[i] << " is " << newcord1.first << ":" << newcord1.second << std::endl;
            newcord2.first = (*it2).second.first;
            newcord2.second = ((*it2).second.second%5)+1;
            std::cout << "new cord for " << outText[i+1] << " is " << newcord2.first << ":" << newcord2.second << std::endl;

        }else if ((*it1).second.second == (*it2).second.second){
            newcord1.first = ((*it1).second.first%5)+1;
            newcord1.second = (*it1).second.second;
            std::cout << "new cord for " << outText[i] << " is " << newcord1.first << ":" << newcord1.second << std::endl;
            newcord2.first = ((*it2).second.first%5)+1;
            newcord2.second = (*it2).second.second;
            std::cout << "new cord for " << outText[i+1] << " is " << newcord2.first << ":" << newcord2.second << std::endl;
        }else{
            newcord1.first = (*it1).second.first;
            newcord1.second = (*it2).second.second; 
            newcord2.first = (*it2).second.first;
            newcord2.second = (*it1).second.second;          
        }
        auto find1 = cord2str_map_.find(newcord1);
        digraph += (*find1).second;
        auto find2 = cord2str_map_.find(newcord2);
        digraph += (*find2).second;
    } 

    // Loop over the input in Digraphs

    // - Find the coords in the grid for each digraph
    // - Apply the rules to these coords to get 'new' coords
    // - Find the letter associated with the new coords

    return digraph;

}
