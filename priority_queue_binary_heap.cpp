//This code snippet shows how to use a priority queue as a binary heap 
//by adding a custom comparator method.
//The default behaviour would be a sorting in descending order, using the custom 
//compare the priority queue gets sorted in ascending order.

#include <iostream>
#include <queue>
#include <vector>

class Priority
{
public:
    Priority(int f, int s) { this->first = f; this->second = s; }
    int first;
    int second;
    bool operator<(const Priority &other) const { return this->first > other.first; }
};

int main(int argc, char *argv[])
{
    std::priority_queue<Priority, std::vector<Priority>, std::less<std::vector<Priority>::value_type> > test_queue;
    Priority test1(100, 1); 
    Priority test2(4, 2);
    Priority test3(95, 3);
    Priority test4(3, 4);

    test_queue.push(test1);
    test_queue.push(test2);
    test_queue.push(test3);
    test_queue.push(test4);

    std::cout << test_queue.top().second << std::endl;
    test_queue.pop();
    std::cout << test_queue.top().second << std::endl;

    return 0;
}
