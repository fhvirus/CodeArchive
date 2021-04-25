#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,i,speed,time,stop,prevstop,ans;
	while(cin>>n&&n!=-1){
		time=0;ans=0;prevstop=0;
		for(i=0;i<n;i++){
			cin>>speed>>stop;
			time=stop-prevstop;
			ans+=speed*time;
			prevstop=stop;
		}
		cout<<ans<<" miles\n";
	}
	return 0;
}