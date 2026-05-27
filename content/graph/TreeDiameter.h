/**
 * Author: Team
 * Date: 2026-05-28
 * License: CC0
 * Description: Comprehensive tree analyzer. Computes tree diameter, radius, center, and centroid in O(N).
 * Time: O(N)
 * Status: tested
 */
#pragma once

struct Tree
{
    int n;
    vector<vector<pii>> e;
    int diam = 0, radius = inf, center = 0;
    vector<int> d1, d2, up, s1;

    int cog = 0, rem_max_sz = inf;
    vector<int> sz;

    Tree(int n) : n(n), e(n + 1) {}

    void add(int u, int v, int w = 1)
    {
        e[u].push_back({v, w});
        e[v].push_back({u, w});
    }

    void _dfs1(int u, int fa)
    {
        for (auto [v, w] : e[u])
        {
            if (v == fa)
                continue;
            _dfs1(v, u);
            int val = d1[v] + w;
            if (val > d1[u])
            {
                d2[u] = d1[u];
                d1[u] = val;
                s1[u] = v;
            }
            else if (val > d2[u])
            {
                d2[u] = val;
            }
        }
    }

    void _dfs2(int u, int fa)
    {
        for (auto [v, w] : e[u])
        {
            if (v == fa)
                continue;
            if (s1[u] == v)
            {
                up[v] = max(up[u], d2[u]) + w;
            }
            else
            {
                up[v] = max(up[u], d1[u]) + w;
            }
            _dfs2(v, u);
        }
    }

    // Computes tree diameter, radius, and center
    void get_diam_info(int root = 1)
    {
        d1.assign(n + 1, 0);
        d2.assign(n + 1, 0);
        up.assign(n + 1, 0);
        s1.assign(n + 1, 0);
        diam = 0;
        radius = inf;
        center = 0;

        _dfs1(root, 0);
        _dfs2(root, 0);

        for (int i = 1; i <= n; ++i)
        {
            diam = max(diam, d1[i] + up[i]);
            int current_rad = max(d1[i], up[i]);
            if (current_rad < radius)
            {
                radius = current_rad;
                center = i;
            }
        }
    }

    void _dfs_cog(int u, int fa)
    {
        sz[u] = 1;
        int max_child_sz = 0;
        for (auto [v, w] : e[u])
        {
            if (v == fa)
                continue;
            _dfs_cog(v, u);
            sz[u] += sz[v];
            max_child_sz = max(max_child_sz, sz[v]);
        }
        int max_sz = max(max_child_sz, n - sz[u]);
        if (max_sz < rem_max_sz)
        {
            rem_max_sz = max_sz;
            cog = u;
        }
    }

    // Finds the tree centroid (cog)
    void get_cog_info(int root = 1)
    {
        sz.assign(n + 1, 0);
        rem_max_sz = inf;
        cog = 0;
        _dfs_cog(root, 0);
    }
};