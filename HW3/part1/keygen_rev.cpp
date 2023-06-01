#include <iostream>
#include <string>

using namespace std;

string ascii_order = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
string keygen_order = ".5`>AdIG-*8Ee}@BDRFkzw]ZYgrsm1q\\2|3Jj(KuX !':_v6aWf{y\"C;+L<S4HO[0?$bh%/MtoT9,N)&l=xUpV^7~n#ciQP";


string keyFromPass(const string& password){
    string key;
    for (auto character : password)
        key += ascii_order[keygen_order.find(character)];
    return key;
}

int main(int argc, char** argv) {
    cout << keyFromPass(argv[1]);
    return 0;
}
