#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	bool mode;
	string last,curr;
	cin>>n>>last>>curr;
	if(last<curr)mode=1;
	else mode=0;
	n-=2;
	while(n--){
		last=curr;
		cin>>curr;
		if(last<curr){
			if(!mode){
				cout<<"NEITHER\n";
				return 0;
			}
		}else{
			if(mode){
				cout<<"NEITHER\n";
				return 0;
			}
		}
	}
	if(mode)cout<<"INCREASING\n";
	else cout<<"DECREASING\n";
	return 0;
}