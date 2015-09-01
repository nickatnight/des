#ifndef DES_H
#define DES_H

#include <iostream>
#include <stdio.h>
#include <bitset>
#include <string>
#include <fstream>
#include <cassert>

using namespace std;
typedef unsigned long long ull;

class Des {

    public:
        Des(const string&);
        void encrypt();
        void decrypt();
        void read_store_file(const string&);
        void generate_keys();
        void fatal(const string&);
        void blocks_creation();
        void test_function();
        void function_block(ull*, ull*, ull);
        ull expand(ull*);
        ull permute(int, int, int*, ull);
        uint32_t rotl(uint32_t, int32_t);
        bool check_if_file_exists(const string&);

    private:
        ull key, pc1, test_message;
        string file_string, file_name;
        static int pc1_key[];
        static int pc2_key[];
        static int ip_key[];
        static int e_key[];
        static int p_key[];
        static int ip_inverse[];
        static uint32_t c[17], d[17];
        static ull keys[16];
        static int sbox[8][4][16];

};

#endif

