#include "program1.h"
#include<map>
#include<iostream>
#include<string>
#include<stdexcept>
#include<fstream>
#include<cctype>
#include<sstream>

using namespace std;
Program1::Program1(string mfile, string pfile){
	iFile.open(mfile);
	iiFile.open(pfile);
	if(!iFile.is_open()){
		cerr<<"error in opening files"<<endl;
	}	    
}
Program1::~Program1(){
}
void Program1::buildMarketMap(){
	string name;
	int price;
	int totalCards=-1;
	string line;
	getline(iFile,line);
	stringstream ss(line);
	ss >> totalCards;
	for(int i=0; i<totalCards; i++){
		getline(iFile, line);
		stringstream ss(line);
		ss >> name >> price;
		mPrices[name]=price;
	}


}
int Program1::buildPricesMap(){
	string name;
	weight=0;
	int problemSize=0;
	totalCost=0;
	int price=0;
	problemNumber++;
	string line;
	getline(iiFile, line);
	stringstream ss(line);
	ss >> problemSize >> weight;
	cout<<problemSize<<endl;
	cout<<weight<<endl;
	for(int i=0; i<problemSize; i++){
		getline(iiFile, line);
		stringstream ss(line);
		ss >> name >> price;
		totalCost+=price;
		auto search = mPrices.find(name);
		if(search != mPrices.end()){
			gPrices[name]=price;
		}
		else{
			cout<<"Unfortunately card "<<name<<" was not found to have a valid market price.  Program will have to end";
			return -1;
		}
	}
	return 0;
}
void Program1::computeMaxProfit(){
	int maxProfit=0;
	int profit=0;
	if(totalCost<=weight){
		//calculate total profit
		map<string, int>::const_iterator
			map_it = gPrices.begin();
		while(map_it != gPrices.end()){
			profit+= mPrices[map_it->first];
			++map_it;
		}
		maxProfit=profit;
	}
}
void Program1::helloworld(){
	cout<<"hello world"<<endl;
}

