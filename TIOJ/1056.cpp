#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>

char b[10], i, o, x;

bool linex(){
	if(b[0] == 'X' and b[0] == b[3] and b[3] == b[6]) return true;
	if(b[1] == 'X' and b[1] == b[4] and b[4] == b[7]) return true;
	if(b[2] == 'X' and b[2] == b[5] and b[5] == b[8]) return true;
	if(b[0] == 'X' and b[0] == b[1] and b[1] == b[2]) return true;
	if(b[3] == 'X' and b[3] == b[4] and b[4] == b[5]) return true;
	if(b[6] == 'X' and b[6] == b[7] and b[7] == b[8]) return true;
	if(b[0] == 'X' and b[0] == b[4] and b[4] == b[8]) return true;
	if(b[2] == 'X' and b[2] == b[4] and b[4] == b[6]) return true;
	return false;
}

bool lineo(){
	if(b[0] == 'O' and b[0] == b[3] and b[3] == b[6]) return true;
	if(b[1] == 'O' and b[1] == b[4] and b[4] == b[7]) return true;
	if(b[2] == 'O' and b[2] == b[5] and b[5] == b[8]) return true;
	if(b[0] == 'O' and b[0] == b[1] and b[1] == b[2]) return true;
	if(b[3] == 'O' and b[3] == b[4] and b[4] == b[5]) return true;
	if(b[6] == 'O' and b[6] == b[7] and b[7] == b[8]) return true;
	if(b[0] == 'O' and b[0] == b[4] and b[4] == b[8]) return true;
	if(b[2] == 'O' and b[2] == b[4] and b[4] == b[6]) return true;
	return false;
}

int main(){
	for(i = 0; i < 9; ++i){
		while((b[i]=getchar_unlocked()) != '.' and b[i] != 'O' and b[i] != 'X' and b[i] != EOF);
		if(b[i] == EOF) break;
		if(b[i] == 'O') ++o;
		if(b[i] == 'X') ++x;
	}
	if(i < 9 or o < x or o - x > 1 or (o == x and lineo()) or (o == x + 1 and linex())) puts("IMPOSSIBLE");
	else puts("POSSIBLE");
	return 0;
}