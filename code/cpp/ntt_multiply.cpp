//
// Created by longluo on 2022/5/18.
//

#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

class Solution {
    static const long long G = 3, Ginv = 332748118, P = 998244353;
    vector<int> rev;

public:
    long long fastpow(long long a, long long n) {
        long long res = 1;
        do {
            if (n & 1) {
                res = (res * a) % P;
            }

            a = (a * a) % P;
        } while (n >>= 1);

        return res % P;
    }

    void ntt(vector<long long> &a, bool inv = false) {
        int n = a.size();

        for (int i = 0; i < n; ++i) {
            if (i < rev[i]) {
                swap(a[i], a[rev[i]]);
            }
        }

        for (int bisector = 1; bisector < n; bisector <<= 1) {
            long long ai = fastpow(inv ? Ginv : G, (P - 1) / (bisector << 1));

            for (int i = 0; i < n; i += (bisector << 1)) {
                long long multiplier = 1;
                for (int j = 0; j < bisector; ++j) {
                    long long a0 = a[i + j], a1 = (multiplier * a[i + j + bisector]) % P;
                    a[i + j] = (a0 + a1) % P;
                    a[i + j + bisector] = (P + a0 - a1) % P;
                    multiplier = (multiplier * ai) % P;
                }
            }
        }
    }

    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") {
            return "0";
        }

        int len1 = num1.size();
        int len2 = num2.size();

        int n = 1;
        int bit = 1;

        while ((n <<= 1) < (len1 + len2)) {
            ++bit;
        }

        rev.resize(n);
        for (int i = 0; i < n; i++) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
        }

        vector<long long> a(n, 0), b(n, 0);

        for (int i = 0; i < len1; ++i) {
            a[i] = num1[len1 - 1 - i] - '0';
        }

        for (int i = 0; i < len2; ++i) {
            b[i] = num2[len2 - 1 - i] - '0';
        }

        ntt(a);
        ntt(b);

        for (int i = 0; i < n; ++i) {
            a[i] = (a[i] * b[i]) % P;
        }

        ntt(a, true);

        long long inv = fastpow(n, P - 2);

        string res;
        long long prev = 0;
        for (int i = 0; i < len1 + len2 - 1; ++i) {
            long long curr = a[i] * inv % P + prev;
            res += curr % 10 + '0';
            prev = curr / 10;
        }

        while (prev) {
            res += prev % 10 + '0';
            prev /= 10;
        }

        reverse(res.begin(), res.end());
        return res;
    }
};

int main() {
    string num1, num2;
    cin >> num1 >> num2;

    Solution s;
    string result = s.multiply(num1, num2);
    cout << "Result:" << result << endl;
}


