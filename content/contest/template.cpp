#include <bits/stdc++.h>
#define PV(var) cout << #var << ":" << var << " ";
#define all(arr) arr.begin(), arr.end()
#define rall(arr) arr.rbegin(), arr.rend()
#define endl "\n"
#define int long long
#define rep(i, start, end) for (int i = start; i < (end); ++i)
#define FOR(i, start, end) for (int i = start; i <= (end); ++i)
#define sz(x) (int)(x).size()
#define uni(v) v.resize(unique(all(v)) - v.begin())
using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long long ll;
const int inf = 4e18;
const double eps = 1e-9;

mt19937_64 gen(random_device{}());
int randint(int l, int r)
{
	return uniform_int_distribution<int>(l, r)(gen);
}

template <typename T>
istream &operator>>(istream &is, vector<T> &v)
{
	for (auto &x : v)
		is >> x;
	return is;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
	if (!v.empty())
	{
		os << v[0];
		rep(i, 1, sz(v))
		{
			os << " " << v[i];
		}
	}
	return os;
}

signed main()
{
	cin.tie(0)->sync_with_stdio(false);
	cin.exceptions(cin.failbit);
	cout << fixed << setprecision(11);
	return 0;
}