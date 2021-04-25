#include<unistd.h>
inline char RC(){static char buf[2048],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,2048))==buf?-1:*p++;}

// R, R', L, L', U, U', D, D', F, F', B, B'
char owo[9][12] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{5, 4, 1, 1, 2, 5, 1, 1, 4, 2, 1, 1},
	{2, 2, 3, 6, 6, 1, 2, 2, 1, 3, 2, 2},
	{3, 3, 8, 2, 3, 3, 4, 8, 2, 4, 3, 3},
	{1, 7, 4, 4, 4, 4, 7, 3, 3, 1, 4, 4},
	{7, 1, 5, 5, 1, 6, 5, 5, 5, 5, 6, 7},
	{6, 6, 2, 8, 5, 2, 6, 6, 6, 6, 8, 5},
	{4, 5, 7, 7, 7, 7, 8, 4, 7, 7, 5, 8},
	{8, 8, 6, 3, 8, 8, 3, 7, 8, 8, 7, 6}
};

inline char get(char c){
	if(c == 'R') return 0;
	if(c == 'L') return 2;
	if(c == 'U') return 4;
	if(c == 'D') return 6;
	if(c == 'F') return 8;
	if(c == 'B') return 10;
	return -1;
}

int main(){
	while(true){
		char c = RC(); char p = 1;
		while(true){
			if(c == '\n') break;
			if(c == -1) break;
			char cmd = get(c);
			c = RC();
			if(cmd == -1) continue;
			if(c == '\'') cmd += 1, c = RC();
			p = owo[p][cmd];
		}
		if(c == -1) break;
		char OB[4] = {'(', '0', ')', '\n'};
		OB[1] += p;
		write(1,OB,4);
	}
}