#include <algorithm>
#include <vector>
using namespace std;
class Solution
{
public:
    int solve(vector<int> &nums)
    {
        // Step 1: Sort the array
        sort(nums.begin(), nums.end());

        int n = nums.size();
        int left = 0;
        int max_len = 0;

        // Step 2: Sliding Window
        for (int right = 0; right < n; right++)
        {
            // While the difference is too big, shrink from the left
            while (nums[right] - nums[left] > 10)
            {
                left++;
            }
            // Update maximum length found
            max_len = max(max_len, right - left + 1);
        }

        return max_len;
    }
};
