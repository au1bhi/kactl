/**
 * Author: Team
 * Date: 2026-05-28
 * License: CC0
 * Description: Dijkstra's algorithm for single-source shortest paths on non-negative weighted graphs.
 * Time: O(M log N)
 * Status: tested
 */
#pragma once
#include "Graph.h"

vector<int> dijkstra(int s, const Graph &g)
{
    vector<int> d(g.n + 1, inf);
    d[s] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, s});
    while (!q.empty())
    {
        auto [dist, u] = q.top();
        q.pop();
        if (dist > d[u])
            continue;
        for (auto [v, w] : g.adj[u])
        {
            if (d[u] + w < d[v])
            {
                d[v] = d[u] + w;
                q.push({d[v], v});
            }
        }
    }
    return d;
}