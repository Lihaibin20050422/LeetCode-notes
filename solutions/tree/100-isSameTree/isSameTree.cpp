#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

bool isSameTree(TreeNode* p, TreeNode* q) {
    if(p == nullptr && q == nullptr){
        return true;
    }
    if(p == nullptr || q == nullptr){
        return false;
    }
    if(p->val != q->val){
        return false;
    }
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

/*---------------------------- 测试 ----------------------------*/
int main(){
    // t1: 1 的左孩子 2、右孩子 3
    TreeNode* t1 = new TreeNode(1, new TreeNode(2), new TreeNode(3));
    // t2: 和 t1 结构、值完全相同
    TreeNode* t2 = new TreeNode(1, new TreeNode(2), new TreeNode(3));
    // t3: 和 t1 相比左右孩子交换了
    TreeNode* t3 = new TreeNode(1, new TreeNode(3), new TreeNode(2));
    // t4: 只有左孩子 2
    TreeNode* t4 = new TreeNode(1, new TreeNode(2), nullptr);

    cout << "相同两棵树      : " << isSameTree(t1,t2)      << "  (期望 1)" << endl;
    cout << "左右孩子交换    : " << isSameTree(t1,t3)      << "  (期望 0)" << endl;
    cout << "一棵多一个结点  : " << isSameTree(t1,t4)      << "  (期望 0)" << endl;
    cout << "都是空树        : " << isSameTree(nullptr,nullptr) << "  (期望 1)" << endl;
    cout << "一空一非空      : " << isSameTree(t1,nullptr) << "  (期望 0)" << endl;

    return 0;
}
