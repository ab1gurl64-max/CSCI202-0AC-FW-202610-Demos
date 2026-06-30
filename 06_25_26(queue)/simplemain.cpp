#include "linkedQueue.h"
#include "arrayQueue.h"
#include <random>

int main()
{
    LinkedQueue<int> q1;
    LinkedQueue<int> q2;
    ArrayQueue<int> q3;
    ArrayQueue<int> q4(10);
    std::default_random_engine generator;
    std::uniform_int_distribution<int> dist(1, 200);

    for (int i = 0; i < 80; i++)
    {
        q1.enqueue(dist(generator));
        q3.enqueue(dist(generator));
    }
    q2 = q1;
    q4 = q3;
    for (int i = 0; i < 30; i++)
    {
        std::cout << q1.dequeue() << "\t\t" << q2.dequeue() << "\t\t" << q3.dequeue() << "\t\t" << q4.dequeue() << std::endl;
    }

    return 0;
}