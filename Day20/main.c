#include <inttypes.h>
#include <stdio.h>
#include <string.h>

int main() {
    FILE* file = fopen("testInput.txt", "r");

    int solution = 0;

    if (file != NULL) {
        char line[100];

        while (fgets(line, sizeof(line), file)) {
            // remove newline character
            line[strcspn(line, "\n")] = '\0';

            // if first character is string-terminator, then it is an empty line
            if (line[0] == '\0') {
                continue;
            } 
            
            printf("%s\n", line);
        }

        // close file
        fclose(file);
    } else {
        printf("Unable to open file!\n");
        return 1;
    }
}