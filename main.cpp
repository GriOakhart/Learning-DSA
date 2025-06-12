#include <iostream>
#include <string>
#include "SeqQueue.h"

int main()
{
    SeqQueue<std::string> queue;
    queue.enqueue("hello");
    queue.enqueue("james");
    while (!queue.isEmpty())
    {
        std::cout << queue.dequeue().value() << std::endl;
    }
    queue.enqueue("good");
    queue.enqueue("bye");
    queue.enqueue("?");
    while (!queue.isEmpty())
    {
        std::cout << queue.dequeue().value() << std::endl;
    }
    return 0;
}