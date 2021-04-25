#include<cstdio>
int t = 1;
void solve(int n, int from, int to, int tmp){
	if(n == 0) return;
	solve(n - 1, from, tmp, to);
	printf("#%d : move the dish from #%d to #%d\n", t++, from, to);
	solve(n - 1, tmp, to, from);
}
int main(){
	int n; scanf("%d", &n);
	solve(n, 1, 3, 2);
	return 0;
}