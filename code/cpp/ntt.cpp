//
// Created by longluo on 2022/5/18.
//

#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 4e6 + 10, mod = 998244353, g = 3, gn = 332748118;//3在998244353下的逆元

int p = 1, bit, inver;
int a[maxn], b[maxn], rev[maxn];

inline int power(long long a, int x) {
    long long ans = 1;

    while (x) {
        if (x & 1) {
            ans = (ans * a) % mod;
        }

        a = (a * a) % mod;
        x >>= 1;
    }

    return ans;
}

inline void ntt(int *t, int inv) {
    for (int i = 0; i < p; i++) {
        if (i < rev[i]) swap(t[i], t[rev[i]]);
    }

    for (int mid = 1; mid < p; mid <<= 1) {
        int unit = power(inv == 1 ? g : gn, (mod - 1) / (mid << 1));
        int d = mid << 1;
        for (int l = 0; l < p; l += d) {
            int now = 1;
            for (int i = 0; i < mid; i++) {
                int x = t[l + i], y = (long long) now * t[l + mid + i] % mod;
                t[l + i] = (x + y) % mod;
                t[l + mid + i] = (x - y + mod) % mod;
                now = (long long) now * unit % mod;
            }
        }
    }

    if (inv == -1) {
        for (int i = 0; i < p; i++) {
            a[i] = (long long) a[i] * inver % mod;
        }
    }
}

int main() {
    string num1, num2;
    cin >> num1 >> num2;

    for (int i = 0; i < num1.size(); i++) {
        a[i] = num1[i] - '0';
    }

    for (int i = 0; i < num2.size(); i++) {
        b[i] = num2[i] - '0';
    }

    int sum = num1.size() + num2.size();
    while (p <= sum) {
        p <<= 1, bit++;
    }

    inver = power(p, mod - 2);
    for (int i = 1; i < p; i++) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
    }

    ntt(a, 1);
    ntt(b, 1);
    for (int i = 0; i < p; i++) {
        a[i] = (long long) a[i] * b[i] % mod;
    }
    ntt(a, -1);

    for (int i = 0; i <= sum; i++) {
        cout << a[i] << " ";
    }

    return 0;
}


