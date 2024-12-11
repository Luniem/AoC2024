#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

typedef struct {
    uint16_t start;
    uint16_t end;
    uint32_t id;
} FileRange;

int calcSolution(int index, int id) {
    printf("Index: %d, ID: %d\n", index, id);
    return index * id;
}

int main() {
    FILE* file = fopen("./input.txt", "r");

    int solution = 0;

    // file will be null if it cannot be opened
    if (file != NULL) {
        // buffer for line
        char line[20001];

        // read line into buffer
        fgets(line, sizeof(line), file);

        int currentIndex = 0;
        int rangesSize = 0;
        FileRange *ranges = (FileRange *)malloc(rangesSize * sizeof(FileRange));
        
        for(int i = 0; i < strlen(line); i++) {
            int length = line[i] - '0';
            if(i % 2 == 0) {
                // even number - it is a file
                ranges = (FileRange *)realloc(ranges, sizeof(FileRange) * ++rangesSize);

                ranges[rangesSize - 1].start = currentIndex;
                ranges[rangesSize - 1].end = currentIndex + length - 1;
                ranges[rangesSize - 1].id = rangesSize - 1;
            }

            currentIndex += length;
        }

        int lastUsedFreeIndex = ranges[0].end;

        // go from behind 
        for (int i = rangesSize - 1; i >= 0; i--)
        {
            if(lastUsedFreeIndex > ranges[i].end) {
                // already completely placed
                // we dont need to move and just need to add
                for(int j = ranges[i].start; j <= ranges[i].end; j++) {
                    solution += calcSolution(j, ranges[i].id);
                }
            }else {
                // we can shift it into another place
                int spaceLeftToPlace = ranges[i].end - ranges[i].start + 1;
                // check if we still have to place something
                while(spaceLeftToPlace > 0){
                    // search how much free space until next file
                    for(int x = 0; x < rangesSize; x++) {


                        if(ranges[x].start > lastUsedFreeIndex) {
                            if(ranges[x].id != ranges[i].id) {

                                // go until next file
                                for (int j = lastUsedFreeIndex + 1; j < ranges[x].start && spaceLeftToPlace > 0; j++)
                                {
                                    solution += calcSolution(j, ranges[i].id);
                                    spaceLeftToPlace--;
                                    lastUsedFreeIndex = j;
                                }

                                // set last used free index to the end of the file
                                if(spaceLeftToPlace > 0) {
                                    lastUsedFreeIndex = ranges[x].end;
                                }
                            } else {

                                for(int j = lastUsedFreeIndex + 1; j <= lastUsedFreeIndex + spaceLeftToPlace + 1 && spaceLeftToPlace > 0; j++) {
                                    solution += calcSolution(j, ranges[i].id);
                                    spaceLeftToPlace--;
                                    lastUsedFreeIndex = j;
                                }
                            }
                        }
                    }

                }

                // remove out of list
                ranges[i].start = -1;
                ranges[i].end = -1;
            }
        }

    printf("%d\n", solution);

        // close file
        fclose(file);
    } else {
        printf("Unable to open file!\n");
        return 1;
    }

    return 0;
}