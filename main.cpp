#include "des.cpp"


int main(int argc, char **argv){

    Des d;
    clock_t start;
    double dur;

    if(argc == 2) {
        start = clock();
        d.run(argv[1]);

        dur = (clock() - start) / (double) CLOCKS_PER_SEC;
        cout << "Execution time: " << dur << endl;
    } else {
        cout << "Invalid input." << endl;
    }

    return 0;
}
