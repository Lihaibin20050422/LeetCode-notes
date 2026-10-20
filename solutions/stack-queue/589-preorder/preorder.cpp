#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct Node {
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

vector<int> preorder(Node* root) {
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
        // 逆序压入孩子，保证出栈顺序从左到右
        for (int i = p->children.size() - 1; i >= 0; --i) {
            st.push(p->children[i]);
        }
    }
    return res;
}

void printVec(const vector<int>& v){
    for (int x : v) cout << x << " ";
    cout << endl;
}

int main() {
    // 示例：1 -> [3,2,4]，其中 3 -> [5,6]
    Node* n1 = new Node(3, {new Node(5), new Node(6)});
    Node* n2 = new Node(2);
    Node* n3 = new Node(4);
    Node* root = new Node(1, {n1, n2, n3});

    cout << "示例  : "; printVec(preorder(root));         // 期望 1 3 5 6 2 4
    cout << "空树  : "; printVec(preorder(nullptr));       // 期望 空
    cout << "单结点: "; printVec(preorder(new Node(7)));   // 期望 7

    return 0;
}
