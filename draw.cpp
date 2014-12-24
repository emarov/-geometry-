#include <iostream>
#include <cmath>
#include <random>
#include <complex>
#include <typeinfo>

#include "gif.hpp"

using namespace std;

const int size = 512;

class Pixel
{
public:
    void red(uint8_t color)
    {
        px &= 0xFFFFFF00;
        px |= static_cast<uint32_t>(color);
    }
    void green(uint8_t color)
    {
        px &= 0xFFFF00FF;
        px |= static_cast<uint32_t>(color) << 8;
    }
    void blue(uint8_t color)
    {
        px &= 0xFF00FFFF;
        px |= static_cast<uint32_t>(color) << 16;
    }
    Pixel& operator=(uint32_t color)
    {
        px=color;
        return *this;
    }
private:
    uint32_t px {0};
};


class Frame
{
    using FrameRow = Pixel(&)[size];
public:
    FrameRow operator[](int idx)
    {
        return arr[idx];
    }
    operator void*()
    {
        return arr;
    }
private:
    Pixel arr[size][size];
};

class Shape
{
    int x1,y1, x2,y2;
public:
    Shape(int xx1,int yy1,int xx2,int yy2)
    {
        x1 = xx1;
        y1 = yy1;
        x2 = xx2;
        y2 = yy2;
    }
    void paint(Frame &f){
        for(int y=y1; y<=y2; y++) // �� ��������
            for(int x=x1; x<=x2; x++) // �� ��������
            {
                double w,h;
                 w=(x2-x1);
                 h=(y2-y1);
                if( (x-x1)/w + (y-y1)/h < 1.0 )
                    f[y][x].green(255);

            }

    }
};


int main()
{
    // ������ ��������
    Frame frame;
    for(int i=0; i<size; i++) // �� ��������
        for(int j=0; j<size; j++) // �� ��������
            frame[i][j] = 0;

    // �������� ������� (gif-�����) � �������� ������ � ���������
    GifWriter gw("checking.gif",size,size,200);


    for(int i=10; i<size-10; i++) // �� ��������
        for(int j=10; j<size-10; j++) // �� ��������
            frame[i][j].red(255), frame[i][j].blue(255);
 //������� �����������
    Shape t(100,100,320,320);
    t.paint(frame);

for(int i=110; i<200; i++) // �� ��������
        for(int j=110; j<200; j++) // �� ��������
            frame[i][j] = 0;

 for(int i=120; i<190; i++) // �� ��������
        for(int j=120; j<190; j++) // �� ��������
            frame[i][j].blue(100),frame[i][j].green(50);

  for(int i=130; i<180; i++) // �� ��������
        for(int j=130; j<180; j++) // �� ��������
            frame[i][j].red(200),frame[i][j].green(10);

   for(int i=110; i<150; i++) // �� ��������
        for(int j=210; j<250; j++) // �� ��������
            frame[i][j]=0;

    for(int i=210; i<250; i++) // �� ��������
        for(int j=110; j<150; j++) // �� ��������
            frame[i][j]=0;

for(int i=120; i<140; i++) // �� ��������
        for(int j=220; j<240; j++) // �� ��������
            frame[i][j].blue(100),frame[i][j].green(50);

  for(int i=220; i<240; i++) // �� ��������
        for(int j=120; j<140; j++) // �� ��������
            frame[i][j].blue(100),frame[i][j].green(50);

    gw.write(frame);

    return 0;
}
