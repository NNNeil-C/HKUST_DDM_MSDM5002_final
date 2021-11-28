//
// Created by 陈梓峰 on 12/11/2021.
//

#ifndef HKUST_DDM_MSDM5002_FINAL_NOMOSTVISITEDNODEEXCEPTION_HPP
#define HKUST_DDM_MSDM5002_FINAL_NOMOSTVISITEDNODEEXCEPTION_HPP
#include "CustomBaseException.hpp"


class NoMostVisitedNodeException : public CustomBaseException
{
public:
    NoMostVisitedNodeException(std::string);
};

NoMostVisitedNodeException::NoMostVisitedNodeException(std::string msg) : CustomBaseException(msg)
{

}

#endif //HKUST_DDM_MSDM5002_FINAL_NOMOSTVISITEDNODEEXCEPTION_HPP