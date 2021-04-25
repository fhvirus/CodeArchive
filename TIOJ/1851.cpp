#include<cstdio>
#include<cmath>
int main(){
	unsigned n;
	while(scanf("%u", &n), n){
		unsigned x = sqrt(n);
		puts(x * x == n ? "yes" : "no");
	}
}