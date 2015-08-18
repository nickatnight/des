#include "des.h"


// member variable declarations
ull Des::key = 0x133457799BBCDFF1;
ull Des::pc1 = 0;
string Des::file_string = "";
uint32_t Des::c[17] = {};
uint32_t Des::d[17] = {};
ull Des::keys[16] = {};

// Permutation Choice 1 key
int Des::pc1_key[] = {
      57, 49, 41, 33, 25, 17, 9,
      1, 58, 50, 42, 34, 26, 18,
      10, 2, 59, 51, 43, 35, 27,
      19, 11, 3, 60, 52, 44, 36,
      63, 55, 47, 39, 31, 23, 15,
      7, 62, 54, 46, 38, 30, 22,
      14, 6, 61, 53, 45, 37, 29,
      21, 13, 5, 28, 20, 12, 4
};

// Permutation Choice 2 key
int Des::pc2_key[48] = {
      14, 17, 11, 24, 1, 5,
      3, 28, 15, 6, 21, 10,
      23, 19, 12, 4, 26, 8,
      16, 7, 27, 20, 13, 2,
      41, 52, 31, 37, 47, 55,
      30, 40, 51, 45, 33, 48,
      44, 49, 39, 56, 34, 53,
      46, 42, 50, 36, 29, 32
};

// Initial Permutation Key
int Des::ip_key[64] = {
      58, 50, 42, 34, 26, 18, 10, 2,
      60, 52, 44, 36, 28, 20, 12, 4,
      62, 54, 46, 38, 30, 22, 14, 6,
      64, 56, 48, 40, 32, 24, 16, 8,
      57, 49, 41, 33, 25, 17, 9, 1,
      59, 51, 43, 35, 27, 19, 11, 3,
      61, 53, 45, 37, 29, 21, 13, 5,
      63, 55, 47, 39, 31, 23, 15, 7
};

// Expansion Key
int Des::e_key[48] = {
      32, 1, 2, 3, 4, 5,
      4, 5, 6, 7, 8, 9,
      8, 9, 10, 11, 12, 13,
      12, 13, 14, 15, 16, 17,
      16, 17, 18, 19, 20, 21,
      20, 21, 22, 23, 24, 25,
      24, 25, 26, 27, 28, 29,
      28, 29, 30, 31, 32, 1
};

// Main function to execute the encryption
void Des::run(string s) {

    string block_;
    ull ip_out, l0_, r0_, ki_;

    //cout << bitset<64>(key) << endl;
    if(check_if_file_exists(s)) {
        read_store_file(s);
        generate_keys();

        // for loop for ip, then inner fo loop for function blocki
        // for(int i=0;i<(file_string/8);i++) {
        //    block = file_string.substr((i*8)+1,8);
        //    ip_out = initial_permutation(block_);
        //
        //    l0_ = (ip_out & 0x1111111100000000) >> 32;
        //    r0_ = (ip_out & 0x0000000011111111);
        //
        //    for(int j=0;j<16;j++) {
        //        function_block(l0_, r0_, keys[j])
        //    }
        // }
        ip_out = initial_permutation();
        l0_ = (ip_out & 0xffffffff00000000) >> 32;
        r0_ = (ip_out & 0x00000000ffffffff);

        ull *li = &l0_;
        ull *ri = &r0_;

        cout << "L0: " << bitset<32>(l0_) << endl;
        cout << "R0: " << bitset<32>(r0_) << endl;

        for(int j=0;j<16;j++)
            function_block(l0_, r0_, keys[j]);

    } else {
        fatal("File does not exists...exiting program.");
    }
}

// Reads the input file as a string as a binary read and stores the data in a
// string (so each byte can be read individually).
//
// Input: name of the file
void Des::read_store_file(string f) {

    ifstream stream(f, ifstream::binary);

    stream.seekg(0, stream.end);
    int length = stream.tellg();
    stream.seekg(0, stream.beg);

    char * buf = new char[length];
    cout << "Reading file contents...." << endl;
    stream.read(buf, length);

    stream.close();

    file_string = buf;
    cout << file_string << endl;
    cout << "File is " << length << " bytes." << endl;
    delete[] buf;
}

// Determines if the file exists on the system and if it does, the function
// returns true.
//
// Input: file name
// Output: bool
bool Des::check_if_file_exists(string s) {

    if(FILE *f = fopen(s.c_str(), "r")){
        fclose(f);
        return true;
    } else {
        return false;
    }
}

// Function block that does the bulk of the encryption
//
// Input: Left 32 bits of the initial permutation
//        Right 32 bits of the initial permutation
//        Key value for n
void Des::function_block(ull l0, ull r0, ull ki) {

    ull expansion = 0;
    expansion = expand(r0);



}

// Expands the 32 bit input bit rearragning the bits into a 48 bit output
//
// Input: 32 least significant bits of the initial permutation
// Output: 48 bit expansion
ull Des::expand(ull r0) {

    ull exp = 0, temp, row = 0;
    int shft_amt, off_set;

    for(int i=0;i<48;i++) {
        temp = 1;
        temp = temp << (32-e_key[i]);

        if(i==47) exp += ((r0 & temp) >> abs(e_key[i]-(i+1)+16));
        else exp += ((r0 & temp) << abs(e_key[i]-(i+1)+16));
        //cout << "r0:\t" << bitset<48>(r0) << endl;
        //cout << "temp:\t" << bitset<48>(temp) << endl;
        //cout << "exp:\t" << bitset<48>(exp) << endl;
        //cout << endl;

        /*
        ifdef(i < 16) {
            exp += ((r0 & temp) << abs(e_key[i]-(i+1) + 16));
        } else {
            exp += (r0 & temp) << abs(e_key[i]-(i+1) + 16);
            cout << "OK" << endl;
        }
        */

        //cout << bitset<48>(exp) << endl;
    }

    //cout << "Expansion: " << bitset<48>(exp) << endl;
    //exit(1);
    return exp;
}

// Initial permutation rearranges a block of 64 bits from a defined key
//
// Output: 64 bits
ull Des::initial_permutation() {

    cout << "Initial permutation..." << endl;

    ull block = 0x0123456789abcdef;
    ull ip = 0;
    ull temp;
    int shft_amt, off_set;
    for(int i=0;i<64;i++ ) {
        temp = 1;
        shft_amt = 64 - ip_key[i];
        temp = temp << shft_amt;
        off_set = abs((i+1)-ip_key[i]);
        if(((i+1)-ip_key[i]) > 0)
            ip += (block & temp) >> off_set;
        else if(((i+1)-ip_key[i]) < 0)
            ip += (block & temp) << off_set;
        else
            ip += (block & temp);
    }

    cout << "64 bit (8 byte block) initial permutation: " << bitset<64>(ip) << endl;

    return ip;
}

// Permutation 1
void Des::permutation1() {

    cout << "Performing first permutation..." << endl;

    ull temp;
    int shft_amt, off_set;
    for(int i=0;i<56;i++ ) {
        temp = 1;
        shft_amt = 64 - pc1_key[i];
        temp = temp << shft_amt;
        off_set = abs((i+1)-pc1_key[i]);
        if(((i+1)-pc1_key[i]) > 0)
            pc1 += (key & temp) >> off_set;
        else if(((i+1)-pc1_key[i]) < 0)
            pc1 += (key & temp) << off_set;
    }
    pc1 = pc1 >> 8;
    cout << "First Permutation Choice: " << bitset<64>(pc1) << endl;
}

// Permutation 2
ull Des::permutation2(ull cidi) {

    ull temp, temp_keys = 0;
    int shft_amt, off_set;

    // CiDi = 56 bits
    // keys = 48 bits
    //              1   2     3   4     5   6     7   8     9   10    11  12    13  14
    // 0000 0000 _ 1110 0001 1001 1001 0101 0101 1111 1010 1010 1100 1100 1111 0001 1110
    // 0000 0000 _ 0000 0000 xxxx xxxx xxxx xxxx xxxx xxxx xxxx xxxx xxxx xxxx xxxx xxxx
    temp_keys = ((cidi & 0x0000040000000000) << 5) + ((cidi & 0x0000008000000000) << 7)\
                + ((cidi & 0x0000200000000000) << 0) + ((cidi & 0x0000000100000000) << 12)\
                + ((cidi & 0x0080000000000000) >> 12) + ((cidi & 0x0008000000000000) >> 9)\
                + ((cidi & 0x0020000000000000) >> 12) + ((cidi & 0x0000000010000000) << 12)\
                + ((cidi & 0x0000020000000000) >> 2) + ((cidi & 0x0004000000000000) >> 12)\
                + ((cidi & 0x0000008000000000) >> 2) + ((cidi & 0x0000400000000000) >> 10)\
                + ((cidi & 0x0000000200000000) << 2) + ((cidi & 0x0000002000000000) >> 3)\
                + ((cidi & 0x0000100000000000) >> 11) + ((cidi & 0x0010000000000000) >> 20)\
                + ((cidi & 0x0000000040000000) << 1) + ((cidi & 0x0001000000000000) >> 18)\
                + ((cidi & 0x0000010000000000) >> 11) + ((cidi & 0x0002000000000000) >> 21)\
                + ((cidi & 0x0000000020000000) >> 2) + ((cidi & 0x0000001000000000) >> 10)\
                + ((cidi & 0x0000080000000000) >> 18) + ((cidi & 0x0040000000000000) >> 30)\
                + ((cidi & 0x0000000000008000) << 8) + ((cidi & 0x0000000000000010) << 18)\
                + ((cidi & 0x0000000002000000) >> 4) + ((cidi & 0x0000000000080000) << 1)\
                + ((cidi & 0x0000000000000200) << 10) + ((cidi & 0x0000000000000002) << 17)\
                + ((cidi & 0x0000000004000000) >> 9) + ((cidi & 0x0000000000010000) >> 0)\
                + ((cidi & 0x0000000000000020) << 10) + ((cidi & 0x0000000000000800) << 3)\
                + ((cidi & 0x0000000000800000) >> 10) + ((cidi & 0x0000000000000100) << 4)\
                + ((cidi & 0x0000000000001000) >> 1) + ((cidi & 0x0000000000000080) << 3)\
                + ((cidi & 0x0000000000020000) >> 8) + ((cidi & 0x0000000000000001) << 8)\
                + ((cidi & 0x0000000000400000) >> 15) + ((cidi & 0x0000000000000008) << 3)\
                + ((cidi & 0x0000000000000400) >> 5) + ((cidi & 0x0000000000004000) >> 10)\
                + ((cidi & 0x0000000000000040) >> 3) + ((cidi & 0x0000000000100000) >> 18)\
                + ((cidi & 0x0000000008000000) >> 26) + ((cidi & 0x0000000001000000) >> 24);

    //cout << "k1: " << bitset<48>(temp_keys) << endl;
    return temp_keys;
}

// Creates 17 c/d blocks in order to get our permuted k keys
void Des::blocks_creation() {

    c[0] = (uint32_t)((0x00fffffff0000000 & pc1) >> 28);
    d[0] = (uint32_t)(0x000000000fffffff & pc1);

    cout << "c0: " << bitset<28>(c[0]) << endl;
    cout << "d0: " << bitset<28>(d[0]) << endl;
    cout << endl;

    for(int i=1;i<=16;i++) {
        if(i==1 || i==2 || i==9 || i==16){
            c[i] = rotl(c[i-1], 1);
            d[i] = rotl(d[i-1], 1);
        } else{
            c[i] = rotl(c[i-1], 2);
            d[i] = rotl(d[i-1], 2);
        }

        cout << "c" << i << ": " << bitset<28>(c[i]) << endl;
        cout << "d" << i << ": " << bitset<28>(d[i]) << endl;
        cout << endl;
    }
}

// Generation of 16 keys to be used in the function block
void Des::generate_keys() {

    ull ci_di = 0;
    permutation1();

    blocks_creation();

    cout << "Creating keys...." << endl;
    for(int j=0;j<16;j++){
        //ci_di = 0;
        ci_di = ((unsigned long long)c[j+1] << 28) | (unsigned long long)d[j+1];
        //cout << bitset<64>((unsigned long long)c[j+1] << 28) << endl;
        cout << "CnDn(" << j+1 << "): " << bitset<56>(ci_di) << endl;
        //assert(ci_di, j+1);
        keys[j] = permutation2(ci_di);
        cout << "k" << j+1 << ": " << bitset<48>(keys[j]) << endl;
    }
}

// Performs a rotating left shit on a given input
//
// Input: 32 bits
// Output: 32 bits
uint32_t Des::rotl(uint32_t v, int32_t shift) {
    uint32_t result = v;

    for(int i=0;i<shift;i++) {
        if((result >> 27) == 1){
            result = ((result << 1) & 0x0fffffff) + 1;
        }
        else
            result = result << 1;
    }
    return result;
}

// Prompts user of error and exits program
//
// Input: Name of error
void Des::fatal(string s) {
    cout << s << endl;
    exit(1);
}
