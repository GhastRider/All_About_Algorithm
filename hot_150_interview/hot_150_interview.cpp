// hot_150_interview.cpp : This file contains the 'main' function. Program execution begins and ends there.
//





















// array_string.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

//结构化绑定：auto[node,cnt] 是C++ 17特性，在 C++ Language Standard 选项中，选择 ISO C++17 Standard


#include<iostream>
#include<sstream>

#include<vector>
#include<stack>
#include<string>
#include<queue>
//建议显示包含<utility>，虽然即使不显示包含utility，其他标准头文件内部使用了pair，它们间接地包含了<utility>
#include<utility>

#include<algorithm>
#include<numeric>

#include<unordered_map>
#include<unordered_set>
#include<map>

#include<functional>


//C++ 20
#include<ranges>


using namespace std;

//struct ListNode {
//	int value;
//	ListNode* next;
//
//	//constructor:
//	// : 构造函数初始化列表
//	ListNode() : value(0), next(nullptr) {}
//	ListNode(int x) : value(x), next(nullptr) {}
//	ListNode(int x, ListNode* nextnode) :value(x), next(nextnode) {}
//
//};
//struct TreeNode {
//	int val;
//	TreeNode* left;
//	TreeNode* right;
//	TreeNode() : val(0), left(nullptr), right(nullptr) {}
//	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
//};


//88. merge_sorted_array
//https://leetcode.cn/problems/merge-sorted-array

class Solution_88 {
public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		int i = nums1.size() - 1;
		m--;
		n--;
		while (n >= 0) {
			while (m >= 0 && nums1[m] > nums2[n]) {
				swap(nums1[i--], nums1[m--]); //其实没必要交换，直接赋值就可以，因为是从后往前所以不会覆盖到有效数据
				//nums1[i--] = nums1[m--];
			}
			swap(nums1[i--], nums2[n--]);
			// nums1[i--] = nums2[n--];
		}
	}
};

//27. remove-element
//https://leetcode.cn/problems/remove-element/
class Solution_27 //27_快慢指针解
{
public:
	int removeElement(vector<int>& nums, int val) {
		int fast = 0, slow = 0;
		while (fast < nums.size()) {
			if (nums[fast] != val)
			{
				nums[slow] = nums[fast];
				slow++;
			}
			fast++;
		}
		return slow;
	}
};

class Solution_27_2 //27_对撞指针解
{
public:
	int removeElement(vector<int>& nums, int val) {
		int left = 0, right = nums.size() - 1;
		while (left <= right) {
			if (nums[left] == val)
			{
				nums[left] = nums[right];
				right--;
			}
			else
			{
				left++;
			}

		}
		return left;
	}
};


//26. remove duplicates from sorted array
//https://leetcode.cn/problems/remove-duplicates-from-sorted-array/

class Solution_26 {
public:
	int removeDuplicates(vector<int>& nums) {
		int slow = 1, fast = 1;
		while (fast < nums.size())
		{
			if (nums[fast] != nums[slow - 1])
			{
				nums[slow] = nums[fast];
				++slow;
			}
			++fast;
		}

	}
};

//80. remove duplicates from sorted array
//https://leetcode.cn/problems/remove-duplicates-from-sorted-array-ii/
class Solution_80 {
public:
	int removeDuplicates(vector<int>& nums) {
		if (nums.size() <= 2)
		{
			return nums.size();
		}
		int fast = 2, slow = 2;
		while (fast < nums.size())
		{
			if (nums[fast] != nums[slow - 2])
			{
				nums[slow] = nums[fast];
				++slow;
			}
			++fast;
		}
		return slow;
	}
};


//169. majority element
//https://leetcode.cn/problems/majority-element/
class Solution_169_2 //排序后取中间数，nlogn堆排序时间复杂度，空间logn
{
public:
	int majorityElement(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		return nums[nums.size() / 2];
	}
};


/*
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
*/

// 当你访问 unordered_map 中不存在的键时，unordered_map 会自动创建该键，并将它的值初始化为类型的默认值。
// 例如，对于 int 类型，默认值为 0。

class Solution_169_3 //哈希表统计法, 时间复杂度n，空间复杂度n
{
public:
	int majorityElement(vector<int>& nums) {
		unordered_map<int, int> counts;
		int majority = nums.size() / 2;
		int result = 0;

		for (int num : nums) {
			counts[num]++;
			if (counts[num] > majority) {
				result = num;
				break;
			}
		}
		return result;
	}

};

class Solution_169 //摩尔投票法, 时间N空间1，最优解
{
public:
	int majorityElement(vector<int>& nums) {
		int cur_mode = 0, votes = 0;
		for (int num : nums) {
			if (votes == 0)//每次票数和为0的时候，
			{
				cur_mode = num;//假设下一个数为众数。
			}
			votes += num == cur_mode ? 1 : -1;
		}
		return cur_mode;
	}

};


//189. rotate-array
//https://leetcode.cn/problems/rotate-array/
class Solution_189 //翻转数组：1翻转全部 2翻转前k元素 3翻转后n-k个元素。
{
private:
	void reverse(vector<int>& nums, int left, int right)
	{
		while (left < right)
		{
			int temp = nums[right];
			nums[right] = nums[left];
			nums[left] = temp;

			left++; right--;
		}
	}
public:
	void rotate(vector<int>& nums, int k)
	{
		k = k % nums.size();
		reverse(nums, 0, nums.size() - 1);
		reverse(nums, 0, k - 1);
		reverse(nums, k, nums.size() - 1);

	}
};


class Solution_189_2 //环状替换
{
	void rotate(vector<int>& nums, int k)
	{
		int count = 0;
		int start = 0;
		while (count < nums.size())
		{
			int curr = start;
			int prev = nums[start];

			do {
				int next = (curr + k) % nums.size();
				int temp = nums[next];
				nums[next] = prev;
				prev = temp;
				curr = next;
				count++;

			} while (curr != start);

			start++;
		}
	}
};

class Solution_189_3// C++中：std::rotate();
{
public:
	void rotate(vector<int>& nums, int k) {
		k %= nums.size();
		std::rotate(nums.begin(), nums.end() - k, nums.end());
	}
};

//121. best time to buy and sell stock
//https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/

class Solution_121 // memorization sOlution.
{
public:
	vector<vector<int>> memo;
	int maxProfit(vector<int>& prices) {
		memo = vector<vector<int>>(prices.size(), vector<int>(3, -1));
		int result = dfs(0, 0, prices);
		return result;
	}
	int dfs(int idx, int state, vector<int>& prices)
	{
		if (idx >= prices.size() || state == 2) return 0;
		if (memo[idx][state] != -1) return memo[idx][state];
		if (state == 0)// decide when for buying in
		{
			memo[idx][state] = max(dfs(idx + 1, state, prices), dfs(idx + 1, 1, prices) - prices[idx]);
			return memo[idx][state];
		}
		//decide when to sell out
		memo[idx][state] = max(dfs(idx + 1, state, prices), dfs(idx + 1, 2, prices) + prices[idx]);
		return memo[idx][state];

	}

};

class Solution_121_2 //greedy algorithm
{
public:
	int maxProfit(vector<int>& prices) {
		int result = 0;
		int buyin = prices[0];
		for (int i = 0; i < prices.size(); ++i) {
			buyin = min(buyin, prices[i]);//更新前i天的最低价格
			//更新前i天的最高利润：i-1天最高利润和第i天卖出最高利润price
			result = max(result, prices[i] - buyin);
		}
		return result;
	}
};

//122. best time to buy and sell stock ii
//https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/

class Solution_122 //memorization solves
{
public:
	vector<vector<int>> memo;
	int maxProfit(vector<int>& prices) {
		memo = vector<vector<int>>(prices.size(), vector<int>(3, -1));
		return dfs(0, 0, prices);
	}
	int dfs(int idx, int s, vector<int>& prices)
	{
		if (idx >= prices.size()) return 0;
		if (memo[idx][s] != -1)
		{
			return memo[idx][s];
		}
		if (s == 0)
		{
			memo[idx][s] = max(dfs(idx + 1, s, prices), dfs(idx + 1, 1, prices) - prices[idx]);
		}
		if (s == 1)
		{
			memo[idx][s] = max(dfs(idx + 1, s, prices), dfs(idx + 1, 0, prices) + prices[idx]);
		}
		return memo[idx][s];
	}
};


class Solution_122_2 // greedy algorithm
{
public:
	int maxProfit(vector<int>& prices) {
		int ans = 0;
		int n = prices.size();
		for (int i = 1; i < n; ++i) {
			ans += max(0, prices[i] - prices[i - 1]);
		}
		return ans;
	}
};

//55. jump game
//https://leetcode.cn/problems/jump-game/

class Solution_55 // memorization solves
{
public:
	bool canJump(vector<int>& nums) {
		vector<int>memo(nums.size(), -1);
		function<bool(int)> dfs = [&](int idx) {
			if (idx >= nums.size() - 1) return true;//返回true的条件
			if (memo[idx] != -1) return memo[idx] == 1; //读memo
			for (int i = 1; i <= nums[idx]; ++i)
			{
				if (dfs(idx + i)) {
					memo[idx] = 1;
					return true;
				}
			}
			memo[idx] = 0;
			return false;
			};
		return dfs(0);
	}
};

class Solution_55_2 //greedy algorithm 1: update rightmost
{
public:
	bool canJump(vector<int>& nums) {
		int n = nums.size();
		int rightmost = 0;
		for (int i = 0; i < n; ++i) {
			if (i <= rightmost) {
				rightmost = max(rightmost, i + nums[i]);
				if (rightmost >= n - 1) {
					return true;
				}
			}
		}
		return false;
	}
};

class Solution_55_3 //greedy algorithm 2: update nums[i] if(nums[i-1]>0)
{
public:
	bool canJump(vector<int>& nums) {
		for (int i = 1; i < nums.size(); ++i)
		{
			if (nums[i - 1] > 0) {
				nums[i] = max(nums[i], nums[i - 1] - 1);
			}
			else return false;
		}
		return true;
	}
};





//45. jump game ii
//https://leetcode.cn/problems/jump-game-ii/
class Solution_45 // memorization solves
{
public:
	int jump(vector<int>& nums) {
		vector<int>memo(nums.size(), 0);
		function<int(int)> dfs = [&](int idx) {
			if (idx >= nums.size() - 1) return 0;
			if (memo[idx] != 0) return memo[idx];
			int ans = INT_MAX;
			for (int i = 1; i <= nums[idx]; ++i)
			{
				int next = dfs(idx + i);
				if (next != INT_MAX) {
					ans = min(ans, dfs(idx + i) + 1);
				}
			}
			memo[idx] = ans;
			return ans;
			};
		return dfs(0);
	}
};

class Solution_45_2 //最短路径 shortest path solves
{
public:
	int jump(vector<int>& nums) {
		queue<pair<int, int>> q;
		vector<bool> vst(nums.size(), false);
		q.push({ 0,0 });
		vst[0] = true;
		while (!q.empty())
		{
			auto [node, cnt] = q.front(); q.pop(); //结构化绑定auto[a,b]是C++17特性
			if (node == nums.size() - 1) return cnt;
			for (int i = 1; i <= nums[node]; ++i) {
				int next_node = node + i;
				if (next_node >= nums.size() || vst[next_node]) continue;
				q.push({ next_node, cnt + 1 });
				vst[next_node] = true;
			}
		}
		return 0;
	}
};

class Solution_45_3 //greedy algorithm
{
public:
	int jump(vector<int>& nums) {
		int maxpos = 0;
		int end = 0;
		int step = 0;
		for (int i = 0; i < nums.size(); ++i) {
			if (i <= maxpos)
				maxpos = max(maxpos, nums[i] + i);
			if (i == end) {
				end = maxpos;
				++step;
			}
		}
		return step;
	}
};


//274. H-index
// https://leetcode.cn/problems/h-index/description/
class Solution_274 //
{
public:
	int hIndex(vector<int>& citations) {
		sort(citations.begin(), citations.end(), greater<int>());
		for (int i = citations.size() - 1; i >= 0.; --i)
		{
			if (citations[i] >= i + 1)
				return i + 1;
		}
		return 0;
	}
};


//238. product of array except self
// https://leetcode.cn/problems/product-of-array-except-self/

class Solution_238 //前后缀积 时间复杂度n空间复杂度n
{
public:
	vector<int> productExceptSelf(vector<int>& nums) {

		vector<int> pre_product(nums.size(), 1);
		vector<int> sufix_product(nums.size(), 1);

		for (int i = 1; i < nums.size(); ++i) {
			pre_product[i] = pre_product[i - 1] * nums[i - 1];
		}
		for (int i = nums.size() - 2; i >= 0; --i) {
			sufix_product[i] = sufix_product[i + 1] * nums[i + 1];
		}
		vector<int> result;
		result.reserve(nums.size());
		for (int i = 0; i < nums.size(); ++i)
		{
			result.emplace_back(pre_product[i] * sufix_product[i]);
		}

		return result;
	}
};

class Solution_238_2 //空间复杂度1
{
public:
	vector<int> productExceptSelf(vector<int>& nums) {
		int n = nums.size();
		vector<int> answer(n, 1);
		for (int i = 1; i < n; ++i) {
			answer[i] = nums[i - 1] * answer[i - 1];
		}
		int R = 1;
		for (int i = n - 1; i >= 0; i--) {
			answer[i] = answer[i] * R;
			R *= nums[i];
		}
		return answer;
	}
};

//134. gas station
//https://leetcode.cn/problems/gas-station/

class Solution_134 //greedy algorithm
{
public:
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
		int n = gas.size();
		int i = 0;
		while (i < n) {
			int sumOfGas = 0, sumOfCost = 0;
			int cnt = 0;
			while (cnt < n) {
				int j = (i + cnt) % n;
				sumOfGas += gas[j];
				sumOfCost += cost[j];
				if (sumOfCost > sumOfGas) break;
				++cnt;
			}
			if (cnt == n) {
				return i;
			}
			else {
				i = i + cnt + 1;
			}
		}
		return -1;
	}
};

//135. candy
//https://leetcode.cn/problems/candy/
class Solution_135 //two iterations
{
public:
	int candy(vector<int>& ratings) {
		int n = ratings.size();
		vector<int> result(ratings.size(), 1);
		for (int i = 1; i < n; ++i) {
			if (ratings[i] > ratings[i - 1]) result[i] = result[i - 1] + 1;
		}
		for (int i = n - 2; i >= 0; --i) {
			if (ratings[i] > ratings[i + 1] && 
				!(result[i] > result[i + 1])) result[i] = result[i + 1] + 1;
		}
		return accumulate(result.begin(), result.end(), 0);
	}

};

//42. trapping rain water
//https://leetcode.cn/problems/trapping-rain-water/
class Solution_42 //DP: rightMax, leftMax
{
public:
	int trap(vector<int>& height) {
		int n = height.size();
		if (n == 0) {
			return 0;
		}
		vector<int> leftMax(n);
		leftMax[0] = height[0];
		for (int i = 1; i < n; ++i) {
			leftMax[i] = max(leftMax[i - 1], height[i]);
		}
		vector<int> rightMax(n);
		rightMax[n - 1] = height[n - 1];
		for (int i = n - 2; i >= 0; --i) {
			rightMax[i] = max(rightMax[i + 1], height[i]);
		}

		int ans = 0;
		for (int i = 0; i < n; ++i) {
			ans += min(leftMax[i], rightMax[i]) - height[i];
		}
		return ans;
	}
};

class Solution_42_2 // monotonic stack
{
public:
	int trap(vector<int>& height) {
		int ans = 0;
		stack<int> st;
		for (int i = 0; i < height.size(); ++i)
		{
			while (!st.empty() && height[st.top()] < height[i]) {
				int cur = st.top();
				st.pop();
				if (st.empty()) break;
				int l = st.top();
				int r = i;
				int h = min(height[r], height[l]) - height[cur];
				ans += (r - l - 1) * h;
			}
			st.push(i);
		}
		return ans;
	}
};

//13. roman to integer
//https://leetcode.cn/problems/roman-to-integer/

class Solution_13
{
public:
	unordered_map<char, int> ROMAN = {
		{'I',1},
		{'V',5},
		{'X',10},
		{'L',50},
		{'C',100},
		{'D',500},
		{'M',1000},
	};
	int romanToInt(string s) {
		int ans = 0;
		for (int i = 1; i < s.length(); i++) {
			if (i < s.length() - 1 && ROMAN[s[i]] < ROMAN[s[i + 1]]) {
				ans -= ROMAN[s[i]];
			}
			else {
				ans += ROMAN[s[i]];
			}
		}
		return ans;
	}
};

//12. integer to roman
//https://leetcode.cn/problems/integer-to-roman/description/




class Solution_12 //用map，和rbegin(), rend()

{
public:
	static const map<int, string> intToRomanMap;
	
	string intToRoman(int num) {
		string res;
		for (auto it = intToRomanMap.rbegin(); it != intToRomanMap.rend(); ++it)
		{
			int value = it->first;
			string roman = it->second;
			while (num >= value) {
				num -= value;
				res += roman;
				if (num == 0)
					return res;
			}
		
		}
		return "";
}
};
const map<int, string> Solution_12::intToRomanMap = {
	{1000, "M"}, {900, "CM"},
	{500, "D"},  {400, "CD"},
	{100, "C"},  {90, "XC"},
	{50, "L"},   {40, "XL"},
	{10, "X"},   {9, "IX"},
	{5, "V"},    {4, "IV"},
	{1, "I"}
};



class Solution_12_2 //用 pair<int,string> a[13];
{
public:
	//这样做是错的弹性数组是没法作为类成员推断大小的 
	//an initializer cannot be specified for a flexible array member
	//int a[] = { 1, 2, 3, 4, 5 }; 
	static const pair<int, string> map[13];  

string intToRoman(int num) {
	string roman;
	for (const auto& [value, symbol] : map) {
		while (num >= value) {
			num -= value;
			roman += symbol;
			if (num == 0) return roman;
		}
	}
	return roman;
}
};

const pair<int, string> Solution_12_2::map[] = {
{1000,"M"},{900,"CM"},
{500,"D"}, {400,"CD"},
{100,"C"}, {90,"XC"},
{50,"L"},  {40,"XL"},
{10,"X"},  {9,"IX"},
{5,"V"},   {4,"IV"},
{1,"I"},
};


//58. length of last word
//https://leetcode.cn/problems/length-of-last-word/

class Solution_58 {
public:
	int lengthOfLastWord(string s) {
		int end = s.size() - 1;
		while (end >= 0 && s[end] == ' ') {
			--end;
		}
		if (end < 0)
			return 0;
		int res = 0;
		while (end >= 0 && s[end] != ' ')
		{
			--end;
			++res;
		}
		return res;
	}
};



//14. longest common prefix 
//https://leetcode.cn/problems/longest-common-prefix/

class Solution_14  //纵扫
{ 
public:
	string longestCommonPrefix(vector<string>& strs) {
		int length = strs[0].length();
		if (length == 0) return "";
		int count = strs.size();
		for (int i = 0; i < length; ++i) {
			char c = strs[0][i];
			for (int j = 1; j < count; ++j) {
				if (i == strs[j].size() || strs[j][i] != c)
					return strs[0].substr(0, i);
			}
		}
		return strs[0];
	}
};

class Solution_14_2  //横扫
{
public:
	string longestCommonPrefix(vector<string>& strs) {
		if (strs.size() == 0) return "";
		string prefix = strs[0];
		int count = strs.size();
		for (int i = 1; i < count; ++i) {
			prefix = longestCommonPrefix(prefix, strs[i]);
		}
		return prefix;
	}
	
private:
	string longestCommonPrefix(const string& s1, const string& s2) {
		int length = min(s1.size(), s2.size());
		int index = 0;
		while (index < length && s1[index] == s2[index])
		{
			index++;
		}
		return s1.substr(0, index);
	}
};



//151. reverse-words-in-a-string
//https://leetcode.cn/problems/reverse-words-in-a-string/
class Solution_151
{
public:
		
	string reverseWords(string s) {
		removeExtraSpaces1(s);
		reverse(s, 0, s.size() - 1);
		int cur_start = 0;
		for (int i = 0; i <= s.size(); ++i) {
			if (s[i] == ' ' || i == s.size())
			{
				reverse(s, cur_start, i - 1);
				cur_start = i + 1;
			}
		}
	}

private:
	//string s; //也可以把s设为成员变量
	void removeExtraSpaces1(string& s)
	{
		int slow = 0;
		for (int i = 0; i < s.size(); ++i)
		{
			if (s[i] != ' ')//只有s[i]遍历到不是空格的时候才处理
			{	
				//只要slow指针不是0，说明slow指向的不是开头第一个单词第一个字母，
				// ,这时s[i]不等于空格的话，说明是碰到非第一个单词的新单词，
				// 遂s[slow]加空格
				if (slow != 0) s[slow++] = ' ';
				while (i < s.size() && s[i] != ' ') s[slow++] = s[i++];
				//跳出这个while的时候，说明s[i]到空格了，或者s[i]遍历结束了
			}
		}
		s.resize(slow);
	}
	
	void removeExtraSpaces3(string& s)
	{
		int slow = 0, fast = 0;
		while (fast < s.size())
		{
			if (s[fast] != ' ' || (fast - 1 >= 0 && s[fast - 1] != ' '))
			{
				s[slow] = s[fast];
				++slow;
			}
			fast++;
		}

		if (slow > 1 && s[slow - 1] == ' ') slow--;

	}
	void reverse(string& s,int l,int r) {
		while (l < r) swap(s[l++], s[r--]);
	}	
};



//6. zigzag conversion
//https://leetcode.cn/problems/zigzag-conversion/

class Solution_6 //K神题解
{
public:
	string convert(string s, int numRows) {
		if (numRows == 1) return s;
		vector<string> rows(numRows);
		int flag = 1;// 行转向标志
		int idxRows = 0;// 行下标索引
		for (int i = 0; i < s.size(); i++) {
			rows[idxRows].push_back(s[i]);
			idxRows += flag;// 更新行下标
			if (idxRows == numRows - 1 || idxRows == 0) {
				flag = -flag;//转向
			}
		}
		string res;
		for (auto row : rows) {
			// 拿到答案
			res += row;
		}
		return res;
	}
};



//28. find-the-index-of-the-first-occurrence-in-a-string
//https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/
class Solution_28 //the Legendary KMP -unfinished
//KMP: 匹配成功的部分中存在相同的【前缀】和【后缀】, 
//so, 不需要从头匹配，可以将匹配串指针移至【前缀】下一个位置继续匹配
//=================================================================
//关于用形参string大小来初始化类内函数内的局部变量大小,
//在 LeetCode 的某些环境下，它可能会启用变长数组 (VLA) 扩展，
// 允许在运行时指定数组大小，但是这不是标准 C++ 的特性，
// 因此在标准编译器上会出错。
{
public:
	int strStr(string haystack, string needle)
	{
		
		
		//int next[needle.size()]; 这行代码中，needle.size() 是在运行时才能得到的，
		// 而 C++ 要求数组的大小必须是编译时已知的常量，因此编译器会报错
		
		vector<int> next(needle.size());
		
	}
private:
	void getNext(const string& p, vector<int>& next)
	{
		int k = -1;
		next[0] = -1;
		int j = 0;
		while (j < p.size() - 1) {
			if (k == -1 || p[j] == p[k])
			{
				next[++j] = ++k;
			}
		}
	}
};

class Solution_28_2 //violent match
{
public:
	int strStr(string s, string p) {
		int n = s.size(), m = p.size();
		for (int i = 0; i <= n - m; ++i)
		{
			int j = i, k = 0;
			while (k < m && s[j] == p[k]) {
				++j;
				++k;
			}
			if (k == m) return i;
		}
		return -1;
	}
};


//68. text-justification
//https://leetcode.cn/problems/text-justification/solutions/181651/text-justification-by-ikaruga/

class Solution_68 //lkaruga题解
{
private:
	string fillWords(vector<string>& words, int bg, int ed, int maxWidth, bool lastLine = false)
	{
		int wordCount = ed - bg + 1;
		int spaceCount = maxWidth - (-1 + wordCount);	
		
		//额外空格数量=总长度-正常空格数量-单词长度。
		
		for (int i = bg; i <= ed; ++i)
		{
			spaceCount -= words[i].size();
		}

		int spaceSuffix = 1;
		int spaceAvg = (wordCount == 1) ? 1 : spaceCount/(wordCount-1);
		int spaceExtra = (wordCount == 1) ? 0 : spaceCount % (wordCount - 1);

		string ans;
		for (int i = bg; i < ed; ++i) {
			ans += words[i];
			if (lastLine)
			{
				fill_n(back_inserter(ans), 1, ' ');
				continue;
			}
			fill_n(back_inserter(ans), spaceSuffix + spaceAvg + ((i - bg) < spaceExtra), ' ');
		}
		ans += words[ed];
		fill_n(back_inserter(ans), maxWidth - ans.size(), ' ');
		return ans;
	}
public:
	vector<string> fullJustify(vector<string>& words, int maxWidth)
	{
		vector<string> ans;
		int cnt = 0;
		int bg = 0;
		for (int i = 0; i < words.size(); ++i)
		{
			cnt += words[i].size() + 1;
			if (i + 1 == words.size() || cnt + words[i + 1].size() > maxWidth)
			{
				ans.push_back(fillWords(words, bg, i, maxWidth, i + 1 == words.size()));
				bg = i + 1;
				cnt = 0;
				
			}
		}
		return ans;
	}
};


//125. valid palindrome
//https://leetcode.cn/problems/valid-palindrome/


//按位或：|0x20 作用是大写字母转为小写(大写字母打ASCII码+32)
class Solution_125 //对撞指针
{
public:
	bool isPalindrome(string s)
	{
		int left = 0, right = s.size() - 1;
		while (left < right) {
			if (!isalnum(s[left]))
			{
				left++;
				continue;
			}
			if (!isalnum(s[right]))
			{
				right--;
				continue;
			}
			if ((s[left] | 0x20) != (s[right] | 0x20))
			{
				return false;
			}
			++left; --right;
		}
	}
};


//392. is subsequence
//https://leetcode.cn/problems/is-subsequence/

class Solution_392
{
public:
	bool isSubsequence(string s, string t)
	{
		int s_pointer = 0;
		for (int i = 0; i < t.size(); ++i) {
			if (s[s_pointer] == t[i])
				s_pointer++;
		}
		return s_pointer == s.size();
	}
};

//167. two-sum-ii-input-array-is-sorted/
//https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/
class Solution_167 //一层循环内套二分，violent 会超时
{
public:
	vector<int> twoSum(vector<int>& numbers, int target) {
		int n = numbers.size();
		for (int i = 0; i < n; ++i)
		{
			int l = i + 1, r = n - 1;
			int sub_target = target-numbers[i];

			while (l < r)
			{
				int mid = l + r >> 1;
				if (numbers[mid] >= sub_target) {
					r = mid;
				}
				else l = mid+1;
			}
			return { i + 1, r + 1 };
		}
		return vector<int>(2);
	}
};

class Solution_167_2 //双指针
// 左右指针代表：这个范围内是可能考虑项。
// 如果已经在left左，或者right右，代表已经不会考虑了。
// 如果左右之和小于target代表：目前范围最大的可能和最小的可能之和已经达不到要求了，
// 那么这个最小可能就要排除在外，所以left右移。大于target同理。
{
public:
	vector<int> twoSum(vector<int>& numbers, int target) {
		int low = 0, high = numbers.size() - 1;
		while (low < high) {
			int sum = numbers[low] + numbers[high];
			if (sum == target) {
				return { low + 1,high + 1 };
			}
			else if (sum < target) {
				++low;
			}
			else {
				--high;
			}
		}
		return { -1,-1 };
	}
};



//11. container with most water
class Solution_11		//双指针
{
public:
	int maxArea(vector<int>& height) {
		int maxV = 0;
		int left = 0, right = height.size() - 1;
		int lheighest = height[0]; int rheighest = height[right];
		while (left < right)
		{
			if (height[left] < height[right])
			{
				if (height[left] < lheighest)
				{
					left++;
					continue;
				}
				else {
					maxV = (height[left] * (right - left) < maxV) ? maxV : (height[left] * (right - left));
					lheighest = height[left++];
				}
			}
			else
			{
				if (height[right] < rheighest)
				{
					right--;
					continue;
				}
				else {
					maxV = (height[right] * (right - left) < maxV) ? maxV : (height[right] * (right - left));
					rheighest = height[right--];
				}
			}
		}
		return maxV;
	}
};

class Solution_11_2 // 双指针简便写法
{
public:
	int maxArea(vector<int>& height) {
		int l = 0, r = height.size() - 1;
		int lcapacity = -1;
		while (l < r) {
			lcapacity = max(lcapacity, min(height[l], height[r]) * r - l);
			if (height[l] < height[r]) {
				l++;
			}
			else {
				r--;
			}
		}
		return lcapacity;
	}
};

//15. 3sum
//https://leetcode.cn/problems/3sum/
class Solution_15	// 内层双指针
{
public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		//ranges::sort(nums);// why? error reason：MSVS版本问题，导致设置成C++20也没法正常使用ranges
		//std::ranges::sort
		//sort(nums.begin(), nums.end());
		vector<vector<int>> ans;
		sort(nums.begin(), nums.end());
		int n = nums.size();
		for (int i = 0; i < n - 2; ++i) {
			int x = nums[i];
			if(i && x==nums[i-1]) continue;
			if (x + nums[i + 1] + nums[i + 2] > 0) break;
			if (x + nums[n - 2] + nums[n - 1] < 0) continue;
			int j = i + 1, k = n - 1;
			while (j < k) {
				int s = x + nums[j] + nums[k];
				if (s > 0) {
					k--;
				}
				else if (s < 0) {
					++j;
				}
				else {
					ans.push_back({ x, nums[j],nums[k] });
					for (j++; j < k && nums[j] == nums[j - 1]; j++);
					for (k--; k > j && nums[k] == nums[k + 1]; k--);
				}
			}
		}
		return ans;
	}
};



//209. minimum-size subarray sum 
//https://leetcode.cn/problems/minimum-size-subarray-sum/

class Solution_209
{
public:
	int minSubArrayLen(int target, vector<int>& nums) {
		int res = INT_MAX;
		int sum = 0;
		for (int l = 0, r = 0; r < nums.size(); ++r)
		{
			sum += nums[r];
			while (l <= r && sum >= target)
			{
				res = min(res, r - l + 1);
				sum -= nums[l++];
			}
		}
		return res == INT_MAX ? 0 : res;
	}
	
};


//3. longest substring without repeating characters
//https://leetcode.cn/problems/longest-substring-without-repeating-characters/
class Solution_3 //滑窗 sliding window
{
public:
	int lengthOfLongestSubstring(string s) {
		unordered_set<char> substr;
		int n = s.size();
		int maxlen = 0;
		for (int l = 0, r = 0; r < n; ++r)
		{
			while (substr.count(s[r]))
			{
				substr.erase(s[l]);
				++l;
			}
			substr.insert(s[r]);
			maxlen = max(maxlen, r - l + 1);
		}
		return maxlen;
	}
};

//30. substring with concatenation of all words
//https://leetcode.cn/problems/substring-with-concatenation-of-all-words/
class Solution_30 
{
public:
	vector<int> findSubstring(string s, vector<string>& words) {
		vector<int> res;
		int m = words.size(), n = words[0].size(), slen = s.size();
		for (int i = 0; i < n && i + m * n <= slen; ++i) {
			unordered_map<string, int> differ;
			for (int j = 0; j < m; ++j) {
				++differ[s.substr(i + j * n, n)];
			}
			for (string& word : words) {
				if (--differ[word] == 0)
				{
					differ.erase(word);
				}
			}
			for (int start = i; start < slen - m * n + 1; start += n) {
				if (start != i) {
					string word = s.substr(start + (m - 1) * n, n);
					if (++differ[word] == 0)
					{
						differ.erase(word);
					}
					word = s.substr(start - n, n);
					if (--differ[word] == 0) {
						differ.erase(word);
					}
				}
				if (differ.empty()) {
					res.emplace_back(start);
				}
				
			}
		}
		return res;
	}

};



//76. minimum windows substring
//https://leetcode.cn/problems/minimum-window-substring/
class Solution_76
{
public:
	bool check(vector<int>& t_counter, vector<int>& win)
	{
		for (int i = 0; i < 58; ++i)
		{
			if (t_counter[i] > win[i]) return false;
		}
		return true;
	}
	string minWindow(string s, string t) {
		vector<int> t_counter(58, 0), win(58, 0);
		for (char c : t)
		{
			t_counter[c - 'A']++;
		}
		int minLen = INT_MAX, start = -1;
		for (int l = 0, r = 0; r < s.size(); ++r)
		{
			win[s[r] - 'A']++;
			while (l <= r && check(t_counter, win))
			{
				if (r - l + 1 < minLen)
				{
					minLen = r - l + 1;
					start = l;
				}
				win[s[l] - 'A']--;
				l++;
			}
		}
		return start == -1 ? "" : s.substr(start, minLen);
	}
};



//36. valid sudoku
//https://leetcode.cn/problems/valid-sudoku/
class Solution_36 //一次遍历
{
public:
	bool isValidSudoku(vector<vector<char>>& board) {
		int rows[9][9];
		int columns[9][9];
		int subboxes[3][3][9];
		
		memset(rows, 0, sizeof(rows));
		memset(columns, 0, sizeof(columns));
		memset(subboxes, 0, sizeof(subboxes));
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++)
			{
				char c = board[i][j];
				if (c != '.') {
					int index = c - '0' - 1;
					rows[i][index]++;
					columns[j][index]++;
					subboxes[i / 3][j / 3][index]++;
					if (rows[i][index] > 1 || columns[j][index] > 1 || subboxes[i / 3][j / 3][index] > 1)
						return false;
				}
			}
		}
		return true;
	}
};

//73. set matrix zeroes
//https://leetcode.cn/problems/set-matrix-zeroes/
class Solution_73 //标记数组
{
public:
	void setZeroes(vector<vector<int>>& matrix) {
		int m = matrix.size();
		int n = matrix[0].size();
		vector<int> row(m), col(n);
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (!matrix[i][j]) {
					row[i] = col[j] = true;
				}
			}
		}
		
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j)
			{
				if (row[i] || col[j]) {
					matrix[i][j] = 0;
				}
			}
		}
	}
};


//1. two-sum
//https://leetcode.cn/problems/two-sum/
class Solution_1
{
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		vector<int> result;
		unordered_map<int, int> map;
		for (int i = 0; i < nums.size(); ++i)
		{
			auto item = map.find(target - nums[i]);
			if (item != map.end()) {
				result = { item->second, i };
				break;
			}
			map[nums[i]] = i;
		}
		return result;
	}
	
};

//202. happy number
//https://leetcode.cn/problems/happy-number/

class Solution_202
{
public:
	bool isHappy(int n) {
		unordered_set<int> used;
		while (!used.count(n)) {
			if (n == 1) return true;
			used.insert(n);
			int mark = 0;
			while (n > 0) {
				mark += pow(n % 10, 2);
				n = n / 10;
			}
			n = mark;
		}
		return false;
	}
};

//219. contains duplicate II
//https://leetcode.cn/problems/contains-duplicate-ii/
class Solution_219
{
	bool containsNearbyDuplicate(vector<int>& nums, int k) {
		unordered_map<int, int> map;
		for (int i = 0; i < nums.size(); ++i)
		{
			if (map.count(nums[i]) && i - map[nums[i]] < k) return true;
			map[nums[i]] = i;
		}
		return false;
	}
};


//128. longest consecutive sequence
//https://leetcode.cn/problems/longest-consecutive-sequence/
class Solution_128 
{
	int longestConsecutive(vector<int>& nums) {
		unordered_set<int> num_set;
		for (const int& num : nums)
		{
			num_set.insert(num);
		}
		int longestStreak = 0;
		for (const int& num : num_set) {
			if (!num_set.count(num - 1)) {
				int currentNum = num;
				int currentStreak = 1;
				while (num_set.count(currentNum + 1)) {
					currentNum += 1;
					currentStreak += 1;
				}
				longestStreak = max(longestStreak, currentStreak);
				
			}
		}
		return longestStreak;
	}
	
};


//228. summary-ranges
//https://leetcode.cn/problems/summary-ranges/
class Solution_228
{
	vector<string> summaryRanges(vector<int>& nums) {
		vector<string> ret;
		int i = 0;
		int n = nums.size();
		while (i < n) {
			int low = i;
			++i;
			
			while (i < n && nums[i] == nums[i - 1] + 1) {
				++i;
			}

			int high = i - 1;
			string temp = to_string(nums[low]);
			if (low < high) {
				temp.append("->");
				temp.append(to_string(nums[high]));
			}
			ret.push_back(move(temp));
		}
		return ret;
	}
};

//56. merge intervals
//https://leetcode.cn/problems/merge-intervals/description/
class Solution_56 {
	vector<vector<int>> merge(vector<vector<int>>& intervals) {
		if (intervals.size() == 0) return {};
		sort(intervals.begin(), intervals.end());
		vector<vector<int>> merged;
		for (int i = 0; i < intervals.size(); ++i) {
			int L = intervals[i][0], R = intervals[i][1];
			if (merged.size() == 0 || merged.back()[1] < L) {
				merged.push_back({ L,R });
			}
			else {
				merged.back()[1] = max(merged.back()[1], R);
			}
		}
		return merged;
	}
};

//57. insert interval
//https://leetcode.cn/problems/insert-interval/
class Solution_57{
public:
	vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
		vector<vector<int>> ans;
		bool placed = false;
		int left = newInterval[0], right = newInterval[1];

		for (const vector<int>& a : intervals)
		{
			if (right < a[0])
			{
				if (!placed) {
				ans.push_back({ left,right });
				placed = true;
				}
				ans.push_back(a);
			}
			else if (left > a[1])
			{
				ans.push_back(a);
			}
			else {
				left = min(left, a[0]);
				right = max(right, a[1]);
			}
		}
		if (!placed)
		{
			ans.push_back({ left,right });
		}
		return ans;
	}
};


//452. minimum number of arrows to burst balloons
//https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/
class Solution_452
{
public:
	int findMinArrowShots(vector<vector<int>>& points) {
		if (points.empty()) {
			return 0;
		}
		sort(points.begin(), points.end(), [](const vector<int>& u, const vector<int>& v) {
			return u[1] < v[1];
		});
		int pos = points[0][1];
		int ans = 1;
		for (const vector<int>& ballon : points) {
			if (ballon[0] > pos) {
				pos = ballon[1];
				++ans;
			}
		}
		return ans;
	}
};


//20. valid-parentheses
//https://leetcode.cn/problems/valid-parentheses/

class Solution_20 {
public:
	bool isValid(string s) {
		int n = s.size();
		if (n % 2 == 1) return false;
		
		unordered_map<char, char> pairs = {
			{')', '('},
			{']','['},
			{'}','{'},
		};
		stack<char> stk;
		for (char ch : s) {
			if (pairs.count(ch)) {
				if (stk.empty() || stk.top() != pairs[ch]) {
					return false;
				}
				stk.pop();
			}
			else {
				stk.push(ch);
			}
		}
		return stk.empty();
	}
};

//150. evaluate reverse polish notation
//https://leetcode.cn/problems/evaluate-reverse-polish-notation/

class Solution_150 {
public:
	int evalRPN(vector<string>& tokens) {
		stack<long long> stack;
		for (int i = 0; i < tokens.size(); ++i) {
			if (tokens[i] == "-" || tokens[i] == "+" || tokens[i] == "*" || tokens[i] == "/")
			{
				long long a = stack.top();
				stack.pop();
				long long b = stack.top();
				stack.pop();
				if (tokens[i] == "-") stack.push(b - a);
				if (tokens[i] == "+") stack.push(b + a);
				if (tokens[i] == "*") stack.push(b * a);
				if (tokens[i] == "/") stack.push(b / a);
			}
			else {
				stack.push(stoll(tokens[i]));
			}
		}
		return stack.top();
	}
};

class Solution_150_2 // switch case + enum
{
private:
	enum class Operation {
		NOOP,
		ADD,
		SUBTRACT,
		MULTIPLY,
		DIVIDE
	};
	Operation getOperation(const string& token) {
		if (token == "+") return Operation::ADD;
		if (token == "-") return Operation::SUBTRACT;
		if (token == "*") return Operation::MULTIPLY;
		if (token == "/") return Operation::DIVIDE;
		return Operation::NOOP;
	}

public:

	int evalRPN(vector<string>& tokens) {
		stack<long long> stack;
		
		for (const string& token : tokens)
		{
			if (token == "-" || token == "+" || token == "*" || token == "/")
			{
				long long b = stack.top(); stack.pop();
				long long a = stack.top(); stack.pop();
				switch (getOperation(token)) {
				case Operation::ADD:
					stack.push(a + b);
					break;
				case Operation::SUBTRACT:
					stack.push(a - b);
					break;
				case Operation::MULTIPLY:
					stack.push(a * b);
					break;
				case Operation::DIVIDE:
					stack.push(a / b);
					break;
				default:
					break;
				}
			}
			else {
				stack.push(stoll(token));
			}

		}
		return stack.top();
	}
};



//141. linked-list-cycle
//https://leetcode.cn/problems/linked-list-cycle/

struct ListNode {
	
	int val;
	ListNode* next;
	//ListNode() :val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next){}
};

class Solution_141 //快慢指针
{
public:
	using LNp = ListNode*;
	bool hasCycle(ListNode* head) {
		LNp slow = head;
		LNp fast = head;
		
		while (fast != nullptr)
		{
			fast = fast->next;
			
			if (fast != nullptr)
			{
				fast = fast->next;
			}
			if (fast == slow) return true;
			slow = slow->next;
		}
		return false;
	}
	};

class Solution_141_2 //哈希表
{
public:
	bool hasCycle(ListNode* head) {
		using LNp = ListNode*;
		LNp cur = head;
		unordered_set<LNp> marked;
		while (cur != nullptr) {
			if (!marked.count(cur))
			{
				marked.insert(cur);
			}
			else return true;
			
			cur = cur->next;
		}
		return false;
	}
};

//2. add two numbers
//https://leetcode.cn/problems/add-two-numbers/
class Solution_2 //官解迭代
{
public:
	using LNp = ListNode*;
	using LN = ListNode;
	LNp addTwoNumbers(LNp l1, LNp l2)
	{
		LNp head = nullptr, tail = nullptr;
		int carry = 0;
		
		while (l1 || l2)
		{
			int n1 = l1 ? l1->val : 0;
			int n2 = l2 ? l2->val : 0;
			
			int sum = n1 + n2 + carry;
			
			if (!head)
			{
				head = tail = new ListNode(sum % 10);
			}
			else
			{
				tail->next = new LN(sum % 10);
				tail = tail->next;
			}
			carry = sum / 10;
			
			if (l1)
			{
				l1 = l1->next;
			}
			if (l2)
			{
				l2 = l2->next;
			}
			
		}
		if (carry > 0)
		{
			tail->next = new ListNode(carry);
		}
		return head;
	}
};


class Solution_2_2//递归
{
public:
	using LN = ListNode;
	using LNp = ListNode*;
	
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		return add(l1, l2, 0);
	}
	
private:
	LNp add(LNp l1, LNp l2, int carry)
	{
		if (!l1 && !l2 && carry == 0) return nullptr;
		
		int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;
		
		LNp node = new LN(sum % 10);
		node->next = add(l1 ? l1->next : nullptr, l2 ? l2->next : nullptr, sum / 10);
		return node;
	}
};


//21. merge two sorted lists
//https://leetcode.cn/problems/merge-two-sorted-lists/

class Solution_21 //迭代
{
public:
	using LN = ListNode;
	using LNp = ListNode*;
	
	LNp mergeTwoLists(LNp l1, LNp l2) {
		LNp dum = new LN(0);
		LNp cur = dum;
		while (l1 != nullptr && l2 != nullptr)
		{
			if (l1->val < l2->val) {
				cur->next = l1;
				l1 = l1->next;
			}
			else {
				cur->next = l2;
				l2 = l2->next;
			}
			cur = cur->next;
		}
		cur->next = l1 == nullptr ? l2 : l1;
		return dum->next;
	}
};


class Solution_21_2 //递归
{
public:
	using LN = ListNode;
	using LNp = LN*;
	
	LNp mergeTwoLists(LNp l1, LNp l2) {
		if (l1 == nullptr) {
			return l2;
		}
		else if(l2==nullptr){
			return l1;
		}
		else if (l1->val < l2->val)
		{
			l1->next = mergeTwoLists(l1->next, l2);
			return l1;
		}
		else {
			l2->next = mergeTwoLists(l1, l2->next);
			return l2;
		}
	}
};

//138. copy-list-with-random-pointer
//https://leetcode-cn.com/problems/copy-list-with-random-pointer/
class Node {
public:
	int val;
	Node* next;
	Node* random;

	Node(int _val) {
		val = _val;
		next = nullptr;
		random = nullptr;
	}
};


class Solution_138 //回溯，哈希表
{
public:
	using N = Node;
	using Np = Node*;
	unordered_map<Node*, Node*> cachedNode;
	
	Np copyRandomList(Np head) {
		if (head == nullptr) {
			return nullptr;
		}
		if (!cachedNode.count(head)) {
			Np headNew = new N(head->val);
			cachedNode[head] = headNew;
			headNew->next = copyRandomList(head->next);
			headNew->random = copyRandomList(head->random);
		}
		return cachedNode[head];
	}
	
};


class Solution_138_2 //迭代，拼接+拆分，三次遍历
{
public:
	using N = Node;
	using Np = Node*;

	Np copyRandomList(Np head) {
		if (head == nullptr) {
			return nullptr;
		}
		for (Np node = head; node != nullptr; node = node->next->next) {
			Np nodeNew = new Node(node->val);
			nodeNew -> next = node -> next;
			node->next = nodeNew;
		}
		for (Np node = head; node != nullptr; node = node->next->next) {
			Np nodeNew = node->next;
			nodeNew->random = (node->random != nullptr) ? node->random->next : nullptr;
		}
		Np headNew = head->next;
		for (Np node = head; node != nullptr; node = node->next) {
			Np nodeNew = node->next;
			node->next = node->next->next;
			nodeNew->next = (nodeNew->next != nullptr) ? nodeNew->next->next : nullptr;
		}
		return headNew;
	}
};

//92. reverse-linked-list-ii
//https://leetcode.cn/problems/reverse-linked-list-ii/solutions/634701/fan-zhuan-lian-biao-ii-by-leetcode-solut-teyq/

class Solution_92
{
public:
	using LNp = ListNode*;
	using LN = ListNode;
private:
	void reverseLinkedList(ListNode* head) {
		LNp pre = nullptr;
		LNp cur = head;
		while (cur != nullptr)
		{
			LNp next = cur->next;
			cur->next = pre;
			
			pre = cur;
			cur = next;
		}
	}

public:
	ListNode* reverseBetween(LNp head, int l, int r) {
		LNp dum = new LN(-1);
		dum->next = head;
		
		LNp pre = dum;
		for (int i = 0; i < l - 1; ++i)
		{
			pre = pre->next;
		}
		LNp rn = pre;
		for (int i = 0; i < r - l + 1; ++i) {
			rn = rn->next;
		}
		
		LNp leftnode = pre->next;
		LNp cur = rn->next;

		pre->next = nullptr;
		rn->next = nullptr;
		
		reverseLinkedList(leftnode);
		
		pre->next = rn;
		leftnode->next = cur;
		return dum->next;
	}

};


//25. reverse-nodes-in-k-group
//https://leetcode.cn/problems/reverse-nodes-in-k-group/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution_25 {
public:
	using LN = ListNode;

private:
	pair<LN*, LN*> reverseList(LN* head, LN* tail)
	{
		LN* cur = head;
		LN* pre = tail->next;
		// LN* next = head->next;

		while (pre != tail)
		{
			LN* next = cur->next;
			cur->next = pre;

			pre = cur;
			cur = next;
		}
		return { tail, head };
	}

public:
	LN* reverseKGroup(LN* head, int k)
	{
		LN* hair = new LN(0);
		hair->next = head;
		LN* pre = hair;

		while (head)
		{
			LN* tail = pre;

			for (int i = 0; i < k; ++i)
			{
				tail = tail->next;
				if (!tail) {
					return hair->next;
				}
			}
			LN* nex = tail->next;

			pair<LN*, LN*> res = reverseList(head, tail);

			head = res.first;
			tail = res.second;

			pre->next = head;
			tail->next = nex;
			pre = tail;

			head = tail->next;

		}

		return hair->next;
	}

};



//19. remove-nth-node-from-end-of-list
//https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/
class Solution_19
{
public:
using LN = ListNode;
ListNode* removeNthFromEnd(ListNode* head, int n) {

	LN* null_meeter = head;
	LN* pre = new LN(-1);
	LN* res = pre;
	pre->next = null_meeter;

	for (int i = 0; i < n; ++i)
	{
		null_meeter = null_meeter->next;

	}
	while (null_meeter != nullptr) {
		null_meeter = null_meeter->next;
		pre = pre->next;
	}
	pre->next = pre->next->next;
	//return check_n == n ? head->next : head;
	return res->next;
	}
};


//82. remove-duplicates-from-sorted-list-ii
//https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution_82 {
public:
	using LN = ListNode;
	ListNode* deleteDuplicates(ListNode* head) {
		if (head == nullptr) return head;
		LN* hair = new LN(-1, head);
		LN* pre = hair;
		LN* cur = head;
		int mark = 1 - INT_MAX;
		while (cur && cur->next) {
			if (cur->val == cur->next->val)
			{
				mark = cur->val;
				while (cur && cur->val == mark)
				{
					cur = cur->next;
				}
				pre->next = cur;
				continue;
			}
			cur = cur->next;
			pre = pre->next;
		}
		return (*hair).next;
	}
};

//61. rotate-list
//https://leetcode-cn.com/problems/rotate-list/
class Solution_61 //k取模，循环k次操作
{
public:
	using LN = ListNode;
	ListNode* rotateRight(ListNode* head, int k) {
		if (head == nullptr || head->next == nullptr || k == 0) return head;
		LN* cur_head = head;

		int count = 0;
		LN* counter = head;
		while (counter)
		{
			counter = counter->next;
			++count;
		}
		k = k % count;

		for (int i = 0; i < k; ++i)
		{
			LN* cur = cur_head;
			LN* preOfEnd;
			while (cur->next)
			{

				if (cur->next->next == nullptr)
				{
					preOfEnd = cur;
				}
				cur = cur->next;

			}
			cur->next = cur_head;
			preOfEnd->next = nullptr;

			cur_head = cur;
		}
		return cur_head;
	}
};

class Solution_61_2
{
public:
	using LN = ListNode;
	ListNode* rotateRight(ListNode* head, int k) {
		if (head == nullptr || head->next == nullptr || k == 0) return head;
		LN* cur_head = head;

		int count = 0;
		LN* counter = head;
		LN* originEnd;

		while (counter)
		{
			if (counter->next == nullptr)
			{
				originEnd = counter;
			}
			counter = counter->next;
			++count;
		}
		k = k % count; if (k == 0)return head;

		int newEnd = count - k - 1;
		LN* newEndNode = head;
		for (int i = 0; i < newEnd; ++i)
		{
			newEndNode = newEndNode->next;
		}
		LN* newHead = newEndNode->next;
		newEndNode->next = nullptr;
		originEnd->next = head;
		return newHead;
	}
};



//86. partition-list
//

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution_86 {
public:
	using LN = ListNode;
	ListNode* partition(ListNode* head, int x) {
		LN* small = new LN(0);
		LN* smallHead = small;
		LN* large = new LN(0);
		LN* largeHead = large;

		while (head != nullptr)
		{
			if (head->val < x)
			{
				small->next = head;
				small = small->next;
			}
			else {
				large->next = head;
				large = large->next;
			}
			head = head->next;
		}
		large->next = nullptr;
		small->next = largeHead->next;
		return smallHead->next;
	}
};


// Tree TreeNode structure
// TreeNode
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() :val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) :val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) :val(x), left(left), right(right) {}
};

//226. invert binary tree
//https://leetcode.cn/problems/invert-binary-tree/
class Solution_226 
{
public:
	using TN = TreeNode;
	TN* invertTree(TN* root)
	{
		if (root == nullptr) return root;
		TN* temp = root->left;
		root->left = invertTree(root->right);
		root->right = invertTree(temp);
		return root;
	}
};

//105. construct-binary-tree-from-preorder-and-inorder-traversal
//https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
class Solution_105 {
public:
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		if (preorder.empty()) { return nullptr; }

		// int left_size = ranges::find(inorder, preorder[0]) - inorder.begin();
		int left_size = find(inorder.begin(), inorder.end(), preorder[0]) - inorder.begin();

		vector<int> pre1(preorder.begin() + 1, preorder.begin() + 1 + left_size);
		vector<int> pre2(preorder.begin() + 1 + left_size, preorder.end());
		vector<int> in1(inorder.begin(), inorder.begin() + left_size);
		vector<int> in2(inorder.begin() + 1 + left_size, inorder.end());

		TreeNode* left = buildTree(pre1, in1);
		TreeNode* right = buildTree(pre2, in2);
		return new TreeNode(preorder[0], left, right);
	}
};


//106. construct-binary-tree-from-inorder-and-postorder-traversal
//https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/

class Solution_106 {
public:
	TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
		if (postorder.empty())
		{
			return nullptr;
		}
		//int left_size = ranges::find(inorder, *(postorder.end() - 1)) - inorder.begin();
		int left_size = find(inorder.begin(), inorder.end(), postorder.back()) - inorder.begin();
		vector<int> in1(inorder.begin(), inorder.begin() + left_size);
		vector<int> in2(inorder.begin() + left_size + 1, inorder.end());
		vector<int> post1(postorder.begin(), postorder.begin() + left_size);
		vector<int> post2(postorder.begin() + left_size, postorder.end() - 1);

		TreeNode* left = buildTree(in1, post1);
		TreeNode* right = buildTree(in2, post2);


		return new TreeNode(*(postorder.end() - 1), left, right);
	}
};

//114. flatten-binary-tree-to-linked-list
// https://leetcode-cn.com/problems/flatten-binary-tree-to-linked-list/

class Solution_114 {
	using TN = TreeNode;
private:
	TN* head = nullptr;
	
public:
	void flatten(TN* root) {
		if (root == nullptr) return;
		flatten(root->right);
		flatten(root->left);
		
		root->left = nullptr;
		root->right = head;
		head = root;
	}
};


//112. path-sum
//https://leetcode.cn/problems/path-sum/

class Solution_112 {
public:
	bool hasPathSum(TreeNode* root, int sum) {
		if (root == nullptr) return false;
		if (root->left == nullptr && root->right == nullptr) { return sum == root->val; }
		return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
	}
};


//129. sum-root-to-leaf-numbers
//https://leetcode-cn.com/problems/sum-root-to-leaf-numbers/
class Solution_129 //DFS 无返回值
{
	int ans = 0;
public:
	int sumNumbers(TreeNode* root) {
		dfs(root, 0);
		return ans;
	}
private:
	void dfs(TreeNode* root, int cursum)
	{
		if (root == nullptr) return;
		if (root->right == nullptr && root->left == nullptr)
		{
			ans += (cursum + root->val);
			return;
		}
		dfs(root->right, (cursum + root->val) * 10);
		dfs(root->left, (cursum + root->val) * 10);
	}
};

class Solution_129_2 //DFS 有返回值
{
public:
	int sumNumbers(TreeNode* root) {
		return dfs(root, 0);
	}
private:
	int dfs(TreeNode* root, int cursum)
	{
		if (root == nullptr) return 0;
		if (root->right == nullptr && root->left == nullptr)
		{
			return cursum + root->val;
		}
		return dfs(root->right, (cursum + root->val) * 10) + dfs(root->left, (cursum + root->val) * 10);
	}
};



//124. binary-tree-maximum-path-sum
//https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/

class Solution {
public:

	int maxPathSum(TreeNode* root) {
		int ans = INT_MIN;
		dfs(root, ans);
		return ans;
	}
private:
	int dfs(TreeNode* node, int& ans) {
		if (node == nullptr) { return 0; }
		int l_val = dfs(node->left, ans);
		int r_val = dfs(node->right, ans);
		ans = max(ans, l_val + r_val + node->val);
		return max(max(l_val, r_val) + node->val, 0);
	}
};

//222. 完全二叉树的节点个数
//https://leetcode-cn.com/problems/count-complete-tree-nodes/


class Solution_222 {
	int countNodes(TreeNode* root) {
		if (root == nullptr) return 0;
		return countNodes(root->right) + countNodes(root->left) + 1;
	}
};

//class Solution_222_2 {
//public:
//	int countNodes(TreeNode* root) {
//		if (root == nullptr) return 0;
//		
//		int pos = 0;
//		queue<TreeNode*> q;
//		TreeNode* p;
//
//		q.push(root);
//
//		while (!q.empty())
//		{
//			p = q.front();q.pop();
//			pos++;
//			if (!p->left && !p->right) {
//				return pos * 2 - 1;
//			}
//			else if (p->left && !p->right) {
//				return pos * 2;
//			}
//			q.push(p->left);
//			q.push(p->right);
//		}
//		return 0;
//	}
//};


//236. 二叉树的最近公共祖先
//https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/
class Solution_236
{
	using TN = TreeNode;
	TN* lowestCommonAncestor(TN* root, TN* p, TN* q)
	{
		if (root == nullptr || root == p || root == q)
		{
			return root;
		}
		TN* left = lowestCommonAncestor(root->left, p, q);
		TN* right = lowestCommonAncestor(root->right, p, q);
		if (left && right) return root;
		return left ? left : right;
	}
};

//199. binary-tree-right-side-view
//https://leetcode.cn/problems/binary-tree-right-side-view/
class Solution_199
{
public:
	vector<int> rightSideView(TreeNode* root) {
		vector<int> ans;
		if (root == nullptr)
			return ans;
		queue<TreeNode*> q;
		TreeNode* p;
		q.push(root);

		while (!q.empty())
		{
			int len = q.size();
			for (size_t i = 0; i < len; ++i)
			{
				p = q.front(); q.pop();
				if (i == len - 1)
					ans.push_back(p->val);
				if (p->left) q.push(p->left);
				if (p->right) q.push(p->right);
			}
		}
		return ans;
	}
};

//637.average-of-levels-in-binary-tree
//https://leetcode.cn/problems/average-of-levels-in-binary-tree/
class Solution_637
{
public:
	vector<double> averageOfLevels(TreeNode * root) {
		queue<TreeNode*> q;
		TreeNode* p;
		q.push(root);
		vector<double> ans;
		while (!q.empty())
		{
			int len = q.size();
			double curlayer = 0;
			for (int i = 0; i < len; ++i)
			{
				p = q.front(); q.pop();
				curlayer += p->val;
				if (p->left) q.push(p->left);
				if (p->right) q.push(p->right);
			}
			ans.push_back(curlayer / len);
		}
		return ans;
	}
};

//102. binary-tree-level-order-traversal
//https://leetcode-cn.com/problems/binary-tree-level-order-traversal/
class Solution_102 {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int>> ans;
		if (!root) return ans;
		queue<TreeNode*> q;
		q.push(root);
		TreeNode* p;

		while (!q.empty())
		{
			int len = q.size();
			vector<int> layer;
			layer.reserve(len);
			for (int i = 0; i < len; ++i)
			{
				p = q.front(); q.pop();
				if (p->left) q.push(p->left);
				if (p->right) q.push(p->right);
				layer.push_back(p->val);
			}
			ans.emplace_back(layer);
		}
		return ans;
	}
};



//103. binary-tree-zigzag-level-order-traversal
//https://leetcode.cn/problems/binary-tree-zigzag-level-order-traversal/
class Solution_103
{
public:
	vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
		vector<vector<int>> res;
		if (root == nullptr) return res;

		queue<TreeNode*> q;
		q.push(root);
		TreeNode* p;
		int flag = 1;
		while (!q.empty())
		{
			int len = q.size();
			vector<int> ans;
			for (int i = 0; i < len; ++i)
			{
				p = q.front(); q.pop();
				if (p->left) q.push(p->left);
				if (p->right) q.push(p->right);
				ans.push_back(p->val);
			}
			if (flag == -1)
				reverse(ans.begin(), ans.end());
			res.emplace_back(ans);
			flag = -flag;
		}
		return res;
	}
};



//530. minimum-absolute-difference-in-bst
//https://leetcode.cn/problems/minimum-absolute-difference-in-bst/

class Solution_530
{
private:

	int res = INT_MAX;
	TreeNode* pre = nullptr;
	void dfs(TreeNode* cur)
	{
		if (cur == nullptr) return;

		dfs(cur->left);
		if (pre != nullptr) res = min(res, cur->val - pre->val);
		pre = cur;
		dfs(cur->right);
	}
public:
	int getMinimumDifference(TreeNode* root) {
		dfs(root);
		return res;

	}
};

class Solution_530_2
{
private:
	vector<int> vec;
	void dfs(TreeNode* root)
	{
		if (root == nullptr) return;

		dfs(root->left);
		vec.emplace_back(root->val);
		dfs(root->right);
	}
public:
	int getMinimumDifference(TreeNode* root) {
		vec.clear();
		dfs(root);
		if (vec.size() < 2) return 0;
		int result = INT_MAX;

		for (size_t i = 1; i < vec.size(); ++i)
		{
			result = min(result, vec[i] - vec[i - 1]);
		}
		return result;
	}
};

//230. kth-smallest-element-in-a-bst
//https://leetcode-cn.com/problems/kth-smallest-element-in-a-bst/

class Solution_230
{
private:
	int counter = 1;
	TreeNode* pre;
	int flag = 0;
	int ans;
	void dfs(TreeNode* cur, int k)
	{
		if (cur == nullptr || flag == 1)
			return;
		dfs(cur->left, k);
		if (cur != nullptr)
		{
			if (counter == k) { flag = 1; ans = cur->val; }
			counter++;
		}
		dfs(cur->right, k);
	}

public:
	int kthSmallest(TreeNode* root, int k) {
		ans = root->val;
		dfs(root, k);
		return ans;
	}

};

class Solution_230_2
{
public:
	int kthSmallest(TreeNode* root, int k) {
		auto dfs = [&](auto&& dfs, TreeNode* node)->int {
			if (node == nullptr)
				return -1;
			int left_res = dfs(dfs, node->left);
			if (left_res != -1) return left_res;
			if (--k == 0) return node->val;
			return dfs(dfs, node->right);
			};
		return dfs(dfs, root);
	}
};

//98. validate-binary-search-tree
//https://leetcode-cn.com/problems/validate-binary-search-tree/
class Solution_98 //中序遍历：顺序检查相邻节点大小关系
{
public:
	TreeNode* pre = nullptr;
	bool isValidBST(TreeNode* root) {
		if (root == nullptr) return true;

		if (!isValidBST(root->left)) return false;
		if (pre != nullptr) { if (pre->val >= root->val) return false; }
		pre = root;
		if (!isValidBST(root->right)) return false;

		return true;
	}
};

//108. convert-sorted-array-to-binary-search-tree
//https://leetcode-cn.com/problems/convert-sorted-array-to-binary-search-tree/

class Solution_108 {
private:
	TreeNode* dfs(vector<int>& nums, int left, int right)
	{
		if (left == right) return nullptr;
		int m = left + (right - left) / 2;
		return new TreeNode(nums[m], dfs(nums, left, m), dfs(nums, m + 1, right));
	}

public:
	TreeNode* sortedArrayToBST(vector<int>& nums) {
		return dfs(nums, 0, nums.size());
	}
};

//23. merge-k-sorted-lists
//https://leetcode-cn.com/problems/merge-k-sorted-lists/


class Solution_23 {
	using LN = ListNode;
public:
	ListNode* mergeKLists(vector<ListNode*>& lists) {

		auto mycompare = [](const LN* a, const LN* b) {return a->val > b->val; };
		priority_queue<LN*, vector<LN*>, decltype(mycompare)> pq;
		for (auto head : lists)
		{
			if (head)//记得，这里来给输入判空
				pq.push(head);
		}
		LN* dum = new LN(-1);
		LN* cur = dum;
		while (!pq.empty())
		{
			auto p = pq.top(); pq.pop();
			if (p->next) pq.push(p->next);
			cur->next = p;
			cur = cur->next;
		}
		return dum->next;
	}
};


//53. maximum-subarray
//https://leetcode.cn/problems/maximum-subarray
class Solution_53 //前缀和
{
	int ans = INT_MIN;
	int min_presum = 0;
	int presum = 0;
	for (int x : nums)
	{
		presum += x;
		ans = max(ans, presum - min_presum);
		min_presum = min(min_presum, presum);
	}
	return ans;
};

class Solution_53_2//DP
{
public:
	int maxSubArray(vector<int>& nums) {
		vector<int> f(nums.size());
		f[0] = nums[0];
		int ans = f[0];
		for (int i = 1; i < nums.size(); ++i)
		{

			f[i] = max(f[i - 1], 0) + nums[i];
			ans = max(ans, f[i]);
		}
		return ans;
	}

};

class Solution_53_2_1//DP 用max_element或者ranges::max()
{
public:
	int maxSubArray(vector<int>& nums) {
		vector<int> f(nums.size());
		f[0] = nums[0];
		for (int i = 1; i < nums.size(); ++i)
		{
			f[i] = max(f[i - 1], 0) + nums[i];
		}
		return *max_element(f.begin(), f.end());
		//return ranges::max(f);
	}
};



//918. maximum-sum-circular-subarray
//https://leetcode.cn/problems/maximum-sum-circular-subarray/
class Solution_918 {
public:
	int maxSubarraySumCircular(vector<int>& nums) {
		int max_s = INT_MIN;
		int min_s = INT_MAX;
		
		int max_f = 0, min_f = 0;
		int sum = 0;
		
		for (int x : nums)
		{
			sum += x;
			max_f = max(max_f, 0) + x;
			max_s = max(max_s, max_f);

			min_f = min(min_f, 0) + x;
			min_s = min(min_s, min_f);
		}
		return min_s == sum ? max_s : max(max_s, sum - min_s);

	}
};

//35. search-insert-position
//https://leetcode.cn/problems/search-insert-position/
class Solution_35
{
public:
	int searchInsert(vector<int>& nums, int target) {
		int l = 0, r = nums.size();
		while (l < r)
		{
			int mid = ((r - l) >> 1) + l;
			if (target <= nums[mid]) r = mid;
			else l = mid + 1;
		}
		return r;
	}
};

//74. search-a-2d-matrix
//https://leetcode-cn.com/problems/search-a-2d-matrix/

class Solution_74 {
public:
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		int m = matrix.size(), n = matrix[0].size();
		int left = 0, right = m * n - 1;
		while (left < right) {
			int mid = ((right - left) >> 1) + left;
			int x = matrix[mid / n][mid % n];
			if (target <= x)
			{
				right = mid;
			}
			else
			{
				left = mid + 1;
			}
		}
		if (matrix[right / n][right % n] == target)
			return true;
		return false;
	}
};


//33. search-in-rotated-sorted-array
//https://leetcode.cn/problems/search-in-rotated-sorted-array/

class Solution_33
{

	int binarySearchforMin(const vector<int>& nums) {
		int l = 0, r = nums.size() - 1;
		while (l < r) {
			int mid = (r - l >> 1) + l;
			if (nums[mid] < nums.back()) {
				r = mid;
			}
			else
				l = mid + 1;
		}
		return r;
	}

	int binarySearch(const vector<int>& nums, int left, int right, int target) {
		while (left < right)
		{
			int mid = (right - left >> 1) + left;
			if (target <= nums[mid])
				right = mid;
			else
				left = mid + 1;
		}
		return right;
	}
public:

	int search(vector<int>& nums, int target) {
		int minimum_idx = binarySearchforMin(nums);
		int ans = -1;
		if (target > nums.back()) {
			ans = binarySearch(nums, 0, minimum_idx - 1, target);
		}
		else {
			ans = binarySearch(nums, minimum_idx, nums.size() - 1, target);
		}
		return (ans < 0 || ans >= nums.size() || nums[ans] != target) ? -1
			: ans;
	}
};


//153. find-minimum-in-rotated-sorted-array
//https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array/
class Solution_153
{
public:
	int findMin(vector<int>& nums)
	{
		int l = 0, r = nums.size() - 1;
		while (l < r) {
			int mid = (r - l >> 1) + l;
			if (nums[mid] < nums.back()) // 元素互不相同，所以这里 < 等价于 <=
			{
				r = mid;
			}
			else {
				l = mid + 1;
			}
		}
		return nums[r];
	}
};

//34. find-first-and-last-position-of-element-in-sorted-array
//https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/
class Solution_34
{
public:
	vector<int> searchRange(vector<int>& nums, int target) {
		vector<int> ans;
		int start = binarySearch(nums, target);
		if (start<0 || start>nums.size() - 1 || nums[start] != target)
			return { -1,-1 };

		for (int i = start; i < nums.size() && nums[i] == target; ++i)
		{
			ans.push_back(i);
		}
		return { ans.front(),ans.back() };
	}

private:
	int binarySearch(vector<int>& nums, int target) {
		int left = 0, right = nums.size() - 1;

		while (left < right) {
			int mid = ((right - left) >> 1) + left;
			if (target <= nums[mid])
				right = mid;
			else
				left = mid + 1;
		}
		return right;
	}
};

//66. plus-one
//https://leetcode-cn.com/problems/plus-one/

class Solution_66
{
public:
	vector<int> plusOne(vector<int>& digits) {
		for (int i = digits.size() - 1; i >= 0; --i)
		{
			digits[i]++;
			if (digits[i] == 10)
				digits[i] = 0;
			else return digits;
		}
		digits.insert(digits.begin(), 1);
		return digits;
	}
};


//172. factorial-trailing-zeroes
// https://leetcode.cn/problems/factorial-trailing-zeroes/
class Solution_172
{
	int trailing - zeroes(int n)
	{
		while (n)
		{
			n /= n;
			ans += n;
		}
		return ans;
	}
};


//69. sqrtx
//https://leetcode-cn.com/problems/sqrtx/
class Solution_69 {
public:
	int mySqrt(int x) {
		int l = 0, r = x;
		while (l < r) {
			int mid = ((l - r + 1) >> 1) + r;
			if (x >= (long)mid * mid)
			{
				l = mid;
			}
			else
			{
				r = mid - 1;
			}
		}
		return r;
	}
};

//50. powx-n
//https://leetcode-cn.com/problems/powx-n/
class Solution_50 
{
public:
	double myPow(double x, int n) {
		double ans = 1;
		long long cur = n;
		if (n < 0)
		{
			n = -n;
			x = 1 / x;
		}
		while (n)
		{
			if (n & 1) ans *= x;
			x *= x;
			n >>= 1;
		}
		return ans;
	}
};

//149. max-points-on-a-line
//https://leetcode-cn.com/problems/max-points-on-a-line/














////Solution_12
//int main() {
//	Solution_12 solution;
//	string a= solution.intToRoman(6666);
//	cout << a << endl;
//}




////Solution_238
//int main() {
//	vector<int> input = { 2 };
//	Solution_238 solution;
//	vector<int> a = solution.productExceptSelf(input);
//	for (auto b : a)
//	{
//		cout << b << " ";
//	}
//	cout << endl;
//}



////Solution_45
//int main() {
//	vector<int> input={ 1,2,5,22,1,1,1,1,1,1,1,1 };
//	Solution_45_2 solution;
//	cout << solution.jump(input) << endl;
//}


/*
int main() {
	vector<int> nums1, nums2;
	int m, n;
	string nums1s, nums2s;
	getline(cin, nums1s, '\n');
	stringstream ss(nums1s);
	int tmp;
	while (ss >> tmp)
	{
		nums1.emplace_back(tmp);
	}
	cin >> m;
	getline(cin, nums2s, '\n');
	stringstream ss2(nums2s);
	while (ss2 >> tmp)
	{
		nums2.emplace_back(tmp);
	}
	cin >> n;


	for (int a : nums1) {
		cout << a << " ";
	}
	cout << "--";
	return 0;
}
*/

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

























// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, 
// or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, 
// go to File > Open > Project and select the .sln file
