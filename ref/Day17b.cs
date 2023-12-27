using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;

namespace Advent;

internal enum Direction
{
    None,
    Vertical,
    Horizontal
}

internal readonly struct Coordinate
{
    public Coordinate(int i, int j, Direction forbidden)
    {
        I = i;
        J = j;
        Forbidden = forbidden;
    }

    public int I { get; }
    public int J { get; }
    public Direction Forbidden { get; }
}

internal sealed class State
{
    public State(uint priority)
    {
        Priority = priority;
        Hi = int.MaxValue;
        Lo = int.MaxValue;
        Left = int.MaxValue;
        Right = int.MaxValue;
    }

    public uint Priority { get; }
    public uint Hi { get; set; }
    public uint Lo { get; set; }
    public uint Left { get; set; }
    public uint Right { get; set; }
}

internal sealed class StateMatrix
{
    private readonly State[,] _items = new State[150, 150];

    public StateMatrix(int columns)
    {
        Columns = columns;
    }

    public State this[int i, int j]
    {
        get
        {
            return _items[i, j];
        }
        set
        {
            _items[i, j] = value;
        }
    }

    public State this[Coordinate coordinate]
    {
        get
        {
            return this[coordinate.I, coordinate.J];
        }
        set
        {
            this[coordinate.I, coordinate.J] = value;
        }
    }

    public int Rows { get; private set; }
    public int Columns { get; private set; }

    public void AddRow()
    {
        Rows++;
    }
}

internal static class Program
{
    public const int Min = 4;
    public const int Max = 10;

    private static void Main()
    {
        using StreamReader reader = File.OpenText("mini.txt");

        Stopwatch stopwatch = Stopwatch.StartNew();

        uint result = Run(reader);

        stopwatch.Stop();
        Console.WriteLine("17a {0} {1}", result, stopwatch.Elapsed.TotalSeconds);
    }

    private static void ScanHi(StateMatrix matrix, Coordinate current, PriorityQueue<Coordinate, uint> coordinates)
    {
        State initialState = matrix[current];

        int j = current.J;
        uint priority = Math.Min(initialState.Left, initialState.Right);

        for (int k = 1; k <= Max; k++)
        {
            int i = current.I - k;

            if (i < 0)
            {
                return;
            }

            State currentState = matrix[i, j];

            priority += currentState.Priority;

            if (k < Min || currentState.Lo <= priority)
            {
                continue;
            }

            currentState.Lo = priority;

            coordinates.Enqueue(new Coordinate(i, j, Direction.Vertical), priority);
        }
    }

    private static void ScanLo(StateMatrix matrix, Coordinate current, PriorityQueue<Coordinate, uint> coordinates)
    {
        State initialState = matrix[current];

        int j = current.J;
        uint priority = Math.Min(initialState.Left, initialState.Right);

        for (int k = 1; k <= Max; k++)
        {
            int i = current.I + k;

            if (i >= matrix.Rows)
            {
                return;
            }

            State currentState = matrix[i, j];

            priority += currentState.Priority;

            if (k < Min || currentState.Hi <= priority)
            {
                continue;
            }

            currentState.Hi = priority;

            coordinates.Enqueue(new Coordinate(i, j, Direction.Vertical), priority);
        }
    }

    private static void ScanLeft(StateMatrix matrix, Coordinate current, PriorityQueue<Coordinate, uint> coordinates)
    {
        State initialState = matrix[current];

        int i = current.I;
        uint priority = Math.Min(initialState.Hi, initialState.Lo);

        for (int k = 1; k <= Max; k++)
        {
            int j = current.J - k;

            if (j < 0)
            {
                return;
            }

            State currentState = matrix[i, j];

            priority += currentState.Priority;

            if (k < Min || currentState.Right <= priority)
            {
                continue;
            }

            currentState.Right = priority;

            coordinates.Enqueue(new Coordinate(i, j, Direction.Horizontal), priority);
        }
    }

    private static void ScanRight(StateMatrix matrix, Coordinate current, PriorityQueue<Coordinate, uint> coordinates)
    {
        State initialState = matrix[current];

        int i = current.I;
        uint priority = Math.Min(initialState.Hi, initialState.Lo);

        for (int k = 1; k <= Max; k++)
        {
            int j = current.J + k;

            if (j >= matrix.Columns)
            {
                return;
            }

            State currentState = matrix[i, j];

            priority += currentState.Priority;

            if (k < Min || currentState.Left <= priority)
            {
                continue;
            }

            currentState.Left = priority;

            coordinates.Enqueue(new Coordinate(i, j, Direction.Horizontal), priority);
        }
    }

    private static uint Run(StreamReader reader)
    {
        string? line = reader.ReadLine();

        if (line == null)
        {
            throw new FormatException();
        }

        StateMatrix matrix = new StateMatrix(line.Length);

        do
        {
            matrix.AddRow();

            for (int j = 0; j < line.Length; j++)
            {
                matrix[matrix.Rows - 1, j] = new State((uint)(line[j] - '0'));
            }
        }
        while ((line = reader.ReadLine()) != null);

        State initial = matrix[0, 0];

        initial.Hi = 0;
        initial.Lo = 0;
        initial.Left = 0;
        initial.Right = 0;

        PriorityQueue<Coordinate, uint> coordinates = new PriorityQueue<Coordinate, uint>();

        coordinates.Enqueue(new Coordinate(0, 0, Direction.None), 0);

        while (coordinates.TryDequeue(out Coordinate current, out _))
        {
            if (current.Forbidden != Direction.Vertical)
            {
                ScanHi(matrix, current, coordinates);
                ScanLo(matrix, current, coordinates);
            }

            if (current.Forbidden != Direction.Horizontal)
            {
                ScanLeft(matrix, current, coordinates);
                ScanRight(matrix, current, coordinates);
            }
        }

        State finalState = matrix[matrix.Rows - 1, matrix.Columns - 1];
        uint min = target.Hi;

        if (finalState.Lo < min)
        {
            min = target.Lo;
        }

        if (finalState.Left < min)
        {
            min = finalState.Left;
        }

        if (finalState.Right < min)
        {
            min = finalState.Right;
        }

        return min;
    }
}