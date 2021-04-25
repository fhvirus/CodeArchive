#include<iostream>
#include<sstream>
#include<map>
#include<cctype>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	int T = 1, n;
	string tmp, type;
	stringstream ss;
	map<string, int> lst;
	while(cin>>n && n){
		cin.ignore();
		lst.clear();
		cout<<"List "<<T++<<":\n";
		for(int i = 0; i < n; i++){
			getline(cin, tmp);
			ss.str("");ss.clear();
			ss << tmp;
			while(true){
				ss >> type;
				if(ss.fail())break;
			}
			for(auto &k: type)k = tolower(k);
			lst[type]++;
		}
		for(auto i: lst){
			cout<<i.first<<" | "<<i.second<<'\n';
		}
	}
	return 0;
}