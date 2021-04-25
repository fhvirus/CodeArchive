#include<iostream>
#include<string>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t,n,cnt;
	string visited[100],in;
	bool been;
	cin>>t;
	for(int x=0;x<t;x++){
		cnt=0;
		cin>>n;
		cin.ignore();
		for(int y=0;y<n;y++){
			getline(cin,in);
			been=0;
			for(int i=0;i<cnt;i++){
				if(in==visited[i]){
					been=1;
					break;
				}
			}
			if(!been)visited[cnt++]=in;
		}
		cout<<cnt<<'\n';
	}
	return 0;
}