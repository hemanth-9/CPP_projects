#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <queue>
#include <stack>
#include <unordered_map>

using namespace std;

vector<int> req_path;
bool found_path = false;

class graph
{
private:
    int n;
    unordered_map<int, vector<int>> adj_ver;
    void __init__();

public:
    graph(int n);

    unordered_map<int, bool> visited; // sets to false

    void add_adj_ver_dir(int v, int w);
    void add_adj_ver_undir(int v, int w);
    unordered_map<int, int> dist; // sets distance to 0
    void bfs(int start_ver, vector<int> path, int end_ver);
    void short_path_bfs(int end_ver);
    void dfs(int start_ver, vector<int> path, int end_ver);
    void DFS(int start_ver, vector<int> path, int end_ver);
};

graph::graph(int k)
{
    this->n = k;
    // adj_ver.resize(k);
}

void graph::add_adj_ver_dir(int v, int w)
{
    adj_ver[v].push_back(w);
}

void graph::add_adj_ver_undir(int v, int w)
{
    adj_ver[v].push_back(w);
    adj_ver[w].push_back(v);
}

void graph::__init__()
{
    req_path.clear();
    found_path = false;
    for (unordered_map<int, bool>::iterator it = visited.begin(); it != visited.end(); it++)
    {
        it->second = false;
    }
}

void graph::bfs(int start_ver, vector<int> path, int end_ver)
{
    __init__();
    queue<int> q;

    q.push(start_ver);
    visited[start_ver] = true;
    dist[start_ver] = 1;

    while (!q.empty())
    {
        start_ver = q.front();
        q.pop();
        // cout << start_ver << endl;

        for (int a : adj_ver[start_ver])
        {
            if (!visited[a])
            {
                visited[a] = true;
                dist[a] = dist[start_ver] + 1;
                q.push(a);
                if (start_ver == end_ver)
                {
                    short_path_bfs(end_ver);
                    return;
                }
            }
        }
        if (start_ver == end_ver)
        {
            short_path_bfs(end_ver);
            return;
        }
    }
}

void graph::short_path_bfs(int end_ver)
{
    if (dist[end_ver] == 1)
    {
        req_path.push_back(end_ver);
        return;
    }
    for (int x : adj_ver[end_ver])
    {
        if (dist[x] < dist[end_ver])
        {
            short_path_bfs(x);
            req_path.push_back(end_ver);
        }
    }
}

void graph::dfs(int start_ver, vector<int> path, int end_ver)
{
    __init__();
    if (start_ver == end_ver)
    {
        path.push_back(end_ver);
        req_path = path;
        found_path = true;
    }

    visited[start_ver] = true;

    // cout << start_ver << endl;
    if (found_path)
        return;

    for (int x : adj_ver[start_ver])
    {
        if (found_path)
            break;
        if (!visited[x])
        {
            path.push_back(start_ver);

            if (start_ver == end_ver)
            {
                req_path = path;
                found_path = true;
            }
            // cout<<"&"<<" ";
            DFS(x, path, end_ver);
        }
    }
}

void graph::DFS(int start_ver, vector<int> path, int end_ver)
{
    if (start_ver == end_ver)
    {
        path.push_back(end_ver);
        req_path = path;
        found_path = true;
    }

    visited[start_ver] = true;

    // cout << start_ver << endl;
    if (found_path)
        return;

    for (int x : adj_ver[start_ver])
    {
        if (found_path)
            break;
        if (!visited[x])
        {
            path.push_back(start_ver);

            if (start_ver == end_ver)
            {
                req_path = path;
                found_path = true;
            }
            // cout<<"&"<<" ";
            DFS(x, path, end_ver);
        }
    }
}

int main()
{

    int n;
    cin >> n;
    graph g = graph(n);

    int x, y;

    while (n--)
    {
        cin >> x >> y;
        g.add_adj_ver_dir(x, y);
    }

    int start_vertex = 2;
    int end_vertex = 4;

    vector<int> r_path;

    g.bfs(start_vertex, r_path, end_vertex);

    for (int a : req_path)
    {
        cout << a << " ";
    }

    cout << endl;

    g.dfs(start_vertex, r_path, end_vertex);

    for (int a : req_path)
    {
        cout << a << " ";
    }

    return 0;
}