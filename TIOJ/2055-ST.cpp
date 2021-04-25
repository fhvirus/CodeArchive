1#include<cstdio>

constexpr int MAXN = 1e6;
constexpr int MAXL = 20;

int readint(){
	int ans = 0;
	bool minus = false;
	char ch = getchar();
	while(true){
		if(ch == '-') break;
		if(ch >= '0' and ch <= '9') break;
		ch = getchar();
	}
	if(ch == '-') minus = true;
	else ans = ch - '0';
	while(true){
		ch = getchar();
		if(ch > '9' or ch < '0') break;
		ans = ans * 10 + (ch - '0');
	}
	return minus ? -ans : ans;
}

inline int min(int a, int b){
	return a < b ? a : b;
}

inline int HB(int v){
	int hb = MAXL;
	for(;hb >= 0; --hb)
		if(v & (1 << hb)) return hb;
	return 0;
}

int minval[MAXL][MAXN];
void init(int n){
	for(int i = 0; i < n; i++) minval[0][i] = readint();
	for(int j = 1; j < MAXL; j++){
		for(int i = 0; i + (1 << j) - 1 < n; i++){
			minval[j][i] = min(
				minval[j-1][i],
				minval[j-1][i + (1 << (j-1))]
			);
		}
	}
}
int query(int l, int r){
	int hb = HB(r-l+1);
	return min(minval[hb][l], minval[hb][r - (1 << hb) + 1]);
}

int main(){
	int n;
	n = readint();
	init(n);
	int l, r;
	for(int i = 0; i < n; i++){
		l = readint(), r = readint();
		printf("%d\n", query(l-1, r-1) + 1);
	}
	return 0;
}