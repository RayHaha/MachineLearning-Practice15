#include <iostream>
#include <armadillo>
#include<fstream>
#include<math.h>

using namespace std;
using namespace arma;

// Armadillo documentation is available at:
// http://arma.sourceforge.net/docs.html

int
main(int argc, char** argv){
	
	char theline [100] ;
	
	//read file
	fstream fin;
	fin.open("traindata.txt",ios::in);
	double data[200][5];
	double fold[40][5];
	double fold1[40][5];
	double fold2[40][5];
	double fold3[40][5];
	double fold4[40][5];
	double fold5[40][5];
	double exfold[160][5];


	//initial
	for(int i=0; i<200; i++){
		data[i][0] = 1;
		for(int j=1; j<5; j++){
			data[i][j] = 0 ;
		}
	}
	//分割字串存入二維陣列
	char *token = NULL;
	char *next_token = NULL;
	char seps[]   = " ,\t\n";
	int a=0;
	while(fin.getline(theline,sizeof(theline),'\n')){
		int b = 0;
		token = strtok_s( theline, seps, &next_token);
		while (token != NULL){
			data[a][b+1] = atof(token);
            token = strtok_s( NULL, seps, &next_token);
			b++;
		}
		a++;
	}
	fin.close();

	for(int i=0; i<40; i++){
		for(int j=0; j<5; j++){
			fold1[i][j] = data[i][j];
		}
	}for(int i=0; i<40; i++){
		for(int j=0; j<5; j++){
			fold2[i][j] = data[i+40][j];
		}
	}for(int i=0; i<40; i++){
		for(int j=0; j<5; j++){
			fold3[i][j] = data[i+80][j];
		}
	}for(int i=0; i<40; i++){
		for(int j=0; j<5; j++){
			fold4[i][j] = data[i+120][j];
		}
	}for(int i=0; i<40; i++){
		for(int j=0; j<5; j++){
			fold5[i][j] = data[i+160][j];
		}
	}
	mat I(3,3);
		for(int i=0; i<3; i++){
			for(int j=0; j<3; j++){
				if(i==j){
					I(i,j) = 1;
				}else{
					I(i,j) = 0;
				}
			}
		}
	mat fdata(40,3);
	mat elsedata(160,3);
	double ein[13];
	double lamda[13];
	for(int i=0; i<13; i++){
		lamda[i] = 0;
		ein[i] = 0;
	}
	for(int i=0; i<13; i++){
		lamda[i] = pow(10,i-10);
		cout<<lamda[i]<<endl;
	}
	double smallestein = 100;
	double g[3]={0,0,0};
	int smallestl = 0;
	double wREG[5][3] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
	for(int c=0; c<5; c++){
		if(c==0){
			for(int i=0; i<40; i++){
				for(int j=0; j<3; j++){
					fdata(i,j) = fold1[i][j];
					fold[i][j] = fold1[i][j];
				}
			}
			for(int i=0; i<40; i++){
				fold[i][3] = data[i][3];
			}
			for(int i=0; i<160; i++){
				for(int j=0; j<4; j++){
					if(j!=3){
						elsedata(i,j) = data[i+40][j];
						exfold[i][j] = data[i+40][j];
					}else{
						exfold[i][j] = data[i+40][j];
					}
				}
			}
		}
		if(c==1){
			for(int i=0; i<40; i++){
				for(int j=0; j<3; j++){
					fdata(i,j) = fold2[i][j];
					fold[i][j] = fold2[i][j];
				}
			}
			
			for(int i=0; i<40; i++){
				fold[i][3] = data[i+40][3];
			}
			for(int i=0; i<40; i++){
				for(int j=0; j<4; j++){
					if(j!=3){
						elsedata(i,j) = data[i][j];
						exfold[i][j] = data[i][j];
					}else{
						exfold[i][j] = data[i][j];
					}
				}
			}
			for(int i=40; i<160; i++){
				for(int j=0; j<4; j++){
					if(j!=3){
						elsedata(i,j) = data[i+40][j];
						exfold[i][j] = data[i+40][j];
					}else{
						exfold[i][j] = data[i+40][j];
					}
				}
			}
		}
		if(c==2){
			for(int i=0; i<40; i++){
				for(int j=0; j<3; j++){
					fdata(i,j) = fold3[i][j];
					fold[i][j] = fold3[i][j];
				}
			}
			
			for(int i=0; i<40; i++){
				fold[i][3] = data[i+80][3];
			}
			for(int i=0; i<80; i++){
				for(int j=0; j<4; j++){
					if(j!=3){
						elsedata(i,j) = data[i][j];
						exfold[i][j] = data[i][j];
					}else{
						exfold[i][j] = data[i][j];
					}
				}
			}
			for(int i=80; i<160; i++){
				for(int j=0; j<4; j++){
					if(j!=3){
						elsedata(i,j) = data[i+40][j];
						exfold[i][j] = data[i+40][j];
					}else{
						exfold[i][j] = data[i+40][j];
					}
				}
			}
		}
		if(c==3){
			for(int i=0; i<40; i++){
				for(int j=0; j<3; j++){
					fdata(i,j) = fold4[i][j];
					fold[i][j] = fold4[i][j];
				}
			}
			for(int i=0; i<40; i++){
				fold[i][3] = data[i+120][3];
			}
			for(int i=0; i<120; i++){
				for(int j=0; j<4; j++){
					if(j!=3){
						elsedata(i,j) = data[i][j];
						exfold[i][j] = data[i][j];
					}else{
						exfold[i][j] = data[i][j];
					}
				}
			}
			for(int i=120; i<160; i++){
				for(int j=0; j<4; j++){
					if(j!=3){
						elsedata(i,j) = data[i+40][j];
						exfold[i][j] = data[i+40][j];
					}else{
						exfold[i][j] = data[i+40][j];
					}
				}
			}
		}
		if(c==4){
			for(int i=0; i<40; i++){
				for(int j=0; j<3; j++){
					fdata(i,j) = fold5[i][j];
					fold[i][j] = fold5[i][j];
				}
			}
			for(int i=0; i<40; i++){
				fold[i][3] = data[i+160][3];
			}
			for(int i=0; i<160; i++){
				for(int j=0; j<4; j++){
					if(j!=3){
						elsedata(i,j) = data[i][j];
						exfold[i][j] = data[i][j];
					}else{
						exfold[i][j] = data[i][j];
					}
				}
			}
		}
		for(int l=0; l<13; l++){
			mat inZT(3,160);
			inZT = inv(elsedata.t()*elsedata+lamda[l]*I)*elsedata.t();
			//wREG
			for(int i=0; i<3; i++){
				wREG[c][i] = 0;
			}
			for(int i=0; i<3; i++){
				for(int j=0; j<160; j++){
					wREG[c][i] = wREG[c][i] + inZT(i,j)*exfold[j][3];
				}
			}

			//calculate ein
			for(int i=0; i<40; i++){
				double temp = wREG[c][0]*fold[i][0] + wREG[c][1]*fold[i][1] + wREG[c][2]*fold[i][2];
				int h = 0;
				if(temp>0){
					h = 1;
				}else{
					h = -1;
				}
				if(h==fold[i][3]){

				}else{
					ein[l]++;
				}
			}
		}


	}
	for(int i=0; i<13; i++){
		ein[i] = ein[i]/200;
		cout<<"Ein"<<lamda[i]<<endl;
		cout<<ein[i]<<endl;

		if(ein[i]<=smallestein){
			smallestein = ein[i];
			for(int j=0; j<3; j++){
				g[j] = wREG[i][j];
				smallestl = i;
			}
		}
	}
	
	mat wholedata(200,3);
	for(int i=0; i<200; i++){
		for(int j=0; j<3; j++){
			wholedata(i,j) = data[i][j];
		}
	}
	mat iii = inv(wholedata.t()*wholedata+lamda[smallestl]*I)*wholedata.t();
	//wREG
	double wiii[3] = {0,0,0};
	for(int i=0; i<3; i++){
		for(int j=0; j<200; j++){
			wiii[i] = wiii[i] + iii(i,j)*data[j][3];
		}
	}
	for(int i=0; i<3; i++){
		g[i] = wiii[i];
	}
	double eing = 0;
	//calculate ein
	for(int i=0; i<200; i++){
		double temp = wiii[0]*data[i][0] + wiii[1]*data[i][1] + wiii[2]*data[i][2];
		double h = 0;
		if(temp>0){
			h = 1;
		}else{
			h = -1;
		}
		if(h==data[i][3]){
	
		}else{
			eing++;
		}
	}
	eing = eing/200;
	cout<<"Ein"<<lamda[smallestl]<<endl;
	cout<<eing<<endl;

	//read file
	fin.open("testdata.txt",ios::in);
	double test[1000][5];


	//initial
	for(int i=0; i<1000; i++){
		test[i][0] = 1;
		for(int j=1; j<5; j++){
			test[i][j] = 0 ;
		}
	}
	//分割字串存入二維陣列
	char *token2 = NULL;
	char *next_token2 = NULL;
	a=0;
	while(fin.getline(theline,sizeof(theline),'\n')){
		int b = 0;
		token2 = strtok_s( theline, seps, &next_token2);
		while (token2 != NULL){
			test[a][b+1] = atof(token2);
            token2 = strtok_s( NULL, seps, &next_token2);
			b++;
		}
		a++;
	}
	
	//calculate eout
	double eout = 0;
	for(int i=0; i<1000; i++){
		double temp = g[0]*test[i][0] + g[1]*test[i][1] + g[2]*test[i][2];
		double h = 0;
		if(temp>0){
			h = 1;
		}else{
			h = -1;
		}
		if(h==test[i][3]){

		}else{
			eout++;
		}
	}
	eout = eout/1000;
	cout<<"Eout"<<endl;
	cout<<eout<<endl;
	
	//open file
	char filename3[]="ein.txt";
	fstream fp;
	fp.open(filename3, ios::out);//開啟檔案
	if(!fp){//如果開啟檔案失敗，fp為0；成功，fp為非0
        cout<<"Fail to open file: "<<filename3<<endl;
    }
	for(int i=0; i<13; i++){
		fp<<ein[i]<<endl;//寫入字串
	}
	fp.close();//關閉檔案

  system("pause");
  return 0;
  }