#pragma GCC optimize("Ofast")
#include<cstdio>
#include<cmath>
inline int R(){
	int ans = 0, c = getchar_unlocked();
	while((c<'0'||c>'9')&&c!=EOF) c=getchar_unlocked();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=getchar_unlocked();
	return ans;
}

int m, a, b, c, ans;
int main(){
	m = R();
	for(; m; --m){
		a = R(), b = R(), c = R(), ans = b * b - 4 * a * c;
		puts(ans >= 0 and (int)sqrt(ans) * sqrt(ans) == ans ? "Yes" : "No");
	}
}