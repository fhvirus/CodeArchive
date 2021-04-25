#include "lib1865.h"
int n=GetN()-1,i,j;
int main(){
	for(i=0;i<n;++i)for(j=i;j>=0;--j)Magic_Operate(j);
	End();
}