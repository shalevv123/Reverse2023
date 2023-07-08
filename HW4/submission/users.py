from subprocess import Popen, PIPE, STDOUT
if __name__ == '__main__':
    p = Popen(['hw4_client.exe'], stdout=PIPE, stdin=PIPE, stderr=PIPE)
    stdout_data = p.communicate(input=b'archer\n2BBVAFEX2RNFB2NF\nUSER\n')[0]
    print(stdout_data.decode())
    from subprocess import Popen, PIPE, STDOUT
