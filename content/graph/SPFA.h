/**
 * Author: Team
 * Date: 2026-05-28
 * License: CC0
 * Description: SPFA for graphs with negative weights. Detects negative cycles.
 * ONLY use for Min-Cost Max-Flow or Difference Constraints. Will get TLE on grids.
 * Time: O(NM) worst case
 * Status: tested
 */
#pragma once

pair<bool, vector<long long>> spfa(int n, int s, const vector<vector<pair<int, long long>>> &adj)
{
	const long long INF = (1LL << 62);
	vector<long long> dist(n + 1, INF);
	vector<int> cnt(n + 1, 0);
	vector<bool> in_queue(n + 1, false);
	queue<int> q;
	dist[s] = 0;
	q.push(s);
	in_queue[s] = true;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		in_queue[u] = false;
		for (auto [v, w] : adj[u])
		{
			if (dist[u] + w < dist[v])
			{
				dist[v] = dist[u] + w;
				cnt[v] = cnt[u] + 1;
				if (cnt[v] >= n)
					return {false, {}};
				if (!in_queue[v])
				{
					q.push(v);
					in_queue[v] = true;
				}
			}
		}
	}
	return {true, dist};
}
