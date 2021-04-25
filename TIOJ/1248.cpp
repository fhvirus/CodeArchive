#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#include<cstring>
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}

#define BASE 10000
#define BASELEN 4
char inbuf[1000];

struct bigint{
	int val[60], len;
	bool sign;
	bigint(){
		val[0] = 0;
		len = 1;
		sign = false;
	}
	bool get(){
		if(scanf("%s", inbuf) == EOF) return false;
		sign = false;
		len = -1;
		for(int l = strlen(inbuf)-1, cnt = 0, d = 1; l >= 0; --l){
			if(cnt == 0) ++len, val[len] = 0, d = 1;
			val[len] += (inbuf[l] ^ '0') * d, d *= 10;
			++cnt;
			if(cnt == BASELEN) cnt = 0;
		}
		++len;
		return true;
	}
	void print(){
		if(sign) putchar('-');
		int l = len-1;
		printf("%d", val[l--]);
		while(l >= 0) printf("%04d", val[l--]);
	}
	bool operator<(const bigint &rhs){
		if(sign != rhs.sign) return sign > rhs.sign;
		if(len != rhs.len) return (len < rhs.len) ^ (!sign);
		for(int i = len-1; i >= 0; --i)
			if(val[i] != rhs.val[i]) return (val[i] < rhs.val[i]) ^ (!sign);
		return false;
	}
	void trim(){
		while(len > 0 and val[len-1] == 0) --len;
		if(len == 0) len = 1, sign = false;
	}
};

bigint add(bigint a, bigint b){
	return bigint();
}
bigint sub(bigint a, bigint b){
	if(a < b){
		bigint c = sub(b, a);
		c.sign = true;
		return c;
	}
	return bigint();
}
bigint mul(bigint a, bigint b){
	return bigint();	
}
bigint div(bigint a, bigint b){
	return bigint();
}
bigint mod(bigint a, bigint b){
	bigint c = div(a, b);
	bigint d = mul(b, c);
	return sub(a, d);
}

bigint a, b, c, d;
char move;

int main(){
	while(a.get()){
		move = 0;
		while(move!='+' and move!='-' and move!='*' and move!='/') move = getchar();
		b.get();
		if(move == '+') c = add(a, b);
		else if(move == '-') c = sub(a, b);
		else if(move == '8') c = mul(a, b);
		else if(move == '/') c = div(a, b), d = mod(a, b);
		c.print();
		if(move == '/') printf("..."), d.print();
		puts("");
	}
}