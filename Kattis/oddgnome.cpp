#include<iostream>
using namespace std;

int id[1000];

int main(){
	int T, n;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i = 0; i < n; i++){
			cin>>id[i];
		}
		for(int i = 1; i < n-1; i++){
			if(id[i-1] < id[i+1]){
				if(id[i] < id[i-1] or id[i] > id[i+1]){
					cout<<i+1<<'\n';
					break;
				}
			}
		}
	}
	return 0;
}