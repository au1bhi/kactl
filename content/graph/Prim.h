/**
 * Author: Team
 * Date: 2026-05-28
 * License: CC0
 * Description: Prim's algorithm for Minimum Spanning Tree (MST) on dense graphs.
 * Time: O(M log N)
 * Status: tested
 */
#pragma once
#include "Graph.h"

pair<int, bool> prim(int s, const Graph &g)
{
    int total_weight = 0, visited_cnt = 0;
    vector<int> dist(g.n + 1, inf);
    vector<bool> visited(g.n + 1, false);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();
        if (visited[u])
            continue;
        visited[u] = true;
        total_weight += d;
        visited_cnt++;
        for (auto [v, w] : g.adj[u])
        {
            if (!visited[v] && w < dist[v])
            {
                dist[v] = w;
                pq.push({dist[v], v});
            }
        }
    }
    return {total_weight, visited_cnt == g.n};
}