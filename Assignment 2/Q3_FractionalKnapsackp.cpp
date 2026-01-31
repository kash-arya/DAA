#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int value, weight;
    double ratio;
};

// Comparator must be static or outside class
bool compare_by_Ratio(Item a, Item b) {
    return a.ratio > b.ratio; // Descending order
}

class Solution {
public:
    double maximum_value(int N, vector<int> &value, vector<int> &weight, int W) {
        vector<Item> items;
        
        // 1. Zip and Calculate Ratio
        for (int i = 0; i < N; i++) {
            double r = (double)value[i] / weight[i]; 
            items.push_back({value[i], weight[i], r});
        }
        // 2. Sort
        sort(items.begin(), items.end(), compare_by_Ratio);

        double final_val = 0.0;
        for (int i = 0; i < N; i++) {
            // Boundary check: If bag is full, stop
            if (W == 0) break; 

            if (items[i].weight <= W) {
                // Take whole item
                W -= items[i].weight;
                final_val += items[i].value;
            } else {
                // Take fraction
                // Fix: Use double division for the fraction
                final_val += items[i].value * ((double)W / items[i].weight);
                W = 0; // Bag is now full
                break;
            }
        }
        return final_val;
    }
};

/*
The Rule: Once you move data into a struct and sort it, ignore the original arrays. They are "dead" to you because they are out of sync. Only trust the data inside the sorted struct.
Because 'items' is now sorted, but weight and value (the original arrays) are NOT sorted. They no longer match!

The concise technical reason why we place them outside the class (or make them static):

1. The Comparator (bool) Issue: This is the main cause of errors.
The Problem: std::sort expects a standalone function taking two arguments: (Item a, Item b).
Inside Class: A normal member function has a hidden third argument: (Solution* this, Item a, Item b). This mismatch causes the compiler error.
The Fix:
Option A (Outside): It becomes a true standalone function. (Easiest).
Option B (static): Removes the hidden this pointer, allowing it to stay inside.

2. The Struct Issue
The Problem: If you put a struct inside class Solution, it becomes a nested type (Solution::Item).
Why Outside? It simplifies syntax. You can just type Item anywhere in your file without worrying about private/public access modifiers or scope resolution (Solution::).
Summary:
Comparator: Must be outside or static to satisfy std::sort.
Struct: Placed outside for convenience and global access.
*/
