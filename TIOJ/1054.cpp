#include<cstdio>
char d[7][10] = {
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday",
	"Sunday"
}, in[10];
int n;

int main(){
	scanf("%s%d", in, &n);
	if(in[0] == 'M') n += 0;
	else if(in[0] == 'T') n += (in[1] == 'u' ? 1 : 3);
	else if(in[0] == 'W') n += 2;
	else if(in[0] == 'F') n += 4;
	else n += (in[1] == 'a' ? 5 : 6);
	puts(d[n % 7]);
}