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


int minDepth(TreeNode* root) {
    if(root == nullptr){
        return 0;
    }
    if(root->left == nullptr){
        return minDepth(root->right) + 1;
    }
    if(root->right == nullptr){
        return minDepth(root->left) + 1;
    }
    int lh = minDepth(root->left);
    int rh = minDepth(root->right);
    return lh < rh ? lh + 1 : rh + 1;
}

/*---------------------------- 测试 ----------------------------*/
int main(){
    cout << "空树            : " << minDepth(nullptr)          << "  (期望 0)" << endl;
    cout << "单结点          : " << minDepth(new TreeNode(1)) << "  (期望 1)" << endl;

    // 单支树：1 只有右孩子 2，2 只有右孩子 3  →  最小深度 3（路径不能在半路断）
    TreeNode* chain = new TreeNode(1, nullptr,
                        new TreeNode(2, nullptr,
                          new TreeNode(3)));
    cout << "单支链(3层)     : " << minDepth(chain) << "  (期望 3)" << endl;

    // ⚠️ 反例：1 的左为空、右只有一层
    //    直接写 min(lh,rh)+1 会得到 1（错），正确是 2
    TreeNode* trap = new TreeNode(1, nullptr, new TreeNode(2));
    cout << "左空右一层      : " << minDepth(trap)  << "  (期望 2；直接 min 会得 1)" << endl;

    // 两个孩子都在，且都是叶子  →  最小深度 2
    TreeNode* t = new TreeNode(1, new TreeNode(2), new TreeNode(3));
    cout << "两孩子都是叶子  : " << minDepth(t)     << "  (期望 2)" << endl;

    return 0;
}
