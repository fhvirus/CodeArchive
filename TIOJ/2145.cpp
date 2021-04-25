#pragma Os
#include<unistd.h>
#include<cstring>
char eek[4785158];
int N, t, tp[7] = {1, 3, 9, 27, 81, 243, 729};

int nstack[50], istack[50], jstack[50], ptr;
int n, i, j, jizz, a, k;

char yike[1];

int main(){
	read(0, yike, 1);
	t = yike[0] - '0';
	N = 1;
	for(int i = 0; i < t; ++i) N *= 3;
	memset(eek, '.', N*(N+1));

	nstack[ptr] = t, istack[ptr] = 0, jstack[ptr] = 0, ++ptr;
	while(ptr > 0){
		--ptr, n = nstack[ptr], i = istack[ptr], j = jstack[ptr];
		if(n == 1){
			eek[(i+1)*(N+1) + j + 1] = '#';
			continue;
		}
		--n;
		jizz = tp[n];
		nstack[ptr] = n, istack[ptr] = i, jstack[ptr] = j, ++ptr;
		nstack[ptr] = n, istack[ptr] = i+jizz, jstack[ptr] = j, ++ptr;
		nstack[ptr] = n, istack[ptr] = i+(jizz<<1), jstack[ptr] = j, ++ptr;
		nstack[ptr] = n, istack[ptr] = i, jstack[ptr] = j+jizz, ++ptr;
		nstack[ptr] = n, istack[ptr] = i+(jizz<<1), jstack[ptr] = j+jizz, ++ptr;
		nstack[ptr] = n, istack[ptr] = i, jstack[ptr] = j+(jizz<<1), ++ptr;
		nstack[ptr] = n, istack[ptr] = i+jizz, jstack[ptr] = j+(jizz<<1), ++ptr;
		nstack[ptr] = n, istack[ptr] = i+(jizz<<1), jstack[ptr] = j+(jizz<<1), ++ptr;
		for(a = 0, k = (i + jizz + a) * (N+1) + j + jizz; a < jizz; ++a, k += N+1)
			memset(eek + k, '#', jizz);
	}

	for(int i = 0; i < N; ++i)
		eek[(i+1) * (N+1) - 1] = '\n';
	write(1, eek, N*(N+1));
}