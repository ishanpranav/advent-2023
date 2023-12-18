// Licensed under the MIT License.

// If You Give A Seed A Fertilizer Part 1

#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define BUFFER_SIZE 256
#define DELIMITERS " "
#define LIST_CAPACITY 32
#define RANGES_CAPACITY 64

struct Range
{
    long long destinationOffset;
    long long sourceOffset;
    long long length;
};

struct Function
{
    struct Range ranges[RANGES_CAPACITY];
    int count;
};

struct List
{
    long long items[LIST_CAPACITY];
    int count;
};

typedef const void* Object;
typedef char* String;
typedef struct Function* Function;
typedef struct List* List;

int range_compare(Object left, Object right)
{
    if (!left && !right)
    {
        return 0;
    }

    if (!left)
    {
        return -1;
    }

    if (!right)
    {
        return 1;
    }

    long long leftOffset = ((const struct Range*)left)->sourceOffset;
    long long rightOffset = ((const struct Range*)right)->sourceOffset;

    if (leftOffset < rightOffset)
    {
        return -1;
    }

    if (leftOffset > rightOffset)
    {
        return 1;
    }

    return 0;
}

void function(Function instance)
{
    instance->count = 0;
}

void function_add_range(Function instance, struct Range item)
{
    instance->ranges[instance->count] = item;
    instance->count++;
}

void function_sort_ranges(Function instance)
{
    qsort(
        instance->ranges,
        instance->count,
        sizeof(struct Range),
        range_compare);
}

void function_clear_ranges(Function instance)
{
    instance->count = 0;
}

void list(List instance)
{
    instance->count = 0;
}

void list_add(List instance, long long item)
{
    instance->items[instance->count] = item;
    instance->count++;
}

static struct Range* search(Function function, long long value)
{
    struct Range* lo = function->ranges;
    struct Range* hi = lo + function->count - 1;

    while (lo <= hi)
    {
        struct Range* current = lo + ((hi - lo) / 2);
        long long other = current->sourceOffset;

        if (other == value)
        {
            return current;
        }

        if (other > value)
        {
            hi = current - 1;
        }
        else
        {
            lo = current + 1;
        }
    }

    return hi;
}

static void realize(Function function, List seeds)
{
    if (function->count == 0)
    {
        return;
    }

    function_sort_ranges(function);

    for (long long* p = seeds->items; p < seeds->items + seeds->count; p++)
    {
        long long input = *p;
        struct Range* range = search(function, input);
        long long offset = range->sourceOffset;

        if (input >= offset && input < offset + range->length)
        {
            *p = input - offset + range->destinationOffset;
        }
    }

    function_clear_ranges(function);
}

static bool read(Function function, char buffer[])
{
    String token = strtok(buffer, DELIMITERS);

    if (!token)
    {
        return false;
    }

    struct Range range;

    range.destinationOffset = atoll(token);
    token = strtok(NULL, DELIMITERS);

    if (!token)
    {
        return false;
    }

    range.sourceOffset = atoll(token);
    token = strtok(NULL, DELIMITERS);

    if (!token)
    {
        return false;
    }

    range.length = atoll(token);

    function_add_range(function, range);

    return true;
}

int main(int count, String args[])
{
    if (count != 2)
    {
        printf("Usage: day05a <path>\n");

        return 1;
    }

    FILE* stream = fopen(args[1], "r");

    if (!stream)
    {
        fprintf(stderr, "Error: I/O.\n");

        return 1;
    }

    char buffer[BUFFER_SIZE];
    clock_t start = clock();

    if (!fgets(buffer, sizeof buffer, stream) || !strtok(buffer, DELIMITERS))
    {
        fclose(stream);
        fprintf(stderr, "Error: Format.\n");

        return 1;
    }

    String token;
    struct List seeds;
    struct Function current;

    list(&seeds);
    function(&current);

    while ((token = strtok(NULL, DELIMITERS)))
    {
        list_add(&seeds, atoll(token));
    }

    while (fgets(buffer, sizeof buffer, stream))
    {
        if (buffer[0] == '\n')
        {
            continue;
        }

        if (strchr(buffer, ':'))
        {
            realize(&current, &seeds);

            continue;
        }

        read(&current, buffer);
    }

    realize(&current, &seeds);

    long long min = LLONG_MAX;
    
    for (long long* p = seeds.items; p < seeds.items + seeds.count; p++)
    {
        long long value = *p;

        if (value < min)
        {
            min = value;
        }
    }

    printf("%lld : %lf\n", min, (double)(clock() - start) / CLOCKS_PER_SEC);
    fclose(stream);
}
