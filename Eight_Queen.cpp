//
// Created by jason on 6/24/25.
//
// They have different time complexity for the conflict checking step:
// the iterative version not only stored the information of the placed Queens,
// but also a "threat map" on which the unsafe positions are already shaded out.

#include <bitset>
#include <iostream>

// Using iteration
int eightQueen_Iteration()
{
    // board numbering from 1 to 8
    //   1 2 3 4 5 6 7 8  <- columns
    // 1 Q . . . . . . .
    // 2 . . . . Q . . .
    // 3 . . . . . . . Q
    // 4 . . . . . Q . .
    // 5 . . Q . . . . .
    // 6 . . . . . . Q .
    // 7 . Q . . . . . .
    // 8 . . . Q . . . .
    // ^
    // rows

    std::bitset<8> column { 0 };
    std::bitset<16> leftToRightDiagonal { 0 };
    std::bitset<16> rightToLeftDiagonal { 0 };

    int solution { 0 };
    int position[9] {}; // necessary for tracing back

    int currentRow { 1 };
    int currentColumn { 1 };
    while (currentRow <= 8)
    {
        // find the potential position for Queen
        while (currentColumn <= 8)
        {
            if (!column.test(currentColumn - 1)
                && !leftToRightDiagonal.test(currentRow - currentColumn + 8)
                && !rightToLeftDiagonal.test(currentRow + currentColumn - 1))
                break;
            ++currentColumn;
        }

        // available position found
        if (currentColumn <= 8)
        {
            // store the position
            position[currentRow] = currentColumn;
            // mark the position
            column.set(currentColumn - 1);
            leftToRightDiagonal.set(currentRow - currentColumn + 8);
            rightToLeftDiagonal.set(currentRow + currentColumn - 1);

            // found solution if currentRow == 8
            if (currentRow == 8)
            {
                ++solution;
                // force to trace back
                column.reset(currentColumn - 1);
                leftToRightDiagonal.reset(currentRow - currentColumn + 8);
                rightToLeftDiagonal.reset(currentRow + currentColumn - 1);
                // and move to the next available position
                ++currentColumn;

                continue;
            }

            ++currentRow;
            // set currentColumn back
            currentColumn = 1;
        }
        // not found
        else
        {
            // trace back to the previous line
            --currentRow;

            // mo more solution if currentRow == 0
            if (currentRow == 0)
                break;

            currentColumn = position[currentRow];
            // unmark the position
            column.reset(currentColumn - 1);
            leftToRightDiagonal.reset(currentRow - currentColumn + 8);
            rightToLeftDiagonal.reset(currentRow + currentColumn - 1);
            // move the currentColumn ahead to test the next position available
            ++currentColumn;
        }
    }
    return solution;
}

// Using Recursion
void placingQueenOnLine(int* position, int currentRow, int& solution)
{
    // STOP case
    if (currentRow == 9)
    {
        ++solution;
        return;
    }
    for (int currentColumn { 1 }; currentColumn <= 8; ++currentColumn)
    {
        int row { 1 };
        for (; row < currentRow; ++row)
        {
            // illegal position
            if (position[row] == currentColumn                          // in the same column
                || row - position[row] == currentRow - currentColumn    // in the same 45 diagonal
                || row + position[row] == currentRow + currentColumn)   // in the same 135 diagonal
                    break;
        }
        // legal position found
        if (row == currentRow)
        {
            position[currentRow] = currentColumn;
            placingQueenOnLine(position, currentRow + 1, solution);
            // not necessary, but good for logic
            position[currentRow] = 0;
        }
    }
}

int eightQueen_Recursion()
{
    // these variable should be defined in a higher level than the recursive function itself
    int position[9] {};
    int solution { 0 };
    placingQueenOnLine(position, 1, solution);
    return solution;
}

int main(int argc, char* argv[])
{
    std::cout << "found " << eightQueen_Recursion() << " solutions" << std::endl;
    return 0;
}
