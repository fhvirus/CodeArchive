#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<unistd.h>
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+read(0,buf,S))==buf) ? -1 : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=ans*10+(c^'0'), c=readchar();
	return ans;
}
char outbuf[S];
int outp;
inline void W(bool ans){
	ans ? 
		(outbuf[outp++] = 'Y', outbuf[outp++] = 'e', outbuf[outp++] = 's') :
		(outbuf[outp++] = 'N', outbuf[outp++] = 'o');
	outbuf[outp++] = '\n';
}
#define ll long long
#define P 998244353ll
#define M 1004535809
int last, head, tail;
int t, n, m, in;
bool ans;
int main(){
	t = R();
	for(; t; --t){
		n = R(), m = R(), ans = true;
		if(n == 1){
			for(int i = 0; i < m; ++i)
				in = R();
			W(true); continue;
		}
		if(m == 1){
			for(int i = 0; i < n; ++i)
				in = R();
			W(true); continue;
		}

		last = 0;
		for(int i = 1; i < m; ++i)
			in = R(),
			last = (last * P + in) % M;
		in = R();

		for(int i = 1; i < n; ++i){
			head = R(), tail = 0;
			for(int j = 1; j < m - 1; ++j)
				in = R(),
				head = (head * P + in) % M,
				tail = (tail * P + in) % M;
			in = R(), tail = (tail * P + in) % M;

			ans &= (tail == last);
			last = head;
		}
		W(ans);
	}
	write(1, outbuf, outp);
}