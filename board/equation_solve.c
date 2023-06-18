#include<math.h>
#include<stdio.h>
const double eps=1e-7;
int main(){
    double a,b,c;
    scanf("%lf%lf%lf",&a,&b,&c);
    if(a==0){
        if(b==0){
            if(c==0)printf("+inf!\n");
            else printf("No Solution!\n");
        }
        else printf("%.2lf\n",-c/b);
        return 0;
    }
    double del=b*b-4*a*c;
    if(del<-eps){
        printf("No Solution!\n");
    }else if(del<eps){
        double ans=-b/a/2.0;
        printf("%.2lf\n",ans);
    }else{
        double R1=(-b+sqrt(del))/a/2.0;
        double R2=(-b-sqrt(del))/a/2.0;
        if(R1>R2){
            double tmp=R1;
            R1=R2;
            R2=tmp;
        }
        printf("%.2lf %.2lf\n",R1,R2);
    }
    return 0;
}