#include "lib1087.h"

signed main(){
	Initialize();
	int a[3] = { 10, 15, 20 };
	while(true){
		int s = a[0] xor a[1] xor a[2] xor ( (a[0] > 1) + (a[1] > 1) + (a[2] > 1) <= 1);
		for(int i = 0; i < 3; ++i){
			int d = a[i] - (s xor a[i]);
			if(d <= 0) continue;
			a[i] -= d;
			Take_Stone(i+1, d, &i, &d);
			a[i-1] -= d;
			break;
		}
	}
	return 0;
}
