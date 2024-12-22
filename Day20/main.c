#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

typedef struct {
    uint16_t x;
    uint16_t y;
    void* prev;
    uint32_t cost;
} Node;

int getManhattanDistance(Node* a, Node* b) {
    return abs(a->x - b->x) + abs(a->y - b->y);
}

bool isInManhattanDistance(Node* a, Node* b, int distance) {
    return getManhattanDistance(a,b) <= distance;
}

void resolveDijkstra(Node** nodes, int nodesSize, Node* start) {
    // set start to zero cost
    start->cost = 0;
    int queueSize = 1;
    Node** queue = malloc(sizeof(Node**) * queueSize);
    queue[0] = start;

    while (queueSize > 0) {
        // pop first element
        Node* current = queue[0];
        for (int i = 0; i < queueSize - 1; i++) {
            queue[i] = queue[i + 1];
        }
        queueSize--;

        // check neighbours of current
        for (int i = 0; i < nodesSize; i++) {
            Node* neighbour = nodes[i];
            if (neighbour->x == current->x && neighbour->y == current->y) {
                // same one
                continue;
            }

            if (neighbour->x == current->x && neighbour->y == current->y - 1) {
                // up
                if (neighbour->cost > current->cost + 1) {
                    neighbour->cost = current->cost + 1;
                    neighbour->prev = current;
                    *queue = realloc(queue, sizeof(Node) * (++queueSize));
                    queue[queueSize - 1] = neighbour;
                }
            } else if (neighbour->x == current->x && neighbour->y == current->y + 1) {
                // down
                if (neighbour->cost > current->cost + 1) {
                    neighbour->cost = current->cost + 1;
                    neighbour->prev = current;
                    *queue = realloc(queue, sizeof(Node) * (++queueSize));
                    queue[queueSize - 1] = neighbour;
                }
            } else if (neighbour->x == current->x - 1 && neighbour->y == current->y) {
                // left
                if (neighbour->cost > current->cost + 1) {
                    neighbour->cost = current->cost + 1;
                    neighbour->prev = current;
                    *queue = realloc(queue, sizeof(Node) * (++queueSize));
                    queue[queueSize - 1] = neighbour;
                }
            } else if (neighbour->x == current->x + 1 && neighbour->y == current->y) {
                // right
                if (neighbour->cost > current->cost + 1) {
                    neighbour->cost = current->cost + 1;
                    neighbour->prev = current;
                    *queue = realloc(queue, sizeof(Node) * (++queueSize));
                    queue[queueSize - 1] = neighbour;
                }
            }
        }
    }
}

int main() {
    FILE* file = fopen("input.txt", "r");

    int startX = 0;
    int startY = 0;
    int endX = 0;
    int endY = 0;

    int firstSolution = 0;
    int secondSolution = 0;

    int nodesSize = 0;
    Node** nodes = malloc(sizeof(Node**) * nodesSize);

    int y = 0;
    if (file != NULL) {
        char line[200];

        while (fgets(line, sizeof(line), file)) {
            // remove newline character
            line[strcspn(line, "\n")] = '\0';

            // if first character is string-terminator, then it is an empty line
            if (line[0] == '\0') {
                continue;
            } 

            for (int i = 0; i < strlen(line); i++) {
                char c = line[i];
                if (c == '#') {
                    continue;
                }

                nodes = realloc(nodes, sizeof(Node**) * (++nodesSize));
                Node* node = malloc(sizeof(Node));
                node->x = i;
                node->y = y;
                node->prev = NULL;
                node->cost = UINT32_MAX;
                nodes[nodesSize - 1] = node;

                if (c == 'S') {
                    startX = i;
                    startY = y;
                } else if (c == 'E') {
                    endX = i;
                    endY = y;
                }
            }
            y++;
        }

        // close file
        fclose(file);
    } else {
        printf("Unable to open file!\n");
        return 1;
    }

    // find start 
    Node* start = NULL;
    Node* end = NULL;

    for (int i = 0; i < nodesSize; i++) {
        Node* node = nodes[i];
        if (node->x == startX && node->y == startY) {
            start = node;
            continue;
        }

        if (node->x == endX && node->y == endY) {
            end = node;
            continue;
        }
    }

    resolveDijkstra(nodes, nodesSize, start);

    for (int i = 0; i < nodesSize; i++) {
        Node* startNode = nodes[i];
        for(int j = i + 1; j < nodesSize; j++) {
            Node* node = nodes[j];
            if(node != startNode) {
                if(isInManhattanDistance(node, startNode, 2)){
                    int saved = abs(startNode->cost - node->cost) - getManhattanDistance(startNode, node);
                    if(saved >= 100) {
                        firstSolution++;
                    }
                }

                if(isInManhattanDistance(node, startNode, 20)) {
                    int saved = abs(startNode->cost - node->cost) - getManhattanDistance(startNode, node);
                    if(saved >= 100) {
                        secondSolution++;
                    }
                }
            }

        }
    }

    printf("First solution: %d\n", firstSolution);
    printf("Second solution: %d\n", secondSolution);
}