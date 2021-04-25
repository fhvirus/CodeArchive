#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma loop_opt(on)
#include"lib1087.h"

int a[3] = {10, 15, 20}, compile, comnum;
int main(){
	Initialize();
	while(true){
		if((a[0] ^ a[1]) < a[2]){
			Take_Stone(3, a[2] - (a[0] ^ a[1]), &compile, &comnum);
			a[2] = a[0] ^ a[1];
		} else if((a[1] ^ a[2]) < a[0]){
			Take_Stone(1, a[0] - (a[1] ^ a[2]), &compile, &comnum);
			a[0] = a[1] ^ a[2];
		} else if((a[2] ^ a[0]) < a[1]){
			Take_Stone(2, a[1] - (a[2] ^ a[0]), &compile, &comnum);
			a[1] = a[2] ^ a[0];
		}
		a[compile - 1] -= comnum;
	}
	return 0;
}