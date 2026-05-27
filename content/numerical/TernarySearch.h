/**
 * Author: KACTL, Team
 * Date: 2026-05-28
 * License: CC0
 * Source: KACTL, own work
 * Description: Ternary search for finding the extremum of a unimodal function f.
 * Supports both discrete (integer) and continuous (double) domains.
 * To minimize, reverse the comparison operators.
 * Status: tested
 */
#pragma once

// 1. Integer-domain Ternary Search (Finds Maximum)
// To reverse non-strict inequalities, change < in (A) to <=, and reverse loop (B).
// To minimize, change < to > in (A) and (B).
template <class F>
int ternSearch(int a, int b, F f)
{
    assert(a <= b);
    while (b - a >= 5)
    {
        int mid = (a + b) / 2;
        if (f(mid) < f(mid + 1))
            a = mid; // (A)
        else
            b = mid + 1;
    }
    for (int i = a + 1; i <= b; ++i)
    { // (B)
        if (f(a) < f(i))
            a = i;
    }
    return a;
}

// 2. Real-domain Ternary Search (Finds Maximum)
// To minimize, change < in (C) to >
template <class F>
double ternary_search_double(double l, double r, F f)
{
    // 100 iterations guarantee precision and prevent infinite loops (eps issues)
    for (int i = 0; i < 100; ++i)
    {
        double m1 = l + (r - l) / 3.0;
        double m2 = r - (r - l) / 3.0;

        if (f(m1) < f(m2))
        {           // (C)
            l = m1; // Max is to the right of m1
        }
        else
        {
            r = m2; // Max is to the left of m2
        }
    }
    return l;
}