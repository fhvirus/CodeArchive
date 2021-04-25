#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#include<cstring>

inline char max(char a, char b){
	return a > b ? a : b;
}
inline char min(char a, char b){
	return a < b ? a : b;
}

char s[32], len, ans, eek[64], z[64];

int main(){
	while(scanf("%[^\n]", s) != EOF){
		getchar();

		len = strlen(s);
		memset(eek, '_', sizeof(eek));
		for(int i = 0; i < len; ++i)
			eek[(i<<1)+1] = s[i];
		len = (len << 1) + 1;
		z[0] = 1; ans = 0;
		int l = 0, r = 0;
		for(int i = 1; i < len; ++i){
			z[i] = r > i ? min(z[(l<<1)-i], r - i) : 1;
			while(i - z[i] >= 0 and i + z[i] < len and eek[i-z[i]] == eek[i+z[i]])
				++z[i];
			if(i + z[i] > r) l = i, r = i + z[i];
			ans = max(ans, z[i]);
		}

		printf("%d\n", ans-1);
	}
	return 0;
}