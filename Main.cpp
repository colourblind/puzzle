#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>

using namespace std;

struct edge
{
    int a;
    int b;
    int cost;

    edge(int a0, int b0, int cost0)
        : a(a0), b(b0), cost(cost0)
    { }
};

vector<edge> MAP = {
    edge(0, 1, 1),
    edge(1, 2, -1),
    edge(1, 4, 1),
    edge(2, 3, 1),
    edge(2, 5, -1),
    edge(3, 6, -1),
    edge(4, 5, -1),
    edge(4, 8, 0),
    edge(5, 6, 1),
    edge(5, 9, 1),
    edge(6, 7, -1),
    edge(6, 10, -1),
    edge(7, 17, 1),
    edge(8, 9, 0),
    edge(9, 10, 1),
    edge(10, 13, 0),
    edge(11, 12, 0),
    edge(11, 14, 0),
    edge(12, 13, -1),
    edge(12, 15, 1),
    edge(13, 16, 1),
    edge(14, 15, 0),
    edge(14, 18, 1),
    edge(15, 16, 1),
    edge(15, 19, -1),
    edge(16, 17, -1),
    edge(16, 20, 0),
    edge(18, 19, -1),
    edge(19, 20, 1),
    edge(18, 99, 1)
};

void iterate(vector<vector<int>> &solutions, vector<int> path = vector<int>(), int currentCost = 0, int currentNode = 0)
{
    path.push_back(currentNode);

    if (currentNode == 99)
    {
        solutions.push_back(path);
        //cout << "+++ found solution" << endl << flush;
        return;
    }
    if (path.size() > 32)
    {
        return;
    }

    vector<edge> options;
    copy_if(MAP.begin(), MAP.end(), back_inserter(options), [currentNode, currentCost](edge e) { return (e.a == currentNode || e.b == currentNode) && (currentCost == 0 || e.cost == 0 || e.cost + currentCost == 0); });

    for (auto p : options)
    {
        int nextCost = p.cost == 0 ? currentCost : p.cost;
        int nextNode = p.a == currentNode ? p.b : p.a;
        iterate(solutions, path, nextCost, nextNode);
    }
}

int main(int argc, char **argv)
{
    auto solutions = vector<vector<int>>();
    iterate(solutions);

    sort(solutions.begin(), solutions.end(), [] (vector<int> a, vector<int> b) { return a.size() < b.size(); });

    for (auto s : solutions)
    {
        stringstream ss;
        for (auto n : s)
        {
            ss << n << "|";
        }
        cout << ss.str() << " - " << s.size() << endl;
    }

    return 0;
}
