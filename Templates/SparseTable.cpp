const int L = 17 + 1, N = 1e5;
int val[L][N];
inline void initSparse(){
	for(int i = 0; i < n; ++i) val[0][i] = R();
	for(int l = 1; l < L; ++l)
		for(int i = 0; i + (1<<l) <= n; ++i)
			val[l][i] = max(val[l-1][i], val[l-1][i + (1<<(l-1))]);
}
inline int query(int l, int r){ // [l, r]
	int d = 31 - __builtin_clz(r - l + 1);
	return max(val[d][l], val[d][r - (1<<d) + 1]);
}