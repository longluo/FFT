package com.longluo;

public class DFT {

    public static void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    public static String reverse(String s) {
        StringBuilder sb = new StringBuilder(s.length());
        for (int i = s.length() - 1; i >= 0; i--) {
            sb.append(s.charAt(i));
        }

        return sb.toString();
    }

    public static void main(String[] args) {
        int[] rev = new int[32];

        for (int i = 0; i < 32; ++i) {
            rev[i] = rev[i >> 1] >> 1;
            if ((i & 0x01) == 1) {  // 如果最后一位是 1，则翻转成 len/2
                rev[i] |= 32 >> 1;
            }
        }

        for (int i = 0; i < 32; i++) {
            System.out.println(i + " " + rev[i]);
        }

        for (int i = 0; i < 32; i++) {
            String numStr = Integer.toBinaryString(i);
            String revereStr = reverse(numStr);
            System.out.println(i + " " + numStr + " " + revereStr + " " + Integer.parseInt(revereStr, 2));
        }
    }
}
