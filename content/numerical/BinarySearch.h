/**
 * Author: ICPC Coach
 * Date: 2026-05-28
 * License: CC0
 * Description: Robust binary search templates for integer and real domains.
 * Time: O(\log(R - L)) for integer, strictly 100 iterations for double.
 */
#pragma once

// 1. Integer: Find MINIMUM x where check(x) is true
template <class F>
long long bs_min(long long l, long long r, F check)
{
    long long ans = r + 1; // Default if not found
    while (l <= r)
    {
        long long mid = l + (r - l) / 2;
        if (check(mid))
            ans = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    return ans;
}

// 2. Integer: Find MAXIMUM x where check(x) is true
template <class F>
long long bs_max(long long l, long long r, F check)
{
    long long ans = l - 1; // Default if not found
    while (l <= r)
    {
        long long mid = l + (r - l) / 2;
        if (check(mid))
            ans = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    return ans;
}

template <class F>
double bs_double(double l, double r, F check)
{
    for (int i = 0; i < 100; ++i)
    {
        double mid = l + (r - l) / 2.0;
        if (check(mid))
            r = mid;
        else
            l = mid;
    }
    return l;
}