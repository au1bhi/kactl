/**
 * Author: Team
 * Date: 2026-05-28
 * License: CC0
 * Description: Kruskal's algorithm for Minimum Spanning Tree (MST). Returns total weight and connectivity.
 * Time: O(M log M)
 * Status: tested
 */
#pragma once
#include "Graph.h"

pair<int, bool> kruskal(Graph &g)
{
    sort(g.edges.begin(), g.edges.end(), [](auto &a, auto &b)
         { return get<2>(a) < get<2>(b); });
    struct LocalDSU
    {
        vector<int> p;
        LocalDSU(int n) : p(n + 1) { iota(p.begin(), p.end(), 0); }
        int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
        bool merge(int u, int v)
        {
            int x = find(u), y = find(v);
            if (x == y)
                return false;
            p[y] = x;
            return true;
        }
    } dsu(g.n);

    int total_weight = 0, comp = g.n;
    for (auto [u, v, w] : g.edges)
    {
        if (dsu.merge(u, v))
        {
            total_weight += w;
            --comp;
        }
    }
    return {total_weight, comp == 1};
}