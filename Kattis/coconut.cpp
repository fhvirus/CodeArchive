#include<iostream>
#include<vector>
#include<utility>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int s,p;
	cin>>s>>p;
	vector<pair<int,int>>h(p);
	for(int i=0;i<h.size();i++){
		h[i].second=i+1;
	}
	int ptr=0;
	while(h.size()>1){
		ptr=(ptr+s-1)%h.size();
		if(h[ptr].first==0){
			h[ptr].first=1;
			h.insert(h.begin()+ptr,h[ptr]);
		}else if(h[ptr].first==1){
			h[ptr].first=2;
			ptr++;
		}else{
			h.erase(h.begin()+ptr);
		}
	}
	cout<<h[0].second;
	return 0;
}