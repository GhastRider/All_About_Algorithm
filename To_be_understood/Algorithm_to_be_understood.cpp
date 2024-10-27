#include<iostream>
#include<vector>
#include<climits>
#include<stack>

using namespace std;

//42.����ˮ ����ջ�ⷨ
class Solution_42_2 // monotonic stack
{
public:
	int trap(vector<int>& height) {
		int ans = 0;
		stack<int> st;
		for (int i = 0; i < height.size(); ++i)  // ��i����height�Ĵ�С
		{
			while (!st.empty() && height[st.top()] < height[i]) { //ջ��Ϊ�գ���ջ��height���±�С�ڵ�ǰ������heightʱ
				int cur = st.top(); //ջ��Ԫ�ش�Ϊ��ǰ
				st.pop();  // ջ��Ԫ�ص���ջ
				if (st.empty()) break;  // �������Ϊ�գ�����while 
				int l = st.top(); // �����ջ��height�±�
				int r = i;	//�ҵ��ڵ�ǰ������height[i]�±�
				int h = min(height[r], height[l]) - height[cur];
				ans += (r - l - 1) * h; // 
			}
			st.push(i);
		}
		return ans;
	}
};
f