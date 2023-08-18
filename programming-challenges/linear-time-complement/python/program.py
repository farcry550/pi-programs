import sys

def main():
    target = int(sys.argv[1])

    nums = { }
    index = 0

    f = open("../input.txt", "r")
    for line in f:
        num = int(line)
        complement = str(target - num)

        if complement in nums:
            print(f'Indexes: {index},{nums[complement]}')
            print(f'Values: {num},{complement}\n')

        nums[line.strip()] = index

        index += 1

if __name__ == "__main__":
    main()
