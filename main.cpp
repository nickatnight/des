#include "des.cpp"
#include "test.cpp"


int main(int argc, char **argv){

    // check to make sure a file is included
    if(argc == 2) {

        Des *d = new Des(argv[1]);
        clock_t start;
        double dur;

        start = clock();
        d->run();

        // get duration of the time it took program to run and output to user
        dur = (clock() - start) / (double) CLOCKS_PER_SEC;
        cout << "Execution time: " << dur << endl;
    }
    else {
        cout << "Invalid input. Refer to README." << endl;
    }

    return 0;
}
