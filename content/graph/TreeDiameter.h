/**
 * Author: Team
 * Date: 2026-06-06
 * License: CC0
 * Description: Functions for a 1-indexed tree: weighted diameter endpoints, weighted radius/center, and unweighted centroid.
 * Usage:
 *   vector<vector<pair<int, long long>>> adj(n + 1);
 *   auto [diam, ends] = tree_diameter(adj);
 *   auto [radius, center] = tree_radius_center(adj);
 *   int centroid = tree_centroid(unweighted_adj);
 * Time: O(N)
 * Status: tested
 */
#pragma once

pair<long long, pair<int, int>> tree_diameter(const vector<vector<pair<int, long long>>> &adj, int root = 1)
{
	int n = (int)adj.size() - 1;
	vector<long long> dist(n + 1, 0);
	auto dfs = [&](auto &&self, int u, int p) -> void
	{
		for (auto [v, w] : adj[u])
		{
			if (v == p)
				continue;
			dist[v] = dist[u] + w;
			self(self, v, u);
		}
	};
	dfs(dfs, root, 0);
	int a = root;
	for (int i = 1; i <= n; ++i)
		if (dist[i] > dist[a])
			a = i;
	fill(dist.begin(), dist.end(), 0);
	dfs(dfs, a, 0);
	int b = a;
	for (int i = 1; i <= n; ++i)
		if (dist[i] > dist[b])
			b = i;
	return {dist[b], {a, b}};
}

pair<long long, int> tree_radius_center(const vector<vector<pair<int, long long>>> &adj, int root = 1)
{
	int n = (int)adj.size() - 1;
	auto [diam, ends] = tree_diameter(adj, root);
	auto [a, b] = ends;
	vector<long long> da(n + 1, 0), db(n + 1, 0);
	auto dfs = [&](auto &&self, int u, int p, vector<long long> &dist) -> void
	{
		for (auto [v, w] : adj[u])
		{
			if (v == p)
				continue;
			dist[v] = dist[u] + w;
			self(self, v, u, dist);
		}
	};
	dfs(dfs, a, 0, da);
	dfs(dfs, b, 0, db);
	long long radius = diam;
	int center = a;
	for (int i = 1; i <= n; ++i)
	{
		long long cur = max(da[i], db[i]);
		if (cur < radius)
		{
			radius = cur;
			center = i;
		}
	}
	return {radius, center};
}

int tree_centroid(const vector<vector<int>> &adj, int root = 1)
{
	int n = (int)adj.size() - 1;
	vector<int> sub(n + 1, 0);
	int centroid = root, best = n;
	auto dfs = [&](auto &&self, int u, int p) -> void
	{
		sub[u] = 1;
		int mx = 0;
		for (int v : adj[u])
		{
			if (v == p)
				continue;
			self(self, v, u);
			sub[u] += sub[v];
			mx = max(mx, sub[v]);
		}
		mx = max(mx, n - sub[u]);
		if (mx < best)
		{
			best = mx;
			centroid = u;
		}
	};
	dfs(dfs, root, 0);
	return centroid;
}
