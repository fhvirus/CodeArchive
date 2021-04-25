#include<iostream>
#include<string>
#include<utility>
using namespace std;

int main(){
	string a;
	cin>>a;
	int cnt[26],ccnt[26];
	fill(cnt,cnt+26,0);
	fill(ccnt,ccnt+26,0);
	for(int i=0;i<a.length();i++){
		if(a[i]>64&&a[i]<91){
			ccnt[a[i]-65]++;
		}
		else cnt[a[i]-97]++;
	}
	for(int i=0;i<26;i++){
		if(ccnt[i]){
			cout<<char(i+65)<<": "<<ccnt[i]<<'\n';
		}
		if(cnt[i]){
			cout<<char(i+97)<<": "<<cnt[i]<<'\n';
		}
	}
	return 0;
}