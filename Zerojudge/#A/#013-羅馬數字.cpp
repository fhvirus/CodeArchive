#include<iostream>
#include<string>
using namespace std;

int romanToInt(string romanNum){
	int ans=0;
	for(int i=0;i<romanNum.size();i++){
		switch(romanNum[i]){
			case 'M':
				if(i!=0&&romanNum[i-1]=='C') ans+=800;
				else ans+=1000;
				break;
			case 'D':
				if(i!=0&&romanNum[i-1]=='C') ans+=300;
				else ans+=500;
				break;
			case 'C':
				if(i!=0&&romanNum[i-1]=='X') ans+=80;
				else ans+=100;
				break;
			case 'L':
				if(i!=0&&romanNum[i-1]=='X') ans+=30;
				else ans+=50;
				break;
			case 'X':
				if(i!=0&&romanNum[i-1]=='I') ans+=8;
				else ans+=10;
				break;
			case 'V':
				if(i!=0&&romanNum[i-1]=='I') ans+=3;
				else ans+=5;
				break;
			case 'I':
				ans+=1;
				break;
		}
	}
	return ans;
}

string intToRoman(int i){
	if(i==0){
		return "ZERO";
	}
	else{
		string ans="";
		while(i>0){
			if(i>=1000){i-=1000;ans.append("M");}
			else if(i>=900){i-=900;ans.append("CM");}
			else if(i>=500){i-=500;ans.append("D");}
			else if(i>=400){i-=400;ans.append("CD");}
			else if(i>=100){i-=100;ans.append("C");}
			else if(i>=90){i-=90;ans.append("XC");}
			else if(i>=50){i-=50;ans.append("L");}
			else if(i>=40){i-=40;ans.append("XL");}
			else if(i>=10){i-=10;ans.append("X");}
			else if(i>=9){i-=9;ans.append("IX");}
			else if(i>=5){i-=5;ans.append("V");}
			else if(i>=4){i-=4;ans.append("IV");}
			else if(i>=1){i-=1;ans.append("I");}
		}
		return ans;
	}
}

int main(){
	string romanA,romanB;
	int A,B;
	while(cin>>romanA&&romanA!="#"){
		cin>>romanB;
		A=romanToInt(romanA);
		B=romanToInt(romanB);
		cout<<intToRoman(abs(A-B))<<endl;
	}
	return 0;
}