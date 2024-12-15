#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

typedef struct {
    uint32_t start;
    uint32_t end;
    uint16_t id;
} FileRange;

int calcSolution(FileRange *fileRanges, int* fileRangeSize, uint64_t* solution) {
    // loop over all file ranges and calculate the solution
    for (int i = 0; i < *fileRangeSize; i++) {
        for (int j = fileRanges[i].start; j <= fileRanges[i].end; j++) {
            *solution += j * fileRanges[i].id;
        }
    }
}

void resetRanges(FileRange **fileRanges, FileRange **spaceRanges, int* fileRangeSize, int* spaceRangeSize) {
    *fileRangeSize = 0;
    *spaceRangeSize = 0;
    free(*fileRanges);
    free(*spaceRanges);
    *fileRanges = (FileRange *)malloc(*fileRangeSize * sizeof(FileRange));
    *spaceRanges = (FileRange *)malloc(*spaceRangeSize * sizeof(FileRange));
}

void fillRangeArrays(FileRange **fileRanges, FileRange **spaceRanges, int* fileRangeSize, int* spaceRangeSize, char* line) {
    int currentIndex = 0;
    for(int i = 0; i < strlen(line); i++) {
        int length = line[i] - '0';
            if(i % 2 == 0) {
                // even number - it is a file
                *fileRangeSize += 1;
                *fileRanges = (FileRange *)realloc(*fileRanges, sizeof(FileRange) * *fileRangeSize);

                (*fileRanges)[*fileRangeSize - 1].start = currentIndex;
                (*fileRanges)[*fileRangeSize - 1].end = currentIndex + length - 1;
                (*fileRanges)[*fileRangeSize - 1].id = *fileRangeSize - 1;
            } else {
                *spaceRangeSize += 1;
                // odd number - its empty space
                *spaceRanges = (FileRange *)realloc(*spaceRanges, sizeof(FileRange) * *spaceRangeSize);

                (*spaceRanges)[*spaceRangeSize - 1].start = currentIndex;
                (*spaceRanges)[*spaceRangeSize - 1].end = currentIndex + length - 1;
                // we dont need to care for id here
            }
        currentIndex += length;
    }
}

int main() {
    FILE* file = fopen("./input.txt", "r");

    uint64_t *firstSolution = (uint64_t *)malloc(sizeof(uint64_t));
    uint64_t *secondSolution = (uint64_t *)malloc(sizeof(uint64_t));

    // file will be null if it cannot be opened
    if (file != NULL) {
        // buffer for line
        char line[20000];

        // read line into buffer
        fgets(line, sizeof(line), file);

        int *fileRangeSize = (int *)malloc(sizeof(int));
        FileRange *fileRanges = (FileRange *)malloc(*fileRangeSize * sizeof(FileRange));

        int *spaceRangeSize = (int *)malloc(sizeof(int));
        FileRange *spaceRanges = (FileRange *)malloc(*spaceRangeSize * sizeof(FileRange));

        fillRangeArrays(&fileRanges, &spaceRanges, fileRangeSize, spaceRangeSize, line);

        // solution 1
        for (int i = *fileRangeSize - 1; i >= 0; i--) {
            if(spaceRanges[0].start < fileRanges[i].end) {
                // check if there is free space to the left
                int neededSpace = fileRanges[i].end - fileRanges[i].start + 1;

                // we do it as long as we still need more space
                while (neededSpace > 0) {
                    if(spaceRanges[0].start > fileRanges[i].end) {
                        break;
                    }

                    // find first free space
                    int spaceStart = spaceRanges[0].start;
                    int spaceEnd = spaceRanges[0].end;

                    // calculate how much space we can use
                    int spaceSize = spaceEnd - spaceStart + 1;

                    // create new file range that uses all the space needed/possible
                    int usingSpace = neededSpace > spaceSize ? spaceSize : neededSpace;
                    fileRanges = (FileRange *)realloc(fileRanges, sizeof(FileRange) * ++(*fileRangeSize));
                    fileRanges[*fileRangeSize-1].id = fileRanges[i].id;
                    fileRanges[*fileRangeSize-1].start = spaceStart;
                    fileRanges[*fileRangeSize-1].end = spaceStart + usingSpace - 1;

                    // push start of file-range by the amount of used space
                    fileRanges[i].end -= usingSpace;

                    // subtract available space from needed space
                    neededSpace -= usingSpace;

                    // remove space range from array if it is fully used else just adjust the start
                    if (usingSpace == spaceSize) {
                        for (int j = 0; j < *spaceRangeSize - 1; j++) {
                            spaceRanges[j] = spaceRanges[j + 1];
                        }
                        *spaceRangeSize -= 1;
                    } else {
                        spaceRanges[0].start += usingSpace;
                    }
                }
            }
        }

        calcSolution(fileRanges, fileRangeSize, firstSolution);

        resetRanges(&fileRanges, &spaceRanges, fileRangeSize, spaceRangeSize);
        fillRangeArrays(&fileRanges, &spaceRanges, fileRangeSize, spaceRangeSize, line);

        // solution 2
        for (int i = *fileRangeSize - 1; i >= 0; i--) {
            int neededSpace = fileRanges[i].end - fileRanges[i].start + 1;

            for(int j = 0; j < *spaceRangeSize; j++) {
                // check if we are already to the right 
                if (fileRanges[i].end < spaceRanges[j].start){
                    break;
                }

                // check how much free space
                int spaceSize = spaceRanges[j].end - spaceRanges[j].start + 1;

                // check if we fit
                if(neededSpace <= spaceSize) {
                    // we fit
                    fileRanges[i].start = spaceRanges[j].start;
                    fileRanges[i].end = spaceRanges[j].start + neededSpace - 1;

                    // adjust space range
                    spaceRanges[j].start += neededSpace;
                    break;
                }
            }
        }

        calcSolution(fileRanges, fileRangeSize, secondSolution);

        // close file
        fclose(file);
    } else {
        printf("Unable to open file!\n");
        return 1;
    }

    printf("First Solution: %lu\n", *firstSolution);
    printf("Second Solution: %lu\n", *secondSolution);
    return 0;
}