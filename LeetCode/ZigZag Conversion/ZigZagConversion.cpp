class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1)
            return s;
        
        string rows[numRows];
        int curRow = 0;
        bool row = false;
        
        for (int i = 0; i < s.length(); i++)
        {
            rows[curRow] += s[i];
            if (curRow == 0)
                row = true;
            else if (curRow == numRows - 1)
                row = false;
            if (row)
                curRow++;
            else
                curRow--;
        }
        string res = "";
        for (int i = 0; i < numRows; i++)
            res += rows[i];
        return res;
    }
};