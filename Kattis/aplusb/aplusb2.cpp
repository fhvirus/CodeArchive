#include<iostream>
#include<vector>
#include<climits>
using namespace std;

typedef long long int ll;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	const ll MAX=1e6+10,ADD=50001;
	vector<ll>freq(200008,0),res(200008,0);
	ll n,tmp,mn=INT_MAX,mx=INT_MIN,zeros=0,ans=0;
	vector<ll> all;
	cin>>n;
	if(n<3){cout<<0;return 0;}
	for(ll i=0;i<n;i++){
		cin>>tmp;
		if(!tmp)zeros++;
		freq[tmp+ADD]++;
		all.push_back(tmp+ADD);
		if(mn>tmp+ADD)mn=tmp+ADD;
		if(mx<tmp+ADD)mx=tmp+ADD;
	}
	for(ll i=mn;i<=mx;i++){
		for(ll j=mn;j<=mx;j++){
			res[i+j-ADD]+=freq[i]*freq[j];
		}
	}
	for(auto i: all)res[i*2-ADD]--;
	for(auto i: all)ans+=res[i];
	ans-=(ll)2*zeros*(n-1);
	cout<<ans;
	return 0;
}