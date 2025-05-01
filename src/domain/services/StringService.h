#ifndef STRINGSERVICE_H
#define STRINGSERVICE_H

#include <iostream>
#include <vector>


/**
 * @class StringService
 * @brief Utility methods for strings
 */
class StringService {
    public:
        static std::vector<std::string> split(std::string&, char);
        static std::string generateSpaces(int);
};


/**
 * @brief Split a string with given delimiter
 * @param str Sentence to split
 * @param delimiter Char that marks the end of a word
 * @return Vector with splitted words
 */
std::vector<std::string> StringService::split(std::string& str, char delimiter) {
    std::vector<std::string> splitted;
    std::string aux = "";

    for (int i = 0; i < str.size(); i++){
        if (str[i] == delimiter){
            splitted.push_back(aux);
            aux = "";
        } 
        else {
            aux += str[i];
        }
    }
    splitted.push_back(aux);

    return splitted;
}


/**
 * @brief Generate a string with n spaces
 * @param n Number of spaces to generate
 * @return String with n spaces
 */
std::string StringService::generateSpaces(int n) {
    std::string spaces = "";
    
    for(int i = 0; i < n; i++){
        spaces += " ";
    }

    return spaces;
}

#endif // STRINGSERVICE_H