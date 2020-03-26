class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) 
    {
        vector<int> nums;
        for (int i = 0; i < nums1.size(); i++)
            nums.push_back(nums1[i]);
        for (int i = 0; i < nums2.size(); i++)
            nums.push_back(nums2[i]);
        
        priority_queue<int, vector<int>, less<int>> maximums;
        priority_queue<int, vector<int>, greater<int>> minimums;
        
        for (int i = 0; i < nums.size(); i++)
        {
            int elem = nums[i];
            
            if (maximums.size() == 0 && minimums.size() == 0)
            {
                maximums.push(elem);
                continue;
            }
            
            if (maximums.size() != minimums.size())
            {
                if (maximums.top() > elem)
                {
                    minimums.push(maximums.top());
                    maximums.pop();
                    maximums.push(elem);
                }
                else
                {
                    minimums.push(elem);
                }
            }
            else
            {
                if (minimums.top() < elem)
                {
                    maximums.push(minimums.top());
                    minimums.pop();
                    minimums.push(elem);
                }
                else
                {
                    maximums.push(elem);
                }
            }
        }
        if (maximums.size() == minimums.size())
            return ((double)maximums.top() + (double)minimums.top()) / 2;
        return (double)maximums.top();
    }
};