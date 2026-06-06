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
        if (l > cr or r < cl)
            return;

        if (l <= cl and cr <= r)
            return apply(p, f);
        push(p);
        int mid = (cl + cr) >> 1;
        update(l, r, f, p << 1, cl, mid);
        update(l, r, f, p << 1 | 1, mid + 1, cr);
        d[p] = op(d[p << 1], d[p << 1 | 1]);
    }

    S query(int l, int r, int p, int cl, int cr)
    {
        if (l > cr or r < cl)
            return e();
        if (l <= cl and cr <= r)
            return d[p];
        push(p);
        int mid = (cl + cr) >> 1;
        return op(query(l, r, p << 1, cl, mid), query(l, r, p << 1 | 1, mid + 1, cr));
    }

    void build(const vector<S> &a) { build(a, 1, 0, n - 1); }
    void update(int l, int r, F f) { update(l, r, f, 1, 0, n - 1); }
    S query(int l, int r) { return query(l, r, 1, 0, n - 1); }
};