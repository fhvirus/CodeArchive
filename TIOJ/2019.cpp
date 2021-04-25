#include<cstdio>
#include<cstring>
using namespace std;

#define MAXN 1000000
#define ll long long

char a[MAXN], b[MAXN];
ll t, A, B, x, y, z;

bool judge(char c[], ll n, ll len){
	for(ll i = n; i < len; ++i){
		if(c[i%n] != c[i]) return false;
	}
	return true;
}

ll gcd(ll u, ll v){
	while(v){
		u = u%v;
		u^=v^=u^=v;
	}
	return u;
}

int main(){
	scanf("%lld%s%s", &t, a, b);
	A = strlen(a), B = strlen(b);
	for(ll i = 1; i < A or i < B; ++i){
		if(A%i==0 and judge(a, i, A)) A = i;
		if(B%i==0 and judge(b, i, B)) B = i;
	}
	ll cycle = A*B/gcd(A, B);
	if(cycle >= t){
		for(ll i = 0, pa = 0, pb = 0; i < t; ++i, ++pa, ++pb){
			pa = pa == A ? 0 : pa;
			pb = pb == B ? 0 : pb;
			if(a[pa] == b[pb]) ++z;
			else if(a[pa] == 'S' and b[pb] == 'R' or
					a[pa] == 'R' and b[pb] == 'P' or
					a[pa] == 'P' and b[pb] == 'S') ++y;
			else ++x;
		}
		printf("%lld %lld %lld", x, y, z);
	}else{
		for(ll i = 0, pa = 0, pb = 0; i < cycle; ++i, ++pa, ++pb){
			pa = pa == A ? 0 : pa;
			pb = pb == B ? 0 : pb;
			if(a[pa] == b[pb]) ++z;
			else if(a[pa] == 'S' and b[pb] == 'R' or
					a[pa] == 'R' and b[pb] == 'P' or
					a[pa] == 'P' and b[pb] == 'S') ++y;
			else ++x;
		}
		x *= t/cycle, y *= t/cycle, z *= t/cycle;
		for(ll i = 0, pa = 0, pb = 0; i < t%cycle; ++i, ++pa, ++pb){
			pa = pa == A ? 0 : pa;
			pb = pb == B ? 0 : pb;
			if(a[pa] == b[pb]) ++z;
			else if(a[pa] == 'S' and b[pb] == 'R' or
					a[pa] == 'R' and b[pb] == 'P' or
					a[pa] == 'P' and b[pb] == 'S') ++y;
			else ++x;
		}
		printf("%lld %lld %lld", x, y, z);
	}
	return 0;
}