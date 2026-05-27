/**
 * Author: Team
 * Date: 2026-05-28
 * License: CC0
 * Description: Prefix Trie for lowercase English strings.
 * Keeps track of the count of ending strings.
 * Time: O(L) per operation where L is string length. Space: O(L * 26).
 * Status: tested
 */
#pragma once

struct Trie
{
    vector<array<int, 26>> ch;
    vector<int> cnt;

    Trie() : ch(1), cnt(1, 0)
    {
        ch[0].fill(0);
    }

    void insert(const string &s)
    {
        int u = 0;
        for (char c : s)
        {
            int v = c - 'a';
            if (!ch[u][v])
            {
                ch[u][v] = ch.size();
                ch.emplace_back();
                ch.back().fill(0);
                cnt.push_back(0);
            }
            u = ch[u][v];
        }
        cnt[u]++;
    }

    bool search(const string &s)
    {
        int u = 0;
        for (char c : s)
        {
            int v = c - 'a';
            if (!ch[u][v])
                return false;
            u = ch[u][v];
        }
        return cnt[u] > 0;
    }
};