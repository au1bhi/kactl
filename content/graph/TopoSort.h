/**
 * Author: KACTL, Team
 * Date: 2026-05-28
 * License: CC0
 * Description: Topological sort. Uses vector-as-queue trick for extreme speed.
 * Returns {order, is-DAG}.
 * Time: O(N + M)
 * Status: tested
 */
#pragma once
#include "Graph.h"

pair<vector<int>, bool> topo_sort(const Graph &g)
{
    vector<int> indeg(g.n + 1, 0), q;
    for (int i = 1; i <= g.n; ++i)
    {
        for (auto [v, w] : g.adj[i])
            indeg[v]++;
    }
    for (int i = 1; i <= g.n; ++i)
    {
        if (indeg[i] == 0)
            q.push_back(i);
    }
    // Vector-as-queue trick: j is the head, q.size() is the tail
    for (int j = 0; j < (int)q.size(); ++j)
    {
        for (auto [v, w] : g.adj[q[j]])
        {
            if (--indeg[v] == 0)
                q.push_back(v);
        }
    }
    return {q, (int)q.size() == g.n};
}