#include<iostream>
#include<set>
using namespace std;

int main(){
	int n,c,g;
	set<int> guests;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>c;
		guests.clear();
		for(int j=0;j<c;j++){
			cin>>g;
			if(guests.find(g)!=guests.end())guests.erase(g);
			else guests.insert(g);
		}
		cout<<"Case #"<<i+1<<": "<<*guests.begin()<<endl;
	}
	return 0;
}