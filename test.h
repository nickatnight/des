#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>


using namespace std;
typedef unsigned long long ull;


// member functions are made static to prevent passing the same object to
// different functions.
class Test {

    public:
        Test();
        static void get_file();

    private:
        static ull keybit;
        static ull inputbit;
        static ull cidi[17];
        static ull ks[16];
};
#endif
