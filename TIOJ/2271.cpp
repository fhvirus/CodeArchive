#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int N;
	cin >> N;

	vector<int> a(N);
	for (int& i: a)
		cin >> i;

	nth_element(begin(a), begin(a) + N / 2, end(a));

	cout << accumulate(begin(a), begin(a) + N / 2, 0ll) << '\n';

	return 0;
}

