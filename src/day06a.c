// Licensed under the MIT License.

// Wait For It Part 1

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define BUFFER_SIZE 64
#define DELIMITERS " "
#define POINTS_CAPACITY 4

struct Point
{
    int time;
    int distance;
};

typedef char* String;

int main()
{
    String token;
    char buffer[BUFFER_SIZE];
    clock_t start = clock();

    if (!fgets(buffer, sizeof buffer, stdin) || !strtok(buffer, DELIMITERS))
    {
        fprintf(stderr, "Error: Format.\n");

        return 1;
    }

    int pointCount = 0;
    struct Point points[POINTS_CAPACITY];

    while ((token = strtok(NULL, DELIMITERS)))
    {
        points[pointCount].time = atoi(token);
        pointCount++;
    }

    if (!fgets(buffer, sizeof buffer, stdin) || !strtok(buffer, DELIMITERS))
    {
        fprintf(stderr, "Error: Format.\n");

        return 1;
    }

    for (int i = 0; i < pointCount; i++)
    {
        token = strtok(NULL, DELIMITERS);

        if (!token)
        {
            fprintf(stderr, "Error: Format.\n");

            return 1;
        }

        points[i].distance = atoi(token);
    }

    long product = 1;

    for (int i = 0; i < pointCount; i++)
    {
        int t = points[i].time;
        int dx = points[i].distance;

        product *= ceil((t + sqrt(t * t - 4 * dx)) / 2)
            - floor((t - sqrt(t * t - 4 * dx)) / 2)
            - 1;
    }

    printf("%ld : %lf\n", product, (double)(clock() - start) / CLOCKS_PER_SEC);

    return 0;
}
