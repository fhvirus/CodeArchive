#include<iostream>
#include<map>
#include<utility>
using namespace std;

map<char,pair<int,int>>key;

void setup(){
	key['a']={2,1};
	key['b']={2,2};
	key['c']={2,3};
	key['d']={3,1};
	key['e']={3,2};
	key['f']={3,3};
	key['g']={4,1};
	key['h']={4,2};
	key['i']={4,3};
	key['j']={5,1};
	key['k']={5,2};
	key['l']={5,3};
	key['m']={6,1};
	key['n']={6,2};
	key['o']={6,3};
	key['p']={7,1};
	key['q']={7,2};
	key['r']={7,3};
	key['s']={7,4};
	key['t']={8,1};
	key['u']={8,2};
	key['v']={8,3};
	key['w']={9,1};
	key['x']={9,2};
	key['y']={9,3};
	key['z']={9,4};
	key[' ']={0,1};
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	setup();
	int n;
	string in;
	cin>>n;
	cin.ignore();
	for(int i=0;i<n;i++){
		getline(cin,in);
		cout<<"Case #"<<i+1<<": ";
		for(int j=0;j<in.size();j++){
			for(int k=0;k<key[in[j]].second;k++){
				cout<<key[in[j]].first;
			}
			if(j<in.size()-1&&key[in[j]].first==key[in[j+1]].first)
					cout<<' ';
		}
		cout<<'\n';
	}
	return 0;
}