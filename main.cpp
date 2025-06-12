#include <iostream>
#include <string>
#include "LinkedQueue.h"

int main()
{
    LinkedQueue<std::string> myQueue;
    myQueue.enqueue("hello");
    myQueue.enqueue("world");
    myQueue.enqueue("and");
    while (!myQueue.isEmpty())
    {
        std::cout << myQueue.dequeue().value() << std::endl;
    }
    myQueue.enqueue("james");
    myQueue.enqueue("welcome");
    myQueue.enqueue("to");
    myQueue.enqueue("new world!");
    while (!myQueue.isEmpty())
    {
        std::cout << myQueue.dequeue().value() << std::endl;
    }
    return 0;
}