#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#include<cmath>
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
const int N = 3000001;
int n, q;
int zeros[N], negas[N];
long double lgsum[N] = {0};

int main(){
	n = R(); q = R();
	for(int i = 1, a; i <= n; ++i){
		a = R();
		zeros[i] = zeros[i-1];
		negas[i] = negas[i-1];
		lgsum[i] = lgsum[i-1];
		if(a == 0) ++zeros[i];
		else{
			if(a < 0){
				++negas[i];
				lgsum[i] += log10l(-a);
			}
			else lgsum[i] += log10l(a);
		}
	}
	for(int l, r;q;--q){
		l = R(); r = R();
		if(zeros[r] != zeros[l])
			puts("0");
		else{
			if((negas[r]-negas[l])&1) putchar('-');
			printf("%.10LfE+%1.Lf\n",
				pow10l(lgsum[r]-lgsum[l]-floorl(lgsum[r]-lgsum[l])),
				floorl(lgsum[r]-lgsum[l])
			);
		}
	}
	return 0;
}