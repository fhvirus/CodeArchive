#include<cstdio>
char eek[51], l, f[26], b[26], i;
inline void W(char n){
	n >= 10 ? putchar_unlocked('0' + n/10), putchar_unlocked('0' + n%10) : putchar_unlocked('0' + n);
}
int main(){
	l = fread(eek, 1, 51, stdin);
	for(i=0;i<26;++i)f[i]=b[i]=-1;
	for(i=0;i<l;++i) if(f[eek[i]-'A']==-1) f[eek[i]-'A']=i;
	for(i=l-1;i>-1;--i) if(b[eek[i]-'A']==-1) b[eek[i]-'A']=i;
	for(i=0;i<26;++i) if(f[i]!=-1) putchar_unlocked('A'+i), putchar_unlocked(':'), W(f[i]+1), putchar_unlocked(','),W(b[i]+1),putchar_unlocked('\n');
}