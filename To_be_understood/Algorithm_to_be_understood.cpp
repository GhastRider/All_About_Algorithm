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




//28. find-the-index-of-the-first-occurrence-in-a-string
//https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/
//the Legendary KMP -unfinished
//KMP: ƥ��ɹ��Ĳ����д�����ͬ�ġ�ǰ׺���͡���׺��, 
//so, ����Ҫ��ͷƥ�䣬���Խ�ƥ�䴮ָ��������ǰ׺����һ��λ�ü���ƥ��
//===========================================================

//#include <iostream>
//#include <string>
//#include <vector>
class Solution_28 {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) return 0;  // �߽���������ģʽ������0

        vector<int> next(needle.size(), 0);
        buildNextArray(needle, next);  // ���� next ����

        int i = 0, j = 0;
        while (i < haystack.size()) {
            if (j == -1 || haystack[i] == needle[j]) {
                i++;
                j++;
            }
            else {
                j = next[j];  // ���� next �������ģʽ��ָ��
            }

            // �����ȫƥ�䣬����ƥ�����ʼλ��
            if (j == needle.size()) {
                return i - j;
            }
        }

        return -1;  // ���û��ƥ�䵽������ -1
    }

private:
    void buildNextArray(const string& p, vector<int>& next) {
        int j = -1;
        next[0] = -1;
        for (int i = 1; i < p.size(); ++i) {
            while (j >= 0 && p[i] != p[j + 1]) {
                j = next[j];  // ����
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
//    cout << solution.strStr(haystack, needle) << endl;  // ��� 2
//    return 0;
//}





//68. text-justification
//https://leetcode.cn/problems/text-justification/solutions/181651/text-justification-by-ikaruga/

class Solution_68 //lkaruga���
{
private:
	string fillWords(vector<string>& words, int bg, int ed, int maxWidth, bool lastLine = false)
	{
		int wordCount = ed - bg + 1;
		int spaceCount = maxWidth - (-1 + wordCount);

		//����ո�����=�ܳ���-�����ո�����-���ʳ��ȡ�

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
