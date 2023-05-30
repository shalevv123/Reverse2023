#make a string of all ascii characters in their order from "!" to "~"
import argparse
parser = argparse.ArgumentParser()

parser.add_argument("password", type=str, help="password to generate key from")

args = parser.parse_args()
ascii_odrer = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"
keygen_order =".5`>AdIG-*8Ee}@BDRFkzw]ZYgrsm1q\\2|3Jj(KuX !':_v6aWf{y\"C;+L<S4HO[0?$bh%/MtoT9,N)&l=xUpV^7~n#ciQP"

def keyFromPass(password):
    key = ""
    for i in range(len(password)):
        key += ascii_odrer[keygen_order.index(password[i])]
    return key



def main():
    password = keyFromPass(args.password)
    print(password)
# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    main()

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
