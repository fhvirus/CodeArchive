#pragma GCC optimize("Ofast")
#pragma loop-opt(on)
#pragma GCC optimize("unroll-loop")
#include<cstdio>
#include<utility>
using namespace std;

const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}

#define ll long long
#define x first
#define y second
#define pii pair<ll, ll>
ll cross(pii a, pii b){
	return (a.x * b.y - a.y * b.x);
}
ll dot(pii a, pii b){
	return a.x * b.x + a.y * b.y;
}
pii vec(pii a, pii b){
	return {b.x - a.x, b.y - a.y};
}
ll sign(ll a){
	return a < 0 ? -1 : (a > 0 ? 1 : 0);
}
bool inter(pii p1, pii p2, pii q1, pii q2){
	return (sign(cross(vec(p1, q1), vec(p1, q2))) * sign(cross(vec(p2, q1), vec(p2, q2))) < 0 and sign(cross(vec(q1, p1), vec(q1, p2))) * sign(cross(vec(q2, p1), vec(q2, p2))) < 0);
}
const int N = 1e6;
int n;
pii p[N], a, b;
bool ain, bin, abo;
int main(){
	n = R();
	for(int i = 0; i < n; ++i)
		p[i].x = R(), p[i].y = R();
	a.x = R(), a.y = R(), b.x = R(), b.y = R();
	for(int i = 0; i < n; ++i){
		if(inter(a, {a.x+1, 1ll<<31}, p[i], i+1 >= n ? p[0] : p[i+1])) ain = !ain;
		if(inter(b, {b.x+1, 1ll<<31}, p[i], i+1 >= n ? p[0] : p[i+1])) bin = !bin;
		if(i < n-1 and inter(a, b, p[i], p[i+1])) abo = true;
	}
	if(!ain and !bin)puts("ERROR!");
	else if(!ain) puts("A troll!");
	else if(!bin) puts("B troll!");
	else if(abo) puts("Bug!");
	else puts("Okay!");
}