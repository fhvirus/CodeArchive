#pragma GCC optimize("Ofast")
#include<cstdio>
#include<cstring>
int n, z[10003];
char in[5001], s[10003];
int manacher(){
	int n = strlen(in);
	memset(s, '_', n*2+1);
	memset(z, 0, sizeof z);
	
	for(int i = 0; i < n; ++i)
		s[i*2+1] = in[i];
	n = n * 2 + 1;

	z[0] = 1;
	int l = 0, r = 0, m = 0;
	int maxlen = 0;
	for(int i = 1; i < n; ++i){
		if(i > r){
			m = i, l = m-1, r = m+1;
			while(l >= 0 and r < n and s[l] == s[r])
				--l, ++r;
			++l, --r;
			z[i] = (r - l) / 2 + 1;
		} else {
			if(i + z[m*2 - i] - 1 > r)
				z[i] = r - i + 1;
			else if(i + z[m*2 - i] - 1 < r)
				z[i] = z[m*2 - i];
			else{
				m = i, l = m * 2 - r;
				while(l >= 0 and r < n and s[l] == s[r])
					--l, ++r;
				++l, --r;
				z[i] = (r - l) / 2 + 1;
			}
		}
		maxlen = maxlen > z[i] ? maxlen : z[i];
		if(r == n-1) break;
	}
	return maxlen-1;
}
int main(){
	scanf("%d", &n);
	for(; n; --n)
		scanf("%s", in), printf("%d\n", manacher());
}
