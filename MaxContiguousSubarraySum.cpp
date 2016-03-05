/*
 * MaxContiguousSubarraySum.cpp
 *
 *  Created on	:	Mar 4, 2016
 *  Author		  :	Pavi
 */
/**
 * Find the contiguous subarray within an array (containing at least one number) 
 * which has the largest sum.

 For example:

 Given the array [-2,1,-3,4,-1,2,1,-5,4],

 the contiguous subarray [4,-1,2,1] has the largest sum = 6.

 For this problem, return the maximum sum.
 */
#include <vector>
using namespace std;
class Solution {
public:
	static int maxSubArray(const vector<int> &A);
	static vector<int> maxset(vector<int> &A);
};

int Solution::maxSubArray(const vector<int> &A) {
	int max, currMax;
	if (A.size() > 0)
		max = currMax = A[0];
	for (int i = 1; i < A.size(); i++) {
		if (currMax + A[i] >= A[i])
			currMax += A[i];
		else
			currMax = A[i];
		if (currMax > max)
			max = currMax;

	}
	return max;
}
