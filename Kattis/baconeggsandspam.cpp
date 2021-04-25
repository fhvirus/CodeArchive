#include<iostream>
#include<map>
#include<queue>
#include<vector>
#include<sstream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	int n;
	string name, dish, tmp;
	stringstream ss;
	map<string, priority_queue<string, vector<string> ,greater<string>>> job;
	while(cin>>n && n!=0){
		job.clear();
		cin.ignore();
		for(int i = 0; i < n; i++){
			ss.str("");ss.clear();
			getline(cin, tmp);
			ss << tmp;
			ss >> name;
			while(true){
				ss >> dish;
				if(ss.fail())break;
				job[dish].push(name);
			}
		}
		for(auto i: job){
			cout<<i.first<<' ';
			while(!i.second.empty()){
				cout<<i.second.top()<<' ';
				i.second.pop();
			}
			cout<<'\n';
		}
		cout<<'\n';
	}
	return 0;
}