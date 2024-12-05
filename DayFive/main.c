#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>

typedef struct {
    int16_t leftNumber;
    int16_t rightNumber;
} orderRule;

int findIndexOrderNumber(orderRule *array, int length, int16_t leftNumber, int16_t rightNumber) {
    for (int i = 0; i < length; i++) {
        if (array[i].leftNumber == leftNumber && array[i].rightNumber == rightNumber) {
            return i;
        }
    }

    return -1;
}

// bubble sort through list
void sortBasedOnOrderRules(int16_t *array, int length, orderRule *orderArray, int orderArraySize) {
    for (int i = length - 1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            int currIndex = findIndexOrderNumber(orderArray, orderArraySize, array[j + 1], array[j]);
            if (currIndex >= 0)
            {
                int16_t temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

// find solution based on input file
int findSolution(char *inputFile, bool solveSecondStar){
    FILE* file = fopen(inputFile, "r");

    int solution = 0;

    // file will be null if it cannot be opened
    if (file != NULL) {
        // buffer for line
        char line[100];

        long orderArraySize = 0;
        orderRule *orderArray = (orderRule *)malloc(orderArraySize * sizeof(orderRule));
        
        bool stillProcessingOrderRules = true; 

        while (fgets(line, sizeof(line), file)) {
            // remove newline character
            line[strcspn(line, "\n")] = '\0';

            // if first character is string-terminator, then it is an empty line
            if (line[0] == '\0') {
                stillProcessingOrderRules = false;
                continue;
            } 
            
            if(stillProcessingOrderRules) {
                // order rules
                char *leftNumber, *rightNumber;
    
                // split by seperator
                leftNumber = strtok(line, "|");
                rightNumber = strtok(NULL, "|");

                if(leftNumber == NULL || rightNumber == NULL) {
                    printf("Invalid order rule!\n");
                    return 1;
                }

                int16_t numberOneInt = atoi(leftNumber);
                int16_t numberTwoInt = atoi(rightNumber);

                orderArray = (orderRule *)realloc(orderArray, (++orderArraySize) * sizeof(orderRule));
                orderArray[orderArraySize - 1].leftNumber = numberOneInt;
                orderArray[orderArraySize - 1].rightNumber = numberTwoInt;

            } else {
                int numberArraySize = 0;
                int16_t *numberArray = (int16_t *)malloc(numberArraySize * sizeof(int16_t));

                for (int i = 0; i < strlen(line); i += 3) {
                    char number[3];
                    number[0] = line[i];
                    number[1] = line[i + 1];
                    number[2] = '\0';
                    int16_t numberInt = atoi(number);

                    numberArray = (int16_t *)realloc(numberArray, (++numberArraySize) * sizeof(int16_t));
                    numberArray[numberArraySize - 1] = numberInt;
                }

                bool isCorrect = true;

                for (int i = 0; i < numberArraySize - 1; i++) {
                    int16_t leftNumber = numberArray[i];
                    int16_t rightNumber = numberArray[i + 1];
                    int currIndex = findIndexOrderNumber(orderArray, orderArraySize, rightNumber, leftNumber);

                    if (currIndex >= 0) {
                        isCorrect = false;
                        break;
                    }
                }

                if((!solveSecondStar && isCorrect) || (solveSecondStar && !isCorrect)) {
                    if(solveSecondStar) {
                        sortBasedOnOrderRules(numberArray, numberArraySize, orderArray, orderArraySize);
                    }

                    solution += numberArray[numberArraySize / 2];
                }

                free(numberArray);
            }
        }

        free(orderArray);

        // close file
        fclose(file);
    } else {
        printf("Unable to open file!\n");
        return 1;
    }

    return solution;
}

int main()
{
    char *inputFile = "input.txt";
    int firstSolution = findSolution(inputFile, false);
    int secondSolution = findSolution(inputFile, true);
    printf("First solution: %d\n", firstSolution);
    printf("Second solution: %d\n", secondSolution);
}