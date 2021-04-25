#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

#define eek ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

struct person{
	string name;
	vector<int> klass;
	person(string n, vector<int>k): name(n), klass(k){}
};

bool cmp(person a, person b){
	while(a.klass.size() < b.klass.size()) a.klass.push_back(2);
	while(a.klass.size() > b.klass.size()) b.klass.push_back(2);
	for(int i = 0; i < a.klass.size(); i++){
		if(a.klass[i] > b.klass[i]) return true;
		if(a.klass[i] < b.klass[i]) return false;
	}
	return a.name < b.name;
}

int main(){eek
	int T, n;
	string name, klass, bin;
	vector<int> tmp;
	vector<person> people;
	cin >> T;
	while(T--){
		cin >> n;
		people.clear();
		while(n--){
			cin >> name >> klass >> bin;
			name.pop_back();
			tmp.clear();
			for(int i = 0; i < klass.size(); i++){
				if(klass[i]=='u'){
					tmp.push_back(3);
					i += 6-1;
				} else if(klass[i] == 'l'){
					tmp.push_back(1);
					i+=6-1;
				} else {
					tmp.push_back(2);
					i+=7-1;
				}
			}
			reverse(tmp.begin(), tmp.end());
			people.push_back(person(name, tmp));
		}
		sort(people.begin(), people.end(), cmp);
		for(auto i: people){
			cout << i.name << '\n';
		}
		cout << "==============================\n";
	}
	return 0;
}