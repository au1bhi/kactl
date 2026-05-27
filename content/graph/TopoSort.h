/**
 * Author: Team
 * Date: 2026-05-28
 * License: CC0
 * Description: Topological sort. Returns the order and a boolean indicating if it is a DAG.
 * Time: O(N + M)
 * Status: tested
 */
#pragma once
#include "Graph.h"

pair<vector<int>, bool> topo_sort(const Graph &g)
{
    vector<int> in_degree(g.n + 1, 0);
    for (int i = 1; i <= g.n; ++i)
    {
        for (auto [v, w] : g.adj[i])
        {
            in_degree[v]++;
        }
    }
    queue<int> q;
    for (int i = 1; i <= g.n; ++i)
    {
        if (in_degree[i] == 0)
            q.push(i);
    }
    vector<int> res;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        res.push_back(u);
        for (auto [v, w] : g.adj[u])
        {
            if (--in_degree[v] == 0)
                q.push(v);
        }
    }
    return {res, (int)res.size() == g.n};
}