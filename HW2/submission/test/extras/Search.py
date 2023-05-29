from itertools import permutations

magic_num = 26

def checkSolution(starArray):
      #first triangle

      if starArray[0]+starArray[2]+starArray[5]+starArray[7] != magic_num:
          return False
      if starArray[0]+starArray[3]+starArray[6]+starArray[10] != magic_num:
          return False
      if starArray[7]+starArray[8]+starArray[9]+starArray[10] != magic_num:
          return False

      #second triangle

      if starArray[1]+starArray[2]+starArray[3]+starArray[4] != magic_num:
          return False
      if starArray[1]+starArray[5]+starArray[8]+starArray[11] != magic_num:
          return False
      if starArray[4]+starArray[6]+starArray[9]+starArray[11] != magic_num:
          return False

      # corners
      if starArray[0]+starArray[1]+starArray[4]+starArray[7]+starArray[10]+starArray[11] != magic_num:
          return False
      return True


def main():
    #go over all the permutations of the numbers 1-12 and check if they are a solution
    for permutation in permutations(range(1, 13)):
        if checkSolution(permutation):
            print(permutation)
            return

if __name__ == "__main__":
    main()

