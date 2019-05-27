#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void mat_clear(int height,int width,int mat[height][width]){

		for(int i=0;i<height;i++){ 
				for(int j=0;j<width;j++){
						mat[i][j] = 0;
				}
		}
}


void mat_print(int height,int width,double mat[height][width]){ 
	for(int i=0;i<height;i++){ 
		for(int j=0;j<width;j++){
			printf("%4.3lf\t ",(float)mat[i][j]);
		}
		printf("\n");
	}
}
//file関係
void file_oneLine(FILE *fp){
	while(!(fgetc(fp)=='\n'));
}

double file_oneData(FILE *fp){
	double f;
	fscanf(fp,"%lf ",&f);
	return f;
}

void file_readData(char file_name[],int size,double f[size][15]){

	FILE *fp; // FILE型構造体
	
	fp = fopen(file_name, "r"); // ファイルを開く。失敗するとNULLを返す。
	if(fp == NULL) {
		printf("%s file not open!\n", file_name);
	}
	//printf("file open!%s\n",file_name);
	for(int i=0;i<3;i++)file_oneLine(fp);

	for(int j=0;j<size;j++){
		for(int i=0;i<15;i++){
			f[j][i] = file_oneData(fp);
			//f[j][i] = 0;
			//printf("f[%d][%d]: %lf\n",j,i,f[j][i]);
		}
	}
}

int main(void) {
	
	char fname[] = "city011/city011_001.txt";
	const int size = 61;
	double data[size][15];

	file_readData(fname,size,data);
	mat_print(size,15,data);

	return 0;
}
