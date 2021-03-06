
//   CoorTrans.cpp   :   Defines   the   entry   point   for   the   console   application. 
//




#include   "CoorTrans.h"


//坐标转换 

//度分秒--弧度

double   Dm2Rad(double   Dm)
{
    double   Degree,   Miniute;
    int		 Sign;
    double   Rad;

    if(Dm >= 0)
        Sign  =   1;
    else
        Sign  =   -1;


    Dm       =   fabs(Dm);
    Degree   =   floor(Dm/100); //（ddmm.mmmmmm;dddmm.mmmmmm-->dd.mmmmmmmm;ddd.mmmmmmmm-->dd）
    Miniute  =   Dm - Degree*100; //Miniute  =   fmod(Dm,100.0)!!!
    Rad      =   Sign * (Degree + Miniute / 60.0)  * PI / 180.0;

    return   Rad;
}

double   Dms2Rad(double   Dms) 
{ 
    double   Degree,   Miniute;
    double   Second;
    int      Sign;
    double   Rad;

    if(Dms   >=   0)
        Sign  =   1;
    else
        Sign  =   -1;

    Dms		 =   fabs(Dms); //绝对值Dms:dd.mmssss
    Degree   =   floor(Dms); //取度 floor（2.8359） = 2.00000
    Miniute  =   floor(fmod(Dms * 100.0, 100.0)); //fmod 计算余数;283.60/100-->83
    Second   =   fmod(Dms * 10000.0, 100.0); //28359/100-->59;S最大59.999999
    Rad      =   Sign * (Degree + Miniute / 60.0 + Second / 3600.0) * PI / 180.0;

    return   Rad;
} 

double   Rad2Dms(double   Rad) 
{ 
    double   Degree,   Miniute;
    double   Second;
    int   Sign;
    double   Dms;

    if(Rad   >=   0)
        Sign  =   1;
    else
        Sign  =   -1;

    Rad		 =   fabs(Rad * 180.0 / PI);
    Degree   =   floor(Rad);
    Miniute  =   floor(fmod(Rad * 60.0, 60.0));
    Second   =   fmod(Rad * 3600.0, 60.0);
    Dms		 =   Sign * (Degree + Miniute / 100.0 + Second / 10000.0);

    return   Dms;
} 
/////////////////////////////////////////////////// 
//   Definition   of   PrjPoint 
/////////////////////////////////////////////////// 

//正算公式 

bool   PrjPoint::BL2xy() 
{ 
    //大地测量学基础 （吕志平 乔书波 北京：测绘出版社 2010.03）

    double   X; //由赤道至纬度为B的子午线弧长
    double   N; //椭球的卯酉圈曲率半径
    double   t,   t2,   m,   m2,   ng2;
    double   sinB,   cosB;

    X   =   A1 * B * 180.0 / PI + A2 * sin(2 * B) + A3 * sin(4 * B) + A4 * sin(6 * B); //???

    sinB   =   sin(B);
    cosB   =   cos(B);
    t    =   tan(B);
    t2   =   t * t;

    N    =   a / sqrt(1 - e2 * sinB * sinB);
    m    =   cosB * (L - L0);
    m2   =   m * m;
    ng2  =   cosB * cosB * e2 / (1 - e2);

    //P156  （6-63公式）

    x   =   X + N * t * ((0.5 + ( (5 - t2 + 9 * ng2 + 4 * ng2 * ng2) / 24.0 + (61 - 58 * t2 + t2 * t2) * m2 / 720.0) * m2) * m2);
    y   =   N * m * (1 + m2 * ( (1 - t2 + ng2) / 6.0 + m2 * (5 - 18 * t2 +  t2 * t2 + 14 * ng2 - 58 * ng2 * t2) / 120.0));

    y   +=   500000; //????

    return   true;
} 

//反算公式

bool   PrjPoint::xy2BL() 
{ 
    double   sinB,   cosB,   t,   t2,   N   ,ng2,   V,   yN;
    double   preB0,   B0;
    double   eta;

    y   -=   500000;
    B0   =   x   /   A1;

    do
    {
        preB0  =   B0;
        B0     =   B0 * PI / 180.0;
        B0     =   (x - (A2 * sin(2 * B0) + A3 * sin(4 * B0) + A4 * sin(6 * B0))) / A1;
        eta    =   fabs(B0 - preB0);
    }	while(eta   >   0.000000001);

    B0   	=   B0 * PI / 180.0;
    B	    =   Rad2Dms(B0);
    sinB    =   sin(B0);
    cosB    =   cos(B0);
    t    =   tan(B0);
    t2   =   t * t;

    N    =   a / sqrt(1 - e2 * sinB * sinB);
    ng2  =   cosB * cosB * e2 / (1 - e2);
    V    =   sqrt(1 + ng2);
    yN   =   y / N;

    B   =   B0 - (yN * yN - (5 + 3 * t2 + ng2 - 9 * ng2 * t2) * yN* yN * yN * yN / 12.0 +(61 + 90 * t2 + 45 * t2 * t2) * yN* yN * yN * yN * yN * yN / 360.0) * V * V * t / 2;
    L   =   L0 + (yN - (1 + 2 * t2 + ng2) * yN * yN * yN  / 6.0 + (5 + 28 * t2 + 24 * t2 * t2 + 6 * ng2 + 8 * ng2 * t2) *  yN * yN * yN * yN * yN / 120.0) / cosB;

    return   true;
} 

//设置中央子午线

bool   PrjPoint::SetL0(double   dL0) 
{ 
    L0   =   Dms2Rad(dL0);

    return   true;
} 

//将度分秒经纬度转换为弧度后再转换为平面坐标

bool   PrjPoint::SetBL(double   dB,   double   dL) 
{ 

    B   =   Dm2Rad(dB);
    L   =   Dm2Rad(dL);

    BL2xy();

    return   true;
} 

bool   PrjPoint::GetBL(double   *dB,   double   *dL) 
{ 
    *dB   =   Rad2Dms(B);
    *dL   =   Rad2Dms(L);

    return   true;
} 

//将平面坐标转换为（弧度）经纬度

bool   PrjPoint::Setxy(double   dx,   double   dy) 
{ 
    x   =   dx;
    y   =   dy;

    xy2BL();

    return   true;
} 

bool   PrjPoint::Getxy(double   *dx,   double   *dy) 
{ 
    *dx   =   x;
    *dy   =   y;

    return   true;
}

/////////////////////////////////////////////////// 
//   Definition   of   PrjPoint_IUGG1975 
/////////////////////////////////////////////////// 

PrjPoint_IUGG1975::PrjPoint_IUGG1975()   //在类外定义构造成员函数，要加上类名和域限定符   :: 
{ 
    a   =   6378140;
    f   =   298.257;

    e2   =   1 - ((f - 1) / f) * ((f - 1) / f);
    e12  =   (f / (f - 1)) * (f / (f - 1)) - 1;

    A1   =   111133.0047;     //这几个A是什么意思？
    A2   =   -16038.5282;
    A3   =   16.8326;
    A4   =   -0.0220;
} 

PrjPoint_IUGG1975::~PrjPoint_IUGG1975()       //析构函数，释放构造函数占用的内存 
{ 
} 

/////////////////////////////////////////////////// 
//   Definition   of   PrjPoint_Krasovsky 
/////////////////////////////////////////////////// 

PrjPoint_Krasovsky::PrjPoint_Krasovsky() 
{ 
    a   =   6378245;   //长半径
    f   =   298.3;	   //扁率的倒数 （扁率：(a-b)/a）

    e2   =   1 - ((f - 1) / f) * ((f - 1) / f);	 //第一偏心率的平方
    e12  =   (f / (f - 1)) * (f / (f - 1)) - 1;	 //第二偏心率的平方

    // 克拉索夫斯基椭球

    A1   =   111134.8611;
    A2   =   -16036.4803;
    A3   =   16.8281;
    A4   =   -0.0220;
} 

PrjPoint_Krasovsky::~PrjPoint_Krasovsky() //析构函数，释放构造函数占用的内存
{ 
}
