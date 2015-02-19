#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<cctype>
#include<fstream>
#include<map>
using namespace std;
class Program1 {
	private:
		ifstream iFile;
		ifstream iiFile;
		ofstream oFile;
		//which problem number is being used from grandma file
		int problemNumber=0;
		//prices grandma sells at
		map<string, int> gPrices;
		//total cost of all things in map of grandma prices
		int totalCost=0;
		//total amount of money allowed to spend
		int weight=0;	
		//prices of market
		map<string, int> mPrices;
		//profit per card (marketprices-grandmaprices)
		map<string, int> profitPrices;
		//how much each subset costs (compare it to weight)
		int subsetCost=0;
		//size of problem
		int size=0;
		//where the pattern for the subset generation is stored
		vector<int> foo;
		//Storing the names in a vector
		vector<string> namesSubset;
		//storing the profit for each name
		vector<int> profitSubset;
		//weight of problem
		int wSize=0;
		//the largest profit amongst all eligible subsets
		int maxProfit=0;
		//the subset that has the maxprofit
		vector<string> winningSubset;

	public: 
	//Establishes the class
	Program1(string mfile, string pfile);
	~Program1();
	//a test to see if program works, and make file did
	void helloworld();
	//(grandma prices)builds a map where the key is the card name and the pair is the price
	int buildPricesMap();
	//creates the variable foo where the subset generation template is stored (more on that later)
	void resetArray();
	//(market prices) key is card name and market prices is key
	void buildMarketMap();
	//computes which subset holds max profit
	void computeMaxProfit();
	//creates a map where the key is baseball card and the pair is the profit made form each card (market prices - grandma prices)
	void buildProfitMap();
	//Generates the subset from the subset tempate
	void generateSubset();
	//generates subset template
	int generateSubsetTemplate();
	//runs the program
	void run();
	//are there any more problems? checks for those
	int check();
	
};
