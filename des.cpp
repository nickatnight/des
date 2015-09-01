#include "des.h"
#include "test.h"


// static member variable definition
ull Des::keys[16] = {0};
uint32_t Des::c[17] ={0};
uint32_t Des::d[17] = {0};

// Default constructor
Des::Des(const string &s) {
    file_name = s;
    key = 0x3b3898371520f75e;
    test_message = 0x0123456789abcdef;
    file_string = "";
    pc1 = 0;
};

// Permutation Choice 1 key
int Des::pc1_key[56] = {
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

// Permutation key in function block
int Des::p_key[32] = {
      16, 7, 20, 21,
      29, 12, 28, 17,
      1, 15, 23, 26,
      5, 18, 31, 10,
      2, 8, 24, 14,
      32, 27, 3, 9,
      19, 13, 30, 6,
      22, 11, 4, 25
};

// Inverse permutation key for the final permutation of the cipher block
int Des::ip_inverse[64] = {
      40, 8, 48, 16, 56, 24, 64, 32,
      39, 7, 47, 15, 55, 23, 63, 31,
      38, 6, 46, 14, 54, 22, 62, 30,
      37, 5, 45, 13, 53, 21, 61, 29,
      36, 4, 44, 12, 52, 20, 60, 28,
      35, 3, 43, 11, 51, 19, 59, 27,
      34, 2, 42, 10, 50, 18, 58, 26,
      33, 1, 41, 9, 49, 17, 57, 25
};

// S-Box declarations
int Des::sbox[8][4][16] = {
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
    {
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
    },
    {
        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
    },
    {
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
    },
    {
        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
    },
    {
        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
    },
    {
        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
    },
    {
        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
    }
};

// Main function to execute the encryption
void Des::encrypt() {

    string block_;
    ull ip_out, l0_, r0_, ki_;

    Test::get_file();

    // double check to make sure the file exists before performing any
    // operations on the file
    if(check_if_file_exists(file_name)) {

        // perform a binary scan on the file and store the contents in an array
        // for easy access
        read_store_file(file_name);


        cout << "Message : " << bitset<64>(test_message) << endl;
        assert(test_message == Test::inputbit);

        cout << "Key: " << bitset<64>(key) << endl;
        assert(key == Test::keybit);

        generate_keys();

        // for loop for ip, then inner for loop for function block
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

        // ********* Initial Permutation ***********
        ip_out = permute(64, 64, ip_key, test_message);

        l0_ = (ip_out & 0xffffffff00000000) >> 32;
        r0_ = (ip_out & 0x00000000ffffffff);

        // pointers to the address locations of left and right branches of the
        // initial permutation
        ull *li_ = &l0_;
        ull *ri_ = &r0_;

        cout << "L0: " << bitset<32>(l0_) << endl;
        cout << "R0: " << bitset<32>(r0_) << endl;

        // do sixteen rounds of function block computations
        for(int j=0;j<16;j++) {

            function_block(li_, ri_, keys[j]);

            // leave the last round of msb and lsb unswtiched since we need to
            // switch them again in the final permutaiton of the key
            if(j==15) break;

            //switch the lsb and msb
            ull temp;
            temp = l0_;
            l0_ = r0_;
            r0_ = temp;
        }

        cout << "L16: " << bitset<32>(l0_) << endl;
        cout << "R16: " << bitset<32>(r0_) << endl;

        ull lr = (l0_ << 32) + r0_;

        // TEST L16R16
        assert(lr == Test::l_r);

        // ****** Inverse Permutation *********
        ull fo = permute(64, 64, ip_inverse, lr);
        assert(fo == Test::final_output);

        cout << "Final permutation: " << hex << fo << endl;

    } else {
        fatal("File does not exists...exiting program.");
    }
}

void Des::decrypt() {

}

// Reads the input file as a string using a binary read and stores the data in a
// string (so each byte can be analyzed individually).
//
// Input: name of the file
void Des::read_store_file(const string &f) {

    ifstream stream(f, ifstream::binary);

    stream.seekg(0, stream.end);
    int length = stream.tellg();
    stream.seekg(0, stream.beg);

    char * buf = new char[length];

    stream.read(buf, length);

    stream.close();

    file_string = buf;

    delete[] buf;
}

// Determines if the file exists on the system and if it does, the function
// returns true.
//
// Input: file name
// Output: bool
bool Des::check_if_file_exists(const string &s) {

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
void Des::function_block(ull *li, ull *ri, ull ki) {

    ull expansion = 0, sbox_in = 0, sbox_out = 0, shifter=0x0000fc0000000000, f_out, iso_bits;
    int row, col;

    // expand the lsb
    expansion = expand(ri);

    // XOR function using the expansion output and k of i that assigns a 48 bit
    // value to sbox_in. Each 6 bit group is used as input to get the column and
    // row that determines the output.
    sbox_in = expansion ^ ki;

    // start sbox substitution
    for(int i=0;i < 8;i++) {

        // isolate bits
        iso_bits = sbox_in & shifter ;

        // get row #
        if((iso_bits & 0x0000840000000000) == 0x0000840000000000) row = 3;
        else if((iso_bits & 0x0000800000000000) == 0x0000800000000000) row = 2;
        else if((iso_bits & 0x0000040000000000) == 0x0000040000000000) row = 1;
        else row = 0;

        // get column #
        col = (int)((iso_bits & 0x0000780000000000) >> 43);

        // Cast the 32 bit integer from the static array to 64 bits and add the
        // total to the s_box output
        sbox_out += (ull)(sbox[i][row][col]);

        // shift out previous bits from sbox to get the new isloated bits
        sbox_in <<= 6;

        // break out of loop so we do not have an extra shift in the final sbox
        // output
        if(i == 7) break;

        // shift out 4 bits to add the newest 4
        sbox_out <<= 4;
    }

    //************ Permutation *************
    *li = permute(32, 32, p_key, sbox_out) ^ *li;
}

// Expands the 32 bit input bit rearragning the bits into a 48 bit output
//
// Input: 32 least significant bits of the initial permutation
// Output: 48 bit expansion
ull Des::expand(ull *ri_) {

    ull exp = 0, temp, row = 0;
    int shft_amt, off_set;

    for(int i=0;i<48;i++) {
        temp = 1;
        temp <<= (32-e_key[i]);

        if(i==47) exp += ((*ri_ & temp) >> abs(e_key[i]-(i+1)+16));
        else exp += ((*ri_ & temp) << abs(e_key[i]-(i+1)+16));
    }

    return exp;
}

ull Des::permute(int in_bits, int out_bits, int *key_, ull input_) {

    //ull block = test_message;
    ull temp, return_perm = 0;
    int shft_amt, off_set;

    for(int i=0;i<out_bits;i++ ) {
        temp = 1;
        shft_amt = in_bits - key_[i];
        temp <<= shft_amt;
        off_set = abs((i+1)-key_[i]);
        if(((i+1)-key_[i]) > 0)
            return_perm += (input_ & temp) >> off_set;
        else if(((i+1)-key_[i]) < 0)
            return_perm += (input_ & temp) << off_set;
        else
            return_perm += (input_ & temp);
    }

    return return_perm;
}


// Creates 17 c/d blocks in order to get our permuted k keys
void Des::blocks_creation() {

    // isolate the msb and lsb to get C0 and D0
    c[0] = (uint32_t)((0x00fffffff0000000 & pc1) >> 28);
    d[0] = (uint32_t)(0x000000000fffffff & pc1);

    cout << endl;
    cout << "c0: " << bitset<28>(c[0]) << endl;
    cout << "d0: " << bitset<28>(d[0]) << endl;
    cout << endl;

    // TEST c[0]d[0]
    assert((((ull)c[0] << 28) | (ull)d[0]) == Test::cidi[0]);

    for(int i=1;i<=16;i++) {
        // check if the ci di value to determine how many left shifts need to be
        // performed
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

    // ******** Permutation 1 ************
    pc1 = permute(64, 56, pc1_key, key) >> 8;

    blocks_creation();

    for(int j=0;j<16;j++){

        // format C[i] with D[i] to get 56 bit requierd output. start at j+1
        // since we start with C[1]D[1] for the first key. Cast C and D to 64
        // bit long.
        ci_di = ((ull)c[j+1] << 28) | (ull)d[j+1];
        cout << "CnDn(" << j+1 << "): " << bitset<56>(ci_di) << endl;

        // TEST C sub i and D sub i
        assert(ci_di == Test::cidi[j+1]);

        //********* Permutation 2 ***********
        keys[j] = permute(56, 48, pc2_key, ci_di) >> 8;
        assert(keys[j] == Test::ks[j]);

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
void Des::fatal(const string &s) {
    cout << s << endl;
    exit(1);
}
