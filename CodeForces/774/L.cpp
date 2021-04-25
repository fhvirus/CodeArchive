#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
const int N = 2e5 + 10;
int n, k;
char s[N];

inline bool check(int len){
	int last = 0, left = k - 2;
	for(int i = 1; i < n and left > 0; ++i){
		if(i - last - 1 < len) continue;
		int j = i;
		while(s[j] == '1') --j;
		if(j == last) return false;
		last = j, --left;
	}
	if(n - last - 2 > len) return false;
	return true;
}

int main(){
	scanf("%d%d%s", &n, &k, s);
	int l = 0, r = N, m;
	while(l < r){
		m = (l + r) / 2;
		if(check(m)) r = m;
		else l = m + 1;
	}
	printf("%d\n", r);
}
