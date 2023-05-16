def solve(str):
    str_to_nums = [ord(c) - ord('A') for c in str]
    solution = [0] * len(str_to_nums)
    solution[28] = str_to_nums[28] ^ str_to_nums[0]
    for i in range(27, -1, -1):
        solution[i] = solution[i+1] ^ str_to_nums[i]

    solStr = ""
    for num in solution:
        solStr += chr(num + ord('A'))

    print(solStr)
    print (len("bd72A880033D0611e54a8902FE72"))

def main():
    str = "CIGDGEMCOMHCGPMBBIENHGBDGIDJL"
    solve(str)


if __name__ == "__main__":
    main()
