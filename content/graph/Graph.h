/**
 * Author: Team
 * Date: 2026-05-28
 * License: CC0
 * Source: Chinese competitive programming community
 * Description: Standard Object-Oriented graph representation using adjacency lists.
 * Prevents global variables and facilitates automatic memory cleanup in multi-test scenarios.
 * Status: tested
 */
#pragma once

struct Graph
{
    int n, m;
    vector<vector<pii>> adj;
    vector<tuple<int, int, int>> edges;
    Graph(int n, int m = 0) : n(n), m(m), adj(n + 1) {}
    void add_edge(int u, int v, int w)
    {
        adj[u].push_back({v, w});
        edges.emplace_back(u, v, w);
    }
};