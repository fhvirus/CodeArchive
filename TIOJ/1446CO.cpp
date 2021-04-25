#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

inline char readchar(){
	const int S = 1<<20;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
inline void readstring(char s[]){
	int p = 0, c = readchar();
	while(c > 'z' or c < 'a') c = readchar();
	while(c <= 'z' and c >= 'a') s[p++] = c, c = readchar();
	s[p] = '\0';
}

const int MAXN = 1e5;

char s[MAXN][101];
int id[MAXN];

inline int calc(char a[], char b[]){
	int f = 0, sa = strlen(a), sb = strlen(b);
	while(f < sa and f < sb and a[f] == b[f]) ++f;
	return (sb - f) + (sa - f);
}

int main(){
	int n = R();
	for(int i = 0; i < n; ++i){
		readstring(s[i]);
		id[i] = i;
	}
	sort(id, id + n, [](int a, int b){
		return strcmp(s[a], s[b]) < 0;
	});
	long long ans = strlen(s[id[0]]) + strlen(s[id[n-1]]) + 1;
	for(int i = 1; i < n; ++i){
		ans += calc(s[id[i]], s[id[i-1]]) + 1;
	}
	printf("%lld", ans);
	return 0;
}