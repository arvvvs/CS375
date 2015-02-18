#include<cctype>
#include<iostream>
#include<string>
#include<string.h>
#include<stdio.h>
#include "program1.h"

using namespace std;

int main(int argc, char *argv[]){
	string mFile;
	string pFile;
	string oFile;
	string sFile[4];
	if(argc==5){
		for(int i=0; i<argc; ++i){
			sFile[i]=argv[i];
		//	cout<<sFile[i]<<endl;
		}
	}
	else{
		cout<<"incorrect commands"<<endl;
	}
	if(strcmp(argv[1],"-m") !=0 && strcmp(argv[3],"-p") !=0){
		cout<<"incorrect flags"<<endl;
	}
	else{
		mFile=argv[2];
		pFile=argv[4];
		cout<<mFile<<" "<<oFile<<endl;
	}
	Program1 Hello(mFile, pFile);
	Hello.helloworld();
	Hello.buildMarketMap();
	Hello.buildPricesMap();
	Hello.computeMaxProfit();
	Hello.buildProfitMap();
	Hello.resetArray();
	Hello.generateSubsetTemplate();

	return 0;

}
