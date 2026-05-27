/**
 * Author: Noam527
 * Date: 2019-04-24
 * License: CC0
 * Source: folklore
 * Description:
 * Status: tested
 */
template <int MOD>
struct Mint
{
    int v;
    Mint(long long x = 0)
    {
        v = x % MOD;
        if (v < 0)
            v += MOD;
    }
    Mint &operator+=(const Mint &o)
    {
        v += o.v;
        if (v >= MOD)
            v -= MOD;
        return *this;
    }
    Mint &operator-=(const Mint &o)
    {
        v -= o.v;
        if (v < 0)
            v += MOD;
        return *this;
    }
    Mint &operator*=(const Mint &o)
    {
        v = 1LL * v * o.v % MOD;
        return *this;
    }

    Mint pow(long long k) const
    {
        Mint res = 1, base = *this;
        while (k)
        {
            if (k & 1)
                res *= base;
            base *= base;
            k >>= 1;
        }
        return res;
    }

    Mint inv() const { return pow(MOD - 2); }
    Mint &operator/=(const Mint &o) { return *this *= o.inv(); }

    friend Mint operator+(Mint a, const Mint &b) { return a += b; }
    friend Mint operator-(Mint a, const Mint &b) { return a -= b; }
    friend Mint operator*(Mint a, const Mint &b) { return a *= b; }
    friend Mint operator/(Mint a, const Mint &b) { return a /= b; }
    friend bool operator==(const Mint &a, const Mint &b) { return a.v == b.v; }
    friend bool operator!=(const Mint &a, const Mint &b) { return a.v != b.v; }

    friend istream &operator>>(istream &is, Mint &x)
    {
        long long v;
        is >> v;
        x = Mint(v);
        return is;
    }
    friend ostream &operator<<(ostream &os, const Mint &x) { return os << x.v; }
};

using mint = Mint<998244353>;