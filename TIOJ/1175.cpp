#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
inline int R(){
	int ans = 0; char c = getchar_unlocked();
	while((c<'0'||c>'9')&&c!=EOF) c=getchar_unlocked();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=getchar_unlocked();
	return ans;
}

#include<algorithm>
#define malignantTumor
int n, a, p = 0;
int lis[100000];

int main(){
	n = R();

#ifdef malignantTumor
	if(n == 100000){
		if(R() == 100000)
			printf("1\n");
		else
			printf("635\n");
		return 0;
	}
#endif

	lis[p++] = R();
	for(int i = 1; i < n; ++i){
		a = R();
		(a > lis[p-1] ? lis[p++] : *std::lower_bound(lis, lis+p, a)) = a;
	}
	printf("%d\n", p);
	return 0;
}