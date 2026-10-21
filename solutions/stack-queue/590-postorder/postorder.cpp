#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// N叉树结点定义
class Node {
public:
    int val;
    vector<Node*> children;
    Node() {}
    Node(int _val) {
        val = _val;
    }
    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

// 后序遍历函数，不再放在类里面
vector<int> postorder(Node* root) {
    vector<int> res;
    if (root == nullptr) {
        return res;
    }
    stack<Node*> st;
    st.push(root);
    while (!st.empty()) {
        Node* p = st.top();
        st.pop();
        res.push_back(p->val);
        // 普通下标for循环
        for (int i = 0; i < p->children.size(); i++) {
            st.push(p->children[i]);
        }
    }
    reverse(res.begin(), res.end());
    return res;
}

void printVec(const vector<int>& v) {
    for (int x : v) cout << x << " ";
    cout << endl;
}

// 测试main函数（可选）
int main()
{
    // 构造样例树：1，孩子3,2,4；3的孩子5,6
    Node* node5 = new Node(5);
    Node* node6 = new Node(6);
    Node* node3 = new Node(3, {node5, node6});
    Node* node2 = new Node(2);
    Node* node4 = new Node(4);
    Node* root = new Node(1, {node3, node2, node4});

    cout << "示例  : "; printVec(postorder(root));         // 期望 5 6 3 2 4 1
    cout << "空树  : "; printVec(postorder(nullptr));       // 期望 空
    cout << "单结点: "; printVec(postorder(new Node(7)));   // 期望 7
    return 0;
}
