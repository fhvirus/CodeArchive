#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int time,problem[26],ans=0,sum=0;
	char prob;
	string rw;
	for(int i=0;i<26;i++)problem[i]=0;
	while(cin>>time&&time!=-1){
		cin>>prob>>rw;
		if(rw=="right"){
			ans+=time+problem[(int)prob-65];
			sum++;
		}else if(rw=="wrong"){
			problem[(int)prob-65]+=20;
		}
	}
	cout<<sum<<' '<<ans;
	return 0;
}