#include<cstdio>

int readint(){
	int ans = 0, c = getchar();
	while((c<'0' or c>'9') and c!=EOF)c=getchar();
	while(c >= '0' and c <= '9') ans = (ans<<3)+(ans<<1)+(c-'0'), c = getchar();
	return ans;
}

int main(){
	int a = readint(), b = readint(), c = readint(),
		d = readint(), e = readint(), f = readint(),
		h = d-a, m = e-b, s = f-c;
	if(s<0) --m, s+=60;
	if(m<0) --h, m+=60;
	if(h<0) h+=24;
	printf("%02d:%02d:%02d", h, m, s);
}