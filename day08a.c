// Author: Ishan Pranav
// Copyright (c) 2023 Ishan Pranav. All rights reserved.
// Licensed under the MIT License.

// Custom implementation
// Graph: use base-36 encoding to index into a hashtable

// The best case is ~47%-fragmented memory but takes less time and complexity
// than a dynamic hash table

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define BUFFER_SIZE 32
#define DIRECTIONS_CAPACITY 512
#define DIRECTION_LEFT 'L'
#define DIRECTION_RIGHT 'R'
#define VERTEX_OFFSET -13330
#define VERTEX_FIRST 0
#define VERTEX_LAST 33325

struct VertexPair
{
    int left;
    int right;
};

struct Graph
{
    struct VertexPair vertices[VERTEX_LAST + 1];
};

typedef char* String;
typedef int Vertex;
typedef char Direction;
typedef struct Graph* Graph;
typedef bool (*Predicate)(Vertex vertex);

void graph_add(Graph instance, Vertex vertex, Vertex left, Vertex right)
{
    instance->vertices[vertex].left = left;
    instance->vertices[vertex].right = right;
}

int graph_walk(
    Graph instance, 
    Vertex start, 
    Direction directions[], 
    Predicate predicate)
{
    int result = 0;
    Direction* direction = directions;

    while (!predicate(start))
    {
        switch (*direction)
        {
        case DIRECTION_LEFT:
            start = instance->vertices[start].left;
            direction++;
            result++;
            break;
        case DIRECTION_RIGHT:
            start = instance->vertices[start].right;
            direction++;
            result++;
            break;
        default:
            direction = directions;
            break;
        }
    }

    return result;
}

static bool parse(char buffer[], char window[], Vertex* result)
{
    memcpy(window, buffer, 3);

    window[3] = '\0';

    Vertex vertex = strtol(window, NULL, 36) + VERTEX_OFFSET;

    if (vertex < 0)
    {
        return false;
    }

    *result = vertex;

    return true;
}

static bool read(FILE* stream, Graph graph)
{
    int total = 0;
    char buffer[BUFFER_SIZE];

    if (!fgets(buffer, BUFFER_SIZE, stream))
    {
        return false;
    }

    while (fgets(buffer, BUFFER_SIZE, stream))
    {
        char window[4];
        Vertex vertex;
        Vertex left;
        Vertex right;

        if (strlen(buffer) < 16 ||
            !parse(buffer, window, &vertex) ||
            !parse(buffer + 7, window, &left) ||
            !parse(buffer + 12, window, &right))
        {
            return false;
        }

        graph_add(graph, vertex, left, right);
    }

    return true;
}

static bool stop(Vertex vertex)
{
    return vertex == VERTEX_LAST;
}

int main(int count, String args[])
{
    if (count != 2)
    {
        printf("Usage: day8a <path>\n");

        return 1;
    }

    FILE* stream = fopen(args[1], "r");
    clock_t start = clock();

    if (!stream)
    {
        fprintf(stderr, "Error: I/O.\n");

        return 1;
    }

    struct Graph graph;
    Direction directions[DIRECTIONS_CAPACITY];

    if (!fgets(directions, DIRECTIONS_CAPACITY, stream) ||
        !read(stream, &graph))
    {
        fclose(stream);
        fprintf(stderr, "Error: Format.\n");

        return 1;
    }

    printf("%d : %lf\n",
        graph_walk(&graph, VERTEX_FIRST, directions, stop),
        (double)(clock() - start) / CLOCKS_PER_SEC);
    fclose(stream);

    return 0;
}
