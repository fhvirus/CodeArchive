#include<iostream>
#include<algorithm>
using namespace std;

int main(){
	int b, p, f, h, c, n, ans;
	cin>>n;
	while(n--){
		cin>>b>>p>>f>>h>>c;
		ans = 0;
		if(h < c){
			swap(h, c);
			swap(p, f);
		}
		if(p * 2 > b){
			ans = b / 2 * h;
		} else {
			ans = p * h;
			b -= p * 2;
			if(f * 2 > b){
				ans += b / 2 * c;
			} else {
				ans += f * c;
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}