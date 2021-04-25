#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){
	int n, w, a, b, sum = 0;
	cin>>w>>n;
	while(n--){
		cin>>a>>b;
		sum += a * b;
	}
	cout << sum / w;
	return 0;
}