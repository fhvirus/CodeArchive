#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
inline char readchar(){
	const int S = 1<<20;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

const int N = 1<<20;
struct lenSegTree{
private:
	int sum[N<<1];
	int len[N<<1];
	void pull(int p){
		for(int h = 0; p > 0; p >>= 1, ++h){
			if(sum[p]) len[p] = 1<<h;
			else len[p] = h ? len[p<<1] + len[p<<1|1] : 0;
			// printf("Pulling: %d\n", p);
		}
	}
public:
	inline void init(){
		// for(int i = 0; i < N<<1; ++i) sum[i] = 0;
	}
	
	// for debug
	inline void print(){
		printf("SegTree sum: \n");
		for(int l = 1; l <= N; l<<=1){
			for(int i = 0; i < l; ++i){
				printf("%3d ", sum[i+l]);
			}
			printf("\n");
		}
		printf("\n SegTree len: \n");
		for(int l = 1; l <= N; l<<=1){
			for(int i = 0; i < l; ++i){
				printf("%3d ", len[i+l]);
			}
			printf("\n");
		}
		printf("\n\n\n");
	}

	inline void modify(int l, int r, int v){
		int tl = l, tr = r, h = 0;
		// printf("Modifying: %d ~ %d with val %d\n", l, r, v);
		for(l += N, r += N; l < r; l >>= 1, r >>= 1, ++h){
			if(l&1){
				sum[l] += v;
				if(sum[l]) len[l] = 1<<h;
				else len[l] = h ? len[l<<1] + len[l<<1|1] : 0;
				++l;
			}
			if(r&1){
				--r;
				sum[r] += v;
				if(sum[r]) len[r] = 1<<h;
				else len[r] = h ? len[r<<1] + len[r<<1|1] : 0;
			}
		}
		pull(tl + N), pull(tr-1 + N);
		// print();
	}

	inline long long query(){
		return len[1];
	}
} tree;

// int main(){
// 	tree.init();
// 	tree.print();

// 	tree.modify(0, 8, 1);
// 	tree.print();

// 	tree.modify(1, 3, -1);
// 	tree.print();
// }
#include<algorithm>
struct edge{
	int x, u, d, lr;
} E[200000];
int main(){
	int n = R(), k = 0;
	for(int i = 0, l, r, d, u; i < n; ++i){
		l = R(); r = R();
		d = R(); u = R();
		E[k++] = (edge){l, u, d, 1};
		E[k++] = (edge){r, u, d, -1};
	}
	std::sort(E, E + k, [](edge a, edge b){return a.x < b.x;});
	int prex = 0;
	long long ans = 0;
	for(int i = 0; i < k; ++i){
		ans += tree.query() * (E[i].x - prex);
		tree.modify(E[i].d, E[i].u, E[i].lr);
		prex = E[i].x;
	}
	printf("%lld", ans);
	return 0;
}