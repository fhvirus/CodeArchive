#pragma Os
#include<unistd.h>
const int S = 400;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+read(0,buf,S))==buf) ? -1 : *p++;
}
inline long long R(){
	long long ans = 0; char c = readchar();
	while(c<'0'&&c!=-1) c=readchar();
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
	return ans;
}
char outbuf[S], eek[20];
int outp, eekp;
inline void W(long long n){
    if(n == 0) outbuf[outp++] = '0';
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = '\n';
}

const int N = 600000000, NN = 24494;
bool np[NN+1];
int primes[2717], e;
long long n;
int main(){
	np[0] = np[1] = true;
	for(int i = 2; i <= NN; ++i){
		if(!np[i]) primes[e++] = i;
		for(int p = 0; p < e; ++p){
			if(i * primes[p] > NN) break;
			np[i * primes[p]] = true;
			if(i % primes[p] == 0) break;
		}
	}
	while(n = R(), n != 0){
		if(n > N){ W(n-1); continue;}
		if(n == 1){ W(1); continue;}
		int ans = 1;
		for(int p = 0; p < e; ++p){
			if(primes[p] * primes[p] > n) break;
			if(n % primes[p] != 0) continue;
			int k = 0, jizz = primes[p];
			while(n % (jizz * primes[p]) == 0) ++k, jizz *= primes[p];
			n /= jizz;
			jizz /= primes[p];
			ans *= jizz * (primes[p] - 1);
		}
		if(n > 1) ans *= n - 1;
		W(ans);
	}
	write(1, outbuf, outp);
}