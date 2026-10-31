#include <iostream>
#include <vector>
using namespace std;

int search(vector<int>& nums, int target) {
    int left = 0;
    int right = static_cast<int>(nums.size()) - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            return mid;
        }
        if (nums[left] <= nums[mid]) {
            if (target >= nums[left] && target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else {
            if (target > nums[mid] && target <= nums[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return -1;
}

void show(vector<int>& nums, int target, int expect) {
    cout << "  target=" << target << " -> " << search(nums, target)
         << "   (期望 " << expect << ")" << endl;
}

int main()
{
    vector<int> a = {4,5,6,7,0,1,2};
    cout << "nums = [4,5,6,7,0,1,2]" << endl;
    show(a, 0, 4);
    show(a, 4, 0);
    show(a, 2, 6);
    show(a, 3, -1);
    show(a, 8, -1);

    vector<int> b = {1,2,3,4,5};
    cout << "\nnums = [1,2,3,4,5]（未旋转）" << endl;
    show(b, 3, 2);
    show(b, 6, -1);

    vector<int> c = {1};
    cout << "\nnums = [1]" << endl;
    show(c, 1, 0);
    show(c, 0, -1);

    vector<int> d = {1,3};
    cout << "\nnums = [1,3]" << endl;
    show(d, 3, 1);
    show(d, 1, 0);

    vector<int> e = {};
    cout << "\nnums = []" << endl;
    show(e, 5, -1);

    return 0;
}
