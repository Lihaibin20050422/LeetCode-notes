#include <iostream>
#include <vector>
using namespace std;

int search(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            return mid;
        }
        if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    vector<int> a = {1,3,5,7,9};
    cout << "[1,3,5,7,9] 找 5  -> " << search(a,5)  << "  (期望 2)"  << endl;
    cout << "[1,3,5,7,9] 找 1  -> " << search(a,1)  << "  (期望 0)"  << endl;
    cout << "[1,3,5,7,9] 找 9  -> " << search(a,9)  << "  (期望 4)"  << endl;
    cout << "[1,3,5,7,9] 找 2  -> " << search(a,2)  << "  (期望 -1)" << endl;
    cout << "[1,3,5,7,9] 找 10 -> " << search(a,10) << "  (期望 -1)" << endl;

    vector<int> b = {5};
    cout << "[5] 找 5          -> " << search(b,5) << "  (期望 0)"  << endl;
    cout << "[5] 找 1          -> " << search(b,1) << "  (期望 -1)" << endl;

    vector<int> c = {};
    cout << "[]  找 5           -> " << search(c,5) << "  (期望 -1，空数组)" << endl;

    return 0;
}
