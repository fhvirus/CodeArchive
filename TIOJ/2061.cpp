#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
char s[200015], out[2000], prv[10001][10001];
int len, cnt[10], lcs[10001], p;

inline void print(int l, int i, int j){
	while(l > 0){
		if(prv[i][j] == 0)
			--l, out[p++] = s[i], --i, --j;
		else if(prv[i][j] == 1)
			--j;
		else
			--i;
	}
}

int main(){
	len = fread(s+1, 1, 200010, stdin);
	if(len >= 10000){
		for(int i = 1; i <= len; ++i)
			cnt[s[i] - '0']++;
		for(int i = 0; i < 10; ++i)
			if(cnt[i] >= 1000){
				for(int j = 0; j < 1000; ++j)
					out[j] = '0' + i;
				fwrite(out, 1, 1000, stdout);
				return 0;
			}
	}

	for(int i = 1; i <= len; ++i){
		int jizz = 0, eek;
		for(int j = 1; j <= len; ++j){
			if(s[i] == s[len - j + 1])
				eek = lcs[j-1] + 1, prv[i][j] = 0;
			else if(jizz > lcs[j])
				eek = jizz, prv[i][j] = 1;
			else
				eek = lcs[j], prv[i][j] = 2;
			lcs[j-1] = jizz, jizz = eek;
		}
		lcs[len] = eek;
		if(i < len / 2 and eek >= 500){
			print(eek, i, len);
			for(int i = 0; i < p; ++i)
				s[p - i - 1] = out[i];
			fwrite(s, 1, p, stdout);
			fwrite(out, 1, p, stdout);
			return 0;
		}
	}

	print(lcs[len], len, len);
	fwrite(out, 1, p, stdout);
}