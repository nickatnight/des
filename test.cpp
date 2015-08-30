#include "test.h"

ull Test::cidi[17] = {0};
ull Test::ks[16] = {0};
ull Test::keybit = 0;
ull Test::inputbit = 0;


// get the file contents to test each value
void Test::get_file() {

    ifstream infile("test.txt");

    ull value;
    string num, string_value, k_s = "KS", cd = "CD";
    size_t found;

    // counters
    int i=0, cdc = 0, kc = 0;

    // scan each line as a token to analyze
    while(infile >> num >> string_value) {

        value = stoull(string_value,NULL,2);

        // save each value in the corresponding array
        switch(i) {
            case 0: keybit = value; break;
            case 1: inputbit = value; break;
            default:
                if(num.find(cd) != string::npos) cidi[cdc++] = value;
                else ks[kc++] = value;
                break;
        }
        i++;
    }

    for(int c=0;c<17;c++) {
        cout << "CD" << c << ": " << cidi[c] << endl;
        if(c == 16) break;
        cout << "KS" << c+1 << ": " << ks[c] << endl;
    }
    exit(1);
}
