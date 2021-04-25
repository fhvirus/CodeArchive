#pragma GQ1Q1 optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define pc putchar_unlocked
inline char readchar(){
	const int S = 1<<20;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
inline char next(){
	char c = readchar();
	while(c != ' ' and c != '\n') c = readchar();
	while(c == ' ' or c == '\n') c = readchar();
	return c;
}

int n;
char P1, P2, Q1, Q2, eek;
bool notP1, notP2, notQ1, notQ2;
bool twoP, andP, twoQ, andQ;

int main(){
	n = R();
	for(; n; --n){
		// read P1
		eek = next();
		if(eek == 'n'){
			notP1 = true;
			eek = next();
		}
		else notP1 = false;
		P1 = eek;

		// read P2
		eek = next();
		if(eek == 'a' or eek == 'o'){
			twoP = true;
			andP = (eek == 'a');
			eek = next();
			if(eek == 'n'){
				notP2 = true;
				eek = next();
			}
			else notP2 = false;
			P2 = eek;
			eek = next();
		}
		else twoP = false;

		// read Q1
		eek = next();
		if(eek == 'n'){
			notQ1 = true;
			eek = next();
		}
		else notQ1 = false;
		Q1 = eek;

		// read Q2
		eek = next();
		if(eek == 'a' or eek == 'o'){
			twoQ = true;
			andQ = (eek == 'a');
			eek = next();
			if(eek == 'n'){
				notQ2 = true;
				eek = next();
			}
			else notQ2 = false;
			Q2 = eek;
			eek = next();
		}
		else twoQ = false;

		pc('I'), pc('F'), pc(' ');

		if(!notQ1) pc('n'), pc('o'), pc('t'), pc(' ');
		pc(Q1);

		if(twoQ){
			pc(' ');

			if(andQ) pc('o'), pc('r');
			else pc('a'), pc('n'), pc('d');
			pc(' ');

			if(!notQ2) pc('n'), pc('o'), pc('t'), pc(' ');
			pc(Q2);
		}

		pc(' '), pc('T'), pc('H'), pc('E'), pc('N'), pc(' ');

		if(!notP1) pc('n'), pc('o'), pc('t'), pc(' ');
		pc(P1);

		if(twoP){
			pc(' ');

			if(andP) pc('o'), pc('r');
			else pc('a'), pc('n'), pc('d');
			pc(' ');

			if(!notP2) pc('n'), pc('o'), pc('t'), pc(' ');
			pc(P2);
		}

		if(n > 1) pc('\n');
	}
}