//When using pointers instead of real objects the binary heap implementation from file
//priority_queue_binary_heap.cpp
//doesn't work because
//std::less<std::vector<Priority*>::value_type>>
//would compare _pointers_ instead of values. Therefor the sorting would depend on the memory layout of the binary heap.
//The solution in this file shows how to deal with priority_queues of pointers.

#include <iostream>
#include <queue>
#include <vector>

class Priority
{
public:
    Priority(int f, int s) { this->first = f; this->second = s; }
    int first;
    int second;
    int getFirst() const { return first; }
};

class compareclass
{
    public:
        bool operator()(Priority *left, Priority *right) const
        {
            return left->getFirst() > right->getFirst(); 
        }
};

int main(int argc, char *argv[])
{
    std::priority_queue<Priority*, std::vector<Priority*>, compareclass> test_queue;
    Priority *test1 = new Priority(100, 1); 
    Priority *test2 = new Priority(4, 2);
    Priority *test3 = new Priority(95, 3);
    Priority *test4 = new Priority(3, 4);

    test_queue.push(test1);
    test_queue.push(test2);
    test_queue.push(test3);
    test_queue.push(test4);

    std::cout << test_queue.top()->second << std::endl;
    test_queue.pop();
    std::cout << test_queue.top()->second << std::endl;

    return 0;
}
