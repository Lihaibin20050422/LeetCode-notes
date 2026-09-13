/*
给你两个按非递减顺序排列的整数数组 nums1 和 nums2，另有两个整数 m 和 n，分别表示 nums1 和 nums2 中的元素数目。
请你合并 nums2 到 nums1 中，使合并后的数组同样按非递减顺序排列。
注意：最终，合并后数组不应由函数返回，而是存储在数组 nums1 中。为了应对这种情况，nums1 的初始长度为 m + n，其中前 m 个元素表示应合并的元素，后 n 个元素为 0，应忽略。nums2 的长度为 n。

示例 1：
输入：nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
输出：[1,2,2,3,5,6]
*/

#include<iostream>
#include<vector>
using namespace std;
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m-1;
    int j = n-1;
    int k = m+n-1;
    while(i>=0&&j>=0){
        if(nums1[i]>nums2[j]){
            nums1[k] = nums1[i];
            i--;
        }else{
            nums1[k] = nums2[j];
            j--;
        }
        k--;
    }
    while (j >= 0) {
        nums1[k] = nums2[j];
        j--;
        k--;
    }
}

int main(){
    int m;
    int n;
    cin >> m >> n;
    vector<int> nums1(m+n);
    vector<int> nums2(n);
    for(int i = 0;i<m;i++){
        cin >> nums1[i];
    }
    for(int i = 0;i<n;i++){
        cin >> nums2[i];
    }
    merge(nums1,m,nums2,n);
    for(int i = 0;i<m+n;i++){
        cout << nums1[i]<< ' ';
    }
    return 0;
}
