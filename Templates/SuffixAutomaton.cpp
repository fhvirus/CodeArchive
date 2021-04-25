const int N = 1e5 + 225, K = 256;
int sz, last;
int ch[N*2][K], len[N*2], par[N*2], cnt[N*2];
inline void init(){
	for(int i = 0; i <= sz; ++i){
		len[i] = 0;
		par[i] = -1;
		cnt[i] = 0;
		for(int j = 0; j < K; ++j)
			ch[i][j] = 0;
	}
	sz = 1;
	last = 0;
}
inline void add(char c){
	int cur = sz++;
	len[cur] = len[last] + 1;
	cnt[cur] = 1;
	par[cur] = 0;

	int p = last;
	while(p != -1 and ch[p][c] == 0)
		ch[p][c] = cur, p = par[p];

	if(p == -1)
		par[cur] = 0;
	else{
		int q = ch[p][c];
		if(len[p] + 1 == len[q])
			par[cur] = q;
		else{
			int clone = sz++;
			len[clone] = len[p] + 1;
			par[clone] = par[q];
			for(int i = 0; i < K; ++i)
				ch[clone][i] = ch[q][i];
			while(p != -1 and ch[p][c] == q)
				ch[p][c] = clone, p = par[p];
		}
	}

	last = cur;
}
int tmp[N];
inline void buildSAM(string s){
	init();
	for(char c: s)
		add(c);
	for(int i = 0; i < sz; ++i) tmp[i] = i;
	sort(tmp, tmp + sz, [](int a, int b){ return len[a] > len[b];});
	for(int i = 0; i < sz; ++i) cnt[par[i]] += cnt[i];
}
