#include "unorderedLinkedList.h"
#include "doublyLinkedList.h"
#include "donut.h"

int main()
{
    UnorderedLinkedList<Donut> d;
    Donut myDonut("none", "none", "none");
    d.insert(myDonut);
    UnorderedLinkedList<int> intList;
    intList.insert(8);
    intList.insert(3);
    intList.insert(9);
    intList.print();
    std::cout << std::endl;
    intList.deleteNode(3);
    intList.print();
    std::cout << std::endl;
    std::cout << intList.search(6) << std::endl;
    try
    {
        intList.deleteNode(6);
    }
    catch (...)
    {
    }

    DoublyLinkedList<double> doubleList;
    doubleList.insert(3.2);
    doubleList.insert(9.23);
    doubleList.insert(1.221);
    doubleList.print();
    std::cout << std::endl;
    doubleList.reversePrint();
    std::cout << std::endl;
    doubleList.deleteNode(9.23);
    doubleList.print();
    std::cout << std::endl;
    doubleList.reversePrint();
    std::cout << std::endl;

    return 0;
}