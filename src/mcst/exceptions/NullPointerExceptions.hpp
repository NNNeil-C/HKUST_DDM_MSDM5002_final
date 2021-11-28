//
// Created by 陈梓峰 on 13/11/2021.
//

#ifndef HKUST_DDM_MSDM5002_FINAL_NULLPOINTEREXCEPTIONS_HPP
#define HKUST_DDM_MSDM5002_FINAL_NULLPOINTEREXCEPTIONS_HPP

#include "CustomBaseException.hpp"


class NullPointerException : public CustomBaseException
{
public:
    NullPointerException(std::string);
};

NullPointerException::NullPointerException(std::string msg) : CustomBaseException(msg)
{

}

#endif //HKUST_DDM_MSDM5002_FINAL_NULLPOINTEREXCEPTIONS_HPP
