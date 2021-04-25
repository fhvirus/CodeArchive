#pragma GCC optimize("Ofast")
#pragma loop-opt(on)
#include<cstdio>
#include<cstring>
#include<stack>

inline int max(int a, int b){
	return a > b ? a : b;
}

char eek[100001];
int leafcnt, depth, d, ary, len;
int a[50000], p = 0;

int main(){
	while(scanf("%[^\n]", eek) != EOF){
		getchar();
		leafcnt = ary = 0;
		depth = d = 1;
		len = strlen(eek);

		a[p++] = 0;
		for(int i = 0; i < len; ++i){
			if(eek[i] == '('){
				a[p-1]++;
				a[p++] = 0;
				++d;
			} else if(eek[i] == ')'){
				ary = max(ary, a[--p]);
				--d;
			}
			depth = max(depth, d);
			if(eek[i] == '*'){
				++a[p-1];
				++leafcnt;
			}
		}

		printf("%d %d %d\n", leafcnt, depth, ary);
	}
	return 0;
}