#pragma Ofast
#include<unistd.h>
const int S = 1<<14;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+read(0,buf,S))==buf) ? -1 : *p++;
}
char out[4], c;
int n, all, tmp;
int main(){
	while((c = readchar()) >= '0') n = n * 10 + c - '0';
	all = (1<<27) - 1;
	for(; n; --n){
		tmp = 0;
		while(c < 'a') c = readchar();
		while(c >= 'a') tmp |= 1<<(c - 'a'), c = readchar();
		all &= tmp;
	}
	if(all > 0) out[0] = 'a' + 31 - __builtin_clz(all & -all), write(1, out, 1);
	else write(1, "7122", 4);
}