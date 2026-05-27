/**
 * Author: Team
 * Date: 2026-05-28
 * License: CC0
 * Description: Tarjan's algorithm for finding Strongly Connected Components (SCC) in directed graphs. Returns 1-based SCC IDs.
 * Time: O(N + M)
 * Status: tested
 */
#pragma once
#include "Graph.h"

vector<int> find_sccs(const Graph &g)
{
    vector<int> dfn(g.n + 1, 0), low(g.n + 1, 0), scc_id(g.n + 1, 0);
    vector<bool> in_stack(g.n + 1, false);
    stack<int> s;
    int timestamp = 0, scc_count = 0;

    auto tarjan = [&](auto &&self, int u) -> void
    {
        dfn[u] = low[u] = ++timestamp;
        s.push(u);
        in_stack[u] = true;
        for (auto [v, w] : g.adj[u])
        {
            if (!dfn[v])
            {
                self(self, v);
                low[u] = min(low[u], low[v]);
            }
            else if (in_stack[v])
            {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (low[u] == dfn[u])
        {
            ++scc_count;
            while (true)
            {
                int node = s.top();
                s.pop();
                in_stack[node] = false;
                scc_id[node] = scc_count;
                if (node == u)
                    break;
            }
        }
    };

    for (int i = 1; i <= g.n; ++i)
    {
        if (!dfn[i])
            tarjan(tarjan, i);
    }
    return scc_id;
}