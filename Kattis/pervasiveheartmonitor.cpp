#include<iostream>
#include<sstream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

bool is_dig(char a){
	return a <= '9' && a >= '0';
}

int main(){OW0
	string in, name, tmp;
	stringstream ss;
	int cnt;
	double sum, t;
	while(getline(cin, in) && in != ""){
		ss.str("");ss.clear();ss.str(in);
		name = "";
		cnt = 0, sum = 0;
		while(true){
			ss>>tmp;
			if(ss.fail())break;
			if(is_dig(tmp[0])){
				sum += stod(tmp);
				cnt++;
			}else{
				name += tmp + " ";
			}
		}
		cout<<sum/cnt<<' '<<name<<'\n';
	}
	return 0;
}