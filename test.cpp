#include "test.h"

ull Test::cidi[17] = {0};
ull Test::ks[16] = {0};
ull Test::keybit = 0;
ull Test::inputbit = 0;
ull Test::l_r = 0;
ull Test::final_output = 0;


// get the file contents to test each value
void Test::get_file() {

    ifstream infile("test.txt");

    ull value;
    string num, string_value, k_s = "KS", cd = "CD";

    // counters
    int i=0, cdc = 0, kc = 0;

    // scan each line as a token to analyze
    while(infile >> num >> string_value) {

        value = stoull(string_value,NULL,2);

        // save each value in the corresponding array
        switch(i) {
            case 0: inputbit = value; break;
            case 1: keybit = value; break;
            case 35: l_r = value; break;
            case 36: final_output = value; break;
            default:
                if(num.find(cd) != string::npos) cidi[cdc++] = value;
                else ks[kc++] = value;
                break;
        }
        i++;
    }

}
