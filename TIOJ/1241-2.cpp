#include <cstdio>
int t, n, cnt[2001], ans;

// 每個人只要考慮看「可能的因數」和「可能的倍數」哪邊多就放哪邊。
// proof: 假設在最佳解中，
// 某 x 在 1~n 不含自己的因數有 a 個、倍數有 b 個，
// 但被分到「因數」的因數只有 c <= a 個、
// 分到「倍數」的倍數只有 d <= b 個。
// 假設 a < b 但 c >= d，我們把 x 分去「倍數」
// 則所有 x 的倍數都丢去「倍數」一定不會比較差，
// 故最後可以換到一組 d = b 的解，
// 又 a < b 可知最後把 x 換來「因數」不會比較差。
// 反之亦然。（要小心，不是比較好，是不會更差！）

int main(){
  scanf("%d", &t);
  while (t --> 0) {
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i)
      cnt[i] = n / i - 1;

    for (int i = 1; i <= n; ++i)
      for (int j = i * 2; j <= n; j += i)
        cnt[j] -= 1;

    ans = 0;
    for (int i = 1; i <= n; ++i)
      if (cnt[i] > 0) ans += cnt[i];

		printf("%d\n", ans);
	}
}
