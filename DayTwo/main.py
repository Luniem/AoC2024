file = open('/home/nico/projects/AoC2024/DayTwo/input.txt', 'r')
lines = file.read().splitlines()

# FIRST SOLUTION
firstSolution = 0

for line in lines:
    numbersString = line.split(' ')

    numbers = []

    for number in numbersString:
        numbers.append(int(number))

    isSafe = True

    for index in range(1, len(numbers)):
        currValue = numbers[index]
        prevValue = numbers[index - 1]

        if index == 1:
            graduallyIncreasing = currValue > prevValue
        else:
            if (graduallyIncreasing and currValue < prevValue) or (not graduallyIncreasing and currValue > prevValue):
                isSafe = False
                break

        distance = abs(currValue - prevValue)

        if distance > 3 or distance == 0:
            isSafe = False
            break

    firstSolution += isSafe

print("Solution first Star: ", firstSolution)

# SECOND SOLUTION
secondSolution = 0

for line in lines:
    numbersString = line.split(' ')

    numbers = []

    for number in numbersString:
        numbers.append(int(number))

    isSafe = True
    failedIndex = None

    for index in range(1, len(numbers)):
        currValue = numbers[index]
        prevValue = numbers[index - 2] if failedIndex is index - 1 else numbers[index - 1]

        if index == 1 or failedIndex == 1:
            graduallyIncreasing = currValue > prevValue
        else:
            if (graduallyIncreasing and currValue < prevValue) or (not graduallyIncreasing and currValue > prevValue):
                if(failedIndex is None):
                    failedIndex = index
                    continue
                else:
                    isSafe = False
                    break

        distance = abs(currValue - prevValue)

        if distance > 3 or distance == 0:
            if(failedIndex is None):
                failedIndex = index
                continue
            else:
                isSafe = False
                break

    secondSolution += isSafe

print("Solution first Star: ", secondSolution)