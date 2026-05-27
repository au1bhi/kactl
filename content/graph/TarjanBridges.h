/**
 * Author: Team
 * Date: 2026-05-28
 * License: CC0
 * Description: Finds all bridges in an undirected multigraph using Tarjan's algorithm. Handles parallel edges.
 * Time: O(N + M)
 * Status: tested
 */
#pragma once
#include "Graph.h"

vector<pii> find_bridges(const Graph &g)
{
    vector<int> dfn(g.n + 1, 0), low(g.n + 1, 0);
    vector<pii> bridges;
    int timestamp = 0;

    vector<vector<tuple<int, int, int>>> adj_eid(g.n + 1);
    int eid = 0;
    for (int u = 1; u <= g.n; ++u)
    {
        for (auto [v, w] : g.adj[u])
        {
            adj_eid[u].emplace_back(v, w, eid++);
        }
    }

    auto tarjan = [&](auto &&self, int u, int p, int peid) -> void
    {
        dfn[u] = low[u] = ++timestamp;
        for (auto [v, w, e] : adj_eid[u])
        {
            if (e == peid)
                continue;
            if (!dfn[v])
            {
                self(self, v, u, e);
                low[u] = min(low[u], low[v]);
                if (low[v] > dfn[u])
                    bridges.push_back({u, v});
            }
            else
            {
                low[u] = min(low[u], dfn[v]);
            }
        }
    };

    for (int i = 1; i <= g.n; ++i)
    {
        if (!dfn[i])
            tarjan(tarjan, i, 0, -1);
    }
    return bridges;
}