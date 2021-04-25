#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#include<cstring>
#include<algorithm>
const int S = 1<<24;
char buf[S];
int n;
int main(){
	fread(buf,1,S,stdin);
	n = strlen(buf);
	fwrite(buf,1,n,stdout);
	std::reverse(buf, buf+n);
	fwrite(buf+1,1,n-1,stdout);
	return 0;
}