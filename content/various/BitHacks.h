/**
 * Author: ICPC Coach
 * Date: 2026-05-28
 * License: CC0
 * Description: Bitwise hacks and SOS DP (Sum Over Subsets).
 */
#pragma once

void bitHacks(int m, int K, vector<int> &D)
{
    int lsb = m & -m;
    for (int x = m; x;)
    {
        --x &= m;
    }
    for (int b = 0; b < K; ++b)
    {
        for (int i = 0; i < (1 << K); ++i)
        {
            if (i & (1 << b))
            {
                D[i] += D[i ^ (1 << b)];
            }
        }
    }
}