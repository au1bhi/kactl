/**
 * Author: Simon Lindholm
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: Segment tree with ability to add or set values of large intervals, and compute max of intervals.
 * Can be changed to other things.
 * Time: O(\log N).
 * Usage: listed
 * Status: stress-tested a bit
 */

// 1. Range Add + Range Max
using S = ll;
using F = ll;

S op(S a, S b) { return max(a, b); }
S e() { return -4e18; }
F id() { return 0; }

S mapping(F f, S x) { return x + f; }
F composition(F f, F g) { return f + g; }

// 2. Range Add + Range Sum
struct S
{
    ll sum;
    int len;
};
using F = ll;

S op(S a, S b) { return {a.sum + b.sum, a.len + b.len}; }
S e() { return {0, 0}; }
F id() { return 0; }

S mapping(F f, S x) { return {x.sum + f * x.len, x.len}; }
F composition(F f, F g) { return f + g; }

// 3. Range Set + Range Max
using S = ll;
using F = ll;

S op(S a, S b) { return max(a, b); }
S e() { return -4e18; }
F id() { return 4e18; }

S mapping(F f, S x)
{
    return (f == id()) ? x : f;
}
F composition(F f, F g)
{
    return (f == id()) ? g : f;
}

// 4. Range Set + Range Sum
struct S
{
    ll sum;
    int len;
};
using F = ll;

S op(S a, S b) { return {a.sum + b.sum, a.len + b.len}; }
S e() { return {0, 0}; }
F id() { return 4e18; }

S mapping(F f, S x)
{
    return (f == id()) ? x : S{f * x.len, x.len};
}
F composition(F f, F g)
{
    return (f == id()) ? g : f;
}

// 5. Range Mult + Range Add + Range Sum
const long long MOD = 1e9 + 7;

struct S
{
    long long sum;
    int len;
};
struct F
{
    long long a, b; // Linear function: ax + b
    bool operator==(const F &o) const = default;
};

S op(S x, S y) { return {(x.sum + y.sum) % MOD, x.len + y.len}; }
S e() { return {0, 0}; }
F id() { return {1, 0}; }

S mapping(F f, S x)
{
    long long new_sum = (f.a * x.sum % MOD + f.b * x.len % MOD) % MOD;
    return {(new_sum + MOD) % MOD, x.len};
}
F composition(F f, F g)
{
    long long new_a = (f.a * g.a) % MOD;
    long long new_b = (f.a * g.b % MOD + f.b) % MOD;
    return {(new_a + MOD) % MOD, (new_b + MOD) % MOD};
}

// Range Add v:  update(L, R, {1, v});
// Range Mult v: update(L, R, {v, 0});
// Range Set v:  update(L, R, {0, v});

struct LazySeg
{
    int n;
    vector<S> d;
    vector<F> lz;
    LazySeg(int _n) : n(_n), d(4 * n, e()), lz(4 * n, id()) {}

    void apply(int p, F f)
    {
        d[p] = mapping(f, d[p]);
        lz[p] = composition(f, lz[p]);
    }

    void push(int p)
    {
        if (lz[p] != id())
        {
            apply(p << 1, lz[p]);
            apply(p << 1 | 1, lz[p]);
            lz[p] = id();
        }
    }

    void build(const vector<S> &a, int p, int cl, int cr)
    {

        if (cl == cr)
            return void(d[p] = a[cl]);
        int mid = (cl + cr) >> 1;
        build(a, p << 1, cl, mid);
        build(a, p << 1 | 1, mid + 1, cr);
        d[p] = op(d[p << 1], d[p << 1 | 1]);
    }

    void update(int l, int r, F f, int p, int cl, int cr)
    {
        if (l > cr || r < cl)
            return;

        if (l <= cl && cr <= r)
            return apply(p, f);
        push(p);
        int mid = (cl + cr) >> 1;
        update(l, r, f, p << 1, cl, mid);
        update(l, r, f, p << 1 | 1, mid + 1, cr);
        d[p] = op(d[p << 1], d[p << 1 | 1]);
    }

    S query(int l, int r, int p, int cl, int cr)
    {
        if (l > cr || r < cl)
            return e();
        if (l <= cl && cr <= r)
            return d[p];
        push(p);
        int mid = (cl + cr) >> 1;
        return op(query(l, r, p << 1, cl, mid), query(l, r, p << 1 | 1, mid + 1, cr));
    }

    void build(const vector<S> &a) { build(a, 1, 0, n - 1); }
    void update(int l, int r, F f) { update(l, r, f, 1, 0, n - 1); }
    S query(int l, int r) { return query(l, r, 1, 0, n - 1); }
};