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
		int subsetCost=0;
		int size=0;
		vector<int> foo;
		vector<string> namesSubset;
		vector<int> profitSubset;
		int wSize=0;
		int maxProfit=0;
		vector<string> winningSubset;

	public: 
	Program1(string mfile, string pfile);
	~Program1();
	void helloworld();
	int buildPricesMap();
	void resetArray();
	void buildMarketMap();
	void computeMaxProfit();
	void buildProfitMap();
	void generateSubset();
	int generateSubsetTemplate();
	void run();
	int check();
	
};
