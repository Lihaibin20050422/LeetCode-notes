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

bool check(TreeNode* p, TreeNode* q)
{
    if (!p && !q)
    {
        return true;
    }
    if (!p || !q)
    {
        return false;
    }
    return (p->val == q->val) && check(p->left, q->right) && check(p->right, q->left);
}


bool isSymmetric(TreeNode* root)
{
    if(root == nullptr) return true;
    return check(root->left, root->right);
}

/*---------------------------- 测试 ----------------------------*/
int main(){
    // 对称树：1 的左孩子 2（左3右4）、右孩子 2（左4右3）
    TreeNode* s1 = new TreeNode(1,
        new TreeNode(2, new TreeNode(3), new TreeNode(4)),
        new TreeNode(2, new TreeNode(4), new TreeNode(3)));

    // 不对称：1 的左孩子 2（只有右孩子3）、右孩子 2（只有右孩子3）
    TreeNode* s2 = new TreeNode(1,
        new TreeNode(2, nullptr, new TreeNode(3)),
        new TreeNode(2, nullptr, new TreeNode(3)));

    // 反例：1 的左孩子 2（只有左孩子3）、右孩子 2（只有左孩子3）
    //       两者按"根左右 / 根右左"得到的序列都是 [2,3]，但这棵树不对称
    TreeNode* s3 = new TreeNode(1,
        new TreeNode(2, new TreeNode(3), nullptr),
        new TreeNode(2, new TreeNode(3), nullptr));

    cout << "对称树      : " << isSymmetric(s1)      << "  (期望 1)" << endl;
    cout << "右侧多一个  : " << isSymmetric(s2)      << "  (期望 0)" << endl;
    cout << "单孩子错位  : " << isSymmetric(s3)      << "  (期望 0)" << endl;
    cout << "空树        : " << isSymmetric(nullptr) << "  (期望 1)" << endl;
    cout << "单结点      : " << isSymmetric(new TreeNode(1)) << "  (期望 1)" << endl;

    return 0;
}
