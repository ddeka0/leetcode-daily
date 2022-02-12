// https://leetcode.com/problems/permutation-in-string/
class Solution {
public:
    /* Idea:
        calculate frequency array from s1
        and then run a two pointer loop in s2 maintaining a current freq array
        these freq array are built on 26 small case letters
    */
    bool checkInclusion(string s1, string s2) {

        int n = s2.size();
        int m = s1.size();
        
        // Build S1 freq table
        vector<int> s1_freq(26,0);
        for(int i = 0;i<m;i++) {
            s1_freq[s1[i] - 'a']++;
        }
        
        vector<int> curr_freq(26,0);
        bool ans = false;

        // j is the leading pointer towards right
        // i will follow as per logic below
        
        // i starts with -1 means, nothing is covered till now
        for(int i = -1,j = i+1; (i < n) && (j < n) && !ans;) { 
           
            // if current letter in S2 does not even present in S1  
            if(0 == s1_freq[s2[j] - 'a']) { 
                
                // we got unwanted character, therefore move i pointer completely towards j
                // because we dont need subsequence kind of thing
                
                // remember the fact that we are dealing with (i,j].
                // thats why i < j - 1 condition is there
                
                while((i >= 0) && (i < j-1)) curr_freq[s2[++i] - 'a']--;
                
                // this s2[j] was bad
                // so move j by 1
                j++;
                // also fix i, this could have been done with i++ also I think
                i = j-1;
                continue;
            }
            
            // now increase the current freq table with current letter of s2
            curr_freq[s2[j] - 'a']++;
            
            // see if we have exceeded the S1 size limit.
            // remember we are not dealing with subsequence
            while(j - i > m) {
                curr_freq[s2[++i] - 'a']--;    
            }
            
            // then just check freq counts of each freq table
            bool ok = true;
            for(int ii = 0;ii<26;ii++) {
                ok &= (s1_freq[ii] <= curr_freq[ii]);
            }
            
            ans = ok;
            
            // keep moving j
            j++;
        }
        
        return ans;
    }
};
