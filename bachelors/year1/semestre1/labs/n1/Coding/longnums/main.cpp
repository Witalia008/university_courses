#include <stdio.h>
#include <cstdlib>
#include <memory.h>
#include <string>
#include <iostream>
#include <math.h>
#include <complex>
#include <vector>
#include <fstream>
#define PI 3.141596535897932384642
#define sqr(a) ((a)*(a))

using namespace std;

typedef complex <double> BASE;

const int nmax=1000;

struct TLong
{
    int len,point,bracket, base;
    char sign;
    int n[nmax+1];
    TLong ()
    {
        len = point = bracket = 0;
        base = 10; sign = '+';
        memset (n, 0, sizeof (n));
    }
    void FromStr (string s);
    string ToStr ();
    void Input(ifstream & fin, int bs);
    void Output(ofstream & fout);
    int LongLen();
    void Shift(int k);
    void DelZeros();
    bool Comp_0();
    int Comp(TLong a);
    int Comp_Abs(TLong a);
    void Add_Abs(TLong a,TLong b);
    void Minus_Abs(TLong a,TLong b);
    TLong Add(TLong a,TLong b);
    TLong Minus(TLong a,TLong b);
    int HalfLongDiv(int b,int k);
    void HalfLongMulti(int b);
    TLong Multi(TLong a,TLong b);
    TLong Div_Mod(TLong b,int k);
    int nMult(int b);
    int Entire(TLong &a,TLong b);
    void GCD(TLong a,TLong b);
    TLong Div_Dec(TLong a,TLong b);
    TLong Power_Abs(TLong a,int b);
    TLong Power(TLong a,int b,int k);
    TLong NWE(TLong a,int k);
    TLong Root(TLong a,int K);
    void FastMulti(const vector <int> & a, const vector <int> & b, vector <int> & res);
    TLong operator + (TLong b)
    {
        return Add(*this,b);
    }
    TLong operator - (TLong b)
    {
        return Minus(*this,b);
    }
    TLong operator * (TLong b)
    {
        return this->Multi(*this, b);
        /*vector <int> A, B, C;
        A.resize(this->len);
        B.resize(b.len);
        for (int i = nmax-this->len+1; i <= nmax; ++i)
            A[nmax - i] = this->n[i];
        for (int i = nmax-b.len+1; i <= nmax; ++i)
            B[nmax - i] = b.n[i];
        FastMulti(A, B, C);
        int x = C.size()-1;
        while (C[x] == 0) x--;
        b.len = x+1;
        if (this->sign == b.sign)
            b.sign = '+';
        else
            b.sign = '-';
        b.point=b.point+this->point;
        b.bracket=0;
        for (int i = x; i >= 0; --i)
            b.n[nmax-i] = C[i];
        return b;*/
    }
    TLong operator / (TLong b)
    {
        return Div_Dec(*this,b);
    }
    bool operator < (TLong b)
    {
        return (this->Comp(b)==-1);
    }
    bool operator <= (TLong b)
    {
        return (this->Comp(b)<=0);
    }
    bool operator > (TLong b)
    {
        return (this->Comp(b)==1);
    }
    bool operator >= (TLong b)
    {
        return (this->Comp(b)>=0);
    }
    void operator << (int b)
    {
        this->Shift(b);
    }
    void operator >> (int b)
    {
        this->Shift(-b);
    }
    int operator % (int b)
    {
        return this->HalfLongDiv(b,0);
    }
    TLong operator % (TLong b)
    {
        return this->Div_Mod(b,0);
    }
    TLong operator / (int b)
    {
        this->HalfLongDiv(b,0);
        return (*this);
    }
    void operator += (TLong b)
    {
        TLong a;
        a=(*this)+b;
        this->point=a.point;
        this->bracket=a.bracket;
        this->len=a.len;
        this->sign=a.sign;
        for (int i=0;i<=nmax;i++)
            this->n[i]=a.n[i];
    }
    void operator -= (TLong b)
    {
        TLong a;
        a=(*this)-b;
        this->point=a.point;
        this->bracket=a.bracket;
        this->len=a.len;
        this->sign=a.sign;
        this->base = a.base;
        for (int i=0;i<=nmax;i++)
            this->n[i]=a.n[i];
    }
    void operator *= (TLong b)
    {
        TLong a;
        a=(*this)*b;
        this->point=a.point;
        this->bracket=a.bracket;
        this->len=a.len;
        this->sign=a.sign;
        this->base = a.base;
        for (int i=0;i<=nmax;i++)
            this->n[i]=a.n[i];
    }
    void operator /= (TLong b)
    {
        TLong a;
        a=(*this)/b;
        this->point=a.point;
        this->bracket=a.bracket;
        this->len=a.len;
        this->sign=a.sign;
        this->base = a.base;
        for (int i=0;i<=nmax;i++)
            this->n[i]=a.n[i];
    }
    void operator %= (TLong b)
    {
        TLong a;
        a=(*this)%b;
        this->point=a.point;
        this->bracket=a.bracket;
        this->len=a.len;
        this->sign=a.sign;
        this->base = a.base;
        for (int i=0;i<=nmax;i++)
            this->n[i]=a.n[i];
    }
    TLong operator ^ (int b)
    {
        TLong a;
        a=Power(*this,b,100);
        a.DelZeros();
        return a;
    }
};

void TLong::FromStr (string s)
{
    memset(this->n,0,sizeof(this->n));
    int min=0;
    if (s[0]=='-' || s[0]=='+')
    {
        this->sign=s[0];
        min=1;
    }else this->sign='+';
    int c=0;
    this->len=s.length();
    this->point=0;
    for (int i=this->len-1;i>=min;i--)
    {
        if (s[i]=='.'){
            c++;
            this->point=this->len-i-c;
        }
        else
        if (s[i]==')') c++;
        else
            if (s[i]=='(')
            {
                c++;
                this->bracket=this->len-i-c;
            }else
                this->n[nmax-this->len+i+c+1]=s[i]-'0';
    }
    this->len-=c+min;
}

string TLong::ToStr()
{
    string res = "";
    if (this->sign=='-') res += '-';
    if (this->point==this->len) res += "0.";
    for (int i=nmax-this->len+1;i<=nmax;i++){
        if (this->n[i] < 10)
            res += this->n[i] + '0';
        else
            res += this->n[i] + 'A' - 10;
        if (i==nmax-this->point && this->point!=0) res += ".";
        if (i==nmax-this->bracket && i<nmax) res += "(";
    }
    if (this->bracket!=0) res += ")";
    return res;
}

void TLong::Input(ifstream & inp, int bs)
{
    string s;
    inp>>s;
    this->FromStr(s);
    this->base = bs;
}

void TLong::Output(ofstream & fout)
{
    fout << this->ToStr() << endl;
}

int TLong::LongLen()
{
    int i=1;
    while (this->n[i]==0 && i<nmax-this->point && i<nmax) i++;
    return max(nmax-i+1, this->point+1);
}

void TLong::Shift(int k)
{
    if (k==0) return;
    if (k>0){
        for (int i=nmax-this->len+1;i<=nmax;i++)
            if (i-k<=nmax){
                this->n[i-k]=this->n[i];
                this->n[i]=0;
            }
    }else{
        for(int  i=nmax+k;i>=nmax-this->len+1;i--){
            this->n[i-k]=this->n[i];
            this->n[i]=0;
        }
    }
    this->len+=k;
    if (this->point!=0) this->point+=k;
}

void TLong::DelZeros()
{
    int k=0;
    while (this->n[nmax-k]==0 && k<this->point) k++;
    this->Shift(-k);
}

bool TLong::Comp_0()
{
    if (this->len!=1) return false; else{
        if (this->n[nmax]!=0) return false; else return true;
    }
}

int TLong::Comp(TLong b)
{
    if (this->sign!=b.sign){
        if (this->sign=='+') return 1; else return -1;
    }
    else{
        if (this->point>b.point){
            b.Shift(this->point-b.point);
            b.point=this->point;
        }
        if (this->point<b.point){
            this->Shift(b.point-this->point);
            this->point=b.point;
        }
        if (this->len==b.len){
            int i=1;
            while (this->n[i]==b.n[i] && i<nmax) i++;
            if (this->sign=='-')    {
                if (this->n[i]<b.n[i]) return 1;
                if (this->n[i]>b.n[i]) return -1;
            }else{
                if (this->n[i]>b.n[i]) return 1;
                if (this->n[i]<b.n[i]) return -1;
            }
            if (this->n[i]==b.n[i]) return 0;
        }else{
            if (this->len<b.len) return -1;else return 1;
        }
    }
}

int TLong::Comp_Abs(TLong b)
{
    int i=1;
    while (this->n[i]==b.n[i] && i<nmax) i++;
    if (this->n[i]==b.n[i]) return 0;
    if (this->n[i]>b.n[i]) return 1;
    if (this->n[i]<b.n[i]) return -1;
}

void TLong::Add_Abs(TLong a,TLong b)
{
    int p=0;
    for (int i=nmax;i>=1;i--)
    {
        int s=a.n[i]+b.n[i]+p;
        p = s / a.base;
        this->n[i]=s % a.base;
    }
    this->len=this->LongLen();
}

void TLong::Minus_Abs(TLong a,TLong b)
{
    int z=0;
    for (int i=nmax;i>=1;i--)
    {
        this->n[i]=a.n[i]-b.n[i]-z;
        if (this->n[i]<0)
        {
            z=1;
            this->n[i]+=a.base;
        }else z=0;
    }
    this->len=this->LongLen();
}

TLong TLong::Add(TLong a,TLong b)
{
    TLong res;
    if (a.point>b.point){
        b.Shift(a.point-b.point);
        b.point=a.point;
    }
    if (a.point<b.point){
        a.Shift(b.point-a.point);
        a.point=b.point;
    }
    if (a.sign!=b.sign)
    {
        if (a.sign=='-') {
            if (a.Comp_Abs(b)<=0){
                res.Minus_Abs(b,a);
                res.sign='+';
            }else
            {
                res.Minus_Abs(a,b);
                res.sign='-';
            }
        }else{
            if (a.Comp_Abs(b)<=0){
                res.Minus_Abs(b,a);
                res.sign='-';
            }else
            {
                res.Minus_Abs(a,b);
                res.sign='+';
            }
        }
    }else{
        res.Add_Abs(a,b);
        res.sign=a.sign;
    }
    res.len=res.LongLen();
    res.point=a.point;
    res.bracket=0;
    res.DelZeros();
    res.base = a.base;
    return res;
}

TLong TLong::Minus(TLong a,TLong b)
{
    TLong res;
    if (a.point>b.point){
        b.Shift(a.point-b.point);
        b.point=a.point;
    }
    if (a.point<b.point){
        a.Shift(b.point-a.point);
        a.point=b.point;
    }
    if (a.sign!=b.sign)
    {
        res.Add_Abs(a,b);
        res.sign=a.sign;
    }else{
        if (a.sign=='-')
        {
            if (a.Comp_Abs(b)>=0){
                res.Minus_Abs(a,b);
                res.sign='-';
            }else{
                res.Minus_Abs(b,a);
                res.sign='+';
            }
        }else{
            if (a.Comp_Abs(b)>=0){
                res.Minus_Abs(a,b);
                res.sign='+';
            }else{
                res.Minus_Abs(b,a);
                res.sign='-';
            }
        }
    }
    res.len=res.LongLen();
    res.point=a.point;
    res.bracket=0;
    res.DelZeros();
    res.base = a.base;
    return res;
}

int TLong::HalfLongDiv(int b,int k)
{
    int ost=0;
    if (b<0){
        b=-b;
        if (this->sign=='-') this->sign='+'; else this->sign='-';
    }
    for (int i=nmax-this->len+1;i<=nmax;i++)
    {
        ost=ost*this->base+this->n[i];
        this->n[i]=ost/b;
        ost%=b;
    }
    this->len=this->LongLen();
    this->Shift(k-this->point);
    for (int i=1;i<=k-this->point;i++)
    {
        ost=ost*this->base;
        this->n[nmax-k+this->point+i]=ost/b;
        ost%=b;
    }
    this->point=k;
    this->bracket=0;
    return ost;
}

void TLong::HalfLongMulti(int b)
{
    int p=0;
    int ost=0;
    if (b<0){
        b=-b;
        if (this->sign=='-') this->sign='+'; else this->sign='-';
    }
    for (int i=nmax;i>=1;i--)
    {
        int s=this->n[i]*b+p;
        p=s/this->base;
        this->n[i]=s%this->base;
    }
    this->len=this->LongLen();
    this->bracket=0;
}

TLong TLong::Multi(TLong a,TLong b)
{
    TLong res;
    memset(res.n,0,sizeof(res.n));
    if (a.sign==b.sign) res.sign='+'; else res.sign='-';
    for (int j=nmax;j>=nmax-b.len;j--)
        if (b.n[j]!=0){
            int p=0;
            for (int i=nmax;i>=nmax-a.len;i--)
            {
                int s=a.n[i]*b.n[j]+p+res.n[i+j-nmax];
                res.n[i+j-nmax]=s%a.base;
                p=s/a.base;
            }
        }
    res.point=a.point+b.point;
    res.base = a.base;
    res.bracket=0;
    res.len=res.LongLen();
    res.DelZeros();
    return res;
}

TLong TLong::Div_Mod(TLong b,int k)
{
    TLong ost;
    memset(ost.n,0,sizeof(ost.n));
    ost.len=1;
    ost.point=0;
    if (this->sign==b.sign)
        this->sign='+';
    else
        this->sign='-';
    if (this->point>b.point)
        b.Shift(this->point-b.point);
    else
        this->Shift(b.point-this->point);
    for (int i=nmax-this->len+1;i<=nmax;i++)
    {
        ost.Shift(1);
        ost.n[nmax]=this->n[i];
        int n=0;
        while (ost.Comp_Abs(b)>=0)
        {
            ost.Minus_Abs(ost,b);
            n++;
        }
        this->n[i]=n;
    }
    this->len=this->LongLen();
    this->Shift(k);
    for (int i=1;i<=k;i++)
    {
        ost.Shift(1);
        int n=0;
        while (ost.Comp_Abs(b)>=0)
        {
            ost.Minus_Abs(ost,b);
            n++;
        }
        this->n[nmax-k+i]=n;
    }
    this->point=k;
    this->DelZeros();
    ost.point=0;
    this->bracket=0;
    ost.bracket=0;
    ost.len=ost.LongLen();
    this->len=this->LongLen();
    ost.sign=this->sign;
    ost.base = b.base;
    return ost;
}

int TLong::nMult(int b)
{
    int n=0;
    while (this->HalfLongDiv(b,0)==0)
        n++;
    return n;
}

int TLong::Entire(TLong &a,TLong b)
{
    a.Shift(1);
    int n=0;
    while (a.Comp_Abs(b)>=0)
    {
        n++;
        a.Minus_Abs(a,b);
    }
    return n;
}

void TLong::GCD(TLong a,TLong b)
{
    TLong gcd;
    while (!a.Comp_0() && !b.Comp_0())
        if (a.Comp_Abs(b)>=0)
            a=a.Div_Mod(b,0);
        else
            b=b.Div_Mod(a,0);
    if (a.Comp_0()) gcd=b; else gcd=a;
    this->point=gcd.point;
    this->sign=gcd.sign;
    this->len=gcd.len;
    this->bracket=gcd.bracket;
    this->base = a.base;
    for (int i=0;i<=nmax;i++)
        this->n[i]=gcd.n[i];
}

TLong TLong::Div_Dec(TLong a,TLong b)
{
    TLong ost,gcd,res;
    if (a.point>b.point)
        b.Shift(a.point-b.point);
    else
        a.Shift(b.point-a.point);
    a.point=0;
    b.point=0;
    gcd.GCD(a,b);
    a.Div_Mod(gcd,0);
    b.Div_Mod(gcd,0);
    res=a;
    ost=res.Div_Mod(b,0);
    res.point=0;
    if (!ost.Comp_0())
    {
        res.point=0;
        a=b;
        int k2=a.nMult(2);
        a=b;
        int k5=a.nMult(5);
        int k;
        if (k2>k5) k=k2; else k=k5;
        for (int i=1;i<=k;i++)
        {
            res.Shift(1);
            if (res.point==0) res.point++;
            res.n[nmax]=Entire(ost,b);
        }
        if (!ost.Comp_0())
        {
            TLong O=ost;
            res.Shift(1);
            if (res.point==0) res.point++;
            res.bracket=1;
            res.n[nmax]=Entire(ost,b);
            int P=1;
            while (ost.Comp_Abs(O) && P<=2000)
            {
                res.Shift(1);
                P++;
                res.bracket++;
                res.n[nmax]=Entire(ost,b);
            }
        }
    }
    return res;
}

TLong TLong::Power_Abs(TLong a,int b)
{
    TLong res;
    res.n[nmax]=1;
    res.bracket=0;
    res.point=0;
    res.len=1;
    res.sign='+';
    while (b)
    {
        if (b & 1) res = Multi(res, a);
        a = Multi(a, a);
        b >>= 1;
    }
    return res;
}

TLong TLong::Power(TLong a,int b,int k)
{
    TLong O,r;
    if (b<0)
    {
        memset(r.n,0,sizeof(r.n));
        r.n[nmax]=1;
        r.bracket=0;
        r.point=0;
        r.len=1;
        r.sign='+';
        r.Div_Mod(Power_Abs(a,b),k);
        return r;
    }else
        return Power_Abs(a,b);
}

TLong TLong::NWE(TLong a,int k)
{
    a.n[nmax]=k;
    a.HalfLongMulti(k);
    return a;
}

TLong TLong::Root(TLong a,int K)
{
    TLong res,A,sub;
    memset(res.n,0,sizeof(res.n));
    res.len=1;
    res.bracket=0;
    res.point=0;
    res.sign='+';
    if (a.point/2<K)
    {
        if (a.bracket==0) a.Shift(K*2-a.point); else{
            int c=K*2-a.point;
            while (c)
            {
                int x=a.bracket;
                if (c<x) x=c;
                a.Shift(x);
                for (int i=nmax-x+1;i<=nmax;i++)
                    a.n[i]=a.n[i-a.bracket];
                c-=x;
            }
        }
        a.point=K*2;
    }
    if (a.point%2==1) a.Shift(1);
    a.len+=a.len%2;
    int i=nmax-a.len+1;
    while (sqr(res.n[nmax]+1)<=a.n[i]*10+a.n[i+1]) res.n[nmax]++;
    sub=res;
    sub.len=2;
    sub.n[nmax]=a.n[i+1];
    sub.n[nmax-1]=a.n[i];
    i+=2;
    A=res*res;
    int top=0;
    for (i;i<nmax;i+=2)
    {
        sub.Minus_Abs(sub,A);
        A=res;
        A.HalfLongMulti(2);
        A.Shift(1);
        sub.Shift(2);
        sub.n[nmax-1]=a.n[i];
        sub.n[nmax]=a.n[i+1];
        int k=0;
        while (NWE(A,k+1).Comp_Abs(sub)<=0) k++;
        res.Shift(1);
        res.n[nmax]=k;
        if (i==nmax-a.point+1)    res.point=1;
        A.n[nmax]=k;
        A.HalfLongMulti(k);
    }
    res.len=res.LongLen();
    if (res.point>K)
    {
        res.Shift(K-res.point);
    }
    return res;
}

void fft(vector <BASE> & a,bool invert)
{
    int n = (int) a.size();
    if (n == 1) return;
    vector <BASE> a0(n/2), a1(n/2);
    for (int i = 0, j = 0; i < n; i+=2, ++j)
    {
        a0[j] = a[i];
        a1[j] = a[i+1];
    }

    fft(a0, invert);
    fft(a1, invert);

    double ang = 2*PI/n*( invert ? -1 : 1);
    BASE w(1) , wn(cos(ang), sin(ang));
    for ( int j = 0; j < n/2; ++j)
    {
        a[j] = a0[j] + w*a1[j];
        a[j + n/2] = a0[j] - w*a1[j];
        if (invert)
            a[j] /= 2, a[j + n/2] /= 2;
        w *= wn;
    }
}

void TLong::FastMulti(const vector <int> & a, const vector <int> & b, vector <int> & res)
{
    vector <BASE> fa (a.begin(), a.end()), fb(b.begin(), b.end());
    int n=1;
    while (n < max(a.size(), b.size())) n<<=1;
    n<<=1;

    fa.resize(n); fb.resize(n);
    fft(fa, false);fft(fb, false);

    for (int i = 0; i < n; ++i)
        fa[i] *= fb[i];
    fft(fa, true);

    res.resize(n);
    for (int i = 0; i < n; ++i)
        res[i] = (int) (fa[i].real() + 0.5);

    int p=0;
    for (int i = 0; i < n; ++i)
    {
        res[i] += p;
        p = res[i] / 10;
        res[i] %= 10;
    }
}

ifstream f1 ("inp1.txt");
ifstream f2 ("inp2.txt");
ofstream fo ("output.txt");

TLong a, b, c;

int main()
{
    a.Input(f1, 10);
    b.Input(f1, 10);
    (a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a).Output(fo);
    (a.Power_Abs(a, 40)).Output(fo);
    return 0;
}
