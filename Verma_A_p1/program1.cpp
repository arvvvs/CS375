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
//opens the files for input and output, checks to see if files open corrrectly
Program1::Program1(string mfile, string pfile){
	iFile.open(mfile);
	iiFile.open(pfile);
	if(!iFile.is_open()){
		cerr<<"error in opening files"<<endl;
	}	    
	oFile.open("output.txt");	
}
//is here due to convention
Program1::~Program1(){
}
//so this function takes all the input from the market price file and builds a map
void Program1::buildMarketMap(){
	//will store key (baseball card) for map
	string name;
	//price of card
	int price;
	//stores total number of cards
	int totalCards=-1;
	//variable for the getline
	string line;
	getline(iFile,line);
	//setting up line retrieval
	stringstream ss(line);
	//pushes total number of cards to totalcards
	ss >> totalCards;
	for(int i=0; i<totalCards; i++){
		getline(iFile, line);
		//ss pushes in each line to name/price key pair
		//name/price key pair established on last line of loop
		stringstream ss(line);
		ss >> name >> price;
		mPrices[name]=price;
	}
}
//builds map of card prices from grandma input jsut like above function
int Program1::buildPricesMap(){
	string name;
	if(!gPrices.empty()){
		gPrices.clear();
	}
	weight=0;
	//which problem is it?
	int problemSize=0;
	totalCost=0;
	//pair to the card prices
	int price=0;
	problemNumber++;
	string line;
	//retrieves info from Grandma text
	getline(iiFile, line);
	stringstream ss(line);
	//establishes string stream to pull it in
	ss >> problemSize >> weight;
	size=problemSize;
	//cout<<problemSize<<endl;
	//cout<<weight<<endl;
	for(int i=0; i<problemSize; i++){
		getline(iiFile, line);
		stringstream ss(line);
		ss >> name >> price;
		totalCost+=price;
		//creates iteration for map to compare and see if Grandma cards are in market cards and quit the program if the  card in grandma's stack is not in market prices
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
/*builds a map that contains the profit for each card*/
void Program1::buildProfitMap(){
	//clears the map early on because if you multiple problems the profit map will keep the cards from previous problems.  If this isn't done then cards from previous problems will be used in the subset calculation
	profitPrices.clear();
	map<string, int>::const_iterator
		map_it = gPrices.begin();
	//establishes map market-prices - grandmaprices
	//iterates
	while(map_it != gPrices.end()){
		profitPrices[map_it->first]=mPrices[map_it->first]-gPrices[map_it->first];	
		//cout<<map_it->first<<endl;
		//cout<<profitPrices[map_it->first]<<endl;
		++map_it;
	}
}
/*The subset template generator is an emulation of binary addition.  
 *The idea behind generator is that when you go from 0000 - 1111 by adding one to the 000 you actually generate all possible patterns.  These 0's and 1's are stored in vector form.
 *This is a visual example of what is supposed to happen
 * [0, 0,0]
 * [a, b, c]
 * in the above the null subset is chosen
 * we now add 1 to the "binary number"
 * [1, 0, 0]
 * [a, b, c]
 * in the above a is chosen.  add one again
 * [0, 1, 0]
 * [a, b, c]
 * in the above b is chosen
 * [1, 1, 0]
 * [a, b, c]
 * in the above a and b are chosen.
 * so on and so forth
 * [1, 1, 1]
 * [a, b, c]
 * in the above a, b, c is chosen
 * This is the algorithm, and below is the implemetation to create the vector representing the binary vector.  each time it is called one is added
 * It is the "template" for the real subset to be chosen
 * the size of the vector is the size of the problem.  if problem is size 20, then it is a vector of size 20 of all zeroes.
 *  that we add one to
 *  the binary number vector is called foo btw
 */
int Program1::generateSubsetTemplate(){
	//the compare vector is a vector of all zeroes.  if we add one to
	//a the binary subset containing all ones it becomes all zeroes again
	//and so for an indication to stop subset generation we implement a do-while lop
	//to stop generation when the 00000 vector ish binary number is reached
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
	//below is the implementation for adding 1 to the binary number vector
	//the binary number vector is called foo
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
//resets the foo array for the next problem 
void Program1::resetArray(){
	for(int i=0; i<size; i++){
		foo.push_back(0);
	}

}
//generates the subset based off the subset template generator. choses which cards are in the subset
void Program1::generateSubset(){
	//the vectors prices and names look at the map and retrieve the pair key values and stores them in seperate vectors
	vector<int> prices;
	vector<string> names;
	map<string, int>::const_iterator
		it = profitPrices.begin();
	while(it != profitPrices.end()){
	prices.push_back(it -> second);
	names.push_back(it -> first);
	++it;
	}	
	//clears them out for the next time this is called
	//uses the foo binary addition array and comparison
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
/*based off the program assignment description as provided by professor meng, this computes the subset with the biggest profit that works with the weight.
 * 
 *
 */
void Program1::computeMaxProfit(){
	//resets the maxProfit (for input files with multiple problems)
	maxProfit=0;
	int profit=0;
	//clears subset that stores the cards of subset with highest profit
	winningSubset.clear();
	//stores current subset in use
	vector<string> currentNames;
	//generates the number of times we have to loop.  aka the powerset of all possible
	//subsets based off given set.  we then subtract one since we are about to generate the profit if we chose all elements of set 
	int looping=pow (2.0, size)-1;
	//cout<<looping<<endl;
	//if cost is less than weight then compute profit, for the entire subset
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
	//uses subset gneration subsets to generate all possible sets and
	//test them to see if their total cost is below the weight 
	//adn then sees if htey have the biggest profit
	else{
		//while(generateSubsetTemplate()!=-2){
		for(int i=0; i<looping; i++){
		generateSubsetTemplate();
		generateSubset();
		profit=0;
		currentNames.clear();
		subsetCost=0;
		//stores subset size.  makes life easier that's why
		int xyz = namesSubset.size();
		for(int j=0; j<xyz; j++){
			profit+=profitPrices[namesSubset.at(j)];
			subsetCost+=gPrices[namesSubset.at(j)];
		        currentNames.push_back(namesSubset.at(j)); 	
			//cout<<"current profit is"<<profit<<endl;
			//cout<<"current subset cost is"<<subsetCost<<endl;
		}
		//if subset costs less than weight
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
//runs the program when called from driver.  computes time builds everything, and finally runs check to see if there are more problems
void Program1::run(){
	//computes time
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
	//pushes results to file
	oFile<<size<<" "<<maxProfit<<" "<<wSize<<" "<<hello<<'\n';
	int xyz = winningSubset.size();
	//push all player cards to outut
	for(int i=0; i<xyz; i++){
		oFile<<winningSubset.at(i)<<'\n';
	}
	check();
}
int Program1::check(){
	//c sees in the grandma file if they are any more problems using peek
	//if they aren't EOF is called and we close out put file
	int c = iiFile.peek();
	if(c == EOF){
		return -1;
		oFile.close();
	}
	//if there are more problems runs program for that set
	else{
		run();
	}
	return 0;
}
//it was a tester function to see if everything worked when i first built everything as it had been a year since i used c++
void Program1::helloworld(){
	//cout<<"hello"<<endl;
}
