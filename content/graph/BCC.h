/**
 * Author: Simon Lindholm, Team
 * Date: 2026-05-28
 * License: CC0
 * Description: Finds all vertex-biconnected components (V-BCC/BCC) in an undirected graph,
 * and automatically identifies all bridges.
 * Completely encapsulated in a struct to prevent multi-test clearing bugs.
 * Usage:
 *   BCC bcc(N);
 *   for each edge (u, v): bcc.add_edge(u, v);
 *   bcc.build(callback); // callback receives vector<int> of edge IDs
 *   // bcc.bridges now contains all bridges as pair<int, int>
 * Time: O(V + E)
 * Status: tested
 */
#pragma once

struct BCC
{
    int n, edge_id = 0, timestamp = 0;
    vector<vector<pii>> adj;
    vector<int> num, st;
    vector<pii> bridges; // Automatically populated during build()

    BCC(int n) : n(n), adj(n + 1) {}

    void add_edge(int u, int v)
    {
        adj[u].push_back({v, edge_id});
        adj[v].push_back({u, edge_id++});
    }

    template <class F>
    int dfs(int at, int par_edge, F &f)
    {
        int me = num[at] = ++timestamp, top = me;
        for (auto [y, e] : adj[at])
        {
            if (e != par_edge)
            {
                if (num[y])
                {
                    top = min(top, num[y]);
                    if (num[y] < me)
                        st.push_back(e);
                }
                else
                {
                    int si = st.size();
                    int up = dfs(y, e, f);
                    top = min(top, up);
                    if (up == me)
                    {
                        st.push_back(e);
                        f(vector<int>(st.begin() + si, st.end()));
                        st.resize(si);
                    }
                    else if (up < me)
                    {
                        st.push_back(e);
                    }
                    else
                    {
                        bridges.push_back({at, y}); // e is a bridge!
                    }
                }
            }
        }
        return top;
    }

    template <class F>
    void build(F f)
    {
        num.assign(n + 1, 0);
        st.clear();
        bridges.clear();
        timestamp = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (!num[i])
                dfs(i, -1, f);
        }
    }
};