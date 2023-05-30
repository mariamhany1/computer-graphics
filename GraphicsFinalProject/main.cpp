#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif
#include <bits/stdc++.h>
#include <tchar.h>
#include <windows.h>
using namespace std;
#define Save 1
#define Load 2
#define RED 3
#define GREEN 4
#define BLUE 5
#define BLACK 6
#define Yellow 7
#define Purple 8
#define Clear 9
#define DDA 10
#define midpoint 11
#define Parametric 12
#define Circle_Direct 13
#define Circle_Polar 14
#define Circle_IterativePolar 15
#define Circle_Midpoint 16
#define Circle_ModifiedMidpoint 17
#define Filling_Circle_withlines1 18
#define Filling_Circle_withlines2 19
#define Filling_Circle_withlines3 20
#define Filling_Circle_withlines4 21
#define Filling_Circle_withcircles1 22
#define Filling_Circle_withcircles2 23
#define Filling_Circle_withcircles3 24
#define Filling_Circle_withcircles4 25
#define Filling_Square 26
#define Filling_Rectangle 27
#define Filling_Convex 28
#define Filling_Non_Convex 29
#define FloodFill_Recursive 30
#define FloodFill_NonRecursive 31
#define Curve_CardinalSpline 32
#define Ellipse_Direct 33
#define Ellipse_Polar 34
#define Ellipse_Midpoint 35
#define Clipping_Rectangle_Point 36
#define Clipping_Rectangle_Line 37
#define Clipping_Rectangle_Polygon 38
#define Clipping_Square_Point 39
#define Clipping_Square_Line 40
#define Clipping_circle_Point 41
#define Clipping_circle_Line 42
#define Intersection 43
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
COLORREF c=RGB(255, 0, 0);
int xc1,xc2,yc1,yc2;

double radius;
int size=0;
int type=100;
int ch1,ch2,len,width,NumberOfPoints;
void ShowMenu(HWND );
HMENU hMenu;
int Round(double x)
{
    return (int)(x+0.5);
}

double distanceBetween2Points(int x1,int x2,int y1,int y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));

}

void save(HWND hwnd)
{
    HDC hdc=GetDC(hwnd);
    ofstream myfile;
    myfile.open ("data.txt");
    RECT rect;
    int width ;
    int height;
    COLORREF c;
    GetWindowRect(hwnd, &rect);
    width = rect.right - rect.left;
    height = rect.bottom - rect.top;
    for(int i =0;i<=width;i++)
    {
       for(int j =0;j<=height;j++)
       {
          c=GetPixel(hdc,i,j);
          myfile <<i<<" "<<j<<" "<<c<<endl;
       }
    }
    myfile.close();
}
void load(HWND hwnd)
{
    HDC hdc=GetDC(hwnd);
    ifstream myfile;
    myfile.open ("data.txt");
    int width ;
    int height;
    COLORREF c;

    while (myfile >> width>>height>>c)
    {
        SetPixel(hdc,width,height,c);
    }

}

struct vector2
{
    double x,y;
    vector2(double a=0,double b=0)
    {
        x=a; y=b;
    }
};


void DrawHermiteCurve(HDC hdc, int x1, int u1, int x2, int u2, int y1, int v1, int y2, int v2, COLORREF c)
{
    int a0 = x1;
    int a1 = u1;
    int a2 = -3 * x1 - 2 * u1 + 3 * x2 - u2;
    int a3 = 2 * x1 + 1 * u1 - 2 * x2 + u2;
    int b0 = y1;
    int b1 = v1;
    int b2 = -3 * y1 - 2 * v1 + 3 * y2 - v2;
    int b3 = 2 * y1 + 1 * v1 - 2 * y2 + v2;

    for (double t=0 ; t <= 1 ; t += 0.001)
    {
        double xt = (t * t * t * a3) + (t * t * a2) + (t * a1) + a0;
        double yt = (t * t * t * b3) + (t * t * b2) + (t * b1) + b0;
        SetPixel(hdc, xt, yt, c);

    }
}

void DrawBezierCurve(HDC hdc, int x1 , int x2, int x3, int x4, int y1, int y2, int y3, int y4,COLORREF c)
{
    int a0 = x1;
    int a1 = 3 * (x2 - x1);
    int a2 = 3 * x1 - 6 * x2 + 3 * x3;
    int a3 = -1 * x1 + 3 * x2 - 3 * x3 + x4;
    int b0 = y1;
    int b1 = 3 * (y2 - y1);
    int b2 = 3 * y1 - 6 * y2 + 3 * y3;
    int b3 = -1 * y1 + 3 * y2 - 3 * y3 + y4;

    for (double t=0 ; t <= 1 ; t += 0.001)
    {
        double xt = (t * t * t * a3) + (t * t * a2) + (t * a1) + a0;
        double yt = (t * t * t * b3) + (t * t * b2) + (t * b1) + b0;
        SetPixel(hdc, xt, yt, c);
    }
}

void swap(int &x1, int &y1, int &x2, int &y2)
{
    int tmp = x1;
    x1 = x2;
    x2 = tmp;
    tmp = y1;
    y1 = y2;
    y2 = tmp;

}
void draw8Points(HDC hdc,int xc,int yc,int x,int y,COLORREF c)
{
    SetPixel(hdc,xc+x,yc+y,c);
    SetPixel(hdc,xc-x,yc+y,c);
    SetPixel(hdc,xc-x,yc-y,c);
    SetPixel(hdc,xc+x,yc-y,c);
    SetPixel(hdc,xc+y,yc+x,c);
    SetPixel(hdc,xc-y,yc+x,c);
    SetPixel(hdc,xc-y,yc-x,c);
    SetPixel(hdc,xc+y,yc-x,c);
}

void Draw4Points(HDC hdc, int xc, int yc, int x, int y, COLORREF c)
{
    SetPixel(hdc, xc+x, yc+y, c);
    SetPixel(hdc, xc-x, yc+y, c);
    SetPixel(hdc, xc-x, yc-y, c);
    SetPixel(hdc, xc+x, yc-y, c);
}

void draw2Points(HDC hdc,int xc,int yc,int x,int y,COLORREF c)
{
    if(ch2==1)
    {
        SetPixel(hdc,xc+x,yc-y,c);
        SetPixel(hdc,xc+y,yc-x,c);

    }
    else if(ch2==2)
    {
        SetPixel(hdc,xc-x,yc-y,c);
        SetPixel(hdc,xc-y,yc-x,c);

    }
    else if(ch2==3)
    {
        SetPixel(hdc,xc-x,yc+y,c);
        SetPixel(hdc,xc-y,yc+x,c);
    }
    else if(ch2==4)
    {
        SetPixel(hdc,xc+x,yc+y,c);
        SetPixel(hdc,xc+y,yc+x,c);
    }
}

void lineDDA(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    if(abs(dx) >= abs(dy))
    {
        if(x1 > x2)
        {
            swap(x1, y1, x2, y2);
        }

        int x = x1;
        double y = y1;
        double m = (double)dy/dx;
        SetPixel(hdc, x1, y1, c);
        while(x < x2)
        {
            x++;
            y = y+m;
            SetPixel(hdc, x, Round(y), c);
        }
    }
    else
    {
        if(y1 > y2)
        {
            swap(x1, y1, x2, y2);
        }
        double x = x1;
        int y = y1;
        SetPixel(hdc, x1, y1, c);
        double ml = (double)dx/dy;
        while(y < y2)
        {
            y++;
            x = x+ml;
            SetPixel(hdc, Round(x), y, c);
        }
    }

}
void lineMidPoint(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int d, x, y;
    int change1;
    int change2;

    if(abs(dx)>=abs(dy))
    {
        d = 2*abs(dy)-abs(dx);
        change1= 2*(abs(dy)-abs(dx));
        change2= 2*abs(dy);
        if (x2 >= x1)
        {
            x = x1;
            y = y1;
        }
        else
        {
            x = x2;
            y = y2;
            swap(x1,x2);
        }
        SetPixel(hdc, x, y, c);

        while(x < x2)
        {
            if(d < 0)
            {
                x++;
                d += change2;
            }
            else
            {
                x++;
                if(dx<0 && dy<0 || dx > 0 && dy > 0)
                    y++;
                else
                    y--;
                d+=change1;
            }
            SetPixel(hdc, x, y, c);
        }
    }
    else
    {
        d = 2*abs(dx)-abs(dy);
        change1= 2*(abs(dx)-abs(dy));
        change2= 2*abs(dx);
        if (y2 >= y1)
        {
            x = x1;
            y = y1;
        }
        else
        {
            x = x2;
            y = y2;
            swap(y1,y2);
        }
        SetPixel(hdc, x, y, c);

        while(y < y2)
        {
            if(d <= 0)
            {
                d += change2;
                y++;
            }
            else
            {
                if(dx<0 && dy<0 || dx > 0 && dy > 0)
                    x++;
                else
                    x--;
                d+=change1;
                y++;
            }
            SetPixel(hdc, x, y, c);
        }

    }
}
void draw8PointsWithFilling(HDC hdc,int xc,int yc,int x,int y,COLORREF c)
{
    SetPixel(hdc,xc+x,yc+y,c);
    SetPixel(hdc,xc-x,yc+y,c);
    SetPixel(hdc,xc-x,yc-y,c);
    SetPixel(hdc,xc+x,yc-y,c);
    SetPixel(hdc,xc+y,yc+x,c);
    SetPixel(hdc,xc-y,yc+x,c);
    SetPixel(hdc,xc-y,yc-x,c);
    SetPixel(hdc,xc+y,yc-x,c);
    if(ch1==1&&ch2==1)
    {
        lineMidPoint(hdc,xc,yc,xc+x,yc-y,c);
        lineMidPoint(hdc,xc,yc,xc+y,yc-x,c);

    }
    else if(ch1==1&&ch2==2)
    {
        lineMidPoint(hdc,xc,yc,xc-x,yc-y,c);
        lineMidPoint(hdc,xc,yc,xc-y,yc-x,c);

    }
    else if(ch1==1&&ch2==3)
    {
        lineMidPoint(hdc,xc,yc,xc-x,yc+y,c);
        lineMidPoint(hdc,xc,yc,xc-y,yc+x,c);
    }
    else if(ch1==1&&ch2==4)
    {
        lineMidPoint(hdc,xc,yc,xc+x,yc+y,c);
        lineMidPoint(hdc,xc,yc,xc+y,yc+x,c);
    }

}
void LineParametric(HDC hdc,int xs,int ys,int xe,int ye,COLORREF color)
{
    double x,y,t;
    int dx=xe-xs;
    int dy=ye-ys;
    for(t=0;t<=1;t+=.002)
    {
        x=xs+(t*dx);
        y=ys+(t*dy);
        SetPixel(hdc,Round(x),Round(y),color);
    }
}
void circlecart(HDC hdc,int xc,int yc,int r,COLORREF c)
{
    double x=0,y=r;
    draw8Points(hdc,xc,yc,0,r,c);
    while(x<y)
    {
        x++;
        y=sqrt((double)r*r-x*x);
        draw8Points(hdc,xc,yc,x,Round(y),c);
    }
}
void cerclePolar(HDC hdc,int xc,int yc,int r,COLORREF c)
{
    double dtheta=1.0/r,theta=0,x=r,y=0;
    draw8Points(hdc,xc,yc,r,0,c);
    while(x>y)
    {
        theta+=dtheta;
        x=r*cos(theta);
        y=r*sin(theta);
        draw8Points(hdc,xc,yc,Round(x),Round(y),c);
    }
}
void circleIterativePolar(HDC hdc,int xc,int yc,int r,COLORREF c)
{
    double dtheta=1.0/r,theta=0,x=r,y=0,ct=cos(dtheta),st=sin(dtheta),x1;
    draw8Points(hdc,xc,yc,r,0,c);
    while(x>y)
    {
        x1=x*ct-y*st;
        y=x*st+y*ct;
        x=x1;
        draw8Points(hdc,xc,yc,Round(x),Round(y),c);

    }
}
void brsenhamCircle1(HDC hdc,int xc,int yc,int r,COLORREF c)
{
    int x=0,y=r,d=1-r,c1=2*x+3,c2=2*x-2*y+5;
    draw8Points(hdc,xc,yc,0,r,c);
    while(x<y)
    {
        if(d>0)
        {
            d+=2*x-2*y+5;
            y--;
        }
        else
           d+=2*x+3;
        x++;
        draw8Points(hdc,xc,yc,x,y,c);
    }
}
void brsenhamCircle2(HDC hdc,int xc,int yc,int r,COLORREF c)
{
    int x=0,y=r,d=1-r,d1=3,d2=5-2*r;
    draw8Points(hdc,xc,yc,0,r,c);
    while(x<y)
    {
        if(d>0)
        {
            d+=d2;
            d2+=4;
            y--;
        }
        else
        {
            d+=d1;
            d2+=2;
        }
        d1+=2;
        x++;
        draw8Points(hdc,xc,yc,x,y,c);
    }
}
void brsenhamCircle2WithFilling(HDC hdc,int xc,int yc,int r,COLORREF c)
{
    int x=0,y=r,d=1-r,d1=3,d2=5-2*r;
    draw8PointsWithFilling(hdc,xc,yc,0,r,c);
    while(x<y)
    {
        if(d>0)
        {
            d+=d2;
            d2+=4;
            y--;
        }
        else
        {
            d+=d1;
            d2+=2;
        }
        d1+=2;
        x++;
        draw8PointsWithFilling(hdc,xc,yc,x,y,c);
    }
    if(ch1==2)
    {
        for(int i=1;i<=r;i++)
        {
            x=0,y=i,d=1-i,d1=3,d2=5-2*i;
            draw2Points(hdc,xc,yc,0,i,c);
            while(x<y)
            {
                if(d>0)
                {
                    d+=d2;
                    d2+=4;
                    y--;
                }
                else
                {
                    d+=d1;
                    d2+=2;
                }
                d1+=2;
                x++;
                draw2Points(hdc,xc,yc,x,y,c);
            }
        }
    }
}



void drawSquare(HDC hdc,vector2& p1,double sideLen,COLORREF c)
{
    double left=p1.x;
    double right=p1.x+sideLen;
    double top=p1.y;
    double bottom=p1.y+sideLen;
    lineDDA(hdc,left,top,right,top,c);
    lineDDA(hdc,left,top,left,bottom,c);
    lineDDA(hdc,right,top,right,bottom,c);
    lineDDA(hdc,left,bottom,right,bottom,c);

    while(left<right)
    {
        double nwLeft=left-sideLen/16;
        vector2 t0( (left - nwLeft),  (top - (top+sideLen/16)));
        vector2 t1( (left - nwLeft), (bottom - (bottom-sideLen/16)));
        vector2 p0(left, top);
        vector2 p1(left, bottom);
        DrawHermiteCurve(hdc, p0.x, t0.x,p1.x, t1.x, p0.y, t0.y,p1.y, t1.y, c);
        left+=sideLen/32;
    }
}

void drawSquareClip(HDC hdc,vector2& p1,double sideLen,COLORREF c)
{
    double left=p1.x;
    double right=p1.x+sideLen;
    double top=p1.y;
    double bottom=p1.y+sideLen;
    lineDDA(hdc,left,top,right,top,c);
    lineDDA(hdc,left,top,left,bottom,c);
    lineDDA(hdc,right,top,right,bottom,c);
    lineDDA(hdc,left,bottom,right,bottom,c);
}

void drawRectangle(HDC hdc,vector2& p1,double height,double width,COLORREF c)
{
    double left=p1.x;
    double right=p1.x+height;
    double top=p1.y;
    double bottom=p1.y+width;
    lineDDA(hdc,left,top,right,top,c);
    lineDDA(hdc,left,top,left,bottom,c);
    lineDDA(hdc,right,top,right,bottom,c);
    lineDDA(hdc,left,bottom,right,bottom,c);
    while(top<bottom)
    {
        vector2 p4( (left+width/32),  (top+height/32));
        vector2 p3( (right-width/32), (top+height/32));
        vector2 p1(left, top);
        vector2 p2(right, top);
        DrawBezierCurve(hdc, p1.x, p4.x,p2.x, p3.x, p1.y, p4.y,p2.y, p3.y, c);
        top+=width/128;
    }
}
void drawRectangleClip(HDC hdc,vector2& p1,double height,double width,COLORREF c)
{
    double left=p1.x;
    double right=p1.x+height;
    double top=p1.y;
    double bottom=p1.y+width;
    lineDDA(hdc,left,top,right,top,c);
    lineDDA(hdc,left,top,left,bottom,c);
    lineDDA(hdc,right,top,right,bottom,c);
    lineDDA(hdc,left,bottom,right,bottom,c);
}

struct Point{
int x,y;
Point(int x=0,int y=0):x(x),y(y){}
};

typedef struct { int xleft, xright; }EdgeTable[800];


void SwapPoints(Point& p1, Point& p2)
{
    Point tmp = p1;
    p1= p2;
    p2= tmp;
}
void InitEdgeTable(EdgeTable tbl) {
    for (int i = 0; i < 800; i++) {
        tbl[i].xleft = INT_MAX;
        tbl[i].xright = -INT_MAX;
    }
}

void scaninitEdge(Point p1, Point p2, EdgeTable tbl) {
    if (p1.y == p2.y) return;
    if (p1.y > p2.y) SwapPoints(p1, p2);
    double minv = (p2.x - p1.x) / (double)(p2.y - p1.y);
    double x = p1.x;
    int y = p1.y;
    while (y < p2.y) {
        if (x < tbl[y].xleft) tbl[y].xleft = ceil(x);
        if (x > tbl[y].xright) tbl[y].xright = floor(x);
        y++;
        x += minv;
    }

}

void polygon2Table(Point p[], int n, EdgeTable tbl) {

    Point v1 = p[n - 1];
    for (int i = 0; i < n; i++) {
        Point v2 = p[i];
        scaninitEdge(v1, v2, tbl);
        v1 = v2;
    }
}
void table2Screen(HDC hdc, EdgeTable tbl, COLORREF c) {
    for (int i = 0; i < 800; i++) {
        if (tbl[i].xleft < tbl[i].xright)
            lineDDA(hdc, tbl[i].xleft, i, tbl[i].xright, i, c);
    }
}

void Convex_filling(HDC hdc, Point p[], int n, COLORREF c) {
    EdgeTable tbl;
    InitEdgeTable(tbl);
    polygon2Table(p, n, tbl);
    table2Screen(hdc, tbl, c);
}

struct EdgeRec
{
    double x,minv;
    int ymax;
    //sorting function to sort edge records in ascending order with x
    bool operator< (EdgeRec r)
    {
        return x<r.x;
    }
};


typedef list<EdgeRec> EdgeList;

EdgeRec InitEdgeRec(Point& v1,Point& v2)
{
    if(v1.y>v2.y)swap(v1,v2);
    EdgeRec rec;
    rec.x=v1.x;
    rec.ymax=v2.y;
    rec.minv=(double)(v2.x-v1.x)/(v2.y-v1.y);
    return rec;
}

void InitEdgeTable2(Point *polygon,int n,EdgeList table[])
{
    Point v1=polygon[n-1];
    for(int i=0; i<n; i++)
    {
        Point v2=polygon[i];
        if(v1.y==v2.y) //horizontal edge
        {
            v1=v2;
            continue;
        }
        EdgeRec rec=InitEdgeRec(v1, v2);
        table[v1.y].push_back(rec);
        v1=polygon[i];
    }
}

void NonConvex_filling(HDC hdc,Point *polygon,int n,COLORREF c)
{
    EdgeList *table=new EdgeList [800];
    InitEdgeTable2(polygon,n,table);
    int y=0;
    while(y<800 && table[y].size()==0)y++; //get the first not null index
    if(y==800)return;
    EdgeList ActiveList=table[y];
    while (ActiveList.size()>0)
    {
        ActiveList.sort();
        //1.sort according to x
        for(EdgeList::iterator it=ActiveList.begin(); it!=ActiveList.end(); it++)
        {
        //2.for each non overlapping two points draw a line
            int x1=(int)ceil(it->x); //first point
            it++;
            int x2=(int)floor(it->x); //second point
            //draw line
            for(int x=x1; x<=x2; x++)SetPixel(hdc,x,y,c);
        }
        //3. increase y
        y++;
        //4.for each node N in active remove the node if N.ymax = y
        EdgeList::iterator it=ActiveList.begin();
        while(it!=ActiveList.end())
            if(y==it->ymax) it=ActiveList.erase(it);
            else it++;
        //5.for each node N in active update N.xmin
        for(EdgeList::iterator it=ActiveList.begin(); it!=ActiveList.end(); it++)
            it->x+=it->minv;
        //6. append table[y] to active
        ActiveList.insert(ActiveList.end(),table[y].begin(),table[y].end());
    }
    delete[] table;
}

void RFloodFill(HDC hdc,int x,int y,COLORREF bc,COLORREF fc)
{
    COLORREF c =GetPixel(hdc,x,y);
    if (c==bc||c==fc)
        return;
    SetPixel(hdc,x,y,fc);
    RFloodFill(hdc,x+1,y,bc,fc);
    RFloodFill(hdc,x,y+1,bc,fc);
    RFloodFill(hdc,x-1,y,bc,fc);
    RFloodFill(hdc,x,y-1,bc,fc);
}

void NRFloodFill(HDC hdc,int x,int y,COLORREF bc,COLORREF fc)
{
    COLORREF c;
    stack<int> sx, sy;
    int a,b;
    sx.push(x);sy.push(y);
    while(!sx.empty())
    {
        a=sx.top(),b=sy.top();
        sx.pop();sy.pop();
        c  =GetPixel(hdc,a,b);
        if (c==bc||c==fc)
            continue;
        SetPixel(hdc,a,b,fc);
        sx.push(a+1);sy.push(b);
        sx.push(a);sy.push(b+1);
        sx.push(a-1);sy.push(b);
        sx.push(a);sy.push(b-1);
    }

}

void DrawcardinalSpline(HDC hdc, vector2 P[], int n, double d,COLORREF c)
{
    double c1 = 1 - d;
    vector2 T[n];
    for(int i=1; i < n-1; i++)
    {
        T[i]=vector2 (c1 * (P[i+1].x - P[i-1].x), c1 * (P[i+1].y - P[i-1].y));
    }
    T[0] = vector2 (c1 * (P[1].x - P[0].x), c1 * (P[1].y - P[0].y));
    T[n-1] = vector2 (c1 * (P[n-1].x - P[n-2].x),c1 * (P[n-1].y - P[n-2].y));
    for(int i=0; i < n-1; i++)
    {
        DrawHermiteCurve(hdc, P[i].x, T[i].x, P[i+1].x, T[i+1].x, P[i].y, T[i].y, P[i+1].y, T[i+1].y,c);
    }
}

void EllipseDirect(HDC hdc, int xc, int yc, int a, int b, COLORREF c)
{
    double x1 = 0, y1 = b, x2 = a, y2 = 0;
    Draw4Points(hdc, xc, yc, x1, y1, c);

    while (b * b * x1 < a * a * y1)
    {
		x1 += 1;
		y1 = b * sqrt(1.0 - (double)pow(x1, 2) / pow(a, 2));
		Draw4Points(hdc,xc, yc, x1, Round(y1),c);

	}
	Draw4Points(hdc, xc, yc, x2, y2, c);
	while (b * b * x2 > a * a * y2)
    {
		y2 += 1;
		x2 = a * sqrt(1.0 - (double)pow(y2, 2) / pow(b, 2));
		Draw4Points(hdc,xc, yc, round(x2), y2,c);
	}

}

void EllipsePolar(HDC hdc, int xc, int yc, int a, int b, COLORREF c)
{
    double x = a, y = 0;
    double theta = 0;
    double dtheta = 1.0/max(a,b);
    Draw4Points(hdc, xc, yc, x, y, c);

    while(theta <= 1.57 )
    {
            x = a*cos(theta);
            y = b*sin(theta);
            Draw4Points(hdc, xc, yc, Round(x), Round(y), c);
            theta += dtheta;
    }
}
void EllipseMidpoint(HDC hdc, int xc, int yc, int a, int b, COLORREF c) {
    int x = 0, y = b;
    int a_sqr = a * a;
    int b_sqr = b * b;
    double d = b_sqr + a_sqr * (-b+0.25);
    Draw4Points(hdc, xc, yc, x, y, c);

    while (b_sqr * (x + 1) < a_sqr * (y - 0.5)) {
        if (d < 0) {
            d += b_sqr * (2 * x + 3);
            x++;
        }
        else {
            d += (b_sqr * (2 * x + 3) + a_sqr * (-2 * y + 2));
            x++;
            y--;
        }
        Draw4Points(hdc, xc, yc, x, y, c);
    }

    d = b_sqr * (x + 0.5) * (x + 0.5) + a_sqr * (y - 1) * (y - 1) - a_sqr * b_sqr;

    while (y >= 0) {
        if (d < 0) {
            d += b_sqr * (2 * x + 2) + a_sqr * (-2 * y + 3);
            x++;
            y--;
        }
        else {
            d += a_sqr * (-2 * y + 3);
            y--;
        }
        Draw4Points(hdc, xc, yc, x, y, c);
    }
}


void clippingPoint(HDC hdc ,int x , int y , int xL , int yT , int xR , int yB , COLORREF c )
{
    if(x>=xL && x<= xR && y>=yT && y<=yB )
	{
	     SetPixel(hdc,x,y,c);
	    cout<<"The point is inside the window\n";

	}
	else cout<<"The point is outside the window\n";
}

union OutCode
{
    unsigned all:4;
    struct{ unsigned left:1, right:1, bottom:1, top:1 ;};
};

OutCode GetOutCode(double x, double y, int xleft,int ytop,int xright,int ybottom)
{
    OutCode r;
    r.all = 0;
    if(x < xleft) r.left = 1;
    else if(x > xright) r.right = 1;
    if(y > ybottom) r.bottom = 1;
    else if(y < ytop) r.top = 1;
    return r;
}

void VIntersection(double x1, double y1, double x2, double y2, int xedge, double *xintersection, double *yintersection)
{
    *xintersection = xedge;
    *yintersection = y1 +((xedge-x1)*(y2-y1)/(x2-x1));

}

void HIntersection(double x1, double y1, double x2, double y2, int yedge, double *xintersection, double *yintersection)
{
    *yintersection = yedge;
    *xintersection = x1 +((yedge-y1)*(x2-x1)/(y2-y1));
}


void CohenSuther(HDC hdc, int xx1, int yy1, int xx2, int yy2, int xleft,int ytop,int xright,int ybottom,COLORREF c)
{
    double x1 = xx1, y1 = yy1, x2 = xx2, y2 = yy2;
    OutCode out1 = GetOutCode(x1, y1, xleft, ytop, xright, ybottom);
    OutCode out2 = GetOutCode(x2, y2, xleft, ytop, xright, ybottom);

    while((out1.all || out2.all) && !(out1.all & out2.all))
    {
        double xi, yi;
        if(out1.all)
        {
            if(out1.left) VIntersection(x1, y1, x2, y2, xleft, &xi, &yi);
            else if(out1.right) VIntersection(x1, y1, x2, y2, xright, &xi, &yi);
            else if(out1.bottom) HIntersection(x1, y1, x2, y2, ybottom, &xi, &yi);
            else HIntersection(x1, y1, x2, y2, ytop, &xi, &yi);
            x1 = xi;
            y1 = yi;
            out1 = GetOutCode(x1, y1, xleft, ytop, xright, ybottom);
        }
        else
        {
            if(out2.left) VIntersection(x1, y1, x2, y2, xleft, &xi, &yi);
            else if(out2.right) VIntersection(x1, y1, x2, y2, xright, &xi, &yi);
            else if(out2.bottom) HIntersection(x1, y1, x2, y2, ybottom, &xi, &yi);
            else HIntersection(x1, y1, x2, y2, ytop, &xi, &yi);
            x2 = xi;
            y2 = yi;
            out2 = GetOutCode(x2, y2, xleft, ytop, xright, ybottom);
        }

    }
    if (!out1.all && !out2.all)
    {
        lineDDA(hdc, x1, y1, x2, y2, c);
    }

}
typedef vector<vector2> VertexList;
typedef bool (*IsInFunc)(vector2& v, int edge);
typedef vector2(*IntersectFunc)(vector2& v1, vector2& v2, int edge);
VertexList ClipWithEdge(VertexList p, int edge, IsInFunc In, IntersectFunc Intersect)
{
    VertexList OutList;
    vector2 v1 = p[p.size() - 1];
    bool v1_in = In(v1, edge);
    for (int i = 0; i < (int)p.size(); i++)
    {
        vector2 v2 = p[i];
        bool v2_in = In(v2, edge);
        if (!v1_in && v2_in)
        {
            OutList.push_back(Intersect(v1, v2, edge));
            OutList.push_back(v2);
        }
        else if (v1_in && v2_in) OutList.push_back(v2);
        else if (v1_in) OutList.push_back(Intersect(v1, v2, edge));
        v1 = v2;
        v1_in = v2_in;
    }
    return OutList;
}
bool InLeft(vector2& v, int edge)
{
    return v.x >= edge;
}
bool InRight(vector2& v, int edge)
{
    return v.x <= edge;
}
bool InTop(vector2& v, int edge)
{
    return v.y >= edge;
}
bool InBottom(vector2& v, int edge)
{
    return v.y <= edge;
}
vector2 VIntersect(vector2& v1, vector2& v2, int xedge)
{
    vector2 res;
    res.x = xedge;
    res.y = v1.y + (xedge - v1.x) * (v2.y - v1.y) / (v2.x - v1.x);
    return res;
}
vector2 HIntersect(vector2& v1, vector2& v2, int yedge)
{
    vector2 res;
    res.y = yedge;
    res.x = v1.x + (yedge - v1.y) * (v2.x - v1.x) / (v2.y - v1.y);
    return res;
}
void PolygonClip(HDC hdc, vector2* p, int n, int xleft, int ytop, int xright, int ybottom,COLORREF c)
{
    VertexList vlist;
    for (int i = 0; i < n; i++)vlist.push_back(vector2(p[i].x, p[i].y));
    vlist = ClipWithEdge(vlist, xleft, InLeft, VIntersect);
    vlist = ClipWithEdge(vlist, ytop, InTop, HIntersect);
    vlist = ClipWithEdge(vlist, xright, InRight, VIntersect);
    vlist = ClipWithEdge(vlist, ybottom, InBottom, HIntersect);
    vector2 v1 = vlist[vlist.size() - 1];
    for (int i = 0; i < (int)vlist.size(); i++)
    {
        vector2 v2 = vlist[i];
        lineDDA(hdc, v1.x, v1.y, v2.x, v2.y, c);
        v1 = v2;
    }
}

void CircleclippingPoint(HDC hdc ,int x , int y ,int xc,int yc,int r, COLORREF c )
{
    int distance = Round(sqrt(pow(x - xc, 2) + pow(y - yc, 2)));
    if (distance <= r)
	{
	     SetPixel(hdc,x,y,c);
	    cout<<"The point is inside the window\n";

	}
	else cout<<"The point is outside the window\n";
}
void Circleclippingline(HDC hdc,int xs,int ys,int xe,int ye,int xc,int yc,int r,COLORREF c)
{
    double x,y,t;
    int dx=xe-xs;
    int dy=ye-ys;
    int distance = Round(sqrt(pow(xs - xc, 2) + pow(ys - yc, 2)));
    if (distance <= r) {
        SetPixel(hdc, xs, ys, c);
    }
    for(t=0;t<=1;t+=.002)
    {
        x=xs+(t*dx);
        y=ys+(t*dy);
        distance = Round(sqrt(pow(x - xc, 2) + pow(Round(y) - yc, 2)));
        if (distance <= r)
        {
            SetPixel(hdc, x, Round(y), c);
        }
    }
}
void check_intersection(HDC hdc, int x1, int y1, int x2, int y2, int r1, int r2,COLORREF c) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    double dist = sqrt(dx * dx + dy * dy);

    if (dist > r1 + r2 ) {
        cout << "The circles do not intersect." << endl;
        return;
    }
    else if (dist == r1 + r2 )
    {
        cout << "The circles intersect in one point" << endl;
        return;
    }

    double theta1 = atan2(dy, dx);
    double theta2 = acos((r1 * r1 - r2 * r2 + dist * dist) / (2 * r1 * dist));

    double x_intersect1 = x1 + r1 * cos(theta1 + theta2);
    double y_intersect1 = y1 + r1 * sin(theta1 + theta2);
    double x_intersect2 = x1 + r1 * cos(theta1 - theta2);
    double y_intersect2 = y1 + r1 * sin(theta1 - theta2);

    double mx  = (x_intersect1+x_intersect2)/2;
    double my  = (y_intersect1+y_intersect2)/2;

    NRFloodFill(hdc,mx,my,c,RGB(0,51,102));


}

static Point convex[10];
static Point NonConvex[10];

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_CROSS);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Code::Blocks Template Windows App"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc= GetDC(hwnd);
    static int count2 =0;
    static vector2 x0,x1,x2,p[100],s;
    static int itr=0;
    static int counter = 0;
    static int index = 0;
    static int xc,yc,dx,dy,dx2,dy2,r,r2,xc2,yc2;
    static int l1,l2,l3,l4;
    switch (message)                  /* handle the messages */
    {
        case WM_COMMAND:
            switch(wParam)
            {//Red","Green","Blue","Black","Yellow","Purple
                case Save:
                    cout<<"You save the window"<<endl;
                    save(hwnd);
                    break;
                case Load:
                    cout<<"You load the window"<<endl;
                    load(hwnd);
                    break;
                case GREEN:
                    cout<<"You change the color to Green"<<endl;
                    c=RGB(0,255,0);
                    break;
                case BLACK:
                    cout<<"You change the color to Blake"<<endl;
                    c=RGB(0,0,0);
                    break;
                case RED:
                    cout<<"You change the color to Red"<<endl;
                    c=RGB(255,0,0);
                    break;
                case BLUE:
                    cout<<"You change the color to Blue"<<endl;
                    c=RGB(0,0,255);
                    break;
                case Yellow:
                    cout<<"You change the color to Yellow"<<endl;
                    c=RGB(255,215,0);
                    break;
                case Purple:
                    cout<<"You change the color to Purple"<<endl;
                    c=RGB(128,0,128);
                    break;
                case Clear:
                    cout<<"You clear the window"<<endl;
                    InvalidateRect(hwnd, 0, TRUE);
                    break;
                case DDA:
                    type=0;
                    break;
                case midpoint :
                    type=1;
                    break;
                case Parametric :
                    type=2;
                    break;
                case Circle_Direct  :
                    type=3;
                    break;
                case Circle_Polar :
                    type=4;
                    break;
                case Circle_IterativePolar  :
                    type=5;
                    break;
                case Circle_Midpoint  :
                    type=6;
                    break;
                case Circle_ModifiedMidpoint  :
                    type=7;
                    break;
                case Filling_Circle_withlines1   :
                    ch1=1;
                    ch2=1;
                    type=8;
                    break;
                case Filling_Circle_withlines2   :
                    ch1=1;
                    ch2=2;
                    type=9;
                    break;
                case Filling_Circle_withlines3   :
                    ch1=1;
                    ch2=3;
                    type=10;
                    break;
                case Filling_Circle_withlines4   :
                    ch1=1;
                    ch2=4;
                    type=11;
                    break;
                case Filling_Circle_withcircles1   :
                    ch1=2;
                    ch2=1;
                    type=12;
                    break;
                case Filling_Circle_withcircles2   :
                    ch1=2;
                    ch2=2;
                    type=13;
                    break;
                case Filling_Circle_withcircles3   :
                    ch1=2;
                    ch2=3;
                    type=14;
                    break;
                case Filling_Circle_withcircles4   :
                    ch1=2;
                    ch2=4;
                    type=15;
                    break;
                 case Filling_Square    :
                    type=16;
                    break;
                case Filling_Rectangle  :
                    type=17;
                    break;
                case Filling_Convex  :
                type=18;
                    cout<<"You fill Convex polygon"<<endl;
                    cout<<"Please Enter Number of Points :";
                    cin>>NumberOfPoints;
                    break;
                case Filling_Non_Convex :
                    type=19;
                    cout<<"You fill NonConvex polygon"<<endl;
                    cout<<"Please Enter Number of Points :";
                    cin>>NumberOfPoints;
                    break;
                case FloodFill_Recursive  :
                    cout<<"You fill the shape by Recursive FloodFill"<<endl;
                    type=20;
                    break;
                case FloodFill_NonRecursive  :
                    cout<<"You fill the shape by NonRecursive FloodFill"<<endl;
                    type=21;
                    break;
                case Curve_CardinalSpline :
                    cout<<"You Draw Cardinal Spline Curve"<<endl;
                    cout<<"Please Enter Number of Points :";
                    cin>>NumberOfPoints;
                    type=22;
                    count2=0;
                    break;
                case Ellipse_Direct  :
                    cout<<"You Draw Direct Ellipse"<<endl;
                    type=23;
                    break;
                case Ellipse_Polar   :
                    cout<<"You Draw Ellipse by Polar"<<endl;
                    type=24;
                    break;
                case Ellipse_Midpoint  :
                    cout<<"You Draw Ellipse by Midpoint"<<endl;
                    type=25;
                    break;
                case Clipping_Rectangle_Point  :
                    cout<<"Draw Rectangle and Clip Point"<<endl;
                    type=26;
                    count2=0;
                    break;
                case Clipping_Rectangle_Line   :
                    cout<<"Draw Rectangle and Clip Line"<<endl;
                    count2=0;
                    type=27;
                    break;
                case Clipping_Rectangle_Polygon :
                    cout<<"Draw Rectangle and Clip Polygon"<<endl;
                    cout<<"Please Enter Number of Points :";
                    cin>>NumberOfPoints;
                    count2=0;
                    type=28;
                    break;
                case Clipping_Square_Point   :
                    cout<<"Draw Rectangle and Clip Point"<<endl;
                    type=29;
                    count2=0;
                    break;
                case Clipping_Square_Line  :
                    cout<<"Draw Rectangle and Clip Line"<<endl;
                    type=30;
                    count2=0;
                    break;
                case Clipping_circle_Point  :
                    cout<<"Draw Circle and Clip Point"<<endl;
                    type=31;
                    count2=0;
                    break;
                case Clipping_circle_Line   :
                    cout<<"Draw Circle and Clip Line"<<endl;
                    type=32;
                    count2=0;
                    break;
                case Intersection:
                    cout<<"Draw 2 Circle And we will fill the Intersection"<<endl;
                    type=33;
                    break;
            }
            break;
        case WM_LBUTTONDOWN:
            xc1 = LOWORD(lParam);
            yc1 = HIWORD(lParam);
            break;
        case WM_RBUTTONDOWN:
            xc2=LOWORD(lParam);
            yc2=HIWORD(lParam);
            radius=distanceBetween2Points(xc1,xc2,yc1,yc2);

            ////////////////////////////////line//////////////////////////////////////
            if(type==0)//call line_DDA  fundtion
            {
                cout<<"You Draw line by DDA"<<endl;
                lineDDA(hdc,xc1,yc1,xc2,yc2,c);
            }
            else if(type==1) //call line_midpoint fundtion
            {
                cout<<"You Draw line by MidPoint"<<endl;
                lineMidPoint(hdc,xc1,yc1,xc2,yc2,c);
            }
            else if(type==2) //call line_Parametric  fundtion
            {
                cout<<"You Draw line by Parametric"<<endl;
                LineParametric(hdc,xc1,yc1,xc2,yc2,c);
            }
            ////////////////////////////////Circle///////////////////////////////////////
            else if(type==3)//call Circle_Direct  fundtion
            {
                cout<<"You Draw Circle by Direct"<<endl;
                circlecart(hdc,xc1,yc1,radius,c);
            }
            else if(type==4)  //call Circle_Polar  fundtion
            {
                cout<<"You Draw Circle by Polar"<<endl;
                cerclePolar(hdc,xc1,yc1,radius,c);
            }
            else if(type==5) //call Circle_IterativePolar fundtion
            {
                cout<<"You Draw Circle by IterativePolar"<<endl;
                circleIterativePolar(hdc,xc1,yc1,radius,c);
            }
            else if(type==6) //call Circle_Midpoint fundtion
            {
                cout<<"You Draw Circle by Midpoint"<<endl;
                brsenhamCircle1(hdc,xc1,yc1,radius,c);
            }
            else if(type==7) //call Circle_ModifiedMidpoint  fundtion
            {
                cout<<"You Draw Circle by ModifiedMidpoint"<<endl;
                brsenhamCircle2(hdc,xc1,yc1,radius,c);
            }
            ////////////////////////////////Filling///////////////////////////////////////
            else if(type==8)  //Filling_Circle_withlines1
            {
                cout<<"You Draw  Circle Filling by lines in First quarter"<<endl;
                brsenhamCircle2WithFilling(hdc,xc1,yc1,radius,c);
            }
            else if(type==9) //Filling_Circle_withlines2
            {
                cout<<"You Draw  Circle Filling by lines in Second quarter"<<endl;
                brsenhamCircle2WithFilling(hdc,xc1,yc1,radius,c);
            }
            else if(type==10) //Filling_Circle_withlines3
            {
                cout<<"You Draw  Circle Filling by lines in Third quarter"<<endl;
                brsenhamCircle2WithFilling(hdc,xc1,yc1,radius,c);
            }
            else if(type==11) //Filling_Circle_withlines4
            {
                cout<<"You Draw  Circle Filling by lines in Fourth quarter"<<endl;
                brsenhamCircle2WithFilling(hdc,xc1,yc1,radius,c);
            }
            else if(type==12)  //Filling_Circle_withcircles1
            {
                cout<<"You Draw  Circle Filling by Circles in First quarter"<<endl;
                brsenhamCircle2WithFilling(hdc,xc1,yc1,radius,c);
            }
            else if(type==13) //Filling_Circle_withcircles2
            {
                cout<<"You Draw  Circle Filling by Circles in Second quarter"<<endl;
                brsenhamCircle2WithFilling(hdc,xc1,yc1,radius,c);
            }
            else if(type==14) //Filling_Circle_withcircles3
            {
                cout<<"You Draw  Circle Filling by Circles in Third quarter"<<endl;
                brsenhamCircle2WithFilling(hdc,xc1,yc1,radius,c);
            }
            else if(type==15) //Filling_Circle_withcircles4
            {
                cout<<"You Draw  Circle Filling by Circles in Fourth quarter"<<endl;
                brsenhamCircle2WithFilling(hdc,xc1,yc1,radius,c);
            }
            else if(type==16)  //Square Filling by Hermite curve
                {

                if(count2==0)
                {
                    cout<<"You Draw  Square Filling by Hermite curve"<<endl;
                    x0.x= LOWORD(lParam);
                    x0.y= HIWORD(lParam);
                    count2++;
                    break;
                }
                else if(count2==1)
                {
                    x1.x= LOWORD(lParam);
                    x1.y= HIWORD(lParam);
                    len=distanceBetween2Points(x0.x,x1.x,x0.y,x1.y);
                    drawSquare(hdc,x0,len,c);
                    count2=0;
                    break;
                }
            }
              else if(type==17) //Rectangle Filling by Bezier curve
            {
                if(count2==0)
                {
                    cout<<"You Draw  Rectangle Filling by Bezier curve"<<endl;
                    x0.x= LOWORD(lParam);
                    x0.y= HIWORD(lParam);
                    count2++;
                    break;
                }
                else if(count2==1)
                {
                    x1.x= LOWORD(lParam);
                    x1.y= HIWORD(lParam);
                    count2++;
                    break;
                }
                else if(count2==2)
                {
                    x2.x=LOWORD(lParam);
                    x2.y= HIWORD(lParam);
                    len=distanceBetween2Points(x0.x,x1.x,x0.y,x1.y);
                    width=distanceBetween2Points(x0.x,x2.x,x0.y,x2.y);
                    drawRectangle(hdc,x0,len,width,c);
                    count2=0;
                    break;
                }
            }
             else if(type==18)  //call Filling_Convex fundtion
            {
                convex[counter].x = LOWORD(lParam);
                convex[counter].y = HIWORD(lParam);
                if (counter == NumberOfPoints-1)
                {
                    int polygonSz= counter+1;
                    Convex_filling(hdc,convex,polygonSz,c);
                    counter = 0;
                }
                else counter++;

            }
            else if(type==19) //call Filling_Non_Convex fundtion
            {
                NonConvex[counter].x = LOWORD(lParam);
                NonConvex[counter].y = HIWORD(lParam);
                if (counter == NumberOfPoints-1)
                {
                    int polygonSz= counter+1;
                    NonConvex_filling(hdc,NonConvex,polygonSz,c);
                    counter = 0;
                }
                else counter++;
            }
            else if(type==20)   //call FloodFill_Recursive fundtion
            {
                RFloodFill(hdc,xc2,yc2,c,RGB(150,40,102));
            }
            else if(type==21)    //call FloodFill_NonRecursive fundtion
            {
                NRFloodFill(hdc,xc2,yc2,c,RGB(0,51,102));
            }
            else if(type==22)//call DrawCardinalSpline
            {
                p[index] = vector2(LOWORD(lParam), HIWORD(lParam));
                if(index==NumberOfPoints-1)
                {
                    DrawcardinalSpline(hdc, p,NumberOfPoints, .5,c);
                    index = 0;
                }
                else
                {
                    index++;
                }
            }
            else if(type==23) //call Ellipse_Direct  fundtion
            {
                if(count2==0)
                {
                    l1= LOWORD(lParam);
                    l2= HIWORD(lParam);
                    count2++;
                    break;
                }
                else if(count2==1)
                {
                    l3= LOWORD(lParam);
                    l4= HIWORD(lParam);
                    count2++;
                    break;
                }
                else if(count2==2)
                {
                    xc= LOWORD(lParam);
                    yc= HIWORD(lParam);
                    len=distanceBetween2Points(xc,l1,yc,l2);
                    width=distanceBetween2Points(xc,l3,yc,l4);
                    EllipseDirect(hdc,xc,yc,len,width,c);
                    count2=0;
                    break;
                }
            }
            else if(type==24) //call Ellipse_Polar  fundtion
            {
                if(count2==0)
                {
                    l1= LOWORD(lParam);
                    l2= HIWORD(lParam);
                    count2++;
                    break;
                }
                else if(count2==1)
                {
                    l3= LOWORD(lParam);
                    l4= HIWORD(lParam);
                    count2++;
                    break;
                }
                else if(count2==2)
                {
                    xc= LOWORD(lParam);
                    yc= HIWORD(lParam);
                    len=distanceBetween2Points(xc,l1,yc,l2);
                    width=distanceBetween2Points(xc,l3,yc,l4);
                    EllipsePolar(hdc,xc,yc,len,width,c);
                    count2=0;
                    break;
                }
            }
            else if(type==25) //call Ellipse_Midpoint fundtion
            {
                if(count2==0)
                {
                    l1= LOWORD(lParam);
                    l2= HIWORD(lParam);
                    count2++;
                    break;
                }
                else if(count2==1)
                {
                    l3= LOWORD(lParam);
                    l4= HIWORD(lParam);
                    count2++;
                    break;
                }
                else if(count2==2)
                {
                    xc= LOWORD(lParam);
                    yc= HIWORD(lParam);
                    len=distanceBetween2Points(xc,l1,yc,l2);
                    width=distanceBetween2Points(xc,l3,yc,l4);
                    EllipseMidpoint(hdc,xc,yc,len,width,c);
                    count2=0;
                    break;
                }
            }
            ////////////////////////////////Clipping///////////////////////////////////////
            else if(type==26) //call Clipping_Rectangle_Point fundtion
            {
                if(count2==0)
                {
                    s.x= LOWORD(lParam);
                    s.y= HIWORD(lParam);
                    count2++;
                    break;
                }
                else if(count2==1)
                {
                    l1= LOWORD(lParam);
                    l2= HIWORD(lParam);
                    count2++;
                    break;
                }
                else if(count2==2)
                {
                    l3=LOWORD(lParam);
                    l4= HIWORD(lParam);
                    len=distanceBetween2Points(s.x,l1,s.y,l2);
                    width=distanceBetween2Points(s.x,l3,s.y,l4);
                    drawRectangleClip(hdc,s,len,width,c);
                    count2++;
                    break;
                }
                else if(count2==3)
                {
                    l1= LOWORD(lParam);
                    l2= HIWORD(lParam);
                    clippingPoint(hdc,l1,l2,s.x,s.y,s.x+len,s.y+width,c);
                    break;
                }
            }
            else if(type==27) //call Clipping_Rectangle_Line fundtion
            {
                if(count2==0)
                {
                    s.x= LOWORD(lParam);
                    s.y= HIWORD(lParam);
                    count2++;
                    break;
                }
                else if(count2==1)
                {
                    l1= LOWORD(lParam);
                    l2= HIWORD(lParam);
                    count2++;
                    break;
                }
                else if(count2==2)
                {
                    l3=LOWORD(lParam);
                    l4= HIWORD(lParam);
                    len=distanceBetween2Points(s.x,l1,s.y,l2);
                    width=distanceBetween2Points(s.x,l3,s.y,l4);
                    drawRectangleClip(hdc,s,len,width,c);
                    count2++;
                    break;
                }
                else if(count2==3)
                {
                    l1=LOWORD(lParam);
                    l2= HIWORD(lParam);
                    count2++;
                    break;
                }
                else if(count2==4)
                {
                    l3=LOWORD(lParam);
                    l4= HIWORD(lParam);
                    CohenSuther(hdc,l1,l2,l3,l4,s.x,s.y,s.x+len,s.y+width,c);
                    count2=3;
                    break;
                }
            }
            else if(type==28) //call Clipping_Rectangle_Polygon fundtion
            {
                if(count2==0)
                {
                    s.x= LOWORD(lParam);
                    s.y= HIWORD(lParam);
                    count2++;
                    break;
                }
                else if(count2==1)
                {
                    l1= LOWORD(lParam);
                    l2= HIWORD(lParam);
                    count2++;
                    break;
                }
                else if(count2==2)
                {
                    l3=LOWORD(lParam);
                    l4= HIWORD(lParam);
                    len=distanceBetween2Points(s.x,l1,s.y,l2);
                    width=distanceBetween2Points(s.x,l3,s.y,l4);
                    drawRectangleClip(hdc,s,len,width,c);
                    count2++;
                    break;
                }
                else if(count2==3)
                {
                    p[index] = vector2(LOWORD(lParam), HIWORD(lParam));
                    if (index == NumberOfPoints - 1)
                    {
                        PolygonClip(hdc, p, NumberOfPoints, s.x, s.y, s.x + len, s.y + width,c);
                        index = 0;
                    }
                    else index++;
                    break;
                }
                break;
            }
            else if(type==29) //call Clipping_Square_Point fundtion
            {
                if(count2==0)
                {
                    s.x= LOWORD(lParam);
                    s.y= HIWORD(lParam);
                    count2++;
                    break;
                }
                else if(count2==1)
                {
                    l1= LOWORD(lParam);
                    l2= HIWORD(lParam);
                    len=distanceBetween2Points(s.x,l1,s.y,l2);
                    drawSquareClip(hdc,s,len,c);
                    count2++;
                    break;
                }
                else if(count2==2)
                {
                    l1= LOWORD(lParam);
                    l2= HIWORD(lParam);
                    clippingPoint(hdc,l1,l2,s.x,s.y,s.x+len,s.y+len,c);
                    break;
                }
            }
            else if(type==30) //call Clipping_Square_Line fundtion
            {
                if(count2==0)
                {
                    s.x= LOWORD(lParam);
                    s.y= HIWORD(lParam);
                    count2++;
                    break;
                }
                else if(count2==1)
                {
                    l1= LOWORD(lParam);
                    l2= HIWORD(lParam);
                    len=distanceBetween2Points(s.x,l1,s.y,l2);
                    drawSquareClip(hdc,s,len,c);
                    count2++;
                    break;
                }
                else if(count2==2)
                {
                    l1=LOWORD(lParam);
                    l2= HIWORD(lParam);
                    count2++;
                    break;
                }
                else if(count2==3)
                {
                    l3=LOWORD(lParam);
                    l4= HIWORD(lParam);
                    CohenSuther(hdc,l1,l2,l3,l4,s.x,s.y,s.x+len,s.y+len,c);
                    count2=2;
                    break;
                }
            }
            else if(type==31) //call CircleclippingPoint  fundtion
            {
                if(count2==0)
                {
                    xc=LOWORD(lParam);
                    yc= HIWORD(lParam);
                    count2++;
                    break;
                }
                else if(count2==1)
                {
                    dx=LOWORD(lParam);
                    dy= HIWORD(lParam);
                    r=distanceBetween2Points(xc,dx,yc,dy);
                    brsenhamCircle2(hdc,xc,yc,r,c);
                    count2++;
                    break;
                }
                else if(count2==2)
                {
                    l1=LOWORD(lParam);
                    l2= HIWORD(lParam);
                    CircleclippingPoint(hdc,l1,l2,xc,yc,r,c);
                }


            }
            else if(type==32) //call CircleclippingLine  fundtion
            {
                if(count2==0)
                {
                    xc=LOWORD(lParam);
                    yc= HIWORD(lParam);
                    count2++;
                    break;
                }
                else if(count2==1)
                {
                    dx=LOWORD(lParam);
                    dy= HIWORD(lParam);
                    r=distanceBetween2Points(xc,dx,yc,dy);
                    brsenhamCircle2(hdc,xc,yc,r,c);
                    count2++;
                    break;
                }
                else if(count2==2)
                {
                    l1=LOWORD(lParam);
                    l2= HIWORD(lParam);
                    count2++;
                    break;
                }
                else if(count2==3)
                {
                    l3=LOWORD(lParam);
                    l4= HIWORD(lParam);
                    Circleclippingline(hdc,l1,l2,l3,l4,xc,yc,r,c);
                    count2=2;
                    break;
                }

            }
             else if(type==33) //call CircleclippingPoint  fundtion
            {
                if(count2==0)
                {
                    xc=LOWORD(lParam);
                    yc= HIWORD(lParam);
                    count2++;
                    break;
                }
                else if(count2==1)
                {
                    dx=LOWORD(lParam);
                    dy= HIWORD(lParam);
                    r=distanceBetween2Points(xc,dx,yc,dy);
                    brsenhamCircle2(hdc,xc,yc,r,c);
                    count2++;
                    break;
                }
                else if(count2==2)
                {
                    l1=LOWORD(lParam);
                    l2= HIWORD(lParam);
                    count2++;
                    break;
                }
                else if(count2==3)
                {
                    l3=LOWORD(lParam);
                    l4= HIWORD(lParam);
                    r2=distanceBetween2Points(l1,l3,l2,l4);
                    circleIterativePolar(hdc,l1,l2,r2,c);
                    check_intersection(hdc,xc,yc,l1,l2,r,r2,c);
                    count2=0;
                    break;
            }

            }
        case WM_CREATE:
            ShowMenu(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

void ShowMenu(HWND hwnd)
{
    hMenu=CreateMenu();

    ///////////File Settings/////////////
    HMENU file=CreateMenu();
    size=2;
    char* load_arr[size]= {"Save","Load"};
    int load1[size]= {Save,Load};

    for(int i=0; i<size; i++)
    {
        AppendMenu(file,MF_STRING,load1[i],load_arr[i]);
        if(i!=size-1)AppendMenu(file,MF_SEPARATOR,NULL,NULL);
    }
    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)file,"File");


    ///////////Colors Settings/////////////
    HMENU color=CreateMenu();
    size=6;
    char* colour[size]= {"Red","Green","Blue","Black","Yellow","Purple"};
    int Colors[size]= {RED,GREEN,BLUE,BLACK,Yellow,Purple};

    for(int i=0; i<size; i++)
    {
        AppendMenu(color,MF_STRING,Colors[i],colour[i]);
        if(i!=size-1)AppendMenu(color,MF_SEPARATOR,NULL,NULL);
    }
    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)color,"Change Color");


    ///////////Clear/////////////
    AppendMenu(hMenu,MF_STRING,Clear,"Clear");


    ///////////Line/////////////
    HMENU Line=CreateMenu();
    size=3;
    char* line_types[size]= {"DDA","midpoint","Parametric"};
    int line1[size]= {DDA,midpoint,Parametric};

    for(int i=0; i<size; i++)
    {
        AppendMenu(Line,MF_STRING,line1[i],line_types[i]);
        if(i!=size-1)  AppendMenu(Line,MF_SEPARATOR,NULL,NULL);
    }
    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)Line,"Line");


    ///////////Circle/////////////
    HMENU Circle=CreateMenu();
    size=5;
    char* Circle_types[size]= {"Direct","Polar","Iterative Polar","Midpoint","Modified Midpoint"};
    int Circle1[size]= {Circle_Direct,Circle_Polar,Circle_IterativePolar,Circle_Midpoint,Circle_ModifiedMidpoint};

    for(int i=0; i<size; i++)
    {
        AppendMenu(Circle,MF_STRING,Circle1[i],Circle_types[i]);
        if(i!=size-1) AppendMenu(Circle,MF_SEPARATOR,NULL,NULL);
    }
    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)Circle,"Circle");


    ///////////Filling/////////////
    HMENU Filling=CreateMenu();
    HMENU FillingCircle=CreateMenu();
    AppendMenu(FillingCircle,MF_STRING,Filling_Circle_withlines1,"First quarter with lines");
    AppendMenu(FillingCircle,MF_SEPARATOR,NULL,NULL);
    AppendMenu(FillingCircle,MF_STRING,Filling_Circle_withlines2,"Second quarter with lines");
    AppendMenu(FillingCircle,MF_SEPARATOR,NULL,NULL);
    AppendMenu(FillingCircle,MF_STRING,Filling_Circle_withlines3,"Third quarter with lines");
    AppendMenu(FillingCircle,MF_SEPARATOR,NULL,NULL);
    AppendMenu(FillingCircle,MF_STRING,Filling_Circle_withlines4,"Fourth quarter with lines");
    AppendMenu(FillingCircle,MF_SEPARATOR,NULL,NULL);
    AppendMenu(FillingCircle,MF_STRING,Filling_Circle_withcircles1,"First quarter with circles");
    AppendMenu(FillingCircle,MF_SEPARATOR,NULL,NULL);
    AppendMenu(FillingCircle,MF_STRING,Filling_Circle_withcircles2,"Second quarter with circles");
    AppendMenu(FillingCircle,MF_SEPARATOR,NULL,NULL);
    AppendMenu(FillingCircle,MF_STRING,Filling_Circle_withcircles3,"Third quarter with circles");
    AppendMenu(FillingCircle,MF_SEPARATOR,NULL,NULL);
    AppendMenu(FillingCircle,MF_STRING,Filling_Circle_withcircles4,"Fourth quarter with circles");
    AppendMenu(Filling,MF_POPUP,(UINT_PTR)FillingCircle,"Circle");

    AppendMenu(Filling,MF_SEPARATOR,NULL,NULL);
    AppendMenu(Filling,MF_STRING,Filling_Square,"Square");
    AppendMenu(Filling,MF_SEPARATOR,NULL,NULL);
    AppendMenu(Filling,MF_STRING,Filling_Rectangle,"Rectangle");
    AppendMenu(Filling,MF_SEPARATOR,NULL,NULL);
    AppendMenu(Filling,MF_STRING,Filling_Convex,"Convex");
    AppendMenu(Filling,MF_SEPARATOR,NULL,NULL);
    AppendMenu(Filling,MF_STRING,Filling_Non_Convex,"Non Convex");
    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)Filling,"Filling");
    //////////////////////////FloodFill//////////////////////////////////
    HMENU FloodFill=CreateMenu();

    size=2;
    char* FloodFill_arr[size]= {"Recursive","Non Recursive"};
    int FloodFill1[size]= {FloodFill_Recursive,FloodFill_NonRecursive};

    for(int i=0; i<size; i++)
    {
        AppendMenu(FloodFill,MF_STRING,FloodFill1[i],FloodFill_arr[i]);
        if(i!=size-1)  AppendMenu(FloodFill,MF_SEPARATOR,NULL,NULL);
    }

    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)FloodFill,"FloodFill");

    //////////////////////////Cardinal Spline Curve//////////////////////////////////

    HMENU Curve=CreateMenu();

    AppendMenu(Curve,MF_STRING,Curve_CardinalSpline,"Cardinal Spline");
    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)Curve,"Curve");

     //////////////////////////Ellipse//////////////////////////////////
    HMENU Ellipse=CreateMenu();
    size=3;
    char* Ellipse_types[size]= {"Direct","Polar","Midpoint"};
    int Ellipse1[size]= {Ellipse_Direct,Ellipse_Polar,Ellipse_Midpoint};

    for(int i=0; i<size; i++)
    {
        AppendMenu(Ellipse,MF_STRING,Ellipse1[i],Ellipse_types[i]);
        if(i!=size-1)  AppendMenu(Ellipse,MF_SEPARATOR,NULL,NULL);
    }
    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)Ellipse,"Ellipse");

    //////////////////////////Clipping algorithms//////////////////////////////////

    HMENU Clipping_algorithms=CreateMenu();

    HMENU Clipping_algorithms2=CreateMenu();

    AppendMenu(Clipping_algorithms2,MF_STRING,Clipping_Rectangle_Point,"Point");
    AppendMenu(Clipping_algorithms2,MF_SEPARATOR,NULL,NULL);
    AppendMenu(Clipping_algorithms2,MF_STRING,Clipping_Rectangle_Line,"Line");
    AppendMenu(Clipping_algorithms2,MF_SEPARATOR,NULL,NULL);
    AppendMenu(Clipping_algorithms2,MF_STRING,Clipping_Rectangle_Polygon,"Polygon");

    HMENU Clipping_algorithms3=CreateMenu();
    AppendMenu(Clipping_algorithms3,MF_STRING,Clipping_Square_Point,"Point");
    AppendMenu(Clipping_algorithms3,MF_SEPARATOR,NULL,NULL);
    AppendMenu(Clipping_algorithms3,MF_STRING,Clipping_Square_Line,"Line");

    HMENU Clipping_algorithms4=CreateMenu();
    AppendMenu(Clipping_algorithms4,MF_STRING,Clipping_circle_Point,"Point");
    AppendMenu(Clipping_algorithms4,MF_SEPARATOR,NULL,NULL);
    AppendMenu(Clipping_algorithms4,MF_STRING,Clipping_circle_Line,"Line");


    AppendMenu(Clipping_algorithms,MF_POPUP,(UINT_PTR)Clipping_algorithms2,"Rectangle");
    AppendMenu(Clipping_algorithms,MF_SEPARATOR,NULL,NULL);
    AppendMenu(Clipping_algorithms,MF_POPUP,(UINT_PTR)Clipping_algorithms3,"Square");
    AppendMenu(Clipping_algorithms,MF_SEPARATOR,NULL,NULL);
    AppendMenu(Clipping_algorithms,MF_POPUP,(UINT_PTR)Clipping_algorithms4,"Circle");


    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)Clipping_algorithms,"Clipping algorithms");


    ////////////////////2 Circle filling///////////
    AppendMenu(hMenu,MF_STRING,Intersection,"Fill intersection of 2 circles");


    SetMenu(hwnd,hMenu);
}
