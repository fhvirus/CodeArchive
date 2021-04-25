#include<iostream>
#include<string>
#include<utility>
using namespace std;

int main(){
	string a;
	bool hadodd,can;
	int n,cnt[26],odd;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a;
		fill(cnt,cnt+26,0);
		hadodd=0;can=1;odd=-1;
		for(int i=0;i<a.length();i++){
			cnt[a[i]-65]++;
		}
		for(int i=0;i<26;i++){
			if(cnt[i]%2){
				if(hadodd){
					can=0;
					break;
				}
				else{
					hadodd=1;
					odd=i;
				}
			}
		}
		if(can){
			for(int i=0;i<26;i++){
				if(odd!=i||cnt[i]>1){
					for(int j=0;j<cnt[i]/2;j++){
						cout<<char(i+65);
					}
				}
			}
			if(odd!=-1)cout<<char(odd+65);
			for(int i=25;i>=0;i--){
				for(int j=0;j<cnt[i]/2;j++){
					cout<<char(i+65);
				}
			}
			cout<<'\n';
		}
		else cout<<"NPSCCSPN\n";
	}
}