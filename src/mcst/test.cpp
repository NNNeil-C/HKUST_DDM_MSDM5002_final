/*
 * @Author: Neil.Chen Zifeng 
 * @Date: 2021-11-02 00:08:26 
 * @Last Modified by: Neil.Chen Zifeng
 * @Last Modified time: 2021-11-02 20:45:20
 */
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
using namespace std;
int main ()
{
    int *a = new int [100];
    free(a);
    int *b = NULL;
    srand(time(NULL));
    cout << rand() % 100 << endl;
    cout << rand() % 100 << endl;
}