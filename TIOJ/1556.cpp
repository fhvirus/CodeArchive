#include <iostream>

int main() {

	long long N;
	std::cin >> N;

	long long ans = 0;
	for (long long i = 1, j, d; i <= N; i = j + 1) {
		d = N / i;
		j = N / d;
		ans += d * (j - i + 1);
	}

	std::cout << ans - N << '\n';

	return 0;
}
