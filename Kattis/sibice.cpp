#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,w,h,m;
	cin>>n>>w>>h;
	for(int i=0;i<n;i++){
		cin>>m;
		cout<<(m*m<=w*w+h*h?"DA\n":"NE\n");
	}
	return 0;
}