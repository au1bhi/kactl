/**
 * Author: Simon Lindholm
 * Date: 2018-07-06
 * License: CC0
 * Description: Precomputes factorials and inverse factorials in O(N).
 * Provides O(1) queries for Combinations C(n, k) and Permutations P(n, k).
 * Requires the `Mint` struct.
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
        inv_f[n] = f[n].inv(); // O(log MOD)
        // O(N) backwards computation: 1/i! = 1/(i+1)! * (i+1)
        for (int i = n - 1; i >= 0; i--)
        {
            inv_f[i] = inv_f[i + 1] * (i + 1);
        }
    }

    // Combination C(n, k)
    mint C(int n, int k)
    {
        if (k < 0 || k > n)
            return 0;
        return f[n] * inv_f[k] * inv_f[n - k];
    }

    // Permutation P(n, k)
    mint P(int n, int k)
    {
        if (k < 0 || k > n)
            return 0;
        return f[n] * inv_f[n - k];
    }
};