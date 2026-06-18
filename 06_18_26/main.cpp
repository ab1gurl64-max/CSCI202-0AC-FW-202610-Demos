#include "unorderedLinkedList.h"
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
    intList.deleteNode(6);

    return 0;
}