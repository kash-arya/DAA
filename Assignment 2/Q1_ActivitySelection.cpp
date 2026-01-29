#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Function to find the maximum number of activities that can be performed
    int activitySelection(vector<int>& start, vector<int>& finish, int n) {
        // 1. "Zip" the arrays: Pair them up to keep start & finish linked during sort.
        // We use {finish, start} logic or a custom struct. 
        // Storing as pair<int, int> activity where first = finish, second = start
        // allows default sorting to work (sorts by first element automatically).
        vector<pair<int, int>> activities;
        
        for (int i = 0; i < n; i++) {
            // Storing {finish, start} simplifies sorting logic
            activities.push_back({finish[i], start[i]});
        }

        // 2. Greedy Sort: Sort by Finish Time (Ascending)
        // This is the core "Greedy Choice Property". Finishing early leaves
        // the maximum resources (time) for subsequent tasks.
        sort(activities.begin(), activities.end());

        // 3. Select Activities
        int count = 1; // Always select the first activity (it finishes earliest)
        int lastFinishTime = activities[0].first;

        for (int i = 1; i < n; i++) {
            // current_start >= previous_finish means no overlap
            if (activities[i].second >= lastFinishTime) {
                count++;
                lastFinishTime = activities[i].first; // Update finish time
            }
        }

        return count;
    }
};
