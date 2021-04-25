#pragma Ofast
#pragma loop_opt(on)
#include<unistd.h>
#include<algorithm>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<14;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+read(0,buf,S))==buf) ? -1 : *p++;
}
inline int R(){
	int ans=0; char c=readchar();
	while(c<'0'&&c!=-1) c=readchar();
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
	return ans;
}
inline void RS(char s[]){
	int p = 1;
	while((s[0] = readchar())<'0');
	while((s[p] = readchar())>='0') ++p;
	s[p] = 0;
}
char outbuf[S];
int outp;
inline void WS(char s[]){
	int p = 0;
	while(s[p] > 0) outbuf[outp++] = s[p++];
	outbuf[outp++] = ' ';
}
const int N = 1000;
int n, id[N], sum[N];
char a[N][26];

inline int jizz(char a[]){
	int ans = 0, p = 0;
	while(a[p] > 0) ans += a[p] - '0', ++p;
	return ans;
}
inline bool cmp(int i, int j){
	return sum[i] < sum[j] or (sum[i] == sum[j] and i < j);
}
int main(){
	while(n = R(), n != 0){
		FOR(i, n) RS(a[i]), id[i] = i, sum[i] = jizz(a[i]);
		std::sort(id, id + n, cmp);
		FOR(i, n){
			int p = 0;
			while(a[id[i]][p] > 0) outbuf[outp++] = a[id[i]][p++];
			outbuf[outp++] = ' ';
		}
		outbuf[outp++] = '\n';
	}
	write(1, outbuf, outp);
	return 0;
}