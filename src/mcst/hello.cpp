/*
 * @Author: Neil.Chen Zifeng 
 * @Date: 2021-10-30 17:55:56 
 * @Last Modified by: Neil.Chen Zifeng
 * @Last Modified time: 2021-11-01 19:44:10
 */
#include<iostream>
#include<ctime>
using namespace std;
extern "C"
void hello() {
    time_t now = time(0);
    char* dt = ctime(&now);
    cout << "hello, it's " << dt << endl;
}