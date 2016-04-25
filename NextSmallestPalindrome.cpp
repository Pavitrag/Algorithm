/*
 * NextSmallestPalindrome.cpp
 *
 *  Created on	:	Apr 25, 2016
 *  Author		:	I309980
 */
// Source 1: http://www.algorithmist.com/index.php/SPOJ_PALIN
//source 2 : http://www.geeksforgeeks.org/given-a-number-find-next-smallest-palindrome-larger-than-this-number/


#include<vector>

using namespace std;
void printVector(vector<int>::iterator b, vector<int>::iterator e);
bool areAllNines(vector<int> number){
	for(vector<int>::iterator it = number.begin(); it != number.end(); it++){
		if(*it != 9)
			return false;
		return true;
	}
}
void generateNextLargerPalindrome(vector<int>& number, int pos1, int pos2) {
	if (pos1 < 0) {
		number.insert(number.begin(), 1);
		number[number.size() - 1] = 1;
		return;
	}
	if (number[pos1] < 9) {
		number[pos1] = number[pos2] = number[pos1] + 1;
		return;
	} else {
		number[pos1] = number[pos2] = 0;
		generateNextLargerPalindrome(number, --pos1, ++pos2);
		return;
	}
}

void copyFirstHalfToSecondHalf(vector<int>& number){
	for(int i = 0; i < number.size()-1-i; i++)
		number[number.size()-1-i] = number[i];
}

int comp(vector<int>& first, vector<int>& second){
	if(first.size() != second.size())
		return first.size() - second.size();
	else{
		for(int i = 0; i < first.size(); i++)
			if(first[i] != second[i])
				return first.size() - second.size();
	}
	return 0;
}

vector<int>& nextSmallestPalindrome(vector<int>& number) {
	vector<int> *orig = new vector<int>(number.begin(), number.end());
	printVector(orig->begin(), orig->end());
	bool all9s = areAllNines(number);
	if (all9s) {
		number.insert(number.begin(), 1);
		for (vector<int>::iterator it = number.begin(); it != number.end() - 1;
				it++)
			*it = 0;
		number[number.size() - 1] = 1;
	}
	copyFirstHalfToSecondHalf(number);
	printVector(number.begin(), number.end());
	int compare = comp(*orig, number);
	if(compare > 0) return number;

	int mid1 = -1, mid2 = -1;
	if (number.size() % 2 == 0) {
		mid1 = number.size() / 2;
		mid2 = mid1 - 1; // not valid in case of total odd elements.
	} else {
		mid1 = mid2 = number.size() / 2;
	}

	generateNextLargerPalindrome(number, mid2, mid1);
	printVector(number.begin(), number.end());
	return number;
}

