#include <queue>
#include <algorithm>
#include <iostream>

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
    std::vector<std::vector<int>> tasks = {{19, 13}, {16, 9}, {21, 10}, {32, 25}, {37, 4}, {49, 24}, {2, 15}, {38, 41}, {37, 34}, {33, 6}, {45, 4}, {18, 18}, {46, 39}, {12, 24}};
    Solution sol;
    std::vector<int> order = sol.getOrder(tasks);
    std::cout << "[ ";
    for (const auto &pair : order)
    {
        std::cout << pair << ", ";
    }
    std::cout << "]" << std::endl;
    return 0;
}