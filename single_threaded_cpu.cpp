#include <queue>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <limits>

class Solution
{
public:
    typedef struct _heap_compare
    {
        bool operator()(const std::vector<int> &l, std::vector<int> &r)
        {
            return l[1] == r[1] ? l[2] > r[2] : l[1] > r[1];
        }
    } heap_compare;

    struct
    {
        bool operator()(const std::vector<int> &l, std::vector<int> &r)
        {
            return l[0] < r[0];
        }
    } sort_compare;

    std::vector<int> getOrder(std::vector<std::vector<int>> &tasks)
    {
        int i = 0;
        int n = tasks.size();
        int time = -1;
        std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, heap_compare> pq;
        std::vector<int> retval;

        for (int i = 0; i < n; i++)
        {
            tasks[i].push_back(i);
        }
        std::sort(tasks.begin(), tasks.end(), sort_compare);
        while (i < n)
        {
            if (tasks[i][0] <= time)
            {
                pq.push(tasks[i++]);
            }
            else if (pq.empty())
            {
                time = tasks[i][0];
                pq.push(tasks[i++]);
            }
            else
            {
                std::vector<int> task = pq.top();
                pq.pop();
                time = time + task[1];
                retval.push_back(task[2]);
            }
        }
        while (pq.size())
        {
            std::vector<int> task = pq.top();
            pq.pop();
            retval.push_back(task[2]);
        }
        return retval;
    }
};

int main()
{
    char c;
    int number;
    std::string line;
    std::vector<std::vector<int>> tasks;
    Solution sol;

    std::cout << "Copy and past Testcases from LeetCode or enter Testcases with the exact same format Ex: [[1,2],[2,4],[3,2],[4,1]]" << std::endl;

    std::getline(std::cin, line);
    std::istringstream stream(line);

    stream.ignore(std::numeric_limits<std::streamsize>::max(), '[');
    while (stream.ignore(std::numeric_limits<std::streamsize>::max(), '['))
    {
        std::vector<int> pair;
        for (int i = 0; i < 2; i++)
        {
            stream >> number;
            stream.ignore(std::numeric_limits<std::streamsize>::max(), ',');
            pair.push_back(number);
        }
        tasks.push_back(pair);
    }
    std::cout << "The results for " << std::endl;
    std::cout << "[";
    for (const auto &pair: tasks)
    {
        std::cout << "[" << pair[0] << "," << pair[1] << "],";
    }
    std::cout << "]" << std::endl;
    std::cout << "are: [";

    std::vector<int> order = sol.getOrder(tasks);
    for (const auto &event: order)
    {
        std::cout << event << ",";
    }
    std::cout << "]" << std::endl;
    // std::cout << "The order the tasks will be scheduled: " << sol.getOrder(tasks) << std::endl;
    return 0;
}