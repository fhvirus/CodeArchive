#include<iostream>
#include<algorithm>
#include<utility>
using namespace std;

typedef pair<int, int> pii;

pii ed[1005];

bool cmp(pii a, pii b){
	return a.second < b.second;
}

int main(){
	int n, m, curTime, e, d;
	bool can;
	cin>>n;
	while(n--){
		cin>>m;
		for(int i = 0; i < m; i++){
			cin>>e>>d;
			ed[i] = {e, d};
		}
		sort(ed, ed + m, cmp);
		can = true;
		curTime = 0;
		for(int i = 0; i < m; i++){
			curTime += ed[i].first;
			if(curTime > ed[i].second){
				can = false;
				break;
			}
		}
		cout<<(can?"schedulable\n":"unschedulable\n");
	}
	return 0;
}