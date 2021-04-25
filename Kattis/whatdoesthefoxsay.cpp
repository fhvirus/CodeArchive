#include<iostream>
#include<string>
#include<sstream>
#include<vector>
using namespace std;

int main(){
	int n;
	stringstream in;
	string input,output,tmp;
	vector<string> tape;
	cin>>n;
	cin.ignore();
	for(int i=0;i<n;i++){
		in.clear();
		tape.clear();
		getline(cin,input);
		in<<input;
		while(in>>tmp)tape.push_back(tmp);
		while(getline(cin,input)){
			if(input=="what does the fox say?"){
				for(int x=0;x<tape.size();x++)cout<<tape[x]<<' ';
				cout<<'\n';
				break;
			}else{
				input.erase(0,input.find("goes ")+5);
				for(int x=0;x<tape.size();){
					if(tape[x]==input)tape.erase(tape.begin()+x);
					else x++;
				}
			}
		}
	}
	return 0;
}