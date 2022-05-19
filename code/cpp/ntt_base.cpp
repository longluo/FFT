#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;
const int G = 3;
const int G_INV = 332748118; //3在998244353下的逆元

long long fastPower(long long a, long long b, int mod) {
    long long res = 1;

    while (b > 0) {
        if (b & 1) {
            res = (res * a) % mod;
        }

        a = (a * a) % mod;
        b >>= 1;
    }

    return res % mod;
}

long long quickPower(long long a, long long b) {
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

long long ksm(long long a, long long b, long long mod) {
    long long ans = 1;
    for (; b > 0; b >>= 1) {
        if (b & 1) {
            ans = ans * a % mod;
        }

        a = a * a % mod;
    }

    return ans;
}

int main() {
    for (int i = 0; i < MOD; i++) {
        if (G * i % MOD == 1) {
            cout << MOD << " inv: " << i << endl;
        }
    }

    for (int i = 0; i < 97; i++) {
        if (G * i % 97 == 1) {
            cout << 97 << " inv: " << i << endl;
        }
    }

    for (int i = 0; i <= 10; i++) {
        cout << i << " " << quickPower(3, i) << " <--> " << quickPower(G_INV, i) << endl;
    }

    for (int i = 0; i <= 48; i++) {
        cout << i << " " << fastPower(3, i, 97) << " " << fastPower(65, i, 97) << endl;
    }

    cout << quickPower(3, 96) % 97 << endl;
    cout << 998244354 / 3 << endl;

    return 0;
}


