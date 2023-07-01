#include <iostream>
#include <vector>
#include <random>
#include <iterator>
#include <algorithm>
#include<execution>
#include<functional>

using namespace std;
static bool odd(int n){
	return n%2;
}

void imp(vector<int> X){
	for(unsigned x=0; x < X.size(); x++){
		cout<<X[x]<<",";
	}
}//void

int main(int argc, char *argv[]){
	vector<int> d (5000);
	mt19937 gen;
	uniform_int_distribution<int> dis(0,100000);
	auto rand_num([=] () mutable {return dis(gen);});
	generate(execution::par,begin(d),end(d),rand_num);
	auto odds (count_if(execution::par,begin(d),end(d),odd));
	cout<<(100.0*odds/d.size())<<"% de numeros impares es:" << endl;
	return 0;
}
