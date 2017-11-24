#include <fstream>
#include <iostream>

using namespace std;

int main (int argc, char** argv) {
    ifstream fin(argv[1], ifstream::binary);
    unsigned int maxInt = 0;
    while (!fin.eof()) {
        unsigned int tmp = 0;
        fin.read((char*)&tmp, sizeof(unsigned int));
        if (maxInt < tmp) maxInt = tmp;
    }
    fin.close();
    cout << maxInt << endl;
    return 0;
}
