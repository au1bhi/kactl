/**
 * Author: Team
 * Date: 2026-05-28
 * License: CC0
 * Description: Kruskal's algorithm for Minimum Spanning Tree (MST). Returns total weight and connectivity.
 * Time: O(M log M)
 * Status: tested
 */
#pragma once
#include "../data-structures/UnionFind.h"

struct Edge
{
	int u, v;
	long long w;
};

pair<long long, bool> kruskal(int n, const vector<Edge> &edges)
{
	vector<Edge> es = edges;
	sort(es.begin(), es.end(), [](const Edge &a, const Edge &b)
	     { return a.w < b.w; });
	DSU dsu(n);
	long long total = 0;
	int used = 0;
	for (const auto &e : es)
	{
		if (dsu.merge(e.u, e.v))
		{
			total += e.w;
			++used;
		}
	}
	return {total, used == n - 1};
}
