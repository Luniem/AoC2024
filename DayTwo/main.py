file = open('./input.txt', 'r')
lines = file.read().splitlines()

sum = 0

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

    sum += isSafe

print("Solution first Star: ", sum)