#include<iostream>
#include<string>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string a,b;
	cin>>a>>b;
	int s=a.size();
	if(a[s-1]=='a'||a[s-1]=='e'||a[s-1]=='i'||a[s-1]=='o'||a[s-1]=='u')
		a.erase(a.begin()+s-1);
	if(!(a[s-2]=='e'&&a[s-1]=='x'))
		a.append("ex");
	a.append(b);
	cout<<a;
	return 0;
}