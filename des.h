#ifndef DES_H
#define DES_H

#include <iostream>
#include <stdio.h>
#include <ctime>
#include <bitset>
#include <string>
#include <fstream>


using namespace std;
typedef unsigned long long ull;

class Des {

    public:
        Des(const string&);
        void run();
        void read_store_file(const string&);
        bool check_if_file_exists(const string&);
        ull permutation(ull);
        void permutation1();
        ull permutation2(ull);
        void generate_keys();
        void fatal(const string&);
        void blocks_creation();
        uint32_t rotl(uint32_t, int32_t);
        ull initial_permutation();
        void test_function();
        void function_block(ull *, ull *, ull);
        ull expand(ull *);

    private:
        ull key, pc1, test_message;
        string file_string, file_name;
        static int pc1_key[];
        static int pc2_key[];
        static int ip_key[];
        static int e_key[];
        static int p_key[];
        static uint32_t c[17], d[17];
        static ull keys[16];
        static int sbox[8][4][16];

};

#endif

