#include<iostream>
#include<set>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	set<int> a;
	for(int i=0;i<10;i++){
		cin>>n;
		a.insert(n%42);
	}
	cout<<a.size();
	return 0;
}