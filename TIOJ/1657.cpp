#include<cstdio>
inline char R(){
	char ans = 0, c = getchar_unlocked();
	while((c<'0'||c>'9')&&c!=EOF) c=getchar_unlocked();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=getchar_unlocked();
	return ans;
}
inline void W(short n){
    if(n >= 100) putchar_unlocked(n / 100 + '0');
    if(n >= 10) putchar_unlocked(n % 100 / 10 + '0');
    putchar_unlocked(n % 10 + '0');
}

short n, m;
int main(){
	while(true){
		n = R(), m = R();
		if(n == 0) break;
		for(int i = 1; i <= n; ++i){
			for(int j = 1; j <= m; ++j){
				W(i);
				putchar_unlocked('*');
				W(j);
				putchar_unlocked('=');
				W(i*j);
				if(j < m) putchar_unlocked(' ');
			}
			putchar_unlocked('\n');
		}
	}
}