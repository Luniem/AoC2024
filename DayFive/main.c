#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>

typedef struct {
    int16_t number;
    int16_t rightAppearances;
} orderNumber;

int findIndexOrderNumber(orderNumber *array, int length, int value) {
    for (int i = 0; i < length; i++) {
        if (array[i].number == value) {
            return i;
        }
    }

    return -1;
}

int findAppearances(int16_t *array, int length, int value) {
    int appearances = 0;

    for (int i = 0; i < length; i++) {
        if (array[i] == value) {
            appearances++;
        }
    }

    return appearances;
}

// bubble sort through list
void sortOrderArray(orderNumber *array, int length) {
    for (int i = length - 1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (array[j].rightAppearances > array[j + 1].rightAppearances)
            {
                orderNumber temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int main()
{
    FILE* file = fopen("testInput.txt", "r");

    // char array for line
    char line[100];

    int currArraySize = 0;
    int16_t *leftNumberArray = (int16_t *)malloc(currArraySize * sizeof(int16_t));
    int16_t *rightNumberArray = (int16_t *)malloc(currArraySize * sizeof(int16_t));

    long orderArraySize = 0;
    orderNumber *orderArray = (orderNumber *)malloc(orderArraySize * sizeof(orderNumber));

    int firstSolution = 0;

    // file will be null if it cannot be opened
    if (file != NULL) {
        
        bool stillOrderingRules = true; 

        while (fgets(line, sizeof(line), file)) {
            // remove newline character
            line[strcspn(line, "\n")] = '\0';

            // if first character is string-terminator, then it is an empty line
            if (line[0] == '\0') {
                stillOrderingRules = false;

                for (int leftIndex = 0; leftIndex < currArraySize; leftIndex++) {
                    int16_t currNumber = leftNumberArray[leftIndex];

                    bool found = findIndexOrderNumber(orderArray, orderArraySize, currNumber) != -1;

                    if (!found) {
                        orderArray = (orderNumber *)realloc(orderArray, (++orderArraySize) * sizeof(orderNumber));

                        orderArray[orderArraySize - 1].number = currNumber;
                        orderArray[orderArraySize - 1].rightAppearances = findAppearances(rightNumberArray, currArraySize, currNumber);
                    }
                }

                sortOrderArray(orderArray, orderArraySize);
            } else if(stillOrderingRules) {
                // order rules
                char numberOne[3];
                numberOne[0] = line[0];
                numberOne[1] = line[1];
                numberOne[2] = '\0';

                char numberTwo[3];
                numberTwo[0] = line[3];
                numberTwo[1] = line[4];
                numberTwo[2] = '\0';

                int16_t numberOneInt = atoi(numberOne);
                int16_t numberTwoInt = atoi(numberTwo);

                leftNumberArray = (int16_t *)realloc(leftNumberArray, (++currArraySize) * sizeof(int16_t));
                rightNumberArray = (int16_t *)realloc(rightNumberArray, (currArraySize) * sizeof(int16_t));

                leftNumberArray[currArraySize - 1] = numberOneInt;
                rightNumberArray[currArraySize - 1] = numberTwoInt;
            } else {
                int numberArraySize = 0;
                int16_t *numberArray = (int16_t *)malloc(currArraySize * sizeof(int16_t));

                for (int i = 0; i < strlen(line); i += 3) {
                    char number[3];
                    number[0] = line[i];
                    number[1] = line[i + 1];
                    number[2] = '\0';
                    int16_t numberInt = atoi(number);

                    numberArray = (int16_t *)realloc(numberArray, (++numberArraySize) * sizeof(int16_t));
                    numberArray[numberArraySize - 1] = numberInt;
                }

                int prevIndex = -1;
                bool isCorrect = true;

                for (int i = 0; i < numberArraySize; i++) {
                    int currNumber = numberArray[i];
                    int currIndex = findIndexOrderNumber(orderArray, numberArraySize, currNumber);

                    if (currIndex >= 0 && currIndex < prevIndex) {
                        isCorrect = false;
                        printf("Order is incorrect!\n");
                        break;
                    }

                    prevIndex = currIndex;
                }

                if (isCorrect) {
                    firstSolution++;
                }

                free(numberArray);
            }
        }

        // close file
        fclose(file);
    } else {
        printf("Unable to open file!\n");
        return 1;
    }

    printf("First solution: %d\n", firstSolution);

    return 0;
}