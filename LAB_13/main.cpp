#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using str = string;

bool canTurnOffAll(ll n, ll k, const vector<ll>& onIndices, ll L) {
    ll actions = 0;
    ll i = 0;
    while (i < onIndices.size()) {
        actions++;
        ll start = onIndices[i];
        while (i < onIndices.size() && onIndices[i] <= start + L - 1) {
            i++;
        }
        if (actions > k) return false;
    }
    return true;
}

ll main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll t;
    cin >> t;

    ll n, k;
    str s;
    while (t--) {
        cin >> n >> k;
        cin >> s;

        vector<ll> onIndices;

        for (ll i = 0; i < n; i++)
            if (s[i] == '1')
                onIndices.push_back(i);


        ll low = 1, high = n;
        ll answer = n;
        ll mid;

        while (low <= high) {
            mid = (low + high) / 2;

            if (canTurnOffAll(n, k, onIndices, mid)) {
                answer = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        cout << answer << "\n";
    }
}
