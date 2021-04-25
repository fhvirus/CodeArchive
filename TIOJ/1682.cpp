#pragma Os
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
inline short R(){
    short ans = 0; char c = getchar_unlocked();
    while((c<'0'||c>'9')&&c!=EOF) c=getchar_unlocked();
    while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=getchar_unlocked();
    return ans;
}
inline void W(short a){
	if(a >= 10000) putchar_unlocked(a / 10000 + '0');
	if(a >= 1000) putchar_unlocked(a % 10000 / 1000 + '0');
	if(a >= 100) putchar_unlocked(a % 1000 / 100 + '0');
	if(a >= 10) putchar_unlocked(a % 100 / 10 + '0');
	putchar_unlocked(a % 10 + '0');
	putchar_unlocked(' ');
}

const int N = 200;
short n, a[N], jizz, j;

int main(){
	while((n = R()) != 0){
		FOR(i,n){
			jizz = R();
			for(j = i-1; j >= 0 and jizz < a[j]; --j)
				a[j+1] = a[j];
			a[j+1] = jizz;
		}
		FOR(i,n) W(a[i]);
		putchar_unlocked('\n');
	}
}