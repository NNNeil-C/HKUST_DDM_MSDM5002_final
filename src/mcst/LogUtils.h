//
// Created by 陈梓峰 on 5/11/2021.
//

#ifndef HKUST_DDM_MSDM5002_FINAL_LOGUTILS_H
#define HKUST_DDM_MSDM5002_FINAL_LOGUTILS_H
#include <cstdio>
#include <string>

#define DEBUG

#define __FILENAME__ (strrchr(__FILE__, '/') + 1)

#ifdef DEBUG
#define LOGD(format, ...) printf("[%s][%s][%d]: " format "\n", __FILENAME__, __FUNCTION__, __LINE__, ## __VA_ARGS__)

#else
#define LOGD(format, ...)
#endif


#endif //HKUST_DDM_MSDM5002_FINAL_LOGUTILS_H
