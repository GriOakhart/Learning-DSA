//
// Created by jason on 6/25/25.
//

#include <iostream>
#include "LinkedStack.h"

int getIndex(int row, int col);

namespace Setting
{
    constexpr int kMazeSizeRow { 10 };
    constexpr int kMazeSizeCol { 10 };

    enum Direction { null = 0, east, south, west, north, MAX_DIRECTION };
    Direction operator++(Direction& dir)
    {
        if (dir == Direction::MAX_DIRECTION) return dir;
        dir = static_cast<Direction>((dir + 1));
        return dir;
    }
    struct Position
    {
        int row {};
        int col {};
        Direction dir {};
    };
    constexpr Position direction[MAX_DIRECTION]
    {
        Position { 0, 0 },
        Position { 0, 1 },
        Position { 1, 0 },
        Position { 0, -1 },
        Position { -1, 0 }
    };
    Position operator+(const Position& lhs, const Position& rhs)
    {
        return Position { lhs.row + rhs.row, lhs.col + rhs.col };
    }
    bool operator==(const Position& lhs, const Position& rhs)
    {
        return lhs.row == rhs.row && lhs.col == rhs.col;
    }
    bool operator!=(const Position& lhs, const Position& rhs)
    {
        return !(lhs == rhs);
    }
}

int getIndex(int row, int col)
{
    return row * Setting::kMazeSizeCol + col;
}

void printMaze(int maze[], int sizeRow, int sizeCol)
{
    for (int row { 0 }; row < sizeRow; ++row)
    {
        for (int col { 0 }; col < sizeCol; ++col)
        {
            switch (maze[getIndex(row, col)])
            {
                case 0: std::cout << ".."; break;
                case 1: std::cout << "##"; break;
                case 2: std::cout << "~~"; break;
            }
        }
        std::cout << '\n';
    }
}

int main(int argc, char* argv[])
{
    int maze[Setting::kMazeSizeRow * Setting::kMazeSizeCol]
    {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 1, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 1, 0, 1, 1, 1, 1, 0, 1,
        1, 0, 1, 0, 0, 0, 0, 1, 0, 1,
        1, 0, 1, 1, 1, 1, 0, 1, 0, 1,
        1, 0, 0, 0, 0, 1, 0, 0, 0, 1,
        1, 1, 1, 1, 0, 1, 0, 1, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 1, 0, 1,
        1, 0, 1, 1, 1, 1, 1, 1, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    };
    printMaze(maze, Setting::kMazeSizeRow, Setting::kMazeSizeCol);
    Setting::Position start { 1, 1 };
    Setting::Position end { Setting::kMazeSizeRow - 2, Setting::kMazeSizeCol - 2 };
    auto currentPos { start };

    LinkedStack<Setting::Position> path;
    Setting::Direction dir { Setting::Direction::east };
    while (currentPos != end)
    {
        // find any legal move by this order:
        // east -> south -> west -> north
        while (dir < Setting::Direction::MAX_DIRECTION)
        {
            auto nextPos { currentPos + Setting::direction[dir] };
            // found legal move
            if (maze[getIndex(nextPos.row, nextPos.col)] == 0)
            {
                // record and push the direction first
                currentPos.dir = dir;
                path.push(currentPos);
                // mark the path as moved
                maze[getIndex(currentPos.row, currentPos.col)] = 2;
                // move ahead
                currentPos = nextPos;
                // reset dir
                dir = Setting::Direction::east;
                break;
            }
            ++dir;
        }

        // no legal move in the current position
        if (dir == Setting::Direction::MAX_DIRECTION)
        {
            do
            {
                if (path.empty())
                {
                    std::cout << "no solution!\n";
                    return 1;
                }
                currentPos = path.pop().value();
                maze[getIndex(currentPos.row, currentPos.col)] = 0;
            } while (currentPos.dir == Setting::Direction::north);
            // north is the last direction to check, so
            // when dir is north, there will be no more choice
            dir = static_cast<Setting::Direction>(currentPos.dir + 1);
        }
    }
    // push and mark the endpoint
    path.push(currentPos);
    maze[getIndex(currentPos.row, currentPos.col)] = 2;
    std::cout << "found solution!\n";
    printMaze(maze, Setting::kMazeSizeRow, Setting::kMazeSizeCol);
    return 0;
}

