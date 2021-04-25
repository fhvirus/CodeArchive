#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<utility>
using namespace std;

int main(){
	int r,c;
	cin>>r>>c;
	vector<string> in(r);
	vector<int> row(c);
	for(auto &i:in){
		cin>>i;
	}
	int cnt=0;
	for(int i=r-1;i>=0;i--){
		map<pair<int,char>,int> m;
		for(int j=0;j<c;j++){
			if(m.count({row[j],in[i][j]})>0){
				row[j]=m[{row[j],in[i][j]}];
			}else{
				cnt++;
				m[{row[j],in[i][j]}]=cnt;
				row[j]=cnt;
			}
		}
		if(m.size()==c){
			cout<<i<<'\n';
			return 0;
		}
	}
	cout<<0<<'\n';
	return 0;
}