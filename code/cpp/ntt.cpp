#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
const int G = 3;
const int G_INV = 332748118; // 3在998244353下的逆元

vector<int> rev;

void display(vector<long long> arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }

    cout << endl;
}

long long quickPower(long long a, int b) {
    long long res = 1;

    while (b > 0) {
        if (b & 1) {
            res = (res * a) % MOD;
        }

        a = (a * a) % MOD;
        b >>= 1;
    }

    return res % MOD;
}

void ntt(vector<long long> &a, bool invert = false) {
    int n = a.size();

    for (int i = 0; i < n; i++) {
        if (i < rev[i]) {
            swap(a[i], a[rev[i]]);
        }
    }

    for (int len = 2; len <= n; len *= 2) {
        long long wn = quickPower(invert ? G_INV : G, (MOD - 1) / len);
        for (int i = 0; i < n; i += len) {
            long long w = 1;
            for (int j = 0; j < len / 2; j++) {
                long long u = a[i + j];
                long long v = (w * a[i + j + len / 2]) % MOD;
                a[i + j] = (u + v) % MOD;
                a[i + j + len / 2] = (u - v + MOD) % MOD;
                w = (w * wn) % MOD;
            }
        }
    }

    if (invert) {
        long long inver = quickPower(n, MOD - 2);
        for (int i = 0; i < n; i++) {
            a[i] = (long long) a[i] * inver % MOD;
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

    cout << "Before FFT" << endl;
    display(a);
    display(b);

    ntt(a, false);
    ntt(b, false);

    cout << "After FFT" << endl;
    display(a);
    display(b);

    for (int i = 0; i < n; i++) {
        a[i] = (a[i] * b[i]) % MOD;
    }

    cout << "After Times:" << endl;
    display(a);

    ntt(a, true);

    cout << "Result: " << endl;
    display(a);

    string res;
    long long carry = 0;
    for (int i = 0; i < len1 + len2 - 1; ++i) {
        long long curr = a[i] + carry;
        res += curr % 10 + '0';
        carry = curr / 10;
    }

    while (carry) {
        res += carry % 10 + '0';
        carry /= 10;
    }

    reverse(res.begin(), res.end());
    return res;
}

int main() {
    cout << "Please Input 2 numbers: " << endl;

    string num1, num2;
    cin >> num1 >> num2;

    string result = multiply(num1, num2);

    cout << result << " = " << num1 << " * " << num2 << endl;

    return 0;
}


