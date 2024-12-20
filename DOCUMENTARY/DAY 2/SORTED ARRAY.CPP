#include <iostream>
#include <vector>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return buildBST(nums, 0, nums.size() - 1);
    }

private:
    TreeNode* buildBST(const vector<int>& nums, int left, int right) {
        if (left > right) {
            return nullptr; // Base case: no elements to form a tree
        }

        int mid = left + (right - left) / 2; // Find the middle index
        TreeNode* root = new TreeNode(nums[mid]); // Create a node with the middle element

        // Recursively build the left and right subtrees
        root->left = buildBST(nums, left, mid - 1); // Left subarray
        root->right = buildBST(nums, mid + 1, right); // Right subarray

        return root;
    }
};

// Function to print the tree in pre-order for verification
void preOrder(TreeNode* node) {
    if (node == nullptr) {
        return;
    }
    cout << node->val << " ";
    preOrder(node->left);
    preOrder(node->right);
}

int main() {
    Solution solution;
    vector<int> nums = {-10, -3, 0, 5, 9};
    TreeNode* root = solution.sortedArrayToBST(nums);

    // Print the tree in pre-order
    preOrder(root); // Output: 0 -10 -3 5 9

    return 0;
}