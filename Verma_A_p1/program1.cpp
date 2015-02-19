#include "program1.h"
#include<time.h>
#include<math.h>
#include<map>
#include<iostream>
#include<string>
#include<list>
#include<vector>
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
	oFile.open("output.txt");	
}
Program1::~Program1(){
}
void Program1::buildMarketMap(){
	string name;
	map<string, int> mmPrices;
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
	if(!gPrices.empty()){
		gPrices.clear();
	}
	weight=0;
	int problemSize=0;
	totalCost=0;
	int price=0;
	problemNumber++;
	string line;
	getline(iiFile, line);
	stringstream ss(line);
	ss >> problemSize >> weight;
	size=problemSize;
	//cout<<problemSize<<endl;
	//cout<<weight<<endl;
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
			abort();
		}
	}
	return 0;
}
void Program1::buildProfitMap(){
	profitPrices.clear();
	map<string, int>::const_iterator
		map_it = gPrices.begin();
	while(map_it != gPrices.end()){
		profitPrices[map_it->first]=mPrices[map_it->first]-gPrices[map_it->first];	
		//cout<<map_it->first<<endl;
		//cout<<profitPrices[map_it->first]<<endl;
		++map_it;
	}
}
int Program1::generateSubsetTemplate(){
	vector<int>compare;
	for(int i=0; i<size; i++){
		compare.push_back(0);
	}
	/*if(compare==foo){
		cout<<"it works"<<endl;
	}*/

	/*for(int i=0; i<size; i++){
		cout<<foo.at(i);
	}*/
	//cout<<endl;
	vector<int>::const_iterator ii;
	do{
	for(unsigned i=0; i<foo.size(); i++){
		if(foo.at(i)==0){
			foo.at(i)=1;
			//cout<<"hello"<<endl;
			return -1;
		}
		else if(foo.at(i)==1){
			//cout<<"hello again"<<endl;
			foo.at(i)=0;
		}
	}
	}while(compare!=foo);
	//cout<<endl;
	if(compare==foo){
	return -2;
	}	
	else{
	return 0;
	}
	return 0;
	
}
void Program1::resetArray(){
	for(int i=0; i<size; i++){
		foo.push_back(0);
	}

}
void Program1::generateSubset(){
	vector<int> prices;
	vector<string> names;
	map<string, int>::const_iterator
		it = profitPrices.begin();
	while(it != profitPrices.end()){
	prices.push_back(it -> second);
	names.push_back(it -> first);
	++it;
	}	
	namesSubset.clear();
	profitSubset.clear();
	for(int i=0; i<size; i++){
		if(foo.at(i)==1){
			namesSubset.push_back(names.at(i));
			//cout<<names.at(i)<<endl;
			profitSubset.push_back(prices.at(i));
		}
		
	}
}

void Program1::computeMaxProfit(){
	maxProfit=0;
	int profit=0;
	winningSubset.clear();
	vector<string> currentNames;
	int looping=pow (2.0, size)-1;
	//cout<<looping<<endl;
	if(totalCost<=weight){
		//calculate total profit
		map<string, int>::const_iterator
			map_it = gPrices.begin();
		while(map_it != gPrices.end()){
			profit+= mPrices[map_it->first]-map_it->second;
			++map_it;
		}
		maxProfit=profit;
	}
	//for(double i=0; i<pow (2.0,size); i++){
	else{
		//while(generateSubsetTemplate()!=-2){
		for(int i=0; i<looping; i++){
		generateSubsetTemplate();
		generateSubset();
		profit=0;
		currentNames.clear();
		subsetCost=0;
		int xyz = namesSubset.size();
		for(int j=0; j<xyz; j++){
			profit+=profitPrices[namesSubset.at(j)];
			subsetCost+=gPrices[namesSubset.at(j)];
		        currentNames.push_back(namesSubset.at(j)); 	
			//cout<<"current profit is"<<profit<<endl;
			//cout<<"current subset cost is"<<subsetCost<<endl;
		}
			if(subsetCost<=weight){
				if(profit>maxProfit){
					winningSubset.clear();
					maxProfit=profit;
					//cout<<profit<<endl;
					for(int k=0; k<xyz; k++){
					winningSubset.push_back(namesSubset.at(k));
					}
				/*	cout<<"names subset size is "<<namesSubset.size()<<endl;
					cout<<namesSubset.at(0)<<endl;
					for(int k=0; k<namesSubset.size(); k++){
						cout<<k<<endl;
						cout<<"printing winning names"<<endl;
						cout<<namesSubset.at(i)<<" ";
						winningSubset.push_back(namesSubset.at(k));
					}
					cout<<endl;
					cout<<"end"<<endl;
					*/
				}
			
		}
		profitSubset.clear();
	}
		//cout<<endl;
	}

	//}		
	/*
	cout<<"winning subset size is"<<winningSubset.size()<<endl;
	cout<<"winning subset is"<<endl;
	for(int i=0; i<winningSubset.size();i++){
		cout<<winningSubset.at(i)<<endl;
	}
	*/
	//}	
	
	//cout<<"max profit is "<<maxProfit<<endl;
	wSize=winningSubset.size();
}
void Program1::run(){
	clock_t init, final;
	init=clock();
	buildMarketMap();
	buildPricesMap();
	buildProfitMap();
	resetArray();
	computeMaxProfit();
	final=clock()-init;
	double hello;
	hello=(double) final/((double)CLOCKS_PER_SEC);
	//cout<<hello;
	oFile<<size<<" "<<maxProfit<<" "<<wSize<<" "<<hello<<'\n';
	int xyz = winningSubset.size();
	for(int i=0; i<xyz; i++){
		oFile<<winningSubset.at(i)<<'\n';
	}
	check();
}
int Program1::check(){
	int c = iiFile.peek();
	if(c == EOF){
		return -1;
		oFile.close();
	}
	else{
		run();
	}
	return 0;
}
void Program1::helloworld(){
	//cout<<"hello"<<endl;
}
