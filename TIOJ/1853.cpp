#pragma GCC optimize("Ofast")
#include<unistd.h>
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

const int N = 1e7 + 225;
char s[N];

int main(){
	read(0,s,N);
	int n = 0, p = 0;
	while(s[p] >= '0') n = n * 10 + s[p] - '0', ++p;
	while(s[p] < '0') ++p;

	int ans = 0;
	bool cur = true;
	for(int i = p; i < p + n - 1; ++i){
		if(s[i] == '0' + cur)
			++ans, cur ^= (s[i+1] == s[i]);
	}
	if(s[p] == '0' + cur) ++ans;
	W(ans);
}