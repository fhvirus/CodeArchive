#include<iostream>
#include<unordered_map>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	if(n<3){cout<<0;return 0;}
	else{
		int nums[n];
		for(int i=0;i<n;i++)cin>>nums[i];
		unordered_map<int,int>nms;
		unsigned long long int ans=0;
		for(int i=2;i<n;i++){
			nms[nums[0]]=1;
			for(int j=1;j<i;j++){
				ans+=2*(nms[nums[i]+nums[j]]
					+nms[nums[i]-nums[j]]
					+nms[nums[j]-nums[i]]);
				nms[nums[j]]++;
			}
			nms.clear();
		}
		cout<<ans;
	}
	return 0;
}