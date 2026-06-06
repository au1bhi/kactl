/**
 * Author: Simon Lindholm
 * Date: 2016-12-15
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Floyd–Warshall_algorithm
 * Description: All-pairs shortest paths with negative weights. Negative-cycle paths get -INF.
 * Time: O(N^3)
 * Status: tested
 */
#pragma once

void floydWarshall(vector<vector<long long>> &adj)
{
	const long long INF = (1LL << 62);
	int n = (int)adj.size();
	for (int i = 0; i < n; ++i)
		adj[i][i] = min(adj[i][i], 0LL);
	for (int k = 0; k < n; ++k)
		for (int i = 0; i < n; ++i)
			if (adj[i][k] != INF)
				for (int j = 0; j < n; ++j)
					if (adj[k][j] != INF)
						adj[i][j] = min(adj[i][j], max(adj[i][k] + adj[k][j], -INF));
	for (int k = 0; k < n; ++k)
		if (adj[k][k] < 0)
			for (int i = 0; i < n; ++i)
				if (adj[i][k] != INF)
					for (int j = 0; j < n; ++j)
						if (adj[k][j] != INF)
							adj[i][j] = -INF;
}
