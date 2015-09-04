# DES

Data Encryption Standard from a hardware standpoint utilizing bitshifts and bit
masks. This was written for fun during the tail end of summer 15'.

*Note: At this point, only one 64 bit "message" is taken as input and outputs a
64 bit ciphertext. This will eventually become a practical program to encrypt any file.

To run:
    make
    ./des -e main.cpp
    ./des -d main.cpp

-__ -;
