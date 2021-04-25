#pragma GCC optimize("Ofast")
#define FOR(i,n) for(int i=0;i<n;++i)
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}


#include<algorithm>

const int N = 1500;
int n, ans;

struct point{
	int x, y;
	point(){}
	point(int x, int y): x(x), y(y){}
	point operator+(const point &rhs) const{
		return point(x + rhs.x, y + rhs.y);
	}
	point operator-(const point &rhs) const{
		return point(x - rhs.x, y - rhs.y);
	}
	inline long long operator*(const point &rhs) const{
		return (long long)x * rhs.x + (long long)y * rhs.y;
	}
	inline long long operator^(const point &rhs) const{
		return (long long)x * rhs.y - (long long)y * rhs.x;
	}
	inline bool operator<(const point &rhs) const{
		if((y > 0 or (y == 0 and x > 0)) and (rhs.y < 0 or (rhs.y == 0 and rhs.x < 0))) return true;
		if((rhs.y > 0 or (rhs.y == 0 and rhs.x > 0)) and (y < 0 or (y == 0 and x < 0))) return false;
		return (long long)x * rhs.y - (long long)y * rhs.x > 0;
	}
}P[N];

point eek[N<<1];
inline int solve(int o){
	int p = 0;
	FOR(i,n) if(i != o) eek[p++] = P[i] - P[o];
	std::sort(eek, eek + n - 1);
	FOR(i,n-1) eek[i+n-1] = eek[i];

	int l = 0, r = 1;
	int yike = 0;
	while(l < n-1){
		if(eek[l] * eek[r] < 0 or (eek[l] ^ eek[r]) < 0){ ++l; continue;}
		if(eek[l] * eek[r] > 0){ ++r; if(r >= l + n - 1) break; continue;}
		int jizz = 0;
		while(eek[l] * eek[r] == 0 and (eek[l] ^ eek[r]) >= 0){
			++jizz;
			++r;
			if(r >= l + n - 1) break;
		}
		r -= jizz;
		yike += jizz;
		++l;
	}
	return yike;
}

int main(){
	while((n = R()) != 0){
		ans = 0;
		FOR(i,n) P[i].x = R(), P[i].y = R();
		FOR(i,n) ans += solve(i);
		W(ans);
	}
	write(1,OB,OP);
}