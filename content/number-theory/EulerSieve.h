/**
 * Author: ICPC Coach
 * Date: 2026-05-28
 * License: CC0
 * Description: Linear prime sieve (Euler Sieve).
 * Time: O(N). LIM=1e7 takes ~0.1s.
 * Status: Tested
 */
#pragma once

const int LIM = 1e7 + 5;
bitset<LIM> isPrime;

vi eulerSieve()
{
    isPrime.set();
    isPrime[0] = isPrime[1] = 0;
    vi pr;
    pr.reserve(LIM / log(LIM) * 1.1);

    for (int i = 2; i < LIM; ++i)
    {
        if (isPrime[i])
            pr.push_back(i);
        for (int p : pr)
        {
            if (i * p >= LIM)
                break;
            isPrime[i * p] = 0;
            if (i % p == 0)
                break;
        }
    }
    return pr;
}