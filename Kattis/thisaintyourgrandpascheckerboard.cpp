#include<iostream>
using namespace std;

bool b[24][24],a;
int rsum[24],csum[24];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin>>n;
	char tmp;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cin>>tmp;
			b[i][j]=(tmp=='W');
			rsum[i]+=(tmp=='W');
			csum[j]+=(tmp=='W');
			if(i>1&&b[i][j]==b[i-1][j]&&b[i][j]==b[i-2][j])a=1;
			if(j>1&&b[i][j]==b[i][j-1]&&b[i][j]==b[i][j-2])a=1;
			if(a)break;
		}
		if(a)break;
	}
	for(int i=0;i<n&&!a;i++){
		if(rsum[i]!=rsum[0]||csum[i]!=csum[0])a=1;
	}
	cout<<!a;
	return 0;
}