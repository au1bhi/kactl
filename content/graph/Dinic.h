/**
 * Author: Team
 * Date: 2026-05-28
 * License: CC0
 * Description: Dinic's algorithm for finding the Maximum Flow in a network.
 * Time: O(N^2 M) in general, O(M \sqrt{N}) for bipartite matching.
 * Status: tested
 */
#pragma once

template <typename T = long long>
struct Dinic
{
    struct Edge
    {
        int to;
        T cap;
    };
    int n;
    vector<Edge> edges;
    vector<vector<int>> g;
    vector<int> d, cur;

    Dinic(int n_nodes) : n(n_nodes + 1), g(n_nodes + 1) {}

    void add(int u, int v, T cap)
    {
        g[u].push_back(edges.size());
        edges.push_back({v, cap});
        g[v].push_back(edges.size());
        edges.push_back({u, 0});
    }

    bool bfs(int s, int t)
    {
        d.assign(n, -1);
        d[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int id : g[u])
            {
                auto &[v, cap] = edges[id];
                if (cap > 0 && d[v] == -1)
                {
                    d[v] = d[u] + 1;
                    if (v == t)
                        return true;
                    q.push(v);
                }
            }
        }
        return false;
    }

    T dfs(int u, int t, T flow)
    {
        if (u == t)
            return flow;
        T pushed = 0;
        for (int &i = cur[u]; i < g[u].size(); ++i)
        {
            int id = g[u][i];
            auto &[v, cap] = edges[id];
            if (cap > 0 && d[v] == d[u] + 1)
            {
                T tr = dfs(v, t, min(flow - pushed, cap));
                if (tr == 0)
                    continue;
                cap -= tr;
                edges[id ^ 1].cap += tr;
                pushed += tr;
                if (pushed == flow)
                    return pushed;
            }
        }
        return pushed;
    }

    T max_flow(int s, int t)
    {
        T total_flow = 0;
        while (bfs(s, t))
        {
            cur.assign(n, 0);
            total_flow += dfs(s, t, inf);
        }
        return total_flow;
    }
};