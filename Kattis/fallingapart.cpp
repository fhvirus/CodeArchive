#include<iostream>
#include<algorithm>
using namespace std;

#define owo ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){
	int n, val[20], a=0, b=0;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>val[i];
	}
	sort(val, val+n, [](int x,int y){return x>y;});
	for(int i=0;i<n;i++){
		if(i%2)b+=val[i];
		else a+=val[i];
	}
	cout<<a<<' '<<b;
	return 0;
}