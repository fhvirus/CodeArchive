#include<iostream>
#include<cmath>
using namespace std;
int n[10]={119,18,93,91,58,107,111,82,127,123};

int cnt1(long long int n){
	int ans=0;
	while(n){ans+=n&1;n>>=1;}
	return ans;
}

int main(){
	long long int diff=0,a,b,c;
	for(cin>>a>>b;a|b;a/=10,b/=10){
		if(abs(cnt1(n[a%10])-cnt1(n[b%10]))<=1){
			c=n[a%10]^n[b%10];
			diff+=cnt1(c);
		}
	}
	cout<<(diff==2?"yes":"no");
	return 0;
}