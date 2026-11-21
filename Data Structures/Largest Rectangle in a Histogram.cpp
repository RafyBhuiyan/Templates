#include <bits/stdc++.h>
using namespace std;

long long histogram_area(const vector<long long>& height) {
    vector<int> stack;
    long long best=0;
    for(int i=0;i<=(int)height.size();++i) {
        while(!stack.empty() && (i==(int)height.size() || height[stack.back()]>=height[i])) {
            long long h=height[stack.back()]; stack.pop_back();
            int left=stack.empty() ? -1 : stack.back();
            best=max(best,h*(i-1-left));
        }
        stack.push_back(i);
    }
    return best;
}
