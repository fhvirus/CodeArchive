#pragma Ofast
#include<unistd.h>
const int S = 1<<10;
char outbuf[S], eek[20];
int outp, eekp;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return p == q and (q = (p = buf) + read(0, buf, S)) == buf ? -1 : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while(c >= '0') ans = ans * 10 + (c ^ '0'), c = readchar();
	return ans;
}
inline int RS(char s[]){
	int len = 1;
	while((s[0] = readchar()) < 'a');
	while((s[len] = readchar()) >= 'a') ++len;
	return len;
}
inline void W(long long n){
    if(n == 0) outbuf[outp++] = '0';
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = '\n';
    if(outp > S-15) write(1, outbuf, outp), outp = 0;
}
int n;
long long frac[21] = {1};
char s[42], cnt[26], len;
int main(){
	for(int i = 1; i <= 20; ++i)
		frac[i] = frac[i-1] * i;
	for(n = R(); n; --n){
		len = RS(s);
		for(int i = 0; i < 26; ++i) cnt[i] = 0;
		for(int i = 0; i < len; ++i) cnt[s[i] - 'a']++;
		int odd = 0;
		for(int i = 0; i < 26; ++i)
			odd += (cnt[i] & 1);
		if(odd > 1){ W(0); continue;}

		long long ans = frac[len / 2];
		for(int i = 0; i < 26; ++i)
			ans /= frac[cnt[i] / 2];
		W(ans);
	}
	write(1, outbuf, outp);
}