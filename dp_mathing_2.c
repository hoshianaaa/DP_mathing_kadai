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

int file_getSize(char fname[]){
	FILE *fp; // FILE型構造体
	
	fp = fopen(fname, "r"); // ファイルを開く。失敗するとNULLを返す。
	if(fp == NULL) {
		printf("%s file not open!\n", fname);
		return -1;
	}
	file_oneLine(fp);
	file_oneLine(fp);
	return (int)file_oneData(fp);
}


void file_nameChange(char fname[],int number){
	if(number < 10){
		fname[16] = 0 + 48;//0はcharでは48
		fname[17] = 0 + 48;
		fname[18] = number + 48;
	}
	else if(number < 100){
		fname[16] = 0 + 48;
		fname[17] = (int)(number/10) + 48;
		fname[18] = number%10 + 48;
	}
	else if(number == 100){
		fname[16] = 1 + 48;
		fname[17] = 0 + 48;
		fname[18] = 0 + 48;
	}
}
	

double min(double x,double y,double z){

	double min=x;
	int num=1;
	if(min>y){min=y;num=2;}
	if(min>z){min=z;num=3;}
	return min;
}

double dp_mathing(int size1,int size2,double data[size1][size2],double g[size1][size2]){
	g[0][0] = data[0][0];
	for(int i=0;i<size1;i++)g[i][0] = g[i-1][0] + data[i][0];
	
	for(int i=0;i<size2;i++)g[0][i] = g[0][i-1] + data[0][i];

	for(int h=1;h<size1;h++){
		for(int w=1;w<size2;w++){
			g[h][w]=min(g[h-1][w]+data[h][w],g[h][w-1]+data[h][w],g[h-1][w-1]+2*data[h][w]);
		}
	}

return g[size1-1][size2-1];

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
	int min = 100;
	int num = 1;

	file_readData(fname,size,data);
	mat_print(size,15,data);
	

	char fname2[] = "city012/city012_001.txt";
	int size2 = 64;
	for(int i=1;i<101;i++){
		file_nameChange(fname2,i);
		size2 = file_getSize(fname2);
		double data2[size2][15];

		file_readData(fname2,size2,data2);
		mat_print(size2,15,data2);

		double data_dis[size][size2];
		distance(size,size2,data,data2,data_dis);
		mat_print(size,size2,data_dis);

		
		double g[size][size2];
		double dis;
		mat_clear(size,size2,g);
		dis = dp_mathing(size,size2,data_dis,g);
		mat_print(size,size2,g);
		printf("distance: %lf\n",g[size-1][size2-1]/(size+size2));
		if(min > dis){min = dis;num = i;}
	}
		
	return 0;
}
