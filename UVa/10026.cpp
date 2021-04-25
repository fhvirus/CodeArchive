#include<iostream>
#include<algorithm>
using namespace std;

struct task{
	int len, fine, num;
};
task tasks[1005];

bool cmp(task a, task b){
	return a.len * b.fine < b.len * a.fine;
}

int main(){
	int n, m;
	cin>>n;
	for(int k = 0; k < n; k++){
		cin>>m;
		for(int i = 0; i < m; i++){
			cin>>tasks[i].len>>tasks[i].fine;
			tasks[i].num = i + 1;
		}
		sort(tasks, tasks + m, cmp);
		for(int i = 0; i < m; i++){
			cout<<tasks[i].num;
			if(i<m-1)cout<<' ';
		}
		cout<<'\n';
		if(k < n - 1)cout<<'\n';
	}
	return 0;
}