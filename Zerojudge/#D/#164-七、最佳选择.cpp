#include<iostream>
using namespace std;

int main(){
	int n,m,i,j,max;
	while(cin>>n>>m){
		int c[n],s[n];
		max=0;
		for(i=0;i<n;i++){
			cin>>c[i];
			s[i]=0;
		}
		for(i=0;i<n;i++){
			for(j=0;j<m;j++){
				s[i]+=c[(i+j)%n];
			}
		}
		for(i=0;i<n;i++){
			max=(max>s[i]?max:s[i]);
		}
		cout<<max<<endl;
	}
	return 0;
}