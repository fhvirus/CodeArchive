#include<cstdio>

int dp[1];

int main(){
	long long int T,k,p,q,m;
	int ans;
	scanf("%lld",&T);
	while(T--){
		scanf("%lld %lld/%lld",&k,&p,&q);
		
		if(q==1){
			printf("%lld 1/%lld\n",k,p+1);
		}
		else{
			long long int cnt=0,tmp;
			while(p>q)p-=q,cnt++;
			tmp=p,p=q,q-=tmp;
			while(cnt--)q+=p;
			printf("%lld %lld/%lld\n",k,p,q);
		}
	}
	return 0;
}