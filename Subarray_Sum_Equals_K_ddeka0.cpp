// https://leetcode.com/problems/subarray-sum-equals-k/
class Solution {
public:
    /* Idea:
    
       segment sum = larger prefix sum - smaller prefix sum
       with this logic
       
       Two pointer would have wroked fine if we only had +ve numbers
       but here -ve numbers are also there.
       
       So, we will use a map to store prefix sums for each i.
       
      
    */
    int subarraySum(vector<int>& nums, int k) {
        std::unordered_map<int,int> Map;
        Map[0] = 1; // 0 prefix sum is there always
        int s = 0;
        int ans = 0;
        for(int i = 0;i<nums.size();i++) {
            s += nums[i]; // update current prefix sum
            int req = s - k; // actually k = s - required prefix to search in Map
            if(Map.find(req) != Map.end()) {
                ans += Map[req];
            }
            Map[s]++;
        }
        return ans;
    }
};
