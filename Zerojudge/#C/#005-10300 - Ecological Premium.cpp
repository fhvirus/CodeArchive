#include<iostream>
using namespace std;

int main(){
	long long int n,f,a,b,c,i,j,s;
	cin>>n;
	for(i=0;i<n;i++){
		s=0;
		cin>>f;
		for(j=0;j<f;j++){
			cin>>a>>b>>c;
			s+=a*c;
		}
		cout<<s<<endl;
	}
	return 0;
}