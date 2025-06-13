#include <iostream>
#include "LinkedQueue.h"

int main()
{
    // Initialization...
    LinkedQueue<int> myQueue;
    myQueue.enqueue(0);
    myQueue.enqueue(1);

    int row { 0 };
    while (row <= 5)
    {
        // enqueue the element
        if (myQueue.show().value().get() == 0)
            myQueue.enqueue(0);
        auto out { myQueue.dequeue().value() };
        myQueue.enqueue(out + myQueue.show().value().get());

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