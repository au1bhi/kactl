/**
 * Author: Team
 * Date: 2026-05-28
 * License: CC0
 * Description: Shortest Path Faster Algorithm (SPFA) for graphs with negative weights. Detects negative cycles.
 * Time: O(NM) worst case
 * Status: tested
 */
#pragma once
#include "Graph.h"

pair<bool, vector<int>> spfa(int s, const Graph &g)
{
    vector<int> dist(g.n + 1, inf), cnt(g.n + 1, 0);
    vector<bool> in_queue(g.n + 1, false);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    in_queue[s] = true;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        in_queue[u] = false;
        for (auto [v, w] : g.adj[u])
        {
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= g.n)
                    return {false, {}}; // Negative cycle detected
                if (!in_queue[v])
                {
                    q.push(v);
                    in_queue[v] = true;
                }
            }
        }
    }
    return {true, dist};
}