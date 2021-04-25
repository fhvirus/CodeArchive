#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n<0)n=-n,OB[OP++]='-';if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

const int N = 3000000 + 225;
int a[N], b[N];
int occ[N], to[N];
#include<algorithm>

int main(){
	int lena = 1, lenb = 1;
	char c; int eek = 0;
	int flag = 0;
	while(true){
		c = RC();
		if(c == '\n'){
			a[lena] = eek;
			break;
		}
		if(c == ' '){
			if(flag == 0){
				a[lena++] = eek; eek = 0;
			}
			flag = 1;
			continue;
		}
		if(c >= '0'){
			flag = 0;
			eek *= 10;
			eek += c - '0';
		}
	}
	eek = 0;
	while(true){
		c = RC();
		if(c == '\n'){
			b[lenb] = eek;
			break;
		}
		if(c == ' '){
			if(flag == 0){
				b[lenb++] = eek; eek = 0;
			}
			flag = 1;
			continue;
		}
		if(c >= '0'){
			flag = 0;
			eek *= 10;
			eek += c - '0';
		}
	}
	if(lena != lenb){
		W(-1);
		return 0;
	}

	for(int i = 1; i <= lena; ++i) occ[a[i]] = i;
	for(int i = 1; i <= lenb; ++i) to[i] = occ[b[i]];
	for(int i = 1; i <= lena; ++i) occ[to[i]] = i;

	int ans = 0;
	for(int i = 1; i <= lena; ++i){
		if(to[i] != i){
			int j = to[i];
			std::swap(to[i], to[occ[i]]);
			std::swap(occ[i], occ[j]);
			++ans;
		}
	}
	W(ans);
	return 0;
}