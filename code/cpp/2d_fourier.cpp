//
// Created by longluo on 2022/8/10.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <opencv2/opencv.hpp>
#include <complex>

using namespace std;
using namespace cv;

#define PI 3.14159265358979323846
#define intsize sizeof(int)
#define complexsize sizeof(complex<float>)

Mat image;
int *a, *b;
int nLen, mLen;
complex<float> *A, *A_In;

void reverse(int);

void fft(int);

void saveResult();

void readImg();

int main() {
    int i, j;
    image = imread("E:\\Code\\FFT\\code\\cpp\\lena.png", 0);
    readImg();

    //一维
    A = (complex<float> *) malloc(complexsize * nLen);
    reverse(nLen);
    for (i = 0; i < mLen; i++) {
        for (j = 0; j < nLen; j++) {
            A[j] = A_In[i * nLen + b[j]];
        }

        fft(nLen);
        printf("%d\n", i);
        for (j = 0; j < nLen; j++) {
            A_In[i * nLen + j] = A[j];
        }
    }
    free(A);

    //二维
    A = (complex<float> *) malloc(complexsize * mLen);
    reverse(mLen);
    for (i = 0; i < nLen; i++) {
        for (j = 0; j < mLen; j++) {
            A[j] = A_In[b[j] * nLen + i];
        }
        printf("_%d\n", i);
        fft(mLen);
        for (j = 0; j < mLen; j++) {
            A_In[j * nLen + i] = A[j];
        }
    }
    free(A);

    saveResult();
    printf("success!\n");
    return 0;
}

/*
*readImg()
*读取图像提取数据
*/
void readImg() {
    int i, j;

    nLen = image.cols;
    mLen = image.rows;

    A_In = (complex<float> *) malloc(complexsize * nLen * mLen);
    for (int x = 0; x <= mLen - 1; x++) {
        for (int y = 0; y <= nLen - 1; y++) {
            //矩阵中数据保存格式为uchar
            const uchar *data_str = image.datastart + x + y * mLen;//定位数据
            int tmp_i = data_str[0];//取出数据，格式为整型
            A_In[x * nLen + y] = tmp_i * 1.0;
        }
    }

}

/*
*fourier_2d(Mat f)
*对数据矩阵f进行二维傅立叶变换
*/
void fft(int fft_nLen) {
    int dist, p;
    complex<float> B, *W;
    int fft_M = log((float) fft_nLen) / log(2.0);
    W = (complex<float> *) malloc(complexsize * fft_nLen / 2);

    for (int lev = 1; lev <= fft_M; lev++)/*共log2N级*/
    {
        //一级蝶形运算
        dist = (int) pow(2.0, lev - 1);/*计算每一组蝶形的个数*/

        for (int t = 0; t < dist; t++)/*每dist+1个蝶形是一组*/
        {
            /* 计算每一组蝶形的旋转因子
             WN[k].real=cos(2*PI/N*k);
　　		 WN[k].img=-sin(2*PI/N*k);*/
            p = t * (int) pow(2.0, fft_M - lev);
            complex<float> tmp((float) cos(2 * PI * p / fft_nLen), (float) (-1 * sin(2 * PI * p / fft_nLen)));/*旋转因子*/
            W[p] = tmp;

            for (int i = t; i < fft_nLen; i += (int) pow(2.0, lev))/*计算每一级的所有组*/
            {
                B = A[i] + A[i + dist] * W[p];
                complex<float> tmp2(A[i].real() - (A[i + dist] * W[p]).real(),
                                    A[i].imag() - (A[i + dist] * W[p]).imag());
                A[i + dist] = tmp2;
                A[i] = B;
            }
        }
    }
    free(W);
}

/*
*saveResult()
*将傅立叶频谱保存
*/
void saveResult() {
    Mat F;
    image.copyTo(F);
    int i, j;

    for (i = 0; i < mLen; i++) {
        for (j = 0; j < nLen; j++) {
            if (A_In[i * nLen + j].imag() < 0) {
                F.col(i).row(j) = A_In[i * nLen + j].real();//将结果存入矩阵
            } else {
                F.col(i).row(j) = A_In[i * nLen + j].real();//将结果存入矩阵
            }
        }
    }
    cv::imwrite("E://LEARN//computer vision//code_c//fourier//lena_fft.png", F);
    free(A_In);
}

/*
*reverse(int len)
*码位倒序函数
*/
void reverse(int len) {
    int i, j;
    int M = log((float) len) / log(2.0);
    a = (int *) malloc(intsize * M);
    b = (int *) malloc(intsize * len);

    for (i = 0; i < M; i++) {
        a[i] = 0;
    }

    b[0] = 0;
    for (i = 1; i < len; i++) {
        j = 0;
        while (a[j] != 0) {
            a[j] = 0;
            j++;
        }

        a[j] = 1;
        b[i] = 0;
        for (j = 0; j < M; j++) {
            b[i] = b[i] + a[j] * (int) pow(2.0, M - 1 - j);
        }
    }
}

