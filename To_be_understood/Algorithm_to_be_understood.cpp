#include<iostream>
#include<vector>
#include<climits>
#include<stack>
#include<unordered_map>

using namespace std;

//42.接雨水 单调栈解法
class Solution_42_2 // monotonic stack
{
public:
	int trap(vector<int>& height) {
		int ans = 0;
		stack<int> st;
		for (int i = 0; i < height.size(); ++i)  // 用i遍历height的大小
		{
			while (!st.empty() && height[st.top()] < height[i]) { //栈不为空，且栈顶height的下标小于当前遍历的height时
				int cur = st.top(); //栈顶元素存为当前
				st.pop();  // 栈顶元素弹出栈
				if (st.empty()) break;  // 如果弹完为空，跳出while 
				int l = st.top(); // 左等于栈顶height下标
				int r = i;	//右等于当前遍历的height[i]下标
				int h = min(height[r], height[l]) - height[cur];
				ans += (r - l - 1) * h; // 
			}
			st.push(i);
		}
		return ans;
	}
};




//28. find-the-index-of-the-first-occurrence-in-a-string
//https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/
//the Legendary KMP -unfinished
//KMP: 匹配成功的部分中存在相同的【前缀】和【后缀】, 
//so, 不需要从头匹配，可以将匹配串指针移至【前缀】下一个位置继续匹配
//===========================================================

//#include <iostream>
//#include <string>
//#include <vector>
class Solution_28 {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) return 0;  // 边界条件，空模式串返回0

        vector<int> next(needle.size(), 0);
        buildNextArray(needle, next);  // 构建 next 数组

        int i = 0, j = 0;
        while (i < haystack.size()) {
            if (j == -1 || haystack[i] == needle[j]) {
                i++;
                j++;
            }
            else {
                j = next[j];  // 根据 next 数组调整模式串指针
            }

            // 如果完全匹配，返回匹配的起始位置
            if (j == needle.size()) {
                return i - j;
            }
        }

        return -1;  // 如果没有匹配到，返回 -1
    }

private:
    void buildNextArray(const string& p, vector<int>& next) {
        int j = -1;
        next[0] = -1;
        for (int i = 1; i < p.size(); ++i) {
            while (j >= 0 && p[i] != p[j + 1]) {
                j = next[j];  // 回退
            }
            if (p[i] == p[j + 1]) {
                j++;
            }
            next[i] = j;
        }
    }
};

//int main() {
//    Solution_28 solution;
//    string haystack = "hello";
//    string needle = "ll";
//    cout << solution.strStr(haystack, needle) << endl;  // 输出 2
//    return 0;
//}





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
		int spaceAvg = (wordCount == 1) ? 1 : spaceCount / (wordCount - 1);
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




//30. substring with concatenation of all words
//https://leetcode.cn/problems/substring-with-concatenation-of-all-words/

//#include<unordered_map>
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


//20. valid-parentheses
//https://leetcode.cn/problems/valid-parentheses/

class Solution  //栈
{
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


//21. merge-two-sorted-lists
//https://leetcode-cn.com/problems/merge-two-sorted-lists/

struct ListNode {
	int val;
	ListNode* next;

	//ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
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
		else if (l2 == nullptr) {
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
