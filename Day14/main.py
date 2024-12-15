import itertools
import os
import time

clear = lambda: os.system('clear')

file = open('/home/nico/projects/AoC2024/Day14/input.txt', 'r')
lines = file.read().splitlines()

wide = 101
tall = 103

firstSolution = 1 # 1 because we are going to multiply
secondSolution = 0

def printRobots(robots):
    for i in range(0, tall):
        for j in range(0, wide):
            found = 0
            for robot in robots:
                if int(robot[0]) == j and int(robot[1]) == i:
                    found += 1
            if found:
                print(found, end="")
            else:
                print(" ", end="")
        print()


def createInitialRobots(lines):
    robots = []

    # create a list of robots
    for i in range(0, len(lines)):
        splitted = lines[i].split(" ")
        positions = splitted[0].split("=")[1].split(",")
        velocities = splitted[1].split("=")[1].split(",")
        
        positionX = positions[0]
        positionY = positions[1]
        velocityX = velocities[0]
        velocityY = velocities[1]

        robots.append([positionX, positionY, velocityX, velocityY])
    
    return robots

robots = createInitialRobots(lines)

max_seconds = 100

seconds = 0

secondSolution = 6355

for i in range(0, max_seconds):
    seconds += 1
    for robot in robots:
        newX = int(robot[0]) + int(robot[2])
        newY = int(robot[1]) + int(robot[3])

        # check if new x is out of bounds so wrap around
        if newX >= wide:
            newX -= wide
        elif newX < 0:
            newX += wide

        if newY >= tall:
            newY -= tall
        elif newY < 0:
            newY += tall

        robot[0] = newX
        robot[1] = newY


left_half = range(0, int(wide / 2))
right_half = range(int(wide / 2) + 1, wide)
top_half = range(0, int(tall / 2))
bottom_half = range(int(tall / 2) + 1, tall)

vertical_halfs = [top_half, bottom_half]
horizonatl_halfs = [left_half, right_half]

combis = list(itertools.product(vertical_halfs, horizonatl_halfs))

count_robots = []


for combi in combis:
    count = 0
    for x in combi[1]:
        for y in combi[0]:
            for robot in robots:
                if int(robot[0]) == x and int(robot[1]) == y:
                    count += 1
    count_robots.append(count)

for count in count_robots:
    firstSolution *= count


# second start - solved it by checking out which noticable patterns are repeating and then calculating the seconds for the iterations
# I noticed that the christmas tree shape is appearing first after 6355 seconds
# The following code shows the solution for the second star
while True:
    seconds += 1
    for robot in robots:
        newX = int(robot[0]) + int(robot[2])
        newY = int(robot[1]) + int(robot[3])

        # check if new x is out of bounds so wrap around
        if newX >= wide:
            newX -= wide
        elif newX < 0:
            newX += wide

        if newY >= tall:
            newY -= tall
        elif newY < 0:
            newY += tall

        robot[0] = newX
        robot[1] = newY



    if seconds == secondSolution:
        printRobots(robots)
        break

print("Solution first Star: ", firstSolution)
print("Solution second Star: ", secondSolution)

