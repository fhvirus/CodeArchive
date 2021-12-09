#include <cstdio>
#include <algorithm>
using namespace std;

const int kP = 50;
int n, ans[kP + 2];
int a[kP * 2 + 3];
int b[kP * 2 + 3];

int main() {
	scanf("%d", &n);
	while ((ans[0] + 1) * (ans[0] + 1) <= n) ++ans[0];
	a[0] = ans[0] * ans[0];
	for (int i = 1; i <= kP + 1; ++i) {
		for (ans[i] = 0; a[0] < n; ++ans[i]) {
			for (int j = 0; j < i; ++j) b[j] = a[j];
			for (int j = i; j <= 2 * i; ++j)
				b[j] = a[j] + 2 * ans[j - i];
			b[2 * i] += 1;
			for (int j = 2 * i; j > 0; --j) {
				b[j - 1] += b[j] / 10;
				b[j] %= 10;
			}
			swap(a, b);
		}
		if (ans[i] > 0) --ans[i], swap(a, b);
	}
	if (ans[kP + 1] >= 5) ++ans[kP];
	
	printf("%d.", ans[0]);
	for (int i = 1; i <= kP; ++i)
		putchar(ans[i] + '0');

	return 0;
}
