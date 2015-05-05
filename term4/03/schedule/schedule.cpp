#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <utility>
#include <stdint.h>
#include <algorithm>

using namespace std;

int main() {
    int n, t = 1;
    uint64_t ans = 0;
    priority_queue<int> s;
    vector< pair<int, int> > in;

    freopen("schedule.in",  "r", stdin);
    freopen("schedule.out", "w", stdout);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int d, w;
        cin >> d >> w;
        in.push_back(make_pair(d, w));
    }

    sort(in.begin(), in.end());

    for (int i = 0; i < n; i++) {
        int d = in[i].first, w = in[i].second;
        ans += w;
        s.push(-w);
        if (d >= t) {
            t++;
        } else {
            s.pop();
        }
    }
    
    while (!s.empty()) {
        int w = s.top();
        s.pop();
        ans += w;
    }
    cout << ans << endl;

    return 0;
}
