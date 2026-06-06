/**
 * Author: Team
 * Date: 2026-05-28
 * License: CC0
 * Description: Dijkstra's algorithm for single-source shortest paths on non-negative weighted graphs.
 * Time: O(M log N)
 * Status: tested
 */
#pragma once

vector<long long> dijkstra(int n, int s, const vector<vector<pair<int, long long>>> &adj)
{
	const long long INF = (1LL << 62);
	vector<long long> dist(n + 1, INF);
	dist[s] = 0;
	priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
	pq.push({0, s});
	while (!pq.empty())
	{
		auto [d, u] = pq.top();
		pq.pop();
		if (d != dist[u])
			continue;
		for (auto [v, w] : adj[u])
		{
			if (dist[u] + w < dist[v])
			{
				dist[v] = dist[u] + w;
				pq.push({dist[v], v});
			}
		}
	}
	return dist;
}
