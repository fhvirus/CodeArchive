#include<iostream>
#include<cmath>
using namespace std;

#define MAXN 500001
#define SQRTN 708
int a[MAXN];
int sum[SQRTN][SQRTN];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,cmd,x,y;
	cin>>n;
	for(int z=0;z<n;z++){
		cin>>cmd>>x>>y;
		if(cmd==1){
			a[x]+=y;
			for(int i=1;i<SQRTN;i++){
				sum[i][x%i]+=y;
			}
		}
		else if(cmd==2){
			if(x<SQRTN){
				cout<<sum[x][y]<<'\n';
			}else{
				int tmp=0;
				for(int i=y;i<MAXN;i+=x){
					tmp+=a[i];
				}
				cout<<tmp<<'\n';
			}
		}
	}
	return 0;
}