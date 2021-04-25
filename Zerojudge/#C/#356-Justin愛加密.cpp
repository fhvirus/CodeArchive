#include<iostream>
#include<string>
using namespace std;

int main(){
	int n;
	char a[5001];
	cin>>n;
	for(int i=0;i<n*n/(n+1)+1;i++){
		cin.ignore();
		cin.getline(a,n+1);
		cout<<a[0];
	}
	cout<<'\n';
	return 0;
}