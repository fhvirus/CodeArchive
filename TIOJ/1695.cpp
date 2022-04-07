#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll binpow (ll x, ll e) {
	ll r = 1;
	while (e) {
		if (e & 1) r = r * x;
		x = x * x;
		e >>= 1;
	}
	return r;
}

typedef uint64_t ull;
ull modmul(ull a, ull b, ull M) {
	return (__uint128_t) a * b % M;
}
ull modpow (ull x, ull e, ull M) {
	ull r = 1;
	while (e) {
		if (e & 1) r = modmul(r, x, M);
		x = modmul(x, x, M);
		e >>= 1;
	}
	return r;
}

namespace Prime {

int squeeze(ll& x, int p) {
	ll d;
	int c = 0;
	while ((d = x / p) * p == x) {
		x = d;
		c += 1;
	}
	return c;
}

bool isPrime(ull n) {
	if (n > 10000000) return 0;
	if (n < 2 or n % 6 % 4 != 1) return (n | 1) == 3;
	static const ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
	ull s = __builtin_ctzll(n - 1), d = n >> s;
	for (ull a: A) {
		ull p = modpow(a % n, d, n), i = s;
		while (p != 1 and p != n - 1 and a % n != 0 and i--)
			p = modmul(p, p, n);
		if (p != n - 1 and i != s) return 0;
	}
	return 1;
}

ull pollard(ull n) {
	auto f = [n](ull x) { return modmul(x, x, n) + 1; };
	ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
	while (t++ % 40 != 0 or gcd(prd, n) == 1) {
		if (x == y) x = ++i, y = f(x);
		if ((q = modmul(prd, max(x, y) - min(x, y), n))) prd = q;
		x = f(x); y = f(f(y));
	}
	return gcd(prd, n);
}

void factor(ull n, vector<int>& fs) {
	if (n == 1) return;
	if (isPrime(n)) {
		fs.push_back(n);
		return;
	}
	ull x = pollard(n);
	factor(x, fs);
	factor(n / x, fs);
}

vector<pair<int, int>>& factorize(ll x) {
	static vector<pair<int, int>> f;
	static vector<int> fs;
	f.clear(); fs.clear();
	factor(x, fs);
	sort(begin(fs), end(fs));

	for (int i = 0, j = 0; i < fs.size(); i = j) {
		while (j < fs.size() and fs[i] == fs[j]) ++j;
		f.emplace_back(fs[i], j - i);
	}
	return f;
}

} // namespace Prime

signed main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	ll N, M;
	while (cin >> N >> M) {
		int stem = 0;
		ll flower = 1;
		vector<pair<int, int>>& f = Prime::factorize(M);
		for (const auto& [p, c]: f) {
			ll n = N;
			int cn = Prime::squeeze(n, p);
			if (cn != 0) {
				stem = max(stem, (c + cn - 1) / cn);
			} else {
				ll mod = binpow(p, c);
				ll len = mod / p * (p - 1);
				for (int i = 1; i * i <= p - 1; ++i) {
					if ((p - 1) % i != 0) continue;
					ll cur = 1;
					for (int j = 0; j < c; ++j) {
						if (modpow(n, cur * i, mod) == 1) len = min(len, cur * i);
						if (modpow(n, cur * (p - 1) / i, mod) == 1) len = min(len, cur * (p - 1) / i);
						cur *= p;
					}
				}
				flower = flower / gcd(flower, len) * len;
			}
		}
		cout << stem << ' ' << flower << '\n';
	}

	return 0;
}
