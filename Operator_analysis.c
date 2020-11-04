#include<stdio.h>
#include<string.h>
char opstack[1024];//����ջ
char input[1024];//����
int topi = -1; 
int tops = -1;//����ջָ��

char nowopchar;//��ǰ����
int nowopint = 0;//��ǰ������Ŷ�Ӧֵ
int lastopint = 0;//��һ��������Ŷ�Ӧֵ
int flag = 0;
int eof = 0;

void init() {
	opstack[++tops] = '#';
}

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
		case '\n':
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
	fp = fopen( argv[1] , "r");//�����ļ� 
//	fp = fopen( "TEST.txt" , "r");//test����  
	if(fp == NULL){
		return 0;
	}
	fgets(input,1024,fp);
	init();
	while(1){
		nowopchar = input[++topi];
		nowopint = optoint(nowopchar);
		if (nowopint == 0){
			printf("E\n");
			break;
		}
		if (nowopint == 7){
			if(input)
			topi--;
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
			printf("E\n");
			break;
		}
		else if(flag == 1){
			char i;
			if(lastopint == 3||lastopint == 8||nowopint == 3){
				
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
				topi--;
				opstack[tops]='N';
				printf("R\n");
			}
			else{
				printf("RE\n");
				break;
			}
		}
		else if(flag == -1){
			opstack[++tops] = nowopchar;	
			printf("I%c\n",nowopchar);
		}
		else if(flag == 2){
			if(opstack[j]=='#'){
				break;
			}
			else{
				opstack[++tops] = nowopchar;	
				printf("I%c\n",nowopchar);	
			}
		}
	}
	fclose(fp);
	return 0;
} 
