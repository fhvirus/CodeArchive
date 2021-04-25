#include<iostream>
#include<set>
#include<map>
using namespace std;

string notes[12] = {
	"A", "A#", "B", "C",
	"C#", "D", "D#", "E",
	"F", "F#", "G", "G#"
};

bool yes[12];

int main(){
	set<string> song;
	int n;
	string tmp;
	cin>>n;
	for(int i = 0; i < n; i++){
		cin>>tmp;
		song.insert(tmp);
	}
	for(int i = 0; i < 12; i++){
		yes[i] = true;
	}

	for(int i = 0; i < 12; i++){
		if( (song.count(notes[(i + 1) % 12]) != 0) ||
			(song.count(notes[(i + 3) % 12]) != 0) ||
			(song.count(notes[(i + 6) % 12]) != 0) ||
			(song.count(notes[(i + 8) % 12]) != 0) ||
			(song.count(notes[(i + 10) % 12]) != 0)
		)yes[i] = false;
	}
	
	bool had = false;
	for(int i = 0; i < 12; i++){
		if(yes[i]){
			cout<<notes[i]<<' ';
			had = true;
		}
	}
	if(!had)cout<<"none";
	return 0;
}