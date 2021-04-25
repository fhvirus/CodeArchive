#include<cstdio>
int main(){
	long long r, c, ans;
	scanf("%lld %lld", &r, &c);
	ans = r;
	for(int i = 1; i < c; ++i){
		ans *= (r-i);
		ans /= i;
	}
	printf("%lld", ans);
}