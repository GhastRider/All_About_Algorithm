#include<iostream>
#include<vector>
#include<climits>
#include<stack>

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
f