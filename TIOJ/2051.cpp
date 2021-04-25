#pragma GCC optimize("Os")
#include<unistd.h>
char OB[1000]; int OP;
inline void PC(char c){ OB[OP++] = c;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';}

char s[256];
int n, cnt[26], cntt[26][26];
inline void read(){
	n = read(0,s,256);
	while(s[n-1] == ' ' or s[n-1] == '\n') --n;
	s[n] = '\0';
}
inline int readint(int p, int r = n){
	int ans = 0;
	while(p < r and s[p] <= '9' and s[p] >= '0'){
		ans = ans * 10 + (s[p] - '0');
		p++;
	}
	return ans == 0 ? 1 : ans;
}
inline void output(){
	for(int i = 0; i < n; ++i) PC(s[i]);
	PC('\n');
	for(int i = 0; i < 26; ++i){
		if(cnt[i] != 0) PC('A' + i), PC(':'), W(cnt[i]);
		for(int j = 0; j < 26; ++j){
			if(cntt[i][j] != 0) PC('A' + i), PC('a' + j), PC(':'), W(cntt[i][j]);
		}
	}
}
inline int findPair(int p, int r){
	int b = 1;
	for(++p ; p < r; ++p){
		if(s[p] == '(') ++b;
		if(s[p] == ')') --b;
		if(b == 0) return p;
	}
	return r;
}

void solve(int l, int r, int mul){
	bool two;
	for(int i = l; i < r; ++i){
		if(s[i] == '('){
			int next = findPair(i, r), m = readint(next+1);
			solve(i+1, next, m * mul);
			i = next;
		}
		if(s[i] >= 'A' and s[i] <= 'Z'){
			two = (i < r-1 and s[i+1] >= 'a' and s[i+1] <= 'z');
			int p = i + (two ? 2 : 1), ans = readint(p, r);
			if(two){
				cntt[s[i]-'A'][s[i+1]-'a'] += ans*mul;
			}
			else{
				cnt[s[i]-'A'] += ans*mul;
			}
		}
	}
}

int main(){
	read();
	solve(0, n, 1);
	output();
	write(1,OB,OP);
}