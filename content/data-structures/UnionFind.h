/**
 * Author: Lukas Polacek
 * Date: 2009-10-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure.
 * Time: $O(\alpha(N))$
 */
#pragma once

struct DSU
{
	vector<int> fa, p, e, f;
	int comp_cnt; // Number of connected components

	DSU(int n) : comp_cnt(n)
	{
		fa.resize(n + 1);
		iota(fa.begin(), fa.end(), 0);
		p.assign(n + 1, 1); // Vertices count
		e.assign(n + 1, 0); // Edges count
		f.assign(n + 1, 0); // Cycle flag
	}

	int find(int x)
	{ // Path compression
		return fa[x] == x ? x : fa[x] = find(fa[x]);
	}

	bool merge(int u, int v)
	{
		int ru = find(u), rv = find(v);
		if (ru == rv)
		{
			f[ru] = 1; // Mark cycle
			e[ru]++;   // Add edge
			return false;
		}
		// Union by size
		if (p[ru] < p[rv])
			swap(ru, rv);
		fa[rv] = ru;
		p[ru] += p[rv];		// Add vertices
		e[ru] += e[rv] + 1; // Add edges + 1 new edge
		f[ru] |= f[rv];		// Merge cycle flags
		comp_cnt--;
		return true;
	}

	bool same(int x, int y) { return find(x) == find(y); }
	bool has_cycle(int x) { return f[find(x)]; }
	int size(int x) { return p[find(x)]; }
	int edges(int x) { return e[find(x)]; }
	int count_sets() { return comp_cnt; }
};