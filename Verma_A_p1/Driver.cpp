#include<cctype>
#include<iostream>
#include<string>
#include<string.h>
#include<stdio.h>
#include "program1.h"
/*I have done this assignment completely on my own.  I have not copied it, nor have I given my solution to someone else.  I understand if I am involved in plagirism or cheatingI will have to sign an official form that I have cheated and that this form will be stored in my official university record.  I also understand I will recieve a grade of 0 for the involved assignment and will recieve a grade of "F" for the course for any additional offense */
using namespace std;

int main(int argc, char *argv[]){
	//establishing the input output files
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
//		cout<<mFile<<" "<<oFile<<endl;
	}
	Program1 Hello(mFile, pFile);
	/*Hello.helloworld();
	Hello.buildMarketMap();
	Hello.buildPricesMap();
	Hello.buildProfitMap();
	Hello.resetArray();
	Hello.computeMaxProfit();
	*/
	Hello.run();
	return 0;
}
