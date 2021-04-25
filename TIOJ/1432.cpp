#pragma GCC optimize("Os")
#include<unistd.h>
char OB[500]; int OP;
inline char RC(){static char buf[500],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,500))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>500)write(1,OB,OP),OP=0;}

int n, w, s[1000];
inline bool check(int k){
	int sum = 0, cnt = 0;
	for(int i = 0; i < n; ++i){
		if(s[i] > k) return false;
		if(sum + s[i] > k){
			++cnt;
			sum = s[i];
			if(cnt > w) return false;
		} else {
			sum += s[i];
		}
	}
	return true;
}

int main(){
	int l, r, m;
	while(true){
		n = R(); w = R();
		if(n == 0) break;
		for(int i = 0; i < n; ++i) s[i] = R();
		l = 0, r = 1000000;
		while(r > l){
			m = (l + r) >> 1;
			(check(m) ? r = m : l = m + 1);
		}
		W(l);
	}
	write(1,OB,OP);
}