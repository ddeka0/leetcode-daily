// my solution link
// https://leetcode.com/problems/maximum-profit-in-job-scheduling/solutions/2851027/binary-search/
class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        vector<int> dp(startTime.size() + 10,0);

        vector<vector<int>> schdule;
        for(int ii = 0;ii < startTime.size();ii++) {
            vector<int> entry;
            entry.push_back(startTime[ii]);
            entry.push_back(endTime[ii]);
            entry.push_back(profit[ii]);
            schdule.push_back(move(entry));
        }

        // by default sorts by 1st element
        sort(begin(schdule),end(schdule));
        

        // iterate from back
        // at ii from back, dp[ii] = answer from ii (including) to end.
        // if we exclude ii, then answer at ii is equal to answer at ii+1
        // if we include ii, then we need find jj where, jj's start time >= ii's end time.
        // and then answer at ii = max(answer with exclusion , profit of ii + dp[jj])
        for(int ii = schdule.size() - 1; ii >= 0;ii--) {
            int start_time = schdule[ii][0];
            int end_time = schdule[ii][1];
            int this_profit = schdule[ii][2];
            // exclude this
            dp[ii] = dp[ii+1];
            // include this
            int jj = FindNextSchedule(end_time,schdule);
            dp[ii] = max(dp[ii],this_profit + (jj>0?dp[jj]:0));
            cout <<"ans at " <<ii<<" - " << dp[ii] << endl;
        }
        return dp[0];
    }
    

    // Please check https://godbolt.org/z/3ecnzejno to understand the lower bound on a vector of vector
    int FindNextSchedule(int end_time,const vector<vector<int>>& schdule) {
        auto iter = lower_bound(begin(schdule),end(schdule),end_time,[](const vector<int>& v, int value) {
            return v[0] < value;
        });
        if(iter != end(schdule)) {
            return iter - begin(schdule);
        }
        return -1;
    }
};
