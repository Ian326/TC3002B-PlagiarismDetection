#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <iostream>

template <class T>
class Token {
        T tag;
        std::string value;

    public:
        Token(T, std::string);
        ~Token();
        
        T getTag() const;
        std::string getValue() const;
};

template <class T>
Token<T>::Token(T tag, std::string value) {
    this->tag = tag;
    this->value = value;
}

template <class T>
Token<T>::~Token(){}

template <class T>
T Token<T>::getTag() const {
    return this->tag;
}

template <class T>
std::string Token<T>::getValue() const {
    return this->value;
}

#endif // TOKEN_H
