/**
 * Author: Simon Lindholm
 * Date: 2018-07-06
 * License: CC0
 * Description: Precomputes factorials and inverse factorials for O(1) C(n,k) and P(n,k) queries. Requires mint.
 * Usage: Comb comb(N); comb.C(n, k); comb.P(n, k);
 * Time: O(N) precomputation, O(1) query
 */
struct Comb
{
	vector<mint> f, inv_f;

	Comb(int n) : f(n + 1), inv_f(n + 1)
	{
		f[0] = 1;
		for (int i = 1; i <= n; i++)
		{
			f[i] = f[i - 1] * i;
		}
		inv_f[n] = f[n].inv();
		for (int i = n - 1; i >= 0; i--)
		{
			inv_f[i] = inv_f[i + 1] * (i + 1);
		}
	}

	mint C(int n, int k)
	{
		if (k < 0 || k > n)
			return 0;
		return f[n] * inv_f[k] * inv_f[n - k];
	}

	mint P(int n, int k)
	{
		if (k < 0 || k > n)
			return 0;
		return f[n] * inv_f[n - k];
	}
};
