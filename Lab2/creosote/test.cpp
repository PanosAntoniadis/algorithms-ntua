//============================================================================
// Name        : commando.cpp
// Author      : Ivan Galban Smith
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000000
#define endl '\n'

typedef long long ll;

ll x[MAXN + 1], sum[MAXN + 1], dp[MAXN + 1];

struct line{
	ll m, b;
	line(ll m, ll b) : m(m), b(b){}
};

struct ConvexHullTrick{

	int len, ptr;
	vector<line> r;

	ConvexHullTrick(int _n)
	{
		r.assign(_n, line(0, 0));
		len = ptr = 0;
	}

	bool bad(line l1, line l2, line l3)
	{
		return (l3.b - l1.b) * (l1.m - l2.m) < (l2.b - l1.b) * (l1.m - l3.m);
	}

	void add(line x)
	{
		while(len >= 2 && bad(r[len-2], r[len-1], x))
			--len;
		r[len++] = x;
	}

	ll query(ll x)
	{
		ptr = min(ptr, len-1);
		while(ptr + 1 < len && r[ptr+1].m * x + r[ptr+1].b >= r[ptr].m * x + r[ptr].b)
			++ptr;
		return r[ptr].m * x + r[ptr].b;
	}

};

ll sq(ll x){return x*x;}

int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
		int n;	cin >> n;
		int a, b, c;	cin >> a >> b >> c;

		for(int i = 1; i <= n; ++i)
		{
			cin >> x[i];
			sum[i] = sum[i-1] + x[i];
		}

		ConvexHullTrick cht(n);

		dp[1] = a * sq(x[1]) + b * x[1] + c;
		cht.add(line(-2 * a * sum[1], dp[1] + a * sq(sum[1]) - b * sum[1]));

		for(int i = 2; i <= n; ++i)
		{
			dp[i] = a * sq(sum[i]) + b * sum[i] + c;
			dp[i] = max(dp[i], dp[i] + cht.query(sum[i]));
			cht.add(line(-2 * a * sum[i], dp[i] + a * sq(sum[i]) - b * sum[i]));
		}
		cout << dp[n] << endl;


	return 0;
}
