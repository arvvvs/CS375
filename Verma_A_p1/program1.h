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
		int problemNumber=0;
		//prices grandma sells at
		map<string, int> gPrices;
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
