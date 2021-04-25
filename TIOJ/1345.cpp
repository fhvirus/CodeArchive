#pragma GCC optimize("Ofast")
#pragma loop-opt(on)
#include<cstdio>
#define FOR(i,n) for(int i = 0; i < n; ++i)
inline char readchar(){
	const int S = 1<<20;
	static char buf[S], *p = buf, *q = buf;
	if(p == q and (q = (p = buf) + fread(buf, 1, S, stdin)) == buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while((c > '9' or c < '0') and c != EOF) c = readchar();
	while(c <= '9' and c >= '0') ans = (ans<<3) + (ans<<1) + (c^'0'), c = readchar();
	return ans;
}

#include<algorithm>

const int N = 100000;
const int LEN2d = 200000; // first question?
const int LEN3d = 75;
const int JIZZ = LEN3d * 3 + 1;
int dimension, n, d, boardsize;

// 1D board
int x[N];
void solve1d(){
	FOR(i,n) x[i] = R();
	std::sort(x, x + n);
	long long ans = 0;
	int head = 0;
	FOR(i,n){
		while(x[head]  + d < x[i]) ++head;
		ans += i - head;
	}
	printf("%lld", ans);
	return;
}

// 2D board
struct point2d{
	int x, y;
	point2d(){}
	bool operator< (const point2d &rhs) const{
		return y < rhs.y;
	}
} p2d[N];
struct BIT2d{
	int val[LEN2d+1];
	void add(int p, int v){
		while(p <= LEN2d) val[p] += v, p += (p & -p);
	}
	int query(int p){
		int ans = 0;
		while(p > 0) ans += val[p], p ^= (p&-p);
		return ans;
	}
	int query(int l, int r){
		return query(r) - query(l - 1);
	}
} bit2d;
void solve2d(){
	int a, b;
	long long ans = 0ll;
	FOR(i,n) a = R(), b = R(), p2d[i].x = a + b, p2d[i].y = a - b;
	std::sort(p2d, p2d + n);
	int head = 0;
	FOR(i,n){
		while(head < i and p2d[head].y + d < p2d[i].y)
			bit2d.add(p2d[head].x, -1), ++head;
		ans += bit2d.query(p2d[i].x - d, p2d[i].x + d);
		bit2d.add(p2d[i].x, 1);
	}
	printf("%lld", ans);
	return;
}

// 3D board
struct point3d{
	int w, x, y, z;
	point3d(){}
	point3d(int a, int b, int c){
		z = a + b + c;
		x = a + b - c + boardsize;
		y = a - b + c + boardsize;
		w = a - b - c;
	}
	bool operator< (const point3d &rhs) const{
		return w < rhs.w;
	}
} p3d[N];
struct BIT3d{
	int val[(JIZZ+1)*(JIZZ+1)*(JIZZ+1)];
	const int EEK = (JIZZ+1)*(JIZZ+1);
	void add(int a, int b, int c, int v){
		for(int x = a; x <= JIZZ; x += (x & -x))
			for(int y = b; y <= JIZZ; y += (y & -y))
				for(int z = c; z < JIZZ; z += (z & -z))
					val[x * EEK + y * (JIZZ + 1) + z] += v;

	}
	int query(int a, int b, int c){
		int ans = 0;
		for(int x = a; x > 0; x -= (x & -x))
			for(int y = b; y > 0; y -= (y & -y))
				for(int z = c; z > 0; z -= (z & -z))
					ans += val[x * EEK + y * (JIZZ + 1) + z];
		return ans;
	}
	int query(int lx, int ly, int lz, int rx, int ry, int rz){
		rx = rx > JIZZ ? JIZZ : rx;
		ry = ry > JIZZ ? JIZZ : ry;
		rz = rz > JIZZ ? JIZZ : rz;
		int ans = query(rx, ry, rz);
		ans -= query(lx - 1, ry, rz) + query(rx, ly - 1, rz) + query(rx, ry, lz - 1);
		ans += query(lx - 1, ly - 1, rz) + query(lx - 1, ry, lz - 1) + query(rx, ly - 1, lz - 1);
		ans -= query(lx - 1, ly - 1, lz - 1);
		return ans;
	}
} bit3d;
void solve3d(){
	FOR(i,n) p3d[i] = point3d(R(), R(), R());
	std::sort(p3d, p3d + n);
	long long ans = 0;
	int head = 0;
	FOR(i,n){
		while(p3d[head].w + d < p3d[i].w)
			bit3d.add(p3d[head].x, p3d[head].y, p3d[head].z, -1), ++head;
		ans += bit3d.query(p3d[i].x - d, p3d[i].y - d, p3d[i].z - d, p3d[i].x + d, p3d[i].y + d, p3d[i].z + d);
		bit3d.add(p3d[i].x, p3d[i].y, p3d[i].z, 1);
	}
	printf("%lld", ans);
	return;
}

int main(){
	dimension = R(); n = R(); d = R(); boardsize = R();
	if(dimension == 1) solve1d();
	else if(dimension == 2) solve2d();
	else solve3d();
	return 0;
}