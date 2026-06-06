/**
 * Author: Team
 * Date: 2026-06-06
 * License: CC0
 * Description: Dijkstra on dense graphs using adjacency matrix.
 * Time: O(N^2)
 * Status: tested
 */
#pragma once

vector<long long> naiveDijkstra(int n, int s, const vector<vector<long long>> &adj)
{
	const long long INF = (1LL << 62);
	vector<long long> dist(n + 1, INF);
	vector<bool> used(n + 1, false);
	dist[s] = 0;
	for (int it = 1; it <= n; ++it)
	{
		int u = -1;
		for (int i = 1; i <= n; ++i)
			if (!used[i] && (u == -1 || dist[i] < dist[u]))
				u = i;
		if (u == -1 || dist[u] == INF)
			break;
		used[u] = true;
		for (int v = 1; v <= n; ++v)
			if (adj[u][v] != INF && dist[u] + adj[u][v] < dist[v])
				dist[v] = dist[u] + adj[u][v];
	}
	return dist;
}
