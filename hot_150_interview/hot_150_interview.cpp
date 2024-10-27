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


#include<functional>

using namespace std;

struct ListNode {
	int value;
	ListNode* next;

	//constructor:
	// : 构造函数初始化列表
	ListNode() : value(0), next(nullptr) {}
	ListNode(int x) : value(x), next(nullptr) {}
	ListNode(int x, ListNode* nextnode) :value(x), next(nextnode) {}

};
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};


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
			result = max(result, prices[i] - buyin);//更新前i天的最高利润：i-1天最高利润和第i天卖出最高利润price
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
			if (ratings[i] > ratings[i + 1] && !(result[i] > result[i + 1])) result[i] = result[i + 1] + 1;
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


class Solution_12
{
public:
	//这样做是错的弹性数组是没法作为类成员推断大小的 
	//int a[] = { 1, 2, 3, 4, 5 }; //an initializer cannot be specified for a flexible array member
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

const pair<int, string> Solution_12::map[] = {
{1000,"M"},{900,"CM"},
{500,"D"}, {400,"CD"},
{100,"C"}, {90,"XC"},
{50,"L"},  {40,"XL"},
{10,"X"},  {9,"IX"},
{5,"V"},   {4,"IV"},
{1,"I"},
};

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
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
