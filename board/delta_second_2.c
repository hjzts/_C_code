#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
int sum_day(int month, int day) {
    //定义十二月的天数
    int month_day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    //因为这个月的天数已经明确 所以只需要加到上个月份就行
    for (int i = 0; i < month - 1; i++) {
        day += month_day[i];  //对天数进行累加
    }
    return day;
}
int interval_year_day(int year, int year2) { /*计算年份之间的天数*/
    int day;
    day = (year2 - year) * 365;
    for (int i = year; i < year2; i++) {
        //把两个日期之间相差年份 中闰年的天数加上
        // i的初始是小的年份  循环到大的年份 正好是相差的年份
        if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) {
            day = day + 1;
        }
    }
    return day;
}
int is_whether_leap(int year) { /*判断是否位闰年，若是返回1*/
    int day = 0;
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        day = 1;
    }
    return day;
}
long long Get_days(int year1, int year2, int month1, int month2, int day1, int day2) {
    int or_year_flag1 = is_whether_leap(year1);
    //计算第一个输入的日期是当前的第几天
    int sum_days1 = sum_day(month1, day1);
    //判断第二个输入日期的是否为闰年
    int or_year_flag2 = is_whether_leap(year2);
    //计算第二个输入的日期是当前的第几天
    int sum_days2 = sum_day(month2, day2);
    //计算两个不同年份之间相差的天数
    int year_intveral = interval_year_day(year1, year2);
    //判断两个日期当年是否为闰年
    //如果是闰年 or_year_flag=1是闰年 不是为0 而且月份大于3才能1 不然 没输入到2月的日期就把2月多一天加上了
    if (or_year_flag1 == 1 && month1 >= 3) {
        sum_days1 += 1;  //天数加1
    }
    if (or_year_flag2 == 1 && month2 >= 3) {
        sum_days2 += 1;  //天数加1
    }
    int day_intveral = (sum_days1 - sum_days2) * -1;
    int sum_intveral = day_intveral + year_intveral;
    return sum_intveral;
}
void swch(int *a, int *b) {
    int tem = *b;
    *b = *a, *a = tem;
}
char date1[100], date2[100];
int main() {
    int year1, year2, month1, month2, day1, day2;
    int h1, h2, m1, m2, s1, s2, flag = 0;
    long long ans = 0;
    scanf("%d%d%d%d%d%d %d%d%d%d%d%d", &year1, &month1, &day1, &h1, &m1, &s1, &year2, &month2, &day2, &h2,
          &m2, &s2);
    if (year1 > year2)
        flag = 1;
    else if (year1 == year2 && month1 > month2)
        flag = 1;
    else if (year1 == year2 && month1 == month2 && day1 > day2)
        flag = 1;
    else if (year1 == year2 && month1 == month2 && day1 == day2 &&
             (h1 * 60 * 60 + m1 * 60 + s1) > (h2 * 60 * 60 + m2 * 60 + s2))
        flag = 1;
    if (flag) {
        swch(&year1, &year2);
        swch(&month1, &month2);
        swch(&day1, &day2);
        swch(&h1, &h2);
        swch(&m1, &m2);
        swch(&s1, &s2);
    }
    ans += (h2 * 60 * 60 + m2 * 60 + s2);
    ans -= (h1 * 60 * 60 + m1 * 60 + s1);
    ans += 24 * 60 * 60 * Get_days(year1, year2, month1, month2, day1, day2);
    printf("%lld", llabs(ans));
}