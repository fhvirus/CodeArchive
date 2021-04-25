#include<iostream>
#include<string>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	string a,b;
	cin>>n;
	cin.ignore();
	for(int x=0;x<n;x++){
		getline(cin,a);
		getline(cin,b);
		cout<<a<<'\n'<<b<<'\n';
		for(int i=0;i<a.length();i++){
			cout<<(a[i]==b[i]?'.':'*');
		}
		cout<<"\n\n";
	}
	return 0;
}