#include<cstdio>
inline int R(){
	int ans = 0, c = getchar_unlocked();
	while((c<'0'||c>'9')&&c!=EOF) c=getchar_unlocked();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=getchar_unlocked();
	return ans;
}
inline int min(int a, int b){
	return a < b ? a : b;
}

int perm[250000];

int main(){
	int n = R(), m = R()-1, k = R();

	int id = 0;
	for(int i = 0; i <= (n-1)<<1; ++i)
		for(int j = min(i, n-1); j >= 0 and i-j < n; --j)
			perm[(i-j)*n+j] = id++;

	int cnt = 0, cur = m;
	do{
		cur = perm[cur];
		++cnt;
	}while(cur != m);

	k %= cnt;
	for(int i = 0; i < k; ++i) m = perm[m];
	printf("%d", m + 1);
}