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

    // Change J -> I 

    std::transform(key_.begin(),key_.end(), key_.begin(), 
        [] (char c) 
        {
            if (c == 'J') return 'I';
            return c;
        
        }
        
    );

    std::string dup_char = {""};

    //Remove duplicated letters

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
    //defines coordinated for keymap grid
    size_t x = 1;
    size_t y = 1;
    //runs through kay phrase and generates the two kep maps
    for (size_t i = 0; i < key_.length();i++)
    {
        std::pair<int, int> cord{y,x};
        //creates map items for each map and inserts them
        std::pair<std::string,std::pair<int,int>> p0{std::string{key_[i]},cord};
        std::pair<std::pair<int,int>,std::string> p1{cord,std::string{key_[i]}};
        str2cord_map_.insert( p0 );
        cord2str_map_.insert( p1 );

        x++;
        //if x becomes greater to 5, then reset to 1 
        switch (x){
            case 6:
                x = 1;
                y++;
        }


    }

}

std::string PlayfairCipher::applycipher(const std::string& inputText,const CipherMode cipherMode) const{

    std::string outText{""};

    std::string digraph{""};
    //Only do following if user wants to encrypt
    switch (cipherMode){
        case (CipherMode::Encrypt):
            //add first letter to outtext
            outText += inputText[0];

            for (size_t i=1;i<inputText.length();i++)
            {
                //if there is not a repeated leeter then add to outtext
                if (inputText[i] != inputText[i-1])
                {
                    outText += inputText[i];
                }
                //if letters are repeated and they are not x then insert an x in between
                else if (inputText[i] != 'X')
                {
                    outText += "X";
                    outText += inputText[i];
                }
                //otherwise insert a q between repeated letters
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
            break;
        //if user wants to decrypt then simply copy inputtext to outtext
        case (CipherMode::Decrypt):
            outText = inputText;
            break;
    }
    // Create digraphs

    std::cout << outText << std::endl;

    std::pair<int,int> newcord1{0,0};
    std::pair<int,int> newcord2{0,0};
    //finding new coordinates
    for (size_t i = 0;i<outText.length();i+=2)
    {
        //iterators for both letters of digraph
        auto it1 = str2cord_map_.find(std::string{outText[i]});
        auto it2 = str2cord_map_.find(std::string{outText[i+1]});
        //if y coordinates are the same 
        if ((*it1).second.first == (*it2).second.first){
            //do not change y coordinates
            newcord1.first = (*it1).second.first;
            newcord2.first = (*it2).second.first;
            switch(cipherMode){
                //in the case of encryption move the x coordinates right
                case(CipherMode::Encrypt):
                    newcord1.second = ((*it1).second.second%5)+1;
                    newcord2.second = ((*it2).second.second%5)+1;
                    break;
                    //in the case of decryption move the x coordinate left
                case(CipherMode::Decrypt):
                    newcord1.second = ((*it1).second.second-1);
                    newcord2.second = ((*it2).second.second-1);
                    break;
            }
            //if the x coordinate is less than 1 wrap-arouind to 0
            switch(newcord2.second){
                case 0 :
                    newcord2.second = 5;
            }
            switch(newcord1.second){
                case 0 :
                    newcord1.second = 5;
            }
        //if x coordinates are the same 
        }else if ((*it1).second.second == (*it2).second.second){
            //do not change x coordinates
            newcord1.second = (*it1).second.second;
            newcord2.second = (*it2).second.second;
            switch(cipherMode){
                //in the case of encryption move the y coordinates down
                case(CipherMode::Encrypt):
                    newcord1.first = ((*it1).second.first%5)+1;
                    newcord2.first = ((*it2).second.first%5)+1;
                    break;
                //in the case of decryption move the y coordinates up
                case(CipherMode::Decrypt):
                    newcord1.first = ((*it1).second.first-1);
                    newcord2.first = ((*it2).second.first-1);
                    break;
                    }
            //if the y coordinate is less than 1 wrap-arouind to 0
            switch(newcord2.first){
                case 0 :
                    newcord2.first = 5;
            }
            switch(newcord1.first){
                case 0 :
                    newcord1.first = 5;
            }
        //otherwise (letters form a rectanle) exchange x coordinates
        }else{
            newcord1.first = (*it1).second.first;
            newcord1.second = (*it2).second.second; 
            newcord2.first = (*it2).second.first;
            newcord2.second = (*it1).second.second;  
        }        
        //add letters to digraph
        auto find1 = cord2str_map_.find(newcord1);
        digraph += (*find1).second;
        auto find2 = cord2str_map_.find(newcord2);
        digraph += (*find2).second;
    } 
    //return encrypted/decrypted text
    return digraph;
}
                        

