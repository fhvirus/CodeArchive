#include<cstdio>

int main(){
	int n;
	while(scanf("%d", &n) != -1){
		int sum = 0, win = 0, mx = 0, mn = 201;
		for(int i = 0; i < n; ++i){
			int t;
			scanf("%d", &t);
			if(t < 0) t = -t;
			else ++win;
			sum += t;
			mx = mx > t ? mx : t;
			mn = mn < t ? mn : t;
		}
		printf("Average time: %.3f sec(s).\nWinning rate: %.3f %%.",
				(float)(sum - mx - mn) / (n - 2),
				(float)win * 100 / n);
	}
}