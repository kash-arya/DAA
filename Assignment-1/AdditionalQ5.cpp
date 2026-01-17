#include <algorithm>
using namespace std;
class Solution
{
public:
    unsigned long long minSquareSide(unsigned long long N, unsigned long long H, unsigned long long W)
    {
        unsigned long long low = 1, high = N * max(H, W); // Safe Upper Bound
        unsigned long long side = high;

        while (low <= high)
        {
            unsigned long long mid = low + (high - low) / 2;

            // Check: How many fit in 'mid'?
            // Logic: (mid / W) items per row * (mid / H) items per col
            unsigned long long count = (mid / W) * (mid / H);

            if (count >= N)
            {
                side = mid; // Possible answer, try smaller
                high = mid - 1;
            }
            else
            {
                low = mid + 1; // Too small, need bigger square
            }
        }
        return side;
    }
};
