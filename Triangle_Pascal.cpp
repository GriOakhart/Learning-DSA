#include <iostream>
#include "LinkedQueue.h"

int main()
{
    // Initialization...
    LinkedQueue<int> TrianglePascal;
    TrianglePascal.enqueue(0);
    TrianglePascal.enqueue(1);

    int row { 0 };
    while (row <= 5)
    {
        // enqueue the element
        if (TrianglePascal.show().value().get() == 0)
            TrianglePascal.enqueue(0);
        auto out { TrianglePascal.dequeue().value() };
        TrianglePascal.enqueue(out + TrianglePascal.show().value().get());

        // print the dequeued element
        if (out == 0)
        {
            std::cout << std::endl;
            ++row;
        }
        else
            std::cout << out << ' ';
    }
    return 0;
}