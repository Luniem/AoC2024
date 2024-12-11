#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

typedef struct {
    uint16_t start;
    uint16_t end;
    uint8_t id;
} FileRange;

int main() {
    FILE* file = fopen("./input.txt", "r");

    int solution = 0;

    // file will be null if it cannot be opened
    if (file != NULL) {
        // buffer for line
        char line[20001];

        // read line into buffer
        fgets(line, sizeof(line), file);

        int rangesSize = 0;
        FileRange *ranges = (FileRange *)malloc(rangesSize * sizeof(FileRange));

        int currentIndex = 0;
        for(int i = 0; i < strlen(line); i++) {
            printf("Index: %d\n", i);
            int length = line[i] - '0';
            if(i % 2 == 0) {
                // even -- file
                printf("Even %d\n", rangesSize);

                ranges = (FileRange *)realloc(ranges, sizeof(FileRange) * ++rangesSize);
                printf("after malloc");
                ranges[currentIndex].start = currentIndex;
                ranges[currentIndex].end = length - 1;
                ranges[currentIndex].id = rangesSize - 1;
            }
            currentIndex += length;
        }

        printf("Ranges: %d\n", rangesSize);

        // close file
        fclose(file);
    } else {
        printf("Unable to open file!\n");
        return 1;
    }

    return solution;
}