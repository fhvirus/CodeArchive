#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
inline char readchar(){
	const int S = 1<<20;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}

#include<algorithm>
#include<vector>
typedef long long ll;
const int N = 100000;
int n, x, y, t, ansx, ansy;
long long sum, xsum, ysum, ans;
struct point{
	int p, v;
	point(){}
	point(int p, int v): p(p), v(v){}
	bool operator< (const point &rhs) const{
		return p == rhs.p ? v < rhs.v : p < rhs.p;
	}
} X[N], Y[N];
std::vector<int> vx, vy;

inline void upd(int i, int j){
	long long jizz = 0ll;
	FOR(k,n) jizz += (ll)abs(X[k].p-i) * X[k].v + (ll)abs(Y[k].p-j) * Y[k].v;
	if(jizz < ans) ans = jizz, ansx = (i+j)>>1, ansy = (i-j)>>1;
	else if(jizz == ans){
		if((i+j) < ansx<<1 or ((i+j) == ansx<<1 and (i-j) < ansy<<1))
			ansx = (i+j)>>1, ansy = (i-j)>>1;
	}
}

int main(){
	while((n = R()) != 0){
		vx.clear(); vy.clear();
		sum = xsum = ysum = 0ll;
		ans = 1ll<<62;
		FOR(i,n)
			x = R(), y = R(), t = R(),
			X[i] = {x + y, t}, Y[i] = {x - y, t}, sum += t;
		std::sort(X, X + n); std::sort(Y, Y + n);

		// odd wont trigger the if==, so no worries
		FOR(i,n){
			xsum += X[i].v;
			if(xsum<<1 > sum){ vx.push_back(X[i].p); break;}
			if(xsum<<1 == sum){ vx.push_back(X[i].p); vx.push_back(X[i+1].p); break;}
		}
		FOR(i,n){
			ysum += Y[i].v;
			if(ysum<<1 > sum){ vy.push_back(Y[i].p); break;}
			if(ysum<<1 == sum){ vy.push_back(Y[i].p);  vy.push_back(Y[i+1].p);break;}
		}

		for(int i: vx) for(int j: vy){
			if(((i+j) & 1) == 0) upd(i, j);
			else upd(i - 1, j),
				 upd(i, j - 1),
				 upd(i + 1, j),
				 upd(i, j + 1);
		}

		printf("%d %d\n", ansx, ansy);
	}
	return 0;
}