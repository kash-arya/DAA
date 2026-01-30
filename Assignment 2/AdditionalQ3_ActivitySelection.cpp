#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// 1. Define a Struct to hold all data for one customer together
struct CustomerInfo
{
    int id; // To remember original index/name if needed
    int arrival;
    int departure;
    int compartment;
};

// 2. Comparator function tells C++ HOW to sort the struct (by Departure)
bool compareByDeparture(const CustomerInfo &a, const CustomerInfo &b)
{
    return a.departure < b.departure;
}

class Solution
{
public:
    int maximum_customers(vector<int> &arrival, vector<int> &departure, vector<int> &preferred, int k, int N)
    {

        // --- ZIP STEP ---
        vector<CustomerInfo> customers;
        for (int i = 0; i < N; i++)
        {
            // Push all 4 attributes into the struct at once
            customers.push_back({i, arrival[i], departure[i], preferred[i]});
        }

        // --- SORT STEP ---
        // Sort the vector of structs using our custom comparator
        sort(customers.begin(), customers.end(), compareByDeparture);

        // --- GREEDY LOGIC ---
        int count = 0;
        // Use K+1 so we can use indices 1 to K directly
        vector<int> FreeTime(k + 1, 0);

        // Iterate through the SORTED customers vector
        for (int i = 0; i < N; i++)
        {
            int current_compartment = customers[i].compartment;
            // Check availability
            if (customers[i].arrival >= FreeTime[current_compartment])
            {
                count++;
                // Update when this compartment will be free next
                FreeTime[current_compartment] = customers[i].departure;
            }
        }
        return count;
    }
};

/*Key Corrections
1. The Struct: Instead of pair<pair...>, we used struct CustomerInfo. It is readable and scalable.
2. The Comparator: We created compareByDeparture to tell sort to look specifically at the .departure integer inside the struct.
3. The Loop: In your original code, you sorted f_vec but then used arrival[i] inside the loop. This is wrong because arrival[] is still the old, unsorted array. You must access the data through the sorted vector (e.g., customers[i].arrival).

You tried to "invent" a way to link 4 arrays using nested pairs (which was creative!), but it was messy. Now you have exposed yourself to the standard tool:
2 Arrays? Use pair.
3+ Arrays? Use struct.

Don't memorize the code. Just memorize this trigger: "If I have to sort multiple arrays together, I need a struct and a custom comparator."
*/
