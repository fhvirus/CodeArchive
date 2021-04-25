#include<iostream>
#include<iomanip>
#include<cmath>
#include<algorithm>
using namespace std;

int gcd(int a,int b){
	while(a%b){
		a%=b;
		swap(a,b);
	}
	return b;
}

bool havegcd(int a,int b){
	return gcd(a,b)!=1;
}

int main(){
	int n,a[60];
	double cnt;
	while(cin>>n&&n!=0){
		for(int i=0;i<n;i++)cin>>a[i];
		cnt=0;
		for(int i=0;i<n-1;i++){
			for(int j=i+1;j<n;j++){
				cnt+=!havegcd(a[i],a[j]);
			}
		}
		if(!cnt)cout<<"No estimate for this data set.\n";
		else cout<<setprecision(6)<<fixed<<sqrt(6*n*(n-1)/2/cnt)<<'\n';
	}
	return 0;
}