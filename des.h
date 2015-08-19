#include <iostream>
#include <stdio.h>
#include <ctime>
#include <bitset>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>


using namespace std;
typedef unsigned long long ull;

class Des {

    public:
        void run(string s = "");
        static void read_store_file(string);
        static bool check_if_file_exists(string);
        static void permutation1();
        static ull permutation2(ull);
        static void generate_keys();
        static void fatal(string);
        static void blocks_creation();
        static uint32_t rotl(uint32_t, int32_t);
        static ull initial_permutation();
        static void test_function();
        static void function_block(ull *, ull *, ull);
        static ull expand(ull *);

    private:
        static ull key, pc1;
        static string file_string;
        static int pc1_key[];
        static int pc2_key[];
        static int ip_key[];
        static int e_key[];
        static uint32_t c[17], d[17];
        static ull keys[16];
        static int sbox[8][4][16];

};
