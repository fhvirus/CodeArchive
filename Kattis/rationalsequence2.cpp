#include<cstdio>

int dp[1];

int main(){
	long long int T,k,p,q;
	int ans;
	scanf("%lld",&T);
	while(T--){
		scanf("%lld %lld/%lld",&k,&p,&q);
		if(p==1&&q==1)ans=1;
		else if(p==1)ans=(1<<(q-1));
		else if(q==1)ans=(1<<p)-1;
		else{
			ans=0;
			int ptr=0;
			while(p!=q){
				if(p>q){
					p-=q;
					ans=ans|(1<<(ptr++));
				}else{
					q-=p;
					ptr++;
				}
			}
			ans=ans|(1<<ptr);
		}
		printf("%lld %d\n",k,ans);
	}
	return 0;
}