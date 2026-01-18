#include<vector>
using namespace std;

class Solution {
public:
    // Helper: Checks if we can split the array into at most M segments
    // such that no segment's Bitwise OR exceeds 'limit'.
    bool canFit(vector<int>& arr, int M, int limit) {
        int segments = 1;
        int current_or = 0;

        for (int x : arr) {
            // If a single number exceeds the limit, it's impossible.
            if (x > limit) return false;

            // If adding 'x' keeps us within limit, extend current segment
            if ((current_or | x) <= limit) {
                current_or |= x;
            } else {
                // Otherwise, start a new segment
                segments++;
                current_or = x;
            }
        }
        return segments <= M;
    }

    int minimizeMaxOR(vector<int>& arr, int M) {
        int low = 0, high = (1 << 30) - 1; // Search range up to max 30-bit integer
        int ans = high;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (canFit(arr, M, mid)) {
                ans = mid;      // mid is feasible, try smaller to minimize
                high = mid - 1;
            } else {
                low = mid + 1;  // mid is too small, need larger limit
            }
        }
        return ans;
    }
};

/*
The choice of high = (1 << 30) - 1 is based on the properties of integer limits and Bitwise OR.
Here is the precise reasoning:
1. Bitwise OR Can't Exceed the Max Bits: If you take any number of integers and OR them together, the result can never have more bits set to 1 than the combined bits of all numbers. In standard algorithm problems, integers are usually 32-bit.
2. The "Worst Case" Sum:Even if you combined a million numbers, if they are all standard integers (under 2 billion), their Bitwise OR sum can never exceed the value where all 30 bits are 1.
The Calculation:
1 << 30 is 2^{30} (approx 1.07 billion).
(1 << 30) - 1 is the number 111...111 (30 times) in binary.
This is a "safe ceiling." The true answer is guaranteed to be smaller than or equal to this, so we search up to this point to be sure we don't miss it.*/
