

#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<ctype.h>
char** token_table;
char buf[256];
void process_token(char* str);
int is_keyword(char* str);
void process_id(char* str);
int main(){

	FILE* handle_r,*handle_w;
	handle_r = fopen("tokeniser1.c","r");
	while(fgets(buf,256,handle_r)!=NULL){

		char* tok;
		tok = strtok(buf," \n\t");
		while(tok!=NULL){
			process_token(tok);
			printf("\n");
		//	printf("%s",tok);
			tok = strtok(NULL," \n\t");

		}

	}

    return 0;

}
void process_token(char* str){


	if(str[0]=='\0'){
		return;
	}
	else if(is_keyword(str)){
		printf(" KEYWORD(%s) ",str);
		return;
	}
	else {

       int i=0,j=0;
       char expr[50];
		while(str[i]!='\0'){


			if(isalpha(str[i])||isdigit(str[i])||strchr("$@_.'\\",str[i])!=NULL||str[i]=='"'){
				expr[j++] = str[i];
			}
		    if(strchr("+-*%^/&=|~><#",str[i])!=NULL){
				expr[j++] ='\0';
				j=0;
				process_token(expr);
				if(strchr("<>=&|+-",str[i])!=NULL&&str[i+1]==str[i]){
					printf(" OPERATOR(%c%c) ",str[i],str[i+1]);
					i++;
				}
				else if(strchr("!+/*%-|&^~",str[i])!=NULL&&str[i+1]=='='){
					printf(" OPERATOR(%c%c) ",str[i],str[i+1]);
					i++;
				}
				else{
					printf(" OPERATOR(%c) ",str[i]);
				}
			}
		    if(str[i]=='('||str[i]=='['||str[i]=='{'){
				expr[j++] = '\0';
				j=0;
				process_token(expr);
				printf(" LPAR('%c') ",str[i]);
			}
		    if(str[i]==')'||str[i]==']'||str[i]=='}'){
				expr[j++] = '\0';
				j=0;
				process_token(expr);
				printf(" RPAR('%c') ",str[i]);
			}
		    if(str[i]==';'||str[i]==','||str[i]=='?'||str[i]==':'){
				expr[j++] = '\0';
				j=0;
				process_token(expr);
				printf(" PUNCT(%c) ",str[i]);
		    }
            i++;
		}
		if(j>=0&&j==i){
			expr[j++] = '\0';
			//printf(" ID(%s) ",str);
			process_id(str);
			return;
		}
		if(j>=0&&j<i-1){
			expr[j++]='\0';
			process_token(expr);
		}

	}


}
void process_id(char* str){


	if(isdigit(str[0])){

		printf(" CONST(%s) ",str);
		return;
	}
	else{
		printf(" ID(%s) ",str);
		return;
	}

}
int is_keyword(char* str){

	int ret=0;
	if(strcmp("if",str)==0){
		ret =1;
	}
	else if(strcmp("for",str)==0){
		ret=1;
	}
	else if(strcmp("while",str)==0){
		ret = 1;
	}
	else if(strcmp("void",str)==0){
		ret=1;
	}
	else if(strcmp("char",str)==0){
		ret=1;
	}
	else if(strcmp("int",str)==0){
		ret=1;
	}
	else if(strcmp("return",str)==0){
		ret=1;
	}
	else if(strcmp("include",str)==0){
			ret=1;
	}
	else if(strcmp("else",str)==0){
			ret=1;
	}
	else{
		ret =0;
	}

	return ret;
}

