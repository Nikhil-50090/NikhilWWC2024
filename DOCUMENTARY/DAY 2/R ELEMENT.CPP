#include <iostream>
#include <vector>

int removeDuplicates(std::vector<int>& nums) {
    if (nums.empty()) {
        return 0; // If the array is empty, return 0
    }

    // Pointer for the last unique element
    int i = 0;

    // Iterate through the array starting from the second element
    for (int j = 1; j < nums.size(); j++) {
        if (nums[j] != nums[i]) { // Found a new unique element
            i++; // Move the unique pointer
            nums[i] = nums[j]; // Update the position with the new unique element
        }
    }

    // The number of unique elements is i + 1
    return i + 1;
}

int main() {
    std::vector<int> nums = {1, 1, 2, 2, 3, 4, 4};
    int uniqueCount = removeDuplicates(nums);
    
    std::cout << "Number of unique elements: " << uniqueCount << std::endl;
    std::cout << "Unique elements: ";
    for (int k = 0; k < uniqueCount; k++) {
        std::cout << nums[k] << " ";
    }
    std::cout << std::endl;

    return 0;
}