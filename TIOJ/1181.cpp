#pragma GCC optimize("Os")
#include<unistd.h>
char OB[999]; int OP;
inline char RC(){static char buf[999],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,999))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}

bool r, g, b, y, p, jizz;
char t, eek, cnt;

int main(){
	t = RC() - '0';
	eek = RC();
	if(eek <= '9' and eek >= '0') t = t * 10 + (eek ^ '0');
	for(; t; --t){
		cnt = 0;
		r = b = g = y = p = false;
		while(cnt < 72){
			eek = RC(); jizz = false;
			(eek == 'G' ? g : (eek == 'B' ? b : (eek == 'R' ? r : (eek == 'Y' ? y : (eek == 'P' ? p : jizz))))) = true;
			if(!jizz or eek == 'X' or eek == '.') ++cnt;
		}
		cnt = r + b + g + y + p + '0';
		OB[OP++] = (cnt), OB[OP++] = ('\n');
	}
	write(1,OB,OP);
}