#include<cstdio>
typedef long long ll;
ll t, a, b, c, k, x, y, d;

void extgcd(ll a, ll b, ll &x, ll &y, ll &d){
	if(!b){
		d = a;
		x = 1;
		y = 0;
		return;
	}
	extgcd(b, a%b, x, y, d);
	ll newX = y, newY = x - a / b * y;
	x = newX, y = newY;
}

int main(){
	scanf("%lld", &t);
	for(; t; --t){
		scanf("%lld%lld%lld%lld", &a, &b, &c, &k);
		if(a == b){
			puts("0");
			continue;
		}
		if(c == 0){
			puts("FOREVER");
			continue;
		}

		extgcd(c, (1ll<<k), x, y, d);
		if((b - a) % d != 0) puts("FOREVER");
		else printf("%lld\n", ((x < 0 ? x + (1ll<<k) : x) * ((b > a ? b - a : b - a + (1ll<<k)) / d)) % (1ll<<k));
	}
}