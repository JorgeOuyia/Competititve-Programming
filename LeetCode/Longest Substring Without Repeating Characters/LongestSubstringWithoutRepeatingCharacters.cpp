class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> rep;
        int st = 0, e = 0, cont = 0, maximum = 0;
        while (e < s.length())
        {
            if (rep.find(s[e]) == rep.end())
            {
                rep.insert(s[e]);
                e++;
                cont++;
                maximum = max(maximum, e - st);
            }
            else
            {
                rep.erase(find(rep.begin(), rep.end(), s[st++]));
            }
        }
        return maximum;
    }
};