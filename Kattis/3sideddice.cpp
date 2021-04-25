#include<iostream>
#include<utility>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

using ll = long long;
using ii = pair<ll, ll>;
constexpr ll MAXN = 10000;
#define third(x) (MAXN - x.first - x.second)

ll det(ii p1, ii p2, ii p3){
	ll r = 0LL;
	r += p1.first * p2.second * third(p3);
	r += p2.first * p3.second * third(p1);
	r += p3.first * p1.second * third(p2);
	r -= p1.first * p3.second * third(p2);
	r -= p2.first * p1.second * third(p3);
	r -= p3.first * p2.second * third(p1);
	return r;
}
ll det(ii p1, ii p2){

}
ii sub(ii p1, ii p2){
	return {p1.first-p2.first, p1.second-p2.second};
}

int main(){OW0
	return 0;
}