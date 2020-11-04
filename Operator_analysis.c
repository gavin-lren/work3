#include<stdio.h>
#include<string.h>
char opstack[1024];//符号栈
char input[1024];//读入
int topi = 0; 
int tops = -1;//符号栈指针

char nowopchar;//当前符号
int nowopint = 0;//当前读入符号对应值
int lastopint = 0;//上一个读入符号对应值
int flag = 0;
int eof = 0;


int operator(int x, int y) {
	int a[6][6] = {
		 1,-1,-1,-1, 1, 1,
		 1, 1,-1,-1, 1, 1,
		 1, 1, 0, 0, 1, 1,
		-1,-1,-1,-1, 2, 0,
		 1, 1, 0, 0, 1, 1,
		-1,-1,-1,-1, 0, 2,
	};
	return a[x - 1][y - 1];
}

int optoint(char s) {
	switch (s) {
		case '+': 
			return 1;
		case '*': 
			return 2;
		case 'i': 
			return 3;
		case '(':
			return 4;
		case ')': 
			return 5;
		case '#':
			return 6;
		case '\r':
			return 7;
		case 'N':
			return 8;
		default:
			return 0;
	}
}


int main(int argc,char *argv[]){
	int j=0;
	FILE *fp = NULL;
	fp = fopen( argv[1] , "r");//读入文件 
	if(fp == NULL){
		return 0;
	}
	fgets(input,1024,fp);
	opstack[++tops] = '#';
	while(1){
		nowopchar = input[topi];
		nowopint = optoint(nowopchar);
		if (nowopint == 0){
			printf("E\n");
			break;
		}
		if (nowopint == 7){
			input[topi] = '#';
			nowopchar = '#';
			nowopint = optoint(nowopchar);
		}
		
		if(optoint(opstack[tops]) == 8){
			j = tops-1;
		}
		else{
			j = tops;
		}
		lastopint = optoint(opstack[j]);
		flag = operator(lastopint, nowopint);
		if (flag == 0) {
			printf("RE\n");
			break;
		}
		else if(flag == 1){
			char i;	
			if((nowopint==6 || nowopint==5) && (lastopint !=3 && optoint(opstack[tops])!=8 && lastopint!=5) ){
				printf("RE\n");
				break;
			}
			do{
				i=opstack[j];
				if(optoint(opstack[j-1]) == 8){
					j = j - 2;
				}
				else{
					j = j - 1;
				}
			}while(operator(optoint(opstack[j]),optoint(i))!=-1);
			tops = j + 1;
			opstack[tops]='N';
			printf("R\n");
		}
		else if(flag == -1){
			opstack[++tops] = nowopchar;	
			printf("I%c\n",nowopchar);
			topi++; 
		}
		else if(flag == 2){
			if(opstack[j]=='#'){
				break;
			}
			else{
				opstack[++tops] = nowopchar;	
				printf("I%c\n",nowopchar);	
				topi++;
			}
		}
	}
	fclose(fp);
	return 0;
} 
