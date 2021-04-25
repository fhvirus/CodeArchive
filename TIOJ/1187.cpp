#include<cstdio>
char c;
inline int R(){
	int ans = 0; c = getchar_unlocked();
	while((c<'0'||c>'9')) c=getchar_unlocked();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=getchar_unlocked();
	return ans;
}
inline char readint(){
	c = getchar_unlocked();
	while(c > '9' or c < '0') c = getchar_unlocked();
	if(c == '1') return (getchar_unlocked() == '0') ? 10 : 1;
	return c - '0';
}

int n, sum;
char eek, mn, mx;

int main(){
	while(true){
		n = R();
		if(n == 0) break;
		sum = 0; mn = 127; mx = -128;
		for(int i = 0; i < n; ++i){
			eek = readint();
			mn = mn < eek ? mn : eek;
			mx = mx > eek ? mx : eek;
			sum += eek;
		}
		sum = ((sum-mn-mx) * 1000 / (n-2) + 5) / 10;
		if(sum == 1000){
			putchar_unlocked('1');
			putchar_unlocked('0');
		}
		else putchar_unlocked(sum / 100 + '0');
		putchar_unlocked('.');
		putchar_unlocked((sum % 100) / 10 + '0');
		putchar_unlocked(sum % 10 + '0');
		putchar_unlocked('\n');
	}
	return 0;
}