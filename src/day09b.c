// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav. All rights reserved.
// Licensed under the MIT License.

// Custom implementation using Lagrange interpolation

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define BUFFER_SIZE 128
#define DELIMITERS " "
#define TERMS_CAPACITY 32

struct Series
{
    long terms[TERMS_CAPACITY];
    int n;
};

typedef char* String;
typedef struct Series* Series;

void series(Series instance)
{
    instance->n = 0;
}

void series_add(Series instance, long term)
{
    int n = instance->n;

    instance->terms[n] = term;
    instance->n = n + 1;
}

long series_lagrange_extrapolate(Series instance, int k)
{
    double sum = 0;
    long n = instance->n;

    for (int j = 0; j < n; j++)
    {
        double product = instance->terms[j];

        for (int i = 0; i < j; i++)
        {
            product *= (double)(k - i) / (j - i);
        }

        for (int i = j + 1; i < n; i++)
        {
            product *= (double)(k - i) / (j - i);
        }

        sum += product;
    }

    return round(sum);
}

long series_lagrange_next(Series instance)
{
    return series_lagrange_extrapolate(instance, instance->n);
}

int main(int count, String args[])
{
    if (count != 2)
    {
        printf("Usage: day9a <path>\n");

        return 1;
    }

    FILE* stream = fopen(args[1], "r");

    if (!stream)
    {
        fprintf(stderr, "Error: I/O.\n");

        return 1;
    }

    long sum = 0;
    char buffer[BUFFER_SIZE];
    clock_t start = clock();

    while (fgets(buffer, sizeof buffer, stream))
    {
        String token = strtok(buffer, DELIMITERS);

        if (!token)
        {
            fclose(stream);
            fprintf(stderr, "Error: Format.\n");

            return 1;
        }

        struct Series terms;

        series(&terms);

        do
        {
            series_add(&terms, atol(token));
        }
        while ((token = strtok(NULL, DELIMITERS)));

        sum += series_lagrange_next(&terms);
    }

    printf("%ld : %lf\n", sum, (double)(clock() - start) / CLOCKS_PER_SEC);
    fclose(stream);

    return 0;
}
