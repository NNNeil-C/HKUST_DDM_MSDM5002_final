/*
 * @Author: Neil.Chen Zifeng 
 * @Date: 2021-11-02 00:08:26 
 * @Last Modified by: Neil.Chen Zifeng
 * @Last Modified time: 2021-11-02 00:10:34
 */
#include <cstdlib>
int main ()
{
    int *a = new int [100];
    free(a);
    int *b = NULL;
}