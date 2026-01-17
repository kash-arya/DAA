class Solution {
public:
    // Helper Function: Finds the maximum sum that strictly crosses the midpoint.
    // We MUST include elements touching 'mid' and 'mid+1' for continuity.
    int maxCrossingSum(vector<int>& arr, int low, int mid, int high) {
        
        // 1. Left Part: Start from 'mid' and move backwards to 'low'
        // We go backwards because the subarray must be contiguous and connected to 'mid'.
        int sum = 0;
        int left_sum = INT_MIN;
        for (int i = mid; i >= low; i--) {
            sum += arr[i];
            if (sum > left_sum)
                left_sum = sum;
        }

        // 2. Right Part: Start from 'mid + 1' and move forwards to 'high'
        // We go forwards to connect to the right side of the split.
        sum = 0;
        int right_sum = INT_MIN;
        for (int i = mid + 1; i <= high; i++) {
            sum += arr[i];
            if (sum > right_sum)
                right_sum = sum;
        }

        // 3. Combine: The crossing max is simply the best left-side connected sum 
        // plus the best right-side connected sum.
        return left_sum + right_sum;
    }

    // Main Recursive Function
    int divide(vector<int>& arr, int low, int high) {
        // Base Case: Only one element left, so it is the maximum by itself.
        if (low == high)
            return arr[low]; 

        int mid = (low + high) / 2;

        // Recursion Step:
        // Option A: Max subarray is entirely in the Left half
        int leftMax = divide(arr, low, mid);
        
        // Option B: Max subarray is entirely in the Right half
        int rightMax = divide(arr, mid + 1, high);

        // Option C: Max subarray crosses the middle (handled by helper)
        int crossMax = maxCrossingSum(arr, low, mid, high);

        // Final Answer: Return the largest of the three possibilities
        return max({leftMax, rightMax, crossMax});
    }

    int maxSubArray(vector<int>& nums) {
        return divide(nums, 0, nums.size() - 1);
    }
};
