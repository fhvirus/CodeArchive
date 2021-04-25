#include<iostream>
#include<map>
using namespace std;

map<char, string> charToMorse;
map<string, char> morseToChar;

void set(){
	charToMorse['A']=".-";
	charToMorse['B']="-...";
	charToMorse['C']="-.-.";
	charToMorse['D']="-..";
	charToMorse['E']=".";
	charToMorse['F']="..-.";
	charToMorse['G']="--.";
	charToMorse['H']="....";
	charToMorse['I']="..";
	charToMorse['J']=".---";
	charToMorse['K']="-.-";
	charToMorse['L']=".-..";
	charToMorse['M']="--";
	charToMorse['N']="-.";
	charToMorse['O']="---";
	charToMorse['P']=".--.";
	charToMorse['Q']="--.-";
	charToMorse['R']=".-.";
	charToMorse['S']="...";
	charToMorse['T']="-";
	charToMorse['U']="..-";
	charToMorse['V']="...-";
	charToMorse['W']=".--";
	charToMorse['X']="-..-";
	charToMorse['Y']="-.--";
	charToMorse['Z']="--..";
	charToMorse['_']="..--";
	charToMorse[',']=".-.-";
	charToMorse['.']="---.";
	charToMorse['?']="----";
	for(auto i: charToMorse){
		morseToChar[i.second]=i.first;
	}
}

int main(){
	string in, tmp, out;
	int s, ptr;
	set();
	while(getline(cin, in)){
		tmp.clear();
		out.clear();
		s = in.size();
		for(int i = 0; i < s; i++){
			tmp += charToMorse[in[i]];
		}
		ptr = 0;
		for(int i = 0; i < s; i++){
			out += morseToChar[tmp.substr(ptr,charToMorse[in[s-i-1]].size())];
			ptr += charToMorse[in[s-i-1]].size();
		}
		cout<<out<<'\n';
	}
	return 0;
}