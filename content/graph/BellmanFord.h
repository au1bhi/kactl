/**
 * Author: Simon Lindholm
 * Date: 2015-02-23
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Bellman-Ford_algorithm
 * Description: Shortest paths with negative weights. Negative-cycle reachable nodes get -INF.
 * Time: O(VE)
 * Status: tested
 */
#pragma once

struct Edge
{
	int u, v;
	long long w;
};

vector<long long> bellmanFord(int n, int s, const vector<Edge> &edges)
{
	const long long INF = (1LL << 62);
	vector<long long> dist(n + 1, INF);
	dist[s] = 0;
	for (int i = 1; i < n; ++i)
	{
		bool any = false;
		for (const auto &e : edges)
		{
			if (dist[e.u] == INF || dist[e.u] == -INF)
				continue;
			if (dist[e.u] + e.w < dist[e.v])
			{
				dist[e.v] = dist[e.u] + e.w;
				any = true;
			}
		}
		if (!any)
			break;
	}
	for (int i = 1; i <= n; ++i)
		for (const auto &e : edges)
		{
			if (dist[e.u] == -INF)
				dist[e.v] = -INF;
			else if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v])
				dist[e.v] = -INF;
		}
	return dist;
}
