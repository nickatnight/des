#include "des.cpp"
#include "test.cpp"

#define E_FLAG "-e"
#define D_FLAG "-d"


int main(int argc, char **argv){

    clock_t start;
    double dur;

    start = clock();
    Des *d = new Des(argv[2]);

    // check for proper input
    if(argc == 3) {

        if(!strcmp(argv[1], E_FLAG)) d->run('e');
        else if(!strcmp(argv[1], D_FLAG)) d->run('d');
        else cout << "Invalid input. Refere to README." << endl;
    }
    else {
        cout << "Invalid input. Refer to README." << endl;
    }

    dur = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout << "Execution time: " << dur << endl;
    return 0;
}
