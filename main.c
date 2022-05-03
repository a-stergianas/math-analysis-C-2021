#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double f(double x){
    return 14*x*exp(x-2) - 12*exp(x-2) - 7*pow(x,3) + 20*pow(x,2) - 26*x + 12;
}
double f1(double x){
    return 14*x*exp(x-2) + 2*exp(x-2) - 21*pow(x,2) + 40*x - 26;
}
double f2(double x){
    return 14*x*exp(x-2) + 16*exp(x-2) - 42*x + 40;
}
double y(double x){
    return 54*pow(x,6) + 45*pow(x,5) - 102*pow(x,4) - 69*pow(x,3) + 35*pow(x,2) + 16*x - 4;
}
double y1(double x){
    return 324*pow(x,5) + 225*pow(x,4) - 408*pow(x,3) - 207*pow(x,2) + 70*x + 16;
}
double y2(double x){
    return 1620*pow(x,4) + 900*pow(x,3) - 1224*pow(x,2) - 414*x + 70;
}

double dixotomisi(double a, double b, double e){
    int N=(log(b-a)-log(e))/log(2)+1;
    double m;
    for(int i=0;i<N;i++){
        m=(a+b)/2;
        if(f(m)==0)
            break;
        else if(f(m)*f(a)<0)
            b=m;
        else
            a=m;
    }
    return m;
}
double dixotomisi2(double a, double b, double e){
    int N=(log(b-a)-log(e))/log(2)+1;
    double m;
    for(int i=0;i<N;i++){
        m=(double)rand()*(b-a)/(double)RAND_MAX+a;
        if(y(m)==0)
            break;
        else if(y(m)*y(a)<0)
            b=m;
        else
            a=m;
    }
    return m;
}
double newton_raphson(double m, double M,double e){
    double x[100],error;
    int i=0;
    x[0]=0;
    do{
        i++;
        x[i]=x[i-1]-f(x[i-1])/f1(x[i-1]);
        error=M/(2*m)*pow(fabs(x[i]-x[i-1]),2);
    }while(error>=e);
    return x[i];
}
double newton_raphson2(double m, double M,double e){
    double x[100],error;
    int i=0;
    x[0]=0;
    do{
        i++;
        x[i]=x[i-1]-1/(y1(x[i-1])/y(i-1)-y2(x[i-1])/(2*y1(x[i-1])));
        error=M/(2*m)*pow(fabs(x[i]-x[i-1]),2);
    }while(error>=e);
    return x[i];
}
double temnoysa(double a, double b){
    double x[100],result;
    x[0]=a;
    x[1]=b;
    for(int i=2;i<7;i++){
        x[i]=x[i-1]-((f(x[i-1])*(x[i-1]-x[i-2]))/(f(x[i-1])-f(i-2)));
        result=x[i];
    }
    return result;
}
double temnoysa2(double a, double b, double c){
    double x[100],result,q,r,s;
    x[0]=a;
    x[1]=b;
    x[2]=c;
    for(int i=3;i<10;i++){
        q=y(x[i-3])/y(x[i-2]);
        r=y(x[i-1])/y(x[i-2]);
        s=y(x[i-1])/y(x[i-3]);
        printf("%ld %ld %ld\n",q,r,s);

        //x[i]=x[i-1]-(r*(r-q)*(x[i-2]-x[i-3])+(1-r)*s*(x[i-2]-x[i-4]))/((q-1)(r-1)(s-1));
        result=x[i];
        printf("%ld\n",result);
    }
    return result;
}

int main()
{
    srand((int)time(NULL));

    double e;

    e=0.00001;

    printf("%lf\n",dixotomisi(0,1,e));
    printf("%lf\n",dixotomisi(1,3,e));
    printf("%lf\n",newton_raphson(fabs(f1(1)),fabs(f2(0)),e));
    printf("%lf\n\n",temnoysa(0,1));


    printf("%lf\n",dixotomisi2(-2,2,e));
    printf("%lf\n",newton_raphson2(fabs(y1(1)),fabs(y2(0)),e));
    printf("%lf\n",temnoysa2(0,1,2));

    return 0;
}
