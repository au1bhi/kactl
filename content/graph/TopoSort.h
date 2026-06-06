/**
 * Author: KACTL, Team
 * Date: 2026-05-28
 * License: CC0
 * Description: Topological sort. Uses vector-as-queue trick for extreme speed. Returns {order, is-DAG}.
 * Time: O(N + M)
 * Status: tested
 */
#pragma once

pair<vector<int>, bool> topo_sort(int n, const vector<vector<int>> &adj)
{
	vector<int> indeg(n + 1, 0), q;
	for (int u = 1; u <= n; ++u)
		for (int v : adj[u])
			++indeg[v];
	for (int i = 1; i <= n; ++i)
		if (indeg[i] == 0)
			q.push_back(i);
	for (int j = 0; j < (int)q.size(); ++j)
		for (int v : adj[q[j]])
			if (--indeg[v] == 0)
				q.push_back(v);
	return {q, (int)q.size() == n};
}
