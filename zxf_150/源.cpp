#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> 
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <string>
#include <queue>
#include<functional>
#include <sstream>


using namespace std;


void test() {
    //function<void(int, int)> a = [](int b, int c) {};
    auto a = [](int b, int c) {};
    using t = decltype(a);
    
}


class Solution {
private:
    struct ListNode {
        int val;
        ListNode* next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode* next) : val(x), next(next) {}
    };
    struct Node {
        int val;
        Node* next;
        Node* random;
        Node(int _val) {
            val = _val;
            next = NULL;
            random = NULL;
        }
    };
    struct TreeNode {
        int val;
        TreeNode* left;
        TreeNode* right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
    };
public:
    // 88.合并两个有序数组
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int position1 = 0, position2 = 0;
        vector<int> result;
        while (position1 < m && position2 < n) {
            if (nums1[position1] <= nums2[position2]) {
                result.push_back(nums1[position1]);
                position1++;
            }
            else {
                result.push_back(nums2[position2]);
                position2++;
            }
        }
        cout << position1 << " " << position2 << endl;
        while (position1 < m) {
            result.push_back(nums1[position1]);
            position1++;
        }
        while (position2 < n) {
            result.push_back(nums2[position2]);
            position2++;
        }
        for (int i = 0; i < result.size(); ++i) cout << result[i] << " ";
    }
    // 27.移除元素
    int removeElement(vector<int>& nums, int val) {
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            if (nums[left] == val) {
                nums[left] = nums[right];
                right--;
            }
            else left++;
        }
        return left;
    }
    // 26.删除有序数组中的重复项Ⅰ
    int removeDuplicates1(vector<int>& nums) {
        int right = 1, left = 1;
        while (right < nums.size()) {
            if (nums[right] != nums[right - 1]) {
                nums[left] = nums[right];
                left++;
            }
            right++;
        }
        return left;
    }
    // 80.删除有序数组中的重复项Ⅱ
    int removeDuplicates2(vector<int>& nums) {
        int right = 2, left = 2;
        while (right < nums.size()) {
            if (nums[left - 2] != nums[right]) {
                nums[left] = nums[right];
                left++;
            }
            right++;
        }
        return left;
    }
    // 169.多数元素
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> count;
        int result = 0;
        for (int num : nums) {
            count[num]++;
        }
        for (auto [k, v] : count) {
            if (v > nums.size() / 2) result = k;
        }
        return result;
    }
    // 189.轮转数组（c++中的rotate函数可以实现轮转）
    void rotate(vector<int>& nums, int k) {
        k %= nums.size();
        std::rotate(nums.begin(), nums.end() - k, nums.end());
    }
    // 121.买卖股票的最佳时机Ⅰ
    int maxProfit1(vector<int>& prices) {
        int result = 0;
        int buyin = prices[0];
        for (int i = 0; i < prices.size(); ++i) {
            buyin = min(buyin, prices[i]);
            result = max(result, prices[i] - buyin);
        }
        return result;
    }
    // 122.买卖股票的最佳时机Ⅱ
    int maxProfit2(vector<int>& prices) {
        int result = 0;
        for (int i = 1; i < prices.size(); ++i) {
            result += max(0, prices[i] - prices[i - 1]);
        }
        return result;
    }
    // 55.跳跃游戏Ⅰ
    bool jump1(vector<int>& nums) {
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i - 1] > 0) nums[i] = max(nums[i - 1] - 1, nums[i]);
            else return false;
        }
        return true;
    }
    // 45.跳跃游戏Ⅱ
    int jump2(vector<int>& nums) {
        int maxposition = 0;
        int cur = 0;
        int result = 0;
        for (int i = 0; i < nums.size(); ++i) {
            maxposition = max(maxposition, nums[i] + i);
            if (cur == maxposition) {
                result++;
                cur = maxposition;
                if (maxposition >= nums.size() - 1) break;
            }
        }
        return result;
    }
    // 274.H指数
    int hIndex(vector<int>& citations) {
        int count = citations.size();
        int result = 0;
        sort(citations.begin(), citations.end());
        for (int citation : citations) {
            if (citation < count) count--;
            else if (citation >= count) {
                result = count;
                break;
            }
        }
        return result;
    }
    // 238. 除自身以外数组的乘积
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> result(nums.size());
        for (int i = 0; i < nums.size(); ++i) {
            if (i == 0) result[i] = 1;
            else result[i] = result[i - 1] * nums[i - 1];
        }
        int right = 1;
        for (int i = nums.size() - 1; i >= 0; --i) {
            result[i] = result[i] * right;
            right = right * nums[i];
        }
        return result;
    }
    // 134.加油站
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int minmark = 0;
        int result = 0;
        int mark = 0;
        bool flag = false;
        for (int i = 0; i < gas.size(); ++i) {
            mark = gas[i] -= cost[i];
            if (mark < minmark) {
                minmark = mark;
                result = i;
                flag = true;
            }
        }
        if (mark < 0) return -1;
        if (flag) return result + 1;
        else return 0;
    }
    // 135.分发糖果
    int candy(vector<int>& ratings) {
        vector<int> result(ratings.size(), 1);
        for (int i = 1; i < ratings.size(); ++i) {
            if (ratings[i] > ratings[i - 1]) result[i] = result[i - 1] + 1;
        }
        for (int i = ratings.size() - 2; i >= 0; --i) {
            if (ratings[i] > ratings[i + 1] && result[i] <= result[i + 1]) result[i] = result[i + 1] + 1;
        }
        return accumulate(result.begin(), result.end(), 0);
    }
    // 42.接雨水
    int trap(vector<int>& height) {
        int result = 0;
        stack<int> st;
        for (int i = 0; i < height.size(); ++i) {
            while (!st.empty() && height[i] > height[st.top()]) {
                int mid = st.top();
                st.pop();
                if (!st.empty()) result += (min(height[i], height[st.top()]) - height[mid]) * (i - st.top() - 1);
            }
            st.push(i);
        }
        return result;
    }
    // 13.罗马数字转整数
    int romanToInt(string s) {
        int result = 0;
        unordered_map<char, int> mp = { {'I', 1},{'V', 5},{'X', 10},{'L', 50},{'C', 100}, {'D', 500},{'M', 1000} };
        for (int i = 0; i < s.size(); ++i) {
            int value = mp[s[i]];
            if (i < s.size() - 1 && value < mp[s[i + 1]]) result -= value;
            else result += value;
        }
        return result;
    }
    // 12.整数转罗马数字
    string intToRoman(int num) {
        vector<pair<int, string>> mp = { {1000, "M" }, { 900, "CM" }, { 500, "D" }, { 400, "CD" }, { 100, "C" },
        { 90, "XC" }, { 50, "L" }, { 40, "XL" }, { 10, "X" }, { 9, "IX" }, { 5, "V" }, { 4, "IV" }, { 1, "I" } };
        string result = "";
        for (auto& [k, v] : mp) {
            while (num >= k) {
                num -= k;
                result += v;
            }
            if (num == 0) break;
        }
        return result;
    }
    // 58.最后一个单词长度
    int lengthOfLastWord(string s) {
        int result = 0;
        int index = s.size() - 1;
        while (s[index] == ' ') index--;
        for (; index >= 0; --index) {
            if (s[index] == ' ') break;
            else result++;
        }
        return result;
    }
    // 14.最长公共前缀
    string longestCommonPrefix(vector<string>& strs) {
        string result = "";
        for (int i = 0; i < strs[0].size(); ++i) {
            bool flag = true;
            for (string str : strs) {
                if (str[i] != strs[0][i]) flag = false;
            }
            if (flag) result += strs[0][i];
            else break;
        }
        return result;
    }
    // 151. 反转字符串中的单词
    string reverseWords(string s) {
        vector<string> words;
        string result = "";
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == ' ') continue;
            string tmp = "";
            while (i < s.size() && s[i] != ' ') {
                tmp.push_back(s[i]);
                i++;
            }
            words.push_back(tmp);
        }
        for (int i = words.size() - 1; i >= 0; --i) {
            if (i == 0) result += words[i];
            else result += words[i] + " ";
        }
        return result;
    }
    // 6.Z字形变换(未做)
    string convert(string s, int numRows) {
        if (s.size() < numRows || numRows == 1) return s;
        vector<string> t(numRows, "");
        bool flag = false;
        for (int i = 0, position = 0; i < s.size(); ++i) {
            if (!flag) {
                t[position].push_back(s[i]);
                position++;
                if (position == numRows) {
                    flag = true;
                    position -= 2;
                }
            }
            else {
                t[position].push_back(s[i]);
                position--;
                if (position == -1) {
                    flag = false;
                    position += 2;
                }
            }
        }
        string result = "";
        for (string mark : t) result += mark;
        return result;
    }
    // 28.找出字符串第一个匹配项的下标(KMP算法)
    int strStr(string haystack, string needle) {
        vector<int> next(needle.size(), 0);
        // 获取next数组
        for (int i = 1, j = 0; i < needle.size(); ++i) {
            while (j > 0 && needle[i] != needle[j]) j = next[j - 1];
            if (needle[i] == needle[j]) j++;
            next[i] = j;
        }
        for (int i = 0, j = 0; i < haystack.size(); ++i) {
            while (j > 0 && haystack[i] != needle[j]) j = next[j - 1];
            if (haystack[i] == needle[j]) j++;
            if (j == needle.size()) return i - needle.size() + 1;
        }
        return -1;
    }
    // 68.文本左右对齐
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
        int length = 0;
        vector<string> newWords;
        for (int i = 0; i < words.size(); ++i) {
            if (length + words[i].size() <= maxWidth) {
                newWords.push_back(words[i]);
                length += words[i].size() + 1;
            }
            else {
                addWords(length, maxWidth, newWords, result, false);
                length = 0;
                newWords.clear();
                i--;
            }
        }
        addWords(length, maxWidth, newWords, result, true);
        return result;
    }
    void addWords(int length, int maxWidth, vector<string>& newWords, vector<string>& result, bool flag) {
        string mark = "";
        int space = maxWidth - length + 1;
        if (newWords.size() == 1) {
            mark += newWords[0];
            for (int j = 0; j < space; ++j) mark += " ";
            result.push_back(mark);
        }
        else if (flag) {
            for (int j = 0; j < newWords.size(); ++j) {
                mark += newWords[j];
                if (j != newWords.size() - 1) mark += " ";
            }
            for (int j = 0; j < space; ++j) mark += " ";
            result.push_back(mark);
            cout << mark.size() << endl;
        }
        else {
            int base = space / (newWords.size() - 1) + 1;
            int add = space % (newWords.size() - 1);
            for (int j = 0; j < newWords.size(); ++j) {
                if (j < add) {
                    mark += newWords[j];
                    for (int k = 0; k < base + 1; ++k) mark += " ";
                }
                else if (j < newWords.size() - 1) {
                    mark += newWords[j];
                    for (int k = 0; k < base; ++k) mark += " ";
                }
                else mark += newWords[j];
            }
            result.push_back(mark);
        }
    }
    // 125.验证回文串
    bool isPalindrome(string s) {
        string newS = "";
        for (char ch : s) {
            if (ch <= 'Z' && ch >= 'A') newS.push_back(ch - 'A' + 'a');
            else if (ch <= 'z' && ch >= 'a') newS.push_back(ch);
            else if (ch <= '9' && ch >= '0') newS.push_back(ch);
            else continue;
        }
        int left = 0;
        int right = newS.size() - 1;
        while (left < right) {
            if (newS[left] != newS[right]) return false;
            left++;
            right--;
        }
        return true;
    }
    // 392.判断子序列
    bool isSubsequence(string s, string t) {
        int i = 0, j = 0;
        while (i < s.size() && j < t.size()) {
            if (s[i] == t[j]) i++;
            j++;
        }
        return i == s.size();
    }
    // 167.两数之和Ⅱ-输入有序数组
    vector<int> twoSum1(vector<int>& numbers, int target) {
        int left = 0, right = numbers.size() - 1;
        while (left < right) {
            if (numbers[left] + numbers[right] > target) right--;
            else if (numbers[left] + numbers[right] < target) left++;
            else break;
        }
        vector<int> result = { left + 1, right + 1 };
        return result;
    }
    // 11.盛最多水的容器
    int maxArea(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int result = 0;
        while (left < right) {
            result = max(result, min(height[left], height[right]) * (right - left));
            if (height[left] < height[right]) left++;
            else right--;
        }
        return result;
    }
    // 15.三数之和
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        for (int i = 0; i <= nums.size() - 3; ++i) {
            if (nums[i] > 0) break;
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            vector<int> mark(3);
            mark[0] = nums[i];
            int target = -nums[i];
            int left = i + 1, right = nums.size() - 1;
            while (left < right) {
                if (nums[left] + nums[right] > target) {
                    right--;
                    while (left < right && nums[right] == nums[right + 1]) right--;
                }
                else if (nums[left] + nums[right] < target) {
                    left++;
                    while (left < right && nums[left] == nums[left - 1]) left++;
                }
                else {
                    mark[1] = nums[left], mark[2] = nums[right];
                    result.push_back(mark);
                    left++;
                    right--;
                    while (left < right && nums[left] == nums[left - 1]) left++;
                    while (left < right && nums[right] == nums[right + 1]) right--;
                }
            }
        }
        return result;
    }
    // 209.长度最小的子数组
    int minSubArrayLen(int target, vector<int>& nums) {  
        
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (target > sum) return 0;
        int left = 0, right = 0;
        int current = 0;
        int result = INT_MAX;
        while (right < nums.size()) {
            if (current + nums[right] >= target) {
                result = min(result, right - left);
                current -= nums[left];
                left++;
            }
            else if (current + nums[right] < target) {
                current += nums[right];
                right++;
            }
        }
        return result;
    }
    // 3.无重复字符的最长字串
    int lengthOfLongestSubstring(string s) {
        if (s.size() <= 1) return s.size();
        unordered_set<int> used;
        int left = 0, right = 0;
        int result = 0;
        while (right < s.size()) {
            if (used.empty() || used.find(s[right]) == used.end()) {
                used.insert(s[right]);
                right++;
            }
            else {
                result = max(result, right - left);
                used.erase(s[left]);
                left++;
            }
        }
        return max(result, right - left);
    }
    // 30.串联所有单词的字串
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> result;
        int wordsLength = words.size(), wordLength = words[0].size(), sLength = s.size();
        for (int i = 0; i < wordLength && i + wordsLength * wordLength <= sLength; ++i) {
            unordered_map<string, int> map;
            for (int j = 0; j < wordsLength; ++j) {
                map[s.substr(i + j * wordLength, wordLength)]++;
            }
            for (string& word : words) {
                if (--map[word] == 0) {
                    map.erase(word);
                }
            }
            for (int left = i; left < sLength - wordsLength * wordLength + 1; left += wordLength) {
                if (left != i) {
                    string word = s.substr(left + (wordsLength - 1) * wordLength, wordLength);
                    if (++map[word] == 0) {
                        map.erase(word);
                    }
                    word = s.substr(left - wordLength, wordLength);
                    if (--map[word] == 0) {
                        map.erase(word);
                    }
                }
                if (map.empty()) result.push_back(left);
            }
        }
        return result;
    }
    // 76.最小覆盖字串
    string minWindow(string s, string t) {
        string result = "";
        if (s.size() < t.size()) return result;
        unordered_map<char, int> used, map;
        for (char& ch : t) map[ch]++;
        for (int left = 0, right = 0, cnt = 0; left < s.length(); ++left) {
            if (++used[s[right]] <= map[s[right]]) cnt++;
            while (used[s[left]] > map[s[left]]) {
                used[s[left]]--;
                left++;
            }
            if (cnt == t.size()) {
                if (result.empty() || result.size() > right - left + 1) {
                    result = s.substr(left, right - left + 1);
                }
            }
        }
        return result;
    }
    // 36.有效的数独
    bool isValidSudoku(vector<vector<char>>& board) {
        unordered_set<char> used;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] <= '9' && board[i][j] >= '0') {
                    if (used.count(board[i][j]) > 0) return false;
                    else used.insert(board[i][j]);
                }
                else continue;
            }
            used.clear();
        }
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[j][i] <= '9' && board[j][i] >= '0') {
                    if (used.count(board[j][i]) > 0) return false;
                    else used.insert(board[j][i]);
                }
                else continue;
            }
            used.clear();
        }
        int row = 0, column = 0;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                row = (i / 3) * 3 + j / 3;
                column = (i % 3) * 3 + j % 3;
                if (board[row][column] <= '9' && board[row][column] >= '0') {
                    if (used.count(board[row][column]) > 0) return false;
                    else used.insert(board[row][column]);
                }
                else continue;
            }
            used.clear();
        }
        return true;
    }
    // 73.矩阵置零
    void setZeroes(vector<vector<int>>& matrix) {
        vector<vector<bool>> used(matrix.size(), vector<bool>(matrix[0].size(), false));
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[0].size(); ++j) {
                if (matrix[i][j] == 0 && used[i][j] == false) {
                    for (int row = 0; row < matrix.size(); ++row) {
                        if(matrix[row][j] != 0) used[row][j] = true;
                        matrix[row][j] = 0;                        
                    }
                    for (int column = 0; column < matrix[0].size(); ++column) {
                        if (matrix[i][column] != 0) used[i][column] = true;
                        matrix[i][column] = 0;
                    }
                }
            }
        }
    }
    // 1.两数之和
    vector<int> twoSum2(vector<int>& nums, int target) {
        vector<int> result;
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); ++i) {
            auto item = map.find(target - nums[i]);
            if (item != map.end()) {
                result = { item->second, i };
                break;
            }
            map[nums[i]] = i;
        }
        return result;
    }
    // 202.快乐数
    bool isHappy(int n) {
        unordered_set<int> used;
        while (!used.count(n)) {
            if (n == 1) return true;
            used.insert(n);
            int mark = 0;
            while (n > 0) {
                mark += pow(n % 10, 2);
                n /= 10;
            }
            n = mark;
        }
        return false;
    }
    // 219.存在重复元素Ⅱ
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); ++i) {
            if (!map.count(nums[i])) map[nums[i]] = i;
            else {
                if (i - map[nums[i]] <= k) return true;
                else map[nums[i]] = i;
            }
        }
        return false;
    }
    // 128.最长连续序列
    int longestConsecutive(vector<int>& nums) {
        if (nums.size() < 2) return nums.size();
        unordered_set<int> used;
        for (int i = 0; i < nums.size(); ++i) {
            if (!used.count(nums[i])) used.insert(nums[i]);
            else {
                nums.erase(nums.begin() + i);
                i--;
            }
        }
        if (nums.size() < 2) return nums.size();
        sort(nums.begin(), nums.end());
        int result = 0;
        for (int i = 1; i < nums.size(); ++i) {
            int position = i;
            while (i < nums.size() && nums[i] - nums[i - 1] == 1) {
                i++;
            }
            result = max(result, i - position + 1);
        }
        return result;
    }
    // 228.汇总区间
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> result;
        int left = 0, right = 0;
        while (right < nums.size()) {
            right++;
            while (right < nums.size() && nums[right] == nums[right - 1] + 1) right++;
            if (left == right - 1) result.push_back(to_string(nums[left]));
            else result.push_back(to_string(nums[left]) + "->" + to_string(nums[right - 1]));
            left = right;
        }
        return result;
    }
    // 56.合并区间
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> result;
        int left = intervals[0][0];
        int right = intervals[0][1];
        for (auto mark : intervals) {
            if (!result.empty() && result.back()[1] >= mark[0]) result.back()[1] = max(result.back()[1], mark[1]);
            else result.push_back(mark);
        }
        return result;
    }
    // 57.插入区间
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        intervals.push_back(newInterval);
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> result;
        int left = intervals[0][0];
        int right = intervals[0][1];
        for (auto& mark : intervals) {
            if (!result.empty() && result.back()[1] >= mark[0]) result.back()[1] = max(result.back()[1], mark[1]);
            else result.push_back(mark);
        }
        return result;
    }
    // 452.用最少数量的箭引爆气球
    int findMinArrowShots(vector<vector<int>>& points) {
        sort(points.begin(), points.end(), [](vector<int>& a, vector<int>& b) { return a[0] < b[0]; });
        int result = 1;
        for (int i = 1; i < points.size(); ++i) {
            if (points[i][0] > points[i - 1][1]) result++;
            else points[i][1] = min(points[i - 1][1], points[i][1]);
        }
        return result;
    }
    // 20.有效的括号
    bool isValid(string s) {
        stack<char> st;
        for (char ch : s) {
            if (st.empty() || ch == '(' || ch == '[' || ch == '{') {
                st.push(ch);
            }
            else if (st.empty()) return false;
            else if (ch == ')' && st.top() == '(') st.pop();
            else if (ch == ']' && st.top() == '[') st.pop();
            else if (ch == '}' && st.top() == '{') st.pop();
            else return false;
        }
        if (!st.empty()) return false;
        return true;
    }
    // 150.逆波兰表达式求值
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        int result = 0;
        for (string& str : tokens) {
            if (str == "+" || str == "-" || str == "*" || str == "/") {
                int num1 = st.top();
                st.pop();
                int num2 = st.top();
                st.pop();
                if (str == "+") num2 += num1;
                if (str == "-") num2 -= num1;
                if (str == "*") num2 *= num1;
                if (str == "/") num2 /= num1;
                st.push(num2);
            }
            else st.push(stoi(str));
        }
        return st.top();
    }
    // 141.环形链表
    bool hasCycle(ListNode* head) {
        ListNode* cur = head;
        unordered_set<ListNode*> used;
        while (cur) {
            if (!used.count(cur)) used.insert(cur);
            else return true;
            cur = cur->next;
        }
        return false;
    }
    // 2.两数相加
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* head = nullptr, * tail = nullptr;
        int flag = 0;
        while (l1 || l2) {
            int n1 = l1 ? l1->val : 0;
            int n2 = l2 ? l2->val : 0;
            int sum = n1 + n2 + flag;
            flag = sum / 10;
            if (!head) head = tail = new ListNode(sum % 10);
            else {
                tail->next = new ListNode(sum % 10);
                tail = tail->next;
            }
            if (l1) l1 = l1->next;
            if (l2) l2 = l2->next;
        }
        if (flag) {
            tail->next = new ListNode(1);
        }
        return head;
    }
    // 21.合并两个有序链表
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* head = new ListNode(-1);
        ListNode* cur = head;
        while (list1 && list2) {
            if (list1->val < list2->val) {
                cur->next = list2;
                list2 = list2->next;
            }
            else {
                cur->next = list1;
                list1 = list1->next;
            }
            cur = cur->next;
        }
        cur->next = list1 == nullptr ? list2 : list1;
        return head->next;
    }
    // 138.随机链表的复制
    Node* copyRandomList(Node* head) {
        if (head == nullptr) return nullptr;
        Node* cur = head;
        unordered_map<Node*, Node*> map;
        while (cur) {
            map[cur] = new Node(cur->val);
            cur = cur->next;
        }
        cur = head;
        while (cur) {
            map[cur]->next = map[cur->next];
            map[cur]->random = map[cur->random];
            cur = cur->next;
        }
        return map[head];
    }
    // 92.反转链表
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (left == right) return head;
        ListNode* pre = new ListNode(-1);
        pre->next = head;
        ListNode* result = pre;
        for (int i = 0; i < left - 1; ++i) pre = pre->next;
        ListNode* cur = pre->next;
        ListNode* next;
        for (int i = 0; i < right - left; ++i) {
            next = cur->next;
            cur->next = next->next;
            next->next = pre->next;
            pre->next = next;
        }
        return result->next;
    }
    // 25.k个一组翻转链表
    ListNode* reverseKGroup(ListNode* head, int k) {
        int length = 0;
        ListNode* cur = head;
        while (cur) {
            length++;
            cur = cur->next;
        }
        if (length < k) return head;
        ListNode* dumpy = new ListNode(-1);
        dumpy->next = head;
        ListNode* pre = dumpy;
        cur = head;
        ListNode* next;
        for (int i = 0; i < length / k; ++i) {
            for (int j = 0; j < k - 1; ++j) {
                next = cur->next;
                cur->next = next->next;
                next->next = pre->next;
                pre->next = next;
            }
            pre = cur;
            cur = pre->next;
        }
        return dumpy;
    }
    // 19.删除链表的倒数第N个节点
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int left = 0;
        int right = n;
        ListNode* pre = new ListNode(0, head);
        ListNode* cur = head;
        ListNode* result = pre;
        for (int i = 0; i < n; ++i) cur = cur->next;
        while (cur) {
            cur = cur->next;
            pre = pre->next;
        }
        pre->next = pre->next->next;
        return result->next;
    }
    // 82.删除排序链表中的重复元素Ⅱ
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr) return head;
        ListNode* dumpy = new ListNode(0, head);
        ListNode* pre = dumpy;
        ListNode* cur = head;
        while (cur && cur->next) {
            if (cur->val == cur->next->val) {
                int mark = cur->val;
                while (cur && cur->val == mark) cur = cur->next;
                pre->next = cur;
            }
            else {
                pre = cur;
                cur = cur->next;
            }
        }
        return dumpy->next;
    }
    // 61.旋转链表
    ListNode* rotateRight(ListNode* head, int k) {
        if (k == 0 || head == nullptr || head->next == nullptr) return head;
        int length = 1;
        ListNode* cur = head;
        while (cur->next) {
            length++;
            cur = cur->next;
        }
        cur->next = head;
        length -= k % length;
        while (length) {
            cur = cur->next;
            length--;
        }
        ListNode* result = cur->next;
        cur->next = nullptr;
        return result;
    }
    // 86.分隔链表
    ListNode* partition(ListNode* head, int x) {
        ListNode* dumpyLeft = new ListNode(0), * dumpyRight = new ListNode(0);
        ListNode* left = dumpyLeft, * right = dumpyRight;
        ListNode* cur = head;
        while (cur) {
            if (cur->val < x) {
                left->next = new ListNode(cur->val);
                left = left->next;
            }
            else {
                right->next = new ListNode(cur->val);
                right = right->next;
            }
            cur = cur->next;
        }
        left->next = dumpyRight->next;
        return dumpyLeft->next;
    }
    // 226.翻转二叉树
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) return nullptr;
        TreeNode* tmp = root->left;
        root->left = invertTree(root->right);
        root->right = invertTree(tmp);
        return root;
    }
    // 105.从前序与中序遍历构造二叉树
    TreeNode* buildTree1(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> map;
        int length = preorder.size();
        for (int i = 0; i < length; i++) map[inorder[i]] = i;
        return myBuildTree1(preorder, inorder, 0, length - 1, 0, length - 1, map);
    }
    TreeNode* myBuildTree1(vector<int>& preorder, vector<int>& inorder, int preorderLeft, int preorderRight, int inorderLeft, int inorderRight, unordered_map<int, int>& map) {
        if (preorderLeft > preorderRight) return nullptr;
        int preorderRoot = preorderLeft; 
        int inorderRoot = map[preorder[preorderRoot]];
        TreeNode* root = new TreeNode(preorder[preorderRoot]);
        int sizeLeft = inorderRoot - inorderLeft;
        root->left = myBuildTree1(preorder, inorder, preorderLeft + 1, preorderLeft + sizeLeft, inorderLeft, inorderRoot - 1, map);
        root->right = myBuildTree1(preorder, inorder, preorderLeft + sizeLeft + 1, preorderRight, inorderRoot + 1, inorderRight, map);
        return root;
    }
    // 106.从中序和后序遍历构造二叉树
    TreeNode* buildTree2(vector<int>& inorder, vector<int>& postorder) {
        unordered_map<int, int> map;
        int length = inorder.size();
        for (int i = 0; i < inorder.size(); ++i) map[inorder[i]] = i;
        return myBuildTree2(inorder, postorder, 0, length - 1, 0, length - 1, map);
    }
    TreeNode* myBuildTree2(vector<int>& inorder, vector<int>& postorder, int inorderLeft, int inorderRight, int postorderLeft, int postorderRight, unordered_map<int, int>& map) {
        if (inorderLeft > inorderRight || postorderLeft > postorderRight) return nullptr;
        int inorderRoot = map[postorder[postorderRight]];
        TreeNode* root = new TreeNode(postorder[postorderRight]);
        root->left = myBuildTree2(inorder, postorder, inorderLeft, inorderRoot - 1, postorderLeft, postorderLeft + inorderRoot - inorderLeft - 1, map);
        root->right = myBuildTree2(inorder, postorder, inorderRoot + 1, inorderRight, postorderLeft + inorderRoot - inorderLeft, postorderRight - 1, map);
        return root;
    }
    // 114.二叉树展开为链表
    void flatten(TreeNode* root) {
        TreeNode* pre, * next;
        TreeNode* cur = root;
        while (cur) {
            if (cur->left) {
                pre = cur->left;
                next = cur->right;
                while (next->right) next = next->right;
                next->right = cur->right;
                cur->right = pre;
                cur->left = nullptr;
            }
            else cur = cur->right;
        }
    }
    // 112.路径总和
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) return false;
        if (root->left == nullptr && root->right == nullptr) return root->val == targetSum;
        targetSum -= root->val;
        return hasPathSum(root->left, targetSum) || hasPathSum(root->right, targetSum);
    }
    // 129.求根节点到叶子节点数字之和
    int sumNumbers(TreeNode* root) {
        return mySumNumbers(root, 0);
    }
    int mySumNumbers(TreeNode* root, int cur) {
        if (root == nullptr) return 0;
        cur = cur * 10 + root->val;
        if (root->left == nullptr && root->right == nullptr) {
            return cur;
        }
        else return mySumNumbers(root->left, cur) + mySumNumbers(root->right, cur);
    }
    // 124.二叉树中的最大路径和
    int maxPathSum(TreeNode* root) {
        int result = INT_MIN;
        myMaxPathSum(root, result);
        return result;
    }
    int myMaxPathSum(TreeNode* root, int& result) {
        if (root == nullptr) return 0;
        int maxLeft = max(myMaxPathSum(root->left, result), 0);
        int maxRight = max(myMaxPathSum(root->right, result), 0);
        int maxSum = root->val + maxLeft + maxRight;
        result = max(result, maxSum);
        return root->val + max(maxLeft, maxRight);
    }
    // 222.完全二叉树的节点个数
    int countNodes(TreeNode* root) {
        if (root == nullptr) return 0;
        int result = 0;
        queue<TreeNode*> node;
        node.push(root);
        while (!node.empty()) {
            int length = node.size();
            for (int i = 0; i < length; ++i) {
                result++;
                TreeNode* cur = node.front();
                node.pop();
                if (cur->left) node.push(cur->left);
                if (cur->right) node.push(cur->right);
            }
        }
        return result;
    }
    // 236.二叉树的最近公共祖先(再看一遍)
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* result = root;
        myLowestCommonAncestor(root, p, q, result);
        return result;
    }
    bool myLowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q, TreeNode* result) {
        if (root == nullptr) return false;
        bool isLeftSon = myLowestCommonAncestor(root->left, p, q, result);
        bool isRightSon = myLowestCommonAncestor(root->right, p, q, result);
        if ((isLeftSon && isRightSon) || (root->val == p->val || root->val == q->val) && (isLeftSon || isRightSon)) {
            result = root;
        }
        return isLeftSon || isRightSon || (root->val == p->val || root->val == q->val);
    }
    // 199.二叉树的右视图
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        if (root == nullptr) return result;
        queue<TreeNode*> node;
        node.push(root);
        while (!node.empty()) {
            int length = node.size();
            for (int i = 0; i < length; ++i) {
                TreeNode* cur = node.front();
                node.pop();
                if (i == length - 1) result.push_back(cur->val);
                if (cur->left) node.push(cur->left);
                if (cur->right) node.push(cur->right);
            }
        }
        return result;
    }
    // 637.二叉树的层平均值
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> result;
        if (root == nullptr) return result;
        queue<TreeNode*> node;
        node.push(root);
        while (!node.empty()) {
            int length = node.size();
            long long int sum = 0;
            for (int i = 0; i < length; ++i) {
                TreeNode* cur = node.front();
                node.pop();
                sum += cur->val;
                if (cur->left) node.push(cur->left);
                if (cur->right) node.push(cur->right);
            }
            result.push_back(sum / double(length));
        }
        return result;
    }
    // 102.二叉树的层序遍历
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (root == nullptr) return result;
        queue<TreeNode*> node;
        node.push(root);
        while (!node.empty()) {
            int length = node.size();
            vector<int> mark;
            for (int i = 0; i < length; ++i) {
                TreeNode* cur = node.front();
                node.pop();
                mark.push_back(cur->val);
                if (cur->left) node.push(cur->left);
                if (cur->right) node.push(cur->right);
            }
            result.push_back(mark);
        }
        return result;
    }
    // 103.二叉树的锯齿形遍历
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        bool flag = true;
        if (root == nullptr) return result;
        queue<TreeNode*> node;
        node.push(root);
        while (!node.empty()) {
            int length = node.size();
            vector<int> mark;
            for (int i = 0; i < length; ++i) {
                TreeNode* cur = node.front();
                node.pop();
                mark.push_back(cur->val);
                if (cur->left) node.push(cur->left);
                if (cur->right) node.push(cur->right);
            }
            if (flag) {
                flag = false;
                result.push_back(mark);
            }
            else {
                flag = true;
                reverse(mark.begin(), mark.end());
                result.push_back(mark);
            }
        }
        return result;
    }
    // 530.二叉搜索树的最小绝对差
    int getMinimumDifference(TreeNode* root) {
        int result = INT_MAX;
        int pre = -1;
        myGetMinimumDifference(root, pre, result);
        return result;
    }
    void myGetMinimumDifference(TreeNode* root, int& pre, int& result) {
        if (root == nullptr) return;
        myGetMinimumDifference(root->left, pre, result);
        if (pre == -1) pre = root->val;
        else {
            result = min(root->val - pre, result);
            pre = root->val;
        }        
        myGetMinimumDifference(root->right, pre, result);
    }
    // 230.二叉搜索树中的第K小的元素
    int kthSmallest(TreeNode* root, int k) {
        vector<int> nums;
        myKthSmallest(root, nums);
        return nums[k - 1];
    }
    void myKthSmallest(TreeNode* root, vector<int>& nums) {
        if (root == nullptr) return;
        myKthSmallest(root->left, nums);
        nums.push_back(root->val);
        myKthSmallest(root->right, nums);
    }
    // 98.验证二叉搜索树
    bool isValidBST(TreeNode* root) {
        vector<int> nums;
        myIsValidBST(root, nums);
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] <= nums[i - 1]) return false;
        }
        return true;
    }
    void myIsValidBST(TreeNode* root, vector<int>& nums) {
        if (root == nullptr) return;
        myIsValidBST(root->left, nums);
        nums.push_back(root->val);
        myIsValidBST(root->right, nums);
    }
    // 108.将有序数组转换为二叉搜索树
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;
        return mySortedArrayToBST(nums, left, right);
    }
    TreeNode* mySortedArrayToBST(vector<int>& nums, int left, int right) {
        if (left > right) return nullptr;
        int mid = (right - left) / 2 + left;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = mySortedArrayToBST(nums, left, mid - 1);
        root->right = mySortedArrayToBST(nums, mid + 1, right);
        return root;
    }
    // 23.合并K个升序链表
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto cmp = [](ListNode* a, ListNode* b) {
            return a->val > b->val;
        };
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);
        for (auto list : lists) {
            if (list) pq.push(list);
        }
        ListNode* head = new ListNode(0);
        ListNode* tail = head;
        while (!pq.empty()) {
            ListNode* cur = pq.top();
            pq.pop();
            tail->next = cur;
            tail = tail->next;
            if (cur->next) pq.push(cur->next);
        }
        return head->next;
    }
    // 53.最大子数组和
    int maxSubArray(vector<int>& nums) {
        vector<int> dp(nums.size(), 0);
        for (int i = 0; i < nums.size(); i++) {
            if (i == 0) dp[i] = nums[i];
            else dp[i] = max(dp[i - 1] + nums[i], nums[i]);
        }
        int result = dp[0];
        for (int i = 1; i < dp.size(); i++) {
            result = max(result, dp[i]);
        }
        return result;
    }
    // 918.环形子数组的最大和
    int maxSubarraySumCircular(vector<int>& nums) {
        int maxS = INT_MIN;
        int minS = 0;
        int maxF = 0, minF = 0, sum = 0;
        for (int num : nums) {
            maxF = max(maxF, 0) + num;
            maxS = max(maxS, maxF);
            minF = min(minF, 0) + num;
            minS = min(minS, minF);
            sum += num;
        }
        return sum == minS ? maxS : max(maxS, sum - minS);
    }
    // 35.二分查找
    int searchInsert(vector<int>& nums, int target) {
        int left = 0, right = nums.size();
        while (left < right) {
            int mid = (right - left) / 2 + left;
            if (nums[mid] == target) return mid;
            else if (nums[mid] < target) left = mid + 1;
            else right = mid;
        }
        return left;
    }
    // 74.搜索二维矩阵
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int left = 0, right = matrix.size();
        while (left < right) {
            int mid = (right - left) / 2 + left;
            if (target == matrix[mid][0]) return true;
            else if (target > matrix[mid][0]) left = mid + 1;
            else right = mid;
        }
        int row = left - 1;
        if (left == 0) row++;
        left = 0;
        right = matrix[0].size();
        while (left < right) {
            int mid = (right - left) / 2 + left;
            if (target == matrix[row][mid]) return true;
            else if (target > matrix[row][mid]) left = mid + 1;
            else right = mid;
        }
        return false;
    }
    // 33.搜索旋转排序数组
    int search(vector<int>& nums, int target) {
        if (nums.size() == 0) return -1;
        else if (nums.size() == 1) return nums[0] == target ? 0 : -1;
        int left = 0, right = nums.size();
        while (left < right) {
            int mid = (right - left) / 2 + left;            
            if (nums[0] <= nums[mid]) {
                if (target <= nums[mid] && target >= nums[0]) {
                    if (nums[mid] == target) return mid;
                    else right = mid;
                }
                else left = mid + 1;
            }
            else {
                if (target >= nums[mid] && target <= nums.back()) {
                    if (nums[mid] == target) return mid;
                    else left = mid + 1;
                }
                else right = mid;
            }
        }
        return -1;
    }
    // 34.在排序数组中查找元素的第一个和最后一个位置
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = 0, right = nums.size();
        while (left < right) {
            int mid = (right - left) / 2 + left;
            if (nums[mid] == target) {
                int start = mid, end = mid;
                while (start >= 0 && nums[start] == target) start--;
                while (end < nums.size() && nums[end] == target) end++;
                return { start + 1, end - 1 };
            }
            else if (nums[mid] < target) left = mid + 1;
            else right = mid;
        }
        return { -1,-1 };
    }
    // 153.寻找旋转排序数组中的最小值
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size();
        while (left < right) {
            int mid = (right - left) / 2 + left;
            if (nums[mid] < nums[right]) right = mid;
            else left = mid + 1;
        }
        return nums[left];
    }
    // 66.加一
    vector<int> plusOne(vector<int>& digits) {
        for (int i = digits.size() - 1; i >= 0; --i) {
            if (digits[i] != 9) {
                digits[i]++;
                for (int j = i + 1; j < digits.size(); ++j) digits[i] = 0;
                return digits;
            }
        }
        vector<int> result(digits.size() + 1, 0);
        result[0] = 1;
        return result;
    }
    // 172.阶乘后的零
    int trailingZeroes(int n) {
        int result = 0;
        while (n) {
            n /= 5;
            result += n;
        }
        return result;
    }
    // 69.x的平方根
    int mySqrt(int x) {
        if (x < 2) return x;
        int left = 0, right = x / 2;
        int result = 0;
        while (left <= right) {
            int mid = (right - left) / 2 + left;
            if ((long long)mid * mid <= x) {
                result = mid;
                left = mid + 1;
            }
            else right = mid - 1;
        }
        return result;
    }
    // 50.Pow(x, n)
    double myPow(double x, int n) {
        int N = abs(n);
        double result = 1.0;
        double tmp = x;
        while (N > 0) {
            if (N % 2 == 1) {
                result *= tmp;
            }
            tmp *= tmp;
            N /= 2;
        }
        if (n < 0) return 1 / result;
        return result;
    }
    // 149.直线上最多的点数
    int maxPoints(vector<vector<int>>& points) {
        int length = points.size();
        if (length < 2) return points.size();
        int result = 1;
        for (int i = 0; i < length; ++i) {
            vector<int> x = points[i];
            for (int j = i + 1; j < length; ++j) {
                vector<int> y = points[j];
                int cnt = 2;
                for (int k = j + 1; k < length; ++k) {
                    vector<int> p = points[k];
                    int s1 = (y[1] - x[1]) * (p[0] - y[0]);
                    int s2 = (p[1] - y[1]) * (y[0] - x[0]);
                    if (s1 == s2) cnt++;
                }
                result = max(result, cnt);
            }
        }
        return result;
    }
    // 70.爬楼梯
    int climbStairs(int n) {
        int cur1 = 0;
        int cur2 = 1;
        int result = 0;
        for (int i = 1; i <= n; ++i) {
            result = cur1 + cur2;
            cur1 = cur2;
            cur2 = result;
        }
        return result;
    }
    // 198.打家劫舍
    int rob(vector<int> nums) {
        if (nums.size() == 1) return nums[0];
        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < nums.size(); ++i) {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        return dp.back();
    }
    // 139.单词拆分
    bool wordBreak(string s, vector<string>& wordDict) {
        vector<char> dp(s.size() + 1, false);
        unordered_set<string> words;
        dp[0] = true;
        for (string& mark : wordDict) words.insert(mark);
        for (int i = 1; i <= s.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (dp[j] && words.count(s.substr(j, i - j)) > 0) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[s.size()];
    }
    // 322.零钱兑换
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= amount; ++i) {
            for (int j = 0; j < coins.size(); ++j) {
                if (i - coins[j] >= 0 && dp[i - coins[j]] != INT_MAX) {
                    dp[i] = min(dp[i - coins[j]] + 1, dp[i]);
                }
            }
        }
        if (dp[amount] == INT_MAX) return -1;
        return dp[amount];
    }
};

class Graph {
private:
    struct Node {
        int val;
        vector<Node*> neighbors;
        Node() {
            val = 0;
            neighbors = vector<Node*>();
        }
        Node(int _val) {
            val = _val;
            neighbors = vector<Node*>();
        }
        Node(int _val, vector<Node*> _neighbors) {
            val = _val;
            neighbors = _neighbors;
        }
    };
public:
    // 200.岛屿数量
    int numIslands(vector<vector<char>>& grid) {
        int result = 0;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j] == '1') {
                    result++;
                    myNumIslands(grid, i, j);
                }
            }
        }
        return result;
    }
    void myNumIslands(vector<vector<char> >& grid, int row, int column) {
        if (row < 0 || column < 0 || row > grid.size() - 1 || column > grid[0].size() - 1) return;
        if (grid[row][column] == '0') return;
        grid[row][column] = '0';
        myNumIslands(grid, row - 1, column);
        myNumIslands(grid, row + 1, column);
        myNumIslands(grid, row, column - 1);
        myNumIslands(grid, row, column + 1);
    }
    // 130.被围绕的区域
    void solve(vector<vector<char>>& board) {
        for (int i = 0; i < board.size(); ++i) {
            if (board[i][0] == 'O') mySolve(board, i, 0);
            if (board[i][board[i].size() - 1] == 'O') mySolve(board, i, board[i].size() - 1);
        }
        for (int i = 0; i < board[0].size(); ++i) {
            if (board[0][i] == 'O') mySolve(board, 0, i);
            if (board[board.size() - 1][i] == 'O') mySolve(board, board.size() - 1, i);
        }
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                if (board[i][j] == 'A') board[i][j] = 'O';
                else if (board[i][j] == 'O') board[i][j] = 'X';
            }
        }
    }
    void mySolve(vector<vector<char>>& board, int row, int column) {
        if (row < 0 || column < 0 || row > board.size() - 1 || column > board[0].size() - 1) return;
        if (board[row][column] == 'O') {
            board[row][column] = 'A';
            mySolve(board, row - 1, column);
            mySolve(board, row + 1, column);
            mySolve(board, row, column - 1);
            mySolve(board, row, column + 1);
        }
    }
    // 133.克隆图
    Node* cloneGraph(Node* node) {
        if (node == nullptr) return nullptr;
        unordered_map<Node*, Node*> map;
        queue<Node*> neighbors;
        neighbors.push(node);
        map[node] = new Node(node->val);
        while (!neighbors.empty()) {
            Node* cur = neighbors.front();
            neighbors.pop();
            for (Node* neighbor : cur->neighbors) {
                if (!map.count(neighbor)) {
                    map[neighbor] = new Node(neighbor->val);
                    neighbors.push(neighbor);
                }
                map[cur]->neighbors.push_back(map[neighbor]);
            }
        }
        return map[node];
    }
    // 399.除法求值
    
};

class DFS {
public:
    // 17.电话号码的字母组合
    vector<string> letterCombinations(string digits) {        
        unordered_map<char, vector<string>> map = { {'2', {"a", "b", "c"}}, {'3', {"d", "e", "f"}}, {'4', {"g", "h", "i"}}, {'5', {"j", "k", "l"}},
            {'6', {"m", "n", "o"}}, {'7', {"p", "q", "r", "s"}}, {'8', {"t", "u", "v"}}, {'9', {"w", "x", "y", "z"}} };
        vector<string> result;
        string str;
        if (digits == "") return result;
        myLetterCombinations(digits, 0, result, str, map);
        return result;
    }
    void myLetterCombinations(string digits, int position, vector<string>& result, string& str, unordered_map<char, vector<string>>& map) {
        if (position == digits.size()) {
            result.push_back(str);
            return;
        }
        for (int i = 0; i < map[digits[position]].size(); ++i) {
            str += (map[digits[position]][i]);
            myLetterCombinations(digits, position + 1, result, str, map);
            str = str.substr(0, str.size() - 1);
        }
    }
    // 77.组合
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> result;
        vector<int> path;
        myCombine(result, path, n, k, 1);
        return result;
    }
    void myCombine(vector<vector<int>>& result, vector<int>& path, int n, int k, int cur) {
        if (path.size() == k) {
            result.push_back(path);
            return;
        }
        for (int i = cur; i <= n; ++i) {            
            path.push_back(i);
            myCombine(result, path, n, k, i + 1);
            path.erase(path.end());           
        }
    }
    // 46.全排列
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> path;
        vector<bool> used(nums.size(), false);
        myPermute(result, nums, path, used);
        return result;
    }
    void myPermute(vector<vector<int>>& result, vector<int>& nums, vector<int>& path, vector<bool>& used) {
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); ++i) {
            if (used[i] == false) {
                path.push_back(nums[i]);
                used[i] = true;
                myPermute(result, nums, path, used);
                used[i] = false;
                path.erase(path.end());
            }
        }
    }
    // 39.组合总和
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> path;
        myCombinationSum(candidates, result, path, target, 0);
        return result;
    }
    void myCombinationSum(vector<int>& candidates, vector<vector<int>>& result, vector<int>& path, int target, int cur) {
        if (target == 0) {
            result.push_back(path);
            return;
        }
        if (target < 0) return;
        for (int i = cur; i < candidates.size(); ++i) {
            target -= candidates[i];
            path.push_back(candidates[i]);
            myCombinationSum(candidates, result, path, target, i);
            path.erase(path.end());
            target += candidates[i];
        }
    }
    // 52.N皇后Ⅱ
    int totalNQueens(int n) {
        vector<vector<string>> result;
        vector<string> path;
        myTotalNQeens(result, path, n, 0);
        return result.size();
    }
    void myTotalNQeens(vector<vector<string>>& result, vector<string>& path, int n, int index) {
        if (index == n) {
            result.push_back(path);
            return;
        }
        for (int i = 0; i < n; ++i) {            
            if (isCorrect(path, i, n)) {
                string flag = "";
                for (int j = 0; j < n; ++j) {
                    if (j == i) flag += "Q";
                    else flag += ".";
                }
                path.push_back(flag);
                myTotalNQeens(result, path, n, index + 1);
                path.pop_back();
            }
        }
    }
    bool isCorrect(vector<string>& path, int i, int n) {
        for (int j = 0; j < path.size(); j++) {
            if (path[j][i] == 'Q') return false;
        }
        int k = i;
        for (int j = path.size() - 1; j >= 0 && k < n; j--) {
            k = k + 1;
            if (path[j][k] == 'Q') return false;
        }
        k = i;
        for (int j = path.size() - 1; j >= 0 && k > 0; j--) {
            k = k - 1;
            if (path[j][k] == 'Q') return false;
        }
        return true;
    }
    // 22.括号生成
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        string path;
        myGenerateParenthesis(result, path, n, 0, 0);
        return result;
    }
    void myGenerateParenthesis(vector<string>& result, string& path, int n, int left, int right) {
        if (left < right) return;
        if (left == right && left == n) {
            result.push_back(path);
            return;
        }
        if (left < n) {
            path.push_back('(');
            left++;
            myGenerateParenthesis(result, path, n, left, right);
            left--;
            path.pop_back();
        }
        if (right < n) {
            path.push_back(')');
            right++;
            myGenerateParenthesis(result, path, n, left, right);
            right--;
            path.pop_back();
        }
    }
    // 79.单词搜索
};

int main() {
    Solution solution;
    vector<int> nums = { 2,5,10,1 };
    solution.coinChange(nums, 21);
    return 0;
}