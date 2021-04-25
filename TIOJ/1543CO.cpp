#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
inline char gc(){
	const int S = 1<<20;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
char outbuf[1<<20];
int outp;
inline void W(int n){
    int rev = n, count = 0;
    while((rev % 10) == 0) count++, rev /= 10;
    rev = 0;
    while(n != 0) rev = (rev<<3) + (rev<<1) + n % 10, n /= 10;
    while(rev != 0) outbuf[outp++] = (rev % 10 + '0'), rev /= 10;
    while(count--) outbuf[outp++] = '0';
}

struct box{
	int a, b;
	box(){}
	box(int a, int b): a(a), b(b){}
};
bool can(box a, box b){
	return a.a <= b.a and a.b <= b.b;
}

box s[800000];
int sp = 0;

int main(){
	int cnt = 0, a, b;
	char eek;
	while(true){
		while((eek = gc()) != 'B' and eek != 'Q' and eek != 'E');
		if(eek == 'E') break;
		if(eek == 'Q'){
			outbuf[outp++] = 'Q';
			outbuf[outp++] = 'u';
			outbuf[outp++] = 'e';
			outbuf[outp++] = 'r';
			outbuf[outp++] = 'y';
			outbuf[outp++] = ' ';
			W(++cnt);
			outbuf[outp++] = ':';
			outbuf[outp++] = ' ';
			if(sp == 0){
				outbuf[outp++] = 'N';
				outbuf[outp++] = 'o';
				outbuf[outp++] = 'n';
				outbuf[outp++] = 'e';
			}
			else if(sp == 1){
				outbuf[outp++] = '1';
				outbuf[outp++] = ' ';
				outbuf[outp++] = 'b';
				outbuf[outp++] = 'o';
				outbuf[outp++] = 'x';
			}
			else{
				W(sp);
				outbuf[outp++] = ' ';
				outbuf[outp++] = 'b';
				outbuf[outp++] = 'o';
				outbuf[outp++] = 'x';
				outbuf[outp++] = 'e';
				outbuf[outp++] = 's';
			}
			outbuf[outp++] = '.';
			outbuf[outp++] = '\n';
			if(outp > (1<<20)-64) fwrite(outbuf, 1, outp, stdout), outp = 0;
		}
		else{
			a = 0, b = 0, eek = gc();
			while(eek > '9' or eek < '0') eek = gc();
			while(eek <= '9' and eek >= '0') a = (a<<3)+(a<<1)+(eek-'0'), eek = gc();
			while(eek > '9' or eek < '0') eek = gc();
			while(eek <= '9' and eek >= '0') b = (b<<3)+(b<<1)+(eek-'0'), eek = gc();
			box t(a, b);
			while(sp > 0 and !can(t, s[sp-1])) --sp;
			s[sp++] = t;
		}
	}
	fwrite(outbuf, 1, outp, stdout);
	return 0;
}