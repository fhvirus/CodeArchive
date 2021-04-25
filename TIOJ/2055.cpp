#include<cstdio>

int val[2000000] = {0}, n;

inline int readuint(){
	unsigned int ans = 0;
	char ch = getchar();
	while(true){
		if(ch >= '0' and ch <= '9') break;
		ch = getchar();
	}
	ans = ch - '0';
	while(true){
		ch = getchar();
		if(ch > '9' or ch < '0') break;
		ans = (ans<<3) + (ans<<1) + (ch - '0');
	}
	return ans;
}

inline int min(int a, int b){
	return a < b ? a : b;
}


int main(){
	n = readuint();
	//init
	for(int i = n; i < (n<<1); ++i){
		val[i] = readuint();
	}
	for(int i = n-1; i; --i){
		val[i] = min(val[(i << 1)], val[(i << 1) + 1]);
	}

	//query
	int l, r, ans;
	for(int i = 0; i < n; i++){
		l = readuint()-1+n, r = readuint()-1+n;
		ans = 1e7;
		for(;l <= r; l >>= 1, r >>= 1){
			if(l & 1)
				ans = min(ans, val[l++]);
			if(!(r & 1))
				ans = min(ans, val[r--]);
		}
		printf("%d\n", ans+1);
	}
	return 0;
}