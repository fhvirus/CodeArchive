#include<iostream>
#include<set>
#include<string>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	string uni,team;
	int n,k=0;
	cin>>n;
	set<string> t;
	for(int i=0;i<n;i++){
		cin>>uni>>team;
		if(t.find(uni)==t.end()&&k<12){
			cout<<uni<<' '<<team<<'\n';
			t.insert(uni);
			k++;
		}
	}
	return 0;
}