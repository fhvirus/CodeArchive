#pragma GCC optimize("Os")
#include<unistd.h>
char OB[50], OP;
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=' ';}
char s[9];
int o, x, t;
bool jiz[19683];
int h(){
	int ans = 0;
	for(int i = 0; i < 9; ++i)
		ans *= 3, ans += (s[i] == '-' ? 0 : (s[i] == 'O' ? 1 : 2));
	return ans;
}
const int dir[8][3] = {
	{0, 1, 2},
	{3, 4, 5},
	{6, 7, 8},
	{0, 3, 6},
	{1, 4, 7},
	{2, 5, 8},
	{0, 4, 8},
	{2, 4, 6}
};
bool check(){
	int id = h();
	if(jiz[id]) return true;
	jiz[id] = true;
    bool eek = false;
    for(int d = 0; d < 8 and !eek; ++d){
    	if(s[dir[d][0]] != '-' and s[dir[d][0]] == s[dir[d][1]] and s[dir[d][1]] == s[dir[d][2]])
    		eek = true, ++(s[dir[d][0]] == 'O' ? o : x);
    }
    if(eek) return true;
    for(int i = 0; i < 9; ++i){
        if(s[i] == '-') return false;
    }
    ++t;
    return true;
}
void dfs(int d){
    if(check()) return;
    for(int i = 0; i < 9; ++i){
        if(s[i] == '-'){
            s[i] = (d % 2 == 0 ? 'O' : 'X');
            dfs(d + 1);
            s[i] = '-';
        }
    }
}
int main(){
    read(0,s,9);
    int d = 0;
    for(int i = 0; i < 9; ++i){
        if(s[i] == 'O' or s[i] == 'X')
            ++d;
    }
    dfs(d);
    W(o + x + t);
    W(o);
    W(x);
    W(t);
    write(1, OB, OP);
    return 0;
}