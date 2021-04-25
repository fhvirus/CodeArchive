#include<iostream>
#include<algorithm>
#include<map>
#include<string>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	map<int,string> cups;
	int n;
	cin>>n;
	int r[n];
	string a,b;
	for(int i=0;i<n;i++){
		cin>>a>>b;
		if(isalpha(a[0])){
			r[i]=stoi(b,nullptr,10)*2;
			cups[r[i]]=a;
		}else{
			r[i]=stoi(a,nullptr,10);
			cups[r[i]]=b;
		}
	}
	sort(r,r+n);
	for(int i=0;i<n;i++)cout<<cups[r[i]]<<'\n';
	return 0;
}