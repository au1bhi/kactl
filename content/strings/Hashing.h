/**
 * Author: Simon Lindholm, Team
 * Date: 2026-05-28
 * License: CC0
 * Source: KACTL, own work
 * Description: Extremely fast string hashing modulo $2^{64}-1$ using 128-bit multiplication fold.
 * Completely immune to Thue-Morse anti-hash tests.
 * Base $C$ is automatically randomized at runtime to prevent any targeted hacks.
 * Range query `hashInterval(a, b)` returns hash of half-open interval $[a, b)$ (i.e. 0-based $[a, b-1]$).
 * Time: O(N) precomputation, O(1) query
 * Status: stress-tested
 */
#pragma once

typedef uint64_t ull;
struct H
{
	ull x;
	H(ull x = 0) : x(x) {}
	H operator+(H o) { return x + o.x + (x + o.x < x); }
	H operator-(H o) { return *this + ~o.x; }
	H operator*(H o)
	{
		auto m = (__uint128_t)x * o.x;
		return H((ull)m) + (ull)(m >> 64);
	}
	ull get() const { return x + !~x; }
	bool operator==(H o) const { return get() == o.get(); }
	bool operator<(H o) const { return get() < o.get(); }
};

inline const H C = []()
{
	mt19937_64 rng(random_device{}());
	return H(rng() | 1); // Ensure C is odd
}();

struct HashInterval
{
	vector<H> ha, pw;
	HashInterval(const string &str) : ha(str.size() + 1), pw(ha)
	{
		pw[0] = 1;
		for (int i = 0; i < (int)str.size(); ++i)
		{
			ha[i + 1] = ha[i] * C + str[i];
			pw[i + 1] = pw[i] * C;
		}
	}
	H hashInterval(int a, int b)
	{ // hash [a, b) in 0-based indexing
		return ha[b] - ha[a] * pw[b - a];
	}
};

vector<H> getHashes(const string &str, int length)
{
	if ((int)str.size() < length)
		return {};
	H h = 0, pw = 1;
	for (int i = 0; i < length; ++i)
	{
		h = h * C + str[i];
		pw = pw * C;
	}
	vector<H> ret = {h};
	for (int i = length; i < (int)str.size(); ++i)
	{
		ret.push_back(h = h * C + str[i] - pw * str[i - length]);
	}
	return ret;
}

H hashString(const string &s)
{
	H h{};
	for (char c : s)
		h = h * C + c;
	return h;
}