#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
inline char readchar(){
	const int S = 1<<20;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}

#include<vector>
#include<algorithm>
#include<set>
std::vector<int> jizz;

int main(){
	int t, n, p[4000], eek, head;
	t = R();
	for(; t; --t){
		n = R(); jizz.clear(); head = 0; eek = 0;
		FOR(i,n<<1){
			p[i] = R();
			if(p[i] > head){
				if(eek > 0)jizz.push_back(eek);
				head = p[i];
				eek = 1;
			} else {
				eek++;
			}
		}
		jizz.push_back(eek);
		std::sort(jizz.begin(), jizz.end(), [](int a, int b){return a > b;});
		// for(int in");
		if(jizz.size() == 1 or jizz[0] > n){
			puts("NO");
			continue;
		} else if(jizz[0] == n){
			puts("YES");
			continue;
		}
		bool can[2001];
		std::fill(can, can+n+1, false);
		can[0] = true;
		for(int i: jizz){
			for(int j = n - i; j >= 0; --j){
				if(can[j]) can[j+i] = true;
			}
			// printf("can: ");
			// for(int j = 0; j <= n; ++j) printf("%d ", can[j]);
			// printf("\n");
		}
		puts(can[n] ? "YES" : "NO");
	}
	return 0;
}