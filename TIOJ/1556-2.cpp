// prprprpony orz
// adapted from https://prprprpony.github.io/blog/2017/04/23/tioj-1556/

#include <iostream>

int main() {

	long long N;
	std::cin >> N;

	long long ans = 0, i = 1;
	for (; i * i <= N; ++i) ans += N / i;
	ans *= 2;
	ans -= (i - 1) * (i - 1);
	ans -= N;

	std::cout << ans << '\n';

	return 0;
}
