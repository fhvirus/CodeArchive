#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
	string P, Q;
	cin >> P >> Q;

	string s = P + '$' + Q;
	int n = s.length();
	vector<int> fft(n, 0); // fft stands for failure function table

	for (int i = 1; i < n; ++i) {
		int j = i - 1;
		while (j > 0) {
			if (s[i] == s[fft[j]]) {
				fft[i] = fft[j] + 1;
				break;
			}
			j = fft[j] - 1;
		}
	}

	cout << end(fft)[-1] << '\n';
	return 0;
}
