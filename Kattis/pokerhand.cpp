#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	char card[5],suit[5];
	int kind=1,cnt[5],max=0;
	for(int i=0;i<5;i++){
		cin>>card[i]>>suit[i];
		cnt[i]=0;
	}
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			if(card[i]==card[j])cnt[i]++;
		}
	}
	for(int i=0;i<5;i++){
		max=(max>cnt[i]?max:cnt[i]);
	}
	cout<<max;
	return 0;
}