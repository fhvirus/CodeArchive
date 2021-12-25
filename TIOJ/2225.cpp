#include <functional>
#include <iostream>
#include <string>
using namespace std;

const int kN = 18;
int n, X, S[kN], P[5];

function<bool(int, int)> f[4] = {
	[](int A, int B) { return (A & B) == 0; },
	[](int A, int B) { return A != B and (B & A) == B; },
	[](int A, int B) { return B != A and (A & B) == A; },
	[](int A, int B) { return A != B and (A & B) != 0 and (A & B) != A and (A & B) != B; }
};

void get(int &a) {
	a = 0;
	string s; cin >> s;
	for (char &c: s)
		a |= 1 << (c - 'a');
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> n;
	get(X);
	for (int i = 0; i < n; ++i) {
		get(S[i]);
		for (int j = 0; j < 4; ++j)
			P[j] += f[j](S[i], X);
	}

	for (int i = 0; i < n; ++i) {
		if (!f[3](X, S[i])) continue;
		int a = (X & S[i]);
		int b = (X & ~S[i]);
		bool can = true;
		for (int j = 0; j < n; ++j)
			can &= !f[3](a, S[j]) and !f[3](b, S[j]);
		P[4] = (can ? 2 : 0);
		break;
	}

	for (int j = 0; j < 5; ++j)
		cout << P[j] << " \n"[j == 4];
	return 0;
}
