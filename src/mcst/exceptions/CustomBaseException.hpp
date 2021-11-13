//
// Created by 陈梓峰 on 13/11/2021.
//

#ifndef HKUST_DDM_MSDM5002_FINAL_CUSTOMBASEEXCEPTION_HPP
#define HKUST_DDM_MSDM5002_FINAL_CUSTOMBASEEXCEPTION_HPP

#include <exception>
#include <cstdio>
#include <string>

class CustomBaseException : public std::exception
{
    std::string message;
public:
    CustomBaseException(std::string);
    virtual char * what();
};

CustomBaseException::CustomBaseException(std::string msg) : message(msg) {
}

char *CustomBaseException::what() {
    printf("%s", message.c_str());
    return const_cast<char *>(message.c_str());
}

#endif //HKUST_DDM_MSDM5002_FINAL_CUSTOMBASEEXCEPTION_HPP