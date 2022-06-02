#include <bits/stdc++.h>
using namespace std;

// ans1:
// A+B = ((A|A)|(B|B))
// A*B = ((A|B)|(A|B))
// Cn = An*Bn + (An+Bn) * Cn-1

// ans2:
// Cn = ((An|Bn)|((Cn-1)|((An|An)|(Bn|Bn))))

string add(const string& a, const string& b) {
	return "((" + a + '|' + a + ")|(" + b + '|' + b + "))";
}
string mul(const string& a, const string& b) {
	return "((" + a + '|' + b + ")|(" + a + '|' + b + "))";
}

string solve1(int n) {
	string An = "A" + to_string(n);
	string Bn = "B" + to_string(n);
	if (n == 0) return mul(An, Bn);
	return add(mul(An, Bn), mul(add(An, Bn), solve1(n - 1)));
}

string solve2(int n) {
	string An = "A" + to_string(n);
	string Bn = "B" + to_string(n);
	if (n == 0) return mul(An, Bn);
	return "((" + An + '|' + Bn + ")|(" + solve2(n - 1) + "|" + add(An, Bn) + "))";
}

int count(const string& a) {
	int cnt = 0;
	for (const auto& i: a)
		cnt += (i == '|');
	return cnt;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n;
	cin >> n;

	cout << "ans1:\n";
	string ans1 = solve1(n);
	cout << ans1 << '\n';
	cout << count(ans1) << " NAND(s) used.\n";

	cout << "ans2:\n";
	string ans2 = solve2(n);
	cout << ans2 << '\n';
	cout << count(ans2) << " NAND(s) used.\n";

	return 0;
}
