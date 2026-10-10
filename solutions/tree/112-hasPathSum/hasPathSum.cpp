#include <iostream>
using namespace std;

// 二叉树节点定义
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 解法一：累加（sum 记录"已经走了多少"，所以要辅助函数多传一个参数）
bool dfs(TreeNode* node,int sum,int targetSum){
    if(node==nullptr){
        return false;
    }
    sum+=node->val;
    if(node->left==nullptr&&node->right==nullptr){
        return sum==targetSum;
    }
    return dfs(node->left,sum,targetSum)||dfs(node->right,sum,targetSum);
}

bool hasPathSum(TreeNode* root, int targetSum) {
    return dfs(root,0,targetSum);
}

// 解法二：递减（targetSum 变成"还差多少"，参数自洽，不需要辅助函数）
bool hasPathSum2(TreeNode* root, int targetSum) {
    if(root == nullptr) return false;
    if(root->left == nullptr && root->right == nullptr)
        return root->val == targetSum;
    return hasPathSum2(root->left,  targetSum - root->val)
        || hasPathSum2(root->right, targetSum - root->val);
}

/*---------------------------- 测试 ----------------------------*/
int main(){
    // 测试树：5 的左孩子 4（4 的左孩子 11（左7、右2））
    //         5 的右孩子 8（8 的左孩子 13、右孩子 4（右孩子 1））
    // 四条根到叶的路径：5-4-11-7=27 / 5-4-11-2=22 / 5-8-13=26 / 5-8-4-1=18
    TreeNode* root = new TreeNode(5,
        new TreeNode(4,
            new TreeNode(11, new TreeNode(7), new TreeNode(2)),
            nullptr),
        new TreeNode(8,
            new TreeNode(13),
            new TreeNode(4, nullptr, new TreeNode(1))));

    cout << "target=22  : " << hasPathSum(root,22)  << "  (期望 1；5-4-11-2)"  << endl;
    cout << "target=27  : " << hasPathSum(root,27)  << "  (期望 1；5-4-11-7)"  << endl;
    cout << "target=26  : " << hasPathSum(root,26)  << "  (期望 1；5-8-13)"    << endl;
    cout << "target=18  : " << hasPathSum(root,18)  << "  (期望 1；5-8-4-1)"   << endl;
    cout << "target=100 : " << hasPathSum(root,100) << "  (期望 0)"           << endl;

    cout << "空树       : " << hasPathSum(nullptr,0) << "  (期望 0)"          << endl;
    cout << "单结点1/1  : " << hasPathSum(new TreeNode(1),1) << "  (期望 1)"  << endl;
    cout << "单结点1/2  : " << hasPathSum(new TreeNode(1),2) << "  (期望 0)"  << endl;

    cout << "--- 解法二对照 ---" << endl;
    cout << "target=22  : " << hasPathSum2(root,22)  << "  (期望 1)" << endl;
    cout << "target=100 : " << hasPathSum2(root,100) << "  (期望 0)" << endl;

    return 0;
}
