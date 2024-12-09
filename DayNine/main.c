#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

// TODO: perhaps 32 bit is not enough here?
typedef struct {
    uint32_t start;
    uint32_t end;
} Range;

int main() {
    FILE* file = fopen("./input.txt", "r");

    int solution = 0;

    // file will be null if it cannot be opened
    if (file != NULL) {
        // buffer for line
        char line[20001];

        // read line into buffer
        fgets(line, sizeof(line), file);

        uint64_t sum = 0;
        for(int i = 0; i < strlen(line); i++) {
            printf("Char: %c\n", line[i]);
            int number = strtol(line[i]);
            printf("Number: %d\n", number);

            sum = sum + number;
        }

        printf("Number: %" PRIu64 "\n", sum);

        // close file
        fclose(file);
    } else {
        printf("Unable to open file!\n");
        return 1;
    }

    return solution;
}