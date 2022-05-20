package com.longluo;

import java.util.NoSuchElementException;
import java.util.Scanner;

/**
 * NTT Recursion
 */

/*
123 456
Before FFT
3 2 1 0 0 0 0 0
6 5 4 0 0 0 0 0
After FFT
6 658473933 825076919 65787358 2 166602990 173167438 107380084
15 518064901 565325765 793466147 5 785754073 432918592 897447962
After Times:
90 11925151 784316648 497879635 10 130608434 213927693 357831189
After IFFT
144 216 224 104 32 0 0 0
Result:
18 27 28 13 4 0 0 0
Result:56088
*/
public class NTT_Recursion {

    public static void display(long[] arr) {
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i] + " ");
        }

        System.out.println();
    }

    static class Solution {
        public static final int G = 3;
        public static final int G_INV = 332748118;
        public static final int MOD = 998244353;

        public static long quickPower(long a, long b) {
            long ans = 1;
            while (b > 0) {
                if (b % 2 == 1) {
                    ans = (ans * a) % MOD;
                }

                a = (a * a) % MOD;
                b = b >> 1;
            }

            return ans % MOD;
        }

        public static void NTT(long arr[], boolean invert) {
            int n = arr.length;
            if (n <= 1) {
                return;
            }

            long[] Pe = new long[n / 2];
            long[] Po = new long[n / 2];

            for (int i = 0; i < n / 2; i++) {
                Pe[i] = arr[2 * i];
                Po[i] = arr[2 * i + 1];
            }

            NTT(Pe, invert);
            NTT(Po, invert);

            long wn = quickPower(invert ? G_INV : G, (MOD - 1) / n);
            long w = 1;

            for (int i = 0; i < n / 2; i++) {
                arr[i] = Pe[i] + w * Po[i] % MOD;
                arr[i] = (arr[i] % MOD + MOD) % MOD;
                arr[i + n / 2] = Pe[i] - w * Po[i] % MOD;
                arr[i + n / 2] = (arr[i + n / 2] % MOD + MOD) % MOD;
                w = (w * wn) % MOD;
            }
        }

        public static String multiply(String num1, String num2) {
            if (num1.equals("0") || num2.equals("0")) {
                return "0";
            }

            int len1 = num1.length();
            int len2 = num2.length();

            int n = 1;
            while (n < len1 + len2) {
                n = n << 1;
            }

            long[] A = new long[n];
            long[] B = new long[n];

            for (int i = len1 - 1; i >= 0; i--) {
                A[len1 - 1 - i] = num1.charAt(i) - '0';
            }
            for (int i = len2 - 1; i >= 0; i--) {
                B[len2 - 1 - i] = num2.charAt(i) - '0';
            }

            System.out.println("Before FFT");
            display(A);
            display(B);

            NTT(A, false);
            NTT(B, false);

            System.out.println("After FFT");
            display(A);
            display(B);

            for (int i = 0; i < n; i++) {
                A[i] = (A[i] * B[i]) % MOD;
            }

            System.out.println("After Times");
            display(A);

            NTT(A, true);

            System.out.println("After IFFT");
            display(A);

            long inver = quickPower(n, MOD - 2);
            for (int i = 0; i < n; i++) {
                A[i] = A[i] * inver % MOD;
            }

            System.out.println("Result:");
            display(A);

            StringBuilder ans = new StringBuilder();
            long carry = 0;
            for (int i = 0; i < n; i++) {
                long sum = (A[i] + carry) % MOD;
                carry = sum / 10;
                ans.append((char)(sum % 10 + '0'));
            }

            while (carry > 0) {
                ans.append((char)(carry % 10 + '0'));
                carry /= 10;
            }

            int idx = n - 1;
            while (ans.length() > 0 && ans.charAt(idx) == '0') {
                ans.deleteCharAt(idx);
                idx--;
            }

            return ans.reverse().toString();
        }
    }

    public static void main(String[] args) {
        System.out.println(" " + Long.MIN_VALUE + " " + Long.MAX_VALUE);

        Scanner sc = new Scanner(System.in);
        try {
            while (true) {
                System.out.println("Please Input 2 numbers: ");
                String[] numbers = sc.nextLine().split("\\s+");
                if (numbers.length > 2) {
                    System.out.println("Error Input!");
                    continue;
                }

                Solution s = new Solution();
                String result = s.multiply(numbers[0], numbers[1]);
                System.out.println("Result: " + result + " = " + numbers[0] + " * " + numbers[1]);
            }
        } catch (IllegalStateException | NoSuchElementException e) {
            e.printStackTrace();
        }
    }
}
