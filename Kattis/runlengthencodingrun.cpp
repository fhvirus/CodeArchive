#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	char mode;
	string in;
	cin>>mode>>in;
	if(mode == 'E'){
		int l, ptr;
		char cur;
		ptr = 0, cur = in[ptr], l = 1;
		while(ptr < in.size()){
			while(ptr < in.size() && in[ptr] == cur){
				ptr++, l++;
			}
			cout<<cur<<l-1;
			cur = in[ptr], l = 1;
		}
	}else if(mode == 'D'){
		for(int i = 0; i < in.size(); i+=2){
			for(int j = 0; j < in[i+1]-'0'; j++)cout<<in[i];
		}
	}
	return 0;
}