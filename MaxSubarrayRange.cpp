/**
 * Find out the maximum sub-array of non negative numbers from an array.
 The sub-array should be continuous. That is, a sub-array created by choosing the second and fourth element and skipping the third element is invalid.

 Maximum sub-array is defined in terms of the sum of the elements in the sub-array. Sub-array A is greater than sub-array B if sum(A) > sum(B).

 Example:

 A : [1, 2, 5, -7, 2, 3]
 The two sub-arrays are [1, 2, 5] [2, 3].
 The answer is [1, 2, 5] as its sum is larger than [2, 3]
 NOTE: If there is a tie, then compare with segment's length and return segment which has maximum length
 NOTE 2: If there is still a tie, then return the segment with minimum starting index
 */
 
 /*
* Logic : since we have to find maximum contiguous sub-array of non-negative numbers, whenever we find a negaive number we reset
*           currMax (current maximum) to 0.
*           else we keep adding A[i] to currMax and check if we have exceeded or cam equal to max (global maximum sum).
*           If we have reached either of these two milestones, we increase the range counters.
*/

vector<int> maxset(vector<int> Vec) {
        int N = Vec.size();

        long long mx_sum = 0;
        long long cur_sum = 0;
        int mx_range_left = -1;
        int mx_range_right = -1;
        int cur_range_left = 0;
        int cur_range_right = 0;

        while(cur_range_right < N) {
            if(Vec[cur_range_right] < 0) {
                cur_range_left = cur_range_right + 1;
                cur_sum = 0;
            } else {
                cur_sum += (long long)Vec[cur_range_right];
                if(cur_sum > mx_sum) {
                    mx_sum = cur_sum;
                    mx_range_left = cur_range_left;
                    mx_range_right = cur_range_right + 1;
                } else if(cur_sum == mx_sum) {
                    if(cur_range_right + 1 - cur_range_left > mx_range_right - mx_range_left) {
                        mx_range_left = cur_range_left;
                        mx_range_right = cur_range_right + 1;
                    }
                }
            }
            cur_range_right++;
        }
        vector<int> ans;
        if(mx_range_left == -1 || mx_range_right == -1)
                return ans;

        for(int i = mx_range_left; i < mx_range_right; ++i)
                ans.push_back(Vec[i]);
        return ans;
    }
