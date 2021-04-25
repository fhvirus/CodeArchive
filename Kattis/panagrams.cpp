#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	int t[26];
	for(int i=0;i<26;i++)t[i]=0;
	string in;
	cin>>in;
	for(auto i: in)t[i-'a']++;
	int cnt=0;
	for(int i=0;i<26;i++)if(t[i]%2)cnt++;
	cout<<(cnt==0?0:cnt-1);
	return 0;
}