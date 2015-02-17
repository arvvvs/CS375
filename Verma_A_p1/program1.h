#include<iostream>
#include<string>
#include<cctype>
#include<fstream>
#include<iostream>
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
	public: 
	Program1(string mfile, string pfile);
	~Program1();
	void helloworld();
	int buildPricesMap();
	void buildMarketMap();
	void computeMaxProfit();
	
};
