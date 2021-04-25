#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

const int N = 31623 + 1;

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t;
	long long p, q;
	cin >> t;
	while(t--){
		cin >> p >> q;
		if(p % q != 0){
			cout << p << '\n';
		} else {
			long long ans = 1;
			for(int i = 2; i * i <= q; ++i){
				if(q % i == 0){
					int j = q / i;
					long long jiz = p;
					while(jiz % i == 0 and jiz % q == 0)
						jiz /= i;
					if(jiz % q != 0) ans = max(ans, jiz);
					jiz = p;
					while(jiz % j == 0 and jiz % q == 0)
						jiz /= j;
					if(jiz % q != 0) ans = max(ans, jiz);
				}
			}
			long long jiz = p;
			while(jiz % q == 0)
				jiz /= q;
			ans = max(ans, jiz);
			cout << ans << '\n';
		}
	}
	return 0;
}