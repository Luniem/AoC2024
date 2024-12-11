#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

typedef struct {
    uint32_t start;
    uint32_t end;
    uint16_t id;
} FileRange;

int calcSolution(int index, int id) {
    // printf("Index: %d, ID: %d\n", index, id);
    return index * id;
}

int main() {
    FILE* file = fopen("./input.txt", "r");

    uint64_t solution = 0;

    // file will be null if it cannot be opened
    if (file != NULL) {
        // buffer for line
        char line[30001];

        // read line into buffer
        fgets(line, sizeof(line), file);

        int currentIndex = 0;
        int fileRangeSize = 0;
        FileRange *fileRanges = (FileRange *)malloc(fileRangeSize * sizeof(FileRange));

        int spaceRangeSize = 0;
        FileRange *spaceRanges = (FileRange *)malloc(spaceRangeSize * sizeof(FileRange));
        
        for(int i = 0; i < strlen(line); i++) {
            int length = line[i] - '0';
            if(length > 0) {

            if(i % 2 == 0) {
                // even number - it is a file
                fileRanges = (FileRange *)realloc(fileRanges, sizeof(FileRange) * ++fileRangeSize);

                fileRanges[fileRangeSize - 1].start = currentIndex;
                fileRanges[fileRangeSize - 1].end = currentIndex + length - 1;
                fileRanges[fileRangeSize - 1].id = fileRangeSize - 1;
            } else {

                // odd number - its empty space
                spaceRanges = (FileRange *)realloc(spaceRanges, sizeof(FileRange) * ++spaceRangeSize);

                spaceRanges[spaceRangeSize - 1].start = currentIndex;
                spaceRanges[spaceRangeSize - 1].end = currentIndex + length - 1;
                // we dont need to care for id here
            }

            }
            currentIndex += length;
        }
        
        // reorder elements to the right
        // we start with the most right file and shift it into the most left places
        // we then can just append it to the array
        for (int i = fileRangeSize - 1; i >= 0; i--) {
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
                    fileRanges = (FileRange *)realloc(fileRanges, sizeof(FileRange) * ++fileRangeSize);
                    fileRanges[fileRangeSize-1].id = fileRanges[i].id;
                    fileRanges[fileRangeSize-1].start = spaceStart;
                    fileRanges[fileRangeSize-1].end = spaceStart + usingSpace - 1;

                    // push start of file-range by the amount of used space
                    fileRanges[i].end -= usingSpace;

                    // subtract available space from needed space
                    neededSpace -= usingSpace;

                    // remove space range from array if it is fully used else just adjust the start
                    if (usingSpace == spaceSize) {
                        for (int j = 0; j < spaceRangeSize - 1; j++) {
                            spaceRanges[j] = spaceRanges[j + 1];
                        }
                        spaceRangeSize--;
                    } else {
                        spaceRanges[0].start += usingSpace;
                    }
                }
            }
        }

        // loop over all file ranges and calculate the solution
        for (int i = 0; i < fileRangeSize; i++) {
            for (int j = fileRanges[i].start; j <= fileRanges[i].end; j++) {
                solution += calcSolution(j, fileRanges[i].id);
            }
        }

        // close file
        fclose(file);
    } else {
        printf("Unable to open file!\n");
        return 1;
    }


    printf("Solution: %lu\n", solution);
    return 0;
}