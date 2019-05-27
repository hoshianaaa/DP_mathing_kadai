#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void mat_clear(int height,int width,double mat[height][width]){

		for(int i=0;i<height;i++){ 
				for(int j=0;j<width;j++){
						mat[i][j] = 0;
				}
		}
}


void mat_print(int height,int width,double mat[height][width]){ 
	for(int i=0;i<height;i++){ 
		for(int j=0;j<width;j++){
			//printf("%4.3lf\t ",(float)mat[i][j]);
			printf("%1.0lf ",(float)mat[i][j]);
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


void distance(int size1,int size2,double data1[size1][15],double data2[size2][15],double data[size1][size2]){
	
	mat_clear(size1,size2,data);
	
	for(int height=0;height<size1;height++){
		for(int width=0;width<size2;width++){
			for(int i=0;i<15;i++){
				data[height][width] += pow(data1[height][i] - data2[width][i],2);
			}
		data[height][width] = sqrt(data[height][width]);
		}
	}
}


int main(void) {
	
	char fname[] = "city011/city011_001.txt";
	const int size = 61;
	double data[size][15];

	file_readData(fname,size,data);
	mat_print(size,15,data);
	

	char fname2[] = "city012/city012_001.txt";
	const int size2 = 64;
	double data2[size2][15];

	file_readData(fname2,size2,data2);
	mat_print(size2,15,data2);

	double data_dis[size][size2];
	distance(size,size2,data,data2,data_dis);
	mat_print(size,size2,data_dis);

	return 0;
}
