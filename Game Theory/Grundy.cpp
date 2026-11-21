#include <bits/stdc++.h>
using namespace std;

// Positive subtraction moves. XOR the Grundy numbers of independent heaps to test the winner.
vector<int> grundy_table(int largest_heap, const vector<int>& moves) {
    vector<int> grundy(largest_heap+1), seen(moves.size()+1,-1);
    for (int h=1;h<=largest_heap;++h) {
        for (int m : moves) if (m > 0 && m <= h) seen[grundy[h-m]] = h;
        while (seen[grundy[h]] == h) ++grundy[h];
    }
    return grundy;
}
