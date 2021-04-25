#include<iostream>
using namespace std;

int main(){
	int a,b,c;
	cin>>a>>b>>c;
	int time[105];
	for(int i=0;i<105;i++)time[i]=0;
	int s,t,ans=0;
	for(int i=0;i<3;i++){
		cin>>s>>t;
		time[s]++;
		time[t]--;
	}
	for(int i=1;i<105;i++){
		time[i]+=time[i-1];
	}

	for(int i=0;i<105;i++){
		if(time[i]==1)ans+=a;
		else if(time[i]==2)ans+=2*b;
		else if(time[i]==3)ans+=3*c;
	}

	cout<<ans;

	return 0;
}