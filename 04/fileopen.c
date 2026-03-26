#include<stdio.h>
int main(){
	FILE *fp;
	fp = fopen("./readme.md", "r");
	if(fp == NULL)
		printf("파일 열기 오류\n");
	fclose(fp);

	return 0;
}
