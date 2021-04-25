#include "lib1860.h"
int T, n, observe_num, choose_num, max_moeness, i, moe;
bool flag;
int main(){
	int T = Start_The_Loli_Dream();
	for(;T;--T){
		n = Count_How_Many_Loli();
		observe_num = n * 0.368 + .5;
		choose_num = n - observe_num;
		max_moeness = -2147483648;
		for(i = 0, moe; i < observe_num; ++i){
			moe = Get_Loli_Moeness();
			max_moeness = max_moeness > moe ? max_moeness : moe;
		}
		flag = false;
		for(i = 0; i < choose_num; ++i){
			if(Get_Loli_Moeness() > max_moeness){
				You_Choose_This_Loli();
				flag = true;
				break;
			}
		}
		if(!flag) You_Choose_This_Loli();
	}
}