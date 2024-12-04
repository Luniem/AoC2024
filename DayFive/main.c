#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* file = fopen("input.txt", "r");

    // char array for line
    char line[5000];

    // file will be null if it cannot be opened
    if (file != NULL) {
        // 
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }

        // close file
        fclose(file);
    } else {
        printf("Unable to open file!\n");
        return 1;
    }

    return 0;
}