//
// Created by jason on 6/25/25.
//

#include <iostream>
#include "LinkedStack.h"

class Position
{
public:
    enum Direction { null = 0, east, south, west, north, MAX_DIRECTION };

    Position(int row, int col, Direction dir = null)
        : m_row { row }, m_col { col }, m_dir { dir } {}
    const int& row() const { return m_row; }
    const int& col() const { return m_col; }
    const Direction& dir() const { return m_dir; }
    void setDir(Direction dir) { m_dir = dir; }
    friend bool operator==(const Position& lhs, const Position& rhs)
    {
        return lhs.m_row == rhs.m_row && lhs.m_col == rhs.m_col;
    }
    friend bool operator!=(const Position& lhs, const Position& rhs)
    {
        return !(lhs == rhs);
    }
    friend Position operator+(const Position& lhs, const Position& rhs)
    {
        return Position { lhs.m_row + rhs.m_row, lhs.m_col + rhs.m_col, null };
    }
    void move(Direction dir)
    {
        switch (dir)
        {
        case east: m_col += 1; break;
        case south: m_row += 1; break;
        case west: m_col -= 1; break;
        case north: m_row -= 1; break;
        default: break;
        }
    }
private:
    int m_row { 0 };
    int m_col { 0 };
    Direction m_dir { Direction::null };
};

Position::Direction& operator++(Position::Direction& dir)
{
    if (dir == Position::Direction::MAX_DIRECTION) return dir;
    dir = static_cast<Position::Direction>(dir + 1);
    return dir;
}

class Maze
{
public:
    Maze(int sizeRow, int sizeCol)
    try : m_sizeRow { sizeRow }, m_sizeCol { sizeCol }
    {
        if (sizeRow <= 0 || sizeCol <= 0)
            throw std::invalid_argument("sizeRow and sizeCol must be positive");
        m_maze = new int[sizeRow * sizeCol];
    } catch (std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
        throw;
    }
    void clear()
    {
        for (int i { 0 }; i < m_sizeRow * m_sizeCol; ++i)
            m_maze[i] = 0;
    }
    ~Maze() { delete[] m_maze; }
    template <std::size_t N>
    void init(const int (&maze)[N])
    {
        if (N != m_sizeRow * m_sizeCol)
            throw std::invalid_argument("maze size does not match");
        for (int i { 0 }; i < N; ++i)
        {
            if (maze[i] != 0 && maze[i] != 1)
            {
                clear();
                throw std::runtime_error("tile can only be 0 or 1");
            }
            m_maze[i] = maze[i];
        }
    }
    int& operator()(int row, int col)
    {
        return m_maze[row * m_sizeCol + col];
    }
    const int& operator()(int row, int col) const
    {
        return m_maze[row * m_sizeCol + col];
    }
    void mark(const Position& pos)
    {
        (*this)(pos.row(), pos.col()) = 2;
    }
    void unmark(const Position& pos)
    {
        (*this)(pos.row(), pos.col()) = 0;
    }
    void print() const
    {
        for (int row { 0 }; row < m_sizeRow; ++row)
        {
            for (int col { 0 }; col < m_sizeCol; ++col)
            {
                switch ((*this)(row, col))
                {
                case 0: std::cout << ".."; break;
                case 1: std::cout << "##"; break;
                case 2: std::cout << "~~"; break;
                }
            }
            std::cout << '\n';
        }
    }
private:
    int m_sizeRow { 0 };
    int m_sizeCol { 0 };
    int* m_maze { nullptr };
};

class MazeSolver
{
public:
    MazeSolver(Maze& maze, const Position& start, const Position& end)
        : m_maze { maze }, m_start { start }, m_end { end } {}
    bool solve()
    {
        auto currentPos { m_start };
        currentPos.setDir(Position::Direction::east);
        LinkedStack<Position> path;
        while (currentPos != m_end)
        {
            while (currentPos.dir() < Position::Direction::MAX_DIRECTION)
            {
                auto nextPos { currentPos };
                nextPos.move(currentPos.dir());
                if (m_maze(nextPos.row(), nextPos.col()) == 0)
                {
                    path.push(currentPos);
                    m_maze.mark(currentPos);
                    currentPos = nextPos;
                    currentPos.setDir(Position::Direction::east);
                    break;
                }
                auto nextDir = currentPos.dir();
                ++nextDir;
                currentPos.setDir(nextDir);
            }

            if (currentPos.dir() == Position::Direction::MAX_DIRECTION)
            {
                do
                {
                    if (path.empty())
                        return false;
                    currentPos = path.pop().value();
                    m_maze.unmark(currentPos);
                }
                while (currentPos.dir() == Position::Direction::north);
                auto nextDir = static_cast<Position::Direction>(currentPos.dir() + 1);
                currentPos.setDir(nextDir);
            }
        }
        path.push(currentPos);
        m_maze.mark(currentPos);
        return true;
    }
private:
    Maze& m_maze;
    Position m_start;
    Position m_end;
};

int main(int argc, char* argv[])
{
    constexpr int kMazeSizeRow { 10 };
    constexpr int kMazeSizeCol { 10 };
    Maze maze { kMazeSizeRow, kMazeSizeCol };
    maze.init({
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
    });
    maze.print();
    Position start { 1, 1 };
    Position end { kMazeSizeRow - 2, kMazeSizeCol - 2 };
    
    MazeSolver solver { maze, start, end };
    if (solver.solve())
    {
        std::cout << "found solution!\n";
        maze.print();
    }
    else
    {
        std::cout << "no solution!\n";
    }
    return 0;
}


// int getIndex(int row, int col);
//
// namespace Setting
// {
//     constexpr int kMazeSizeRow { 10 };
//     constexpr int kMazeSizeCol { 10 };
//
//     enum Direction { null = 0, east, south, west, north, MAX_DIRECTION };
//     Direction operator++(Direction& dir)
//     {
//         if (dir == Direction::MAX_DIRECTION) return dir;
//         dir = static_cast<Direction>((dir + 1));
//         return dir;
//     }
//     struct Position
//     {
//         int row {};
//         int col {};
//         Direction dir {};
//     };
//     constexpr Position direction[MAX_DIRECTION]
//     {
//         Position { 0, 0 },
//         Position { 0, 1 },
//         Position { 1, 0 },
//         Position { 0, -1 },
//         Position { -1, 0 }
//     };
//     Position operator+(const Position& lhs, const Position& rhs)
//     {
//         return Position { lhs.row + rhs.row, lhs.col + rhs.col };
//     }
//     bool operator==(const Position& lhs, const Position& rhs)
//     {
//         return lhs.row == rhs.row && lhs.col == rhs.col;
//     }
//     bool operator!=(const Position& lhs, const Position& rhs)
//     {
//         return !(lhs == rhs);
//     }
// }
//
// int getIndex(int row, int col)
// {
//     return row * Setting::kMazeSizeCol + col;
// }
//
// void printMaze(int maze[], int sizeRow, int sizeCol)
// {
//     for (int row { 0 }; row < sizeRow; ++row)
//     {
//         for (int col { 0 }; col < sizeCol; ++col)
//         {
//             switch (maze[getIndex(row, col)])
//             {
//                 case 0: std::cout << ".."; break;
//                 case 1: std::cout << "##"; break;
//                 case 2: std::cout << "~~"; break;
//             }
//         }
//         std::cout << '\n';
//     }
// }
//
// int main(int argc, char* argv[])
// {
//     int maze[Setting::kMazeSizeRow * Setting::kMazeSizeCol]
//     {
//         1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//         1, 0, 1, 0, 0, 0, 0, 0, 0, 1,
//         1, 0, 1, 0, 1, 1, 1, 1, 0, 1,
//         1, 0, 1, 0, 0, 0, 0, 1, 0, 1,
//         1, 0, 1, 1, 1, 1, 0, 1, 0, 1,
//         1, 0, 0, 0, 0, 1, 0, 0, 0, 1,
//         1, 1, 1, 1, 0, 1, 0, 1, 0, 1,
//         1, 0, 0, 0, 0, 0, 0, 1, 0, 1,
//         1, 0, 1, 1, 1, 1, 1, 1, 0, 1,
//         1, 1, 1, 1, 1, 1, 1, 1, 1, 1
//     };
//     printMaze(maze, Setting::kMazeSizeRow, Setting::kMazeSizeCol);
//     Setting::Position start { 1, 1 };
//     Setting::Position end { Setting::kMazeSizeRow - 2, Setting::kMazeSizeCol - 2 };
//     auto currentPos { start };
//
//     LinkedStack<Setting::Position> path;
//     Setting::Direction dir { Setting::Direction::east };
//     while (currentPos != end)
//     {
//         // find any legal move by this order:
//         // east -> south -> west -> north
//         while (dir < Setting::Direction::MAX_DIRECTION)
//         {
//             auto nextPos { currentPos + Setting::direction[dir] };
//             // found legal move
//             if (maze[getIndex(nextPos.row, nextPos.col)] == 0)
//             {
//                 // record and push the direction first
//                 currentPos.dir = dir;
//                 path.push(currentPos);
//                 // mark the path as moved
//                 maze[getIndex(currentPos.row, currentPos.col)] = 2;
//                 // move ahead
//                 currentPos = nextPos;
//                 // reset dir
//                 dir = Setting::Direction::east;
//                 break;
//             }
//             ++dir;
//         }
//
//         // no legal move in the current position
//         if (dir == Setting::Direction::MAX_DIRECTION)
//         {
//             do
//             {
//                 if (path.empty())
//                 {
//                     std::cout << "no solution!\n";
//                     return 1;
//                 }
//                 currentPos = path.pop().value();
//                 maze[getIndex(currentPos.row, currentPos.col)] = 0;
//             } while (currentPos.dir == Setting::Direction::north);
//             // north is the last direction to check, so
//             // when dir is north, there will be no more choice
//             dir = static_cast<Setting::Direction>(currentPos.dir + 1);
//         }
//     }
//     // push and mark the endpoint
//     path.push(currentPos);
//     maze[getIndex(currentPos.row, currentPos.col)] = 2;
//     std::cout << "found solution!\n";
//     printMaze(maze, Setting::kMazeSizeRow, Setting::kMazeSizeCol);
//     return 0;
// }