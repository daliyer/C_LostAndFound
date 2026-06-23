#include "lost_clear.h"
#include "menu_ui.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

/**
 * @brief 判断闰年
 * @param year 待判断年份
 * @return 1=闰年，0=平年
 */
static int isLeapYear(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        return 1;
    return 0;
}

/**
 * @brief 获取指定年份月份的总天数（自动处理2月闰年）
 * @param year 年份
 * @param month 月份1~12
 * @return 当月天数
 */
static int getMonthDay(int year, int month)
{
    int monthDay[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int day = monthDay[month - 1];
    if (month == 2 && isLeapYear(year))
        day = 29;
    return day;
}

/**
 * @brief 校验日期是否合法
 * @param y 年 m月 d日
 * @return 1合法，0非法
 */
static int checkDateValid(int y, int m, int d)
{
    if (y < 1970 || m < 1 || m > 12 || d < 1)
        return 0;
    if (d > getMonthDay(y, m))
        return 0;
    return 1;
}

/**
 * @brief 计算从公元元年到指定年月日的总天数，用于精确求差值
 */
static int calcTotalDay(int y, int m, int d)
{
    int total = 0;
    int i; // 循环变量统一提前定义，兼容C89
    // 累加所有整年天数
    for (i = 1; i < y; i++)
    {
        total += isLeapYear(i) ? 366 : 365;
    }
    // 累加当年前面月份天数
    for (i = 1; i < m; i++)
    {
        total += getMonthDay(y, i);
    }
    total += d;
    return total;
}

/**
 * @brief 计算捡拾日期距离当前系统日期的天数差（重构后跨平台无报错）
 * @param targetDate 存储的日期字符串 yyyy-MM-dd
 * @return 相差天数（当前日期 - 捡拾日期），非法日期返回-1
 */
int getDateInterval(char targetDate[])
{
    int nowY, nowM, nowD;
    int tarY, tarM, tarD;
    int totalNow, totalTar;
    // 1. 获取当前系统日期（替换localtime_r，标准localtime全平台兼容）
    time_t now = time(NULL);
    struct tm *pNowTm = localtime(&now);
    nowY = pNowTm->tm_year + 1900;
    nowM = pNowTm->tm_mon + 1;
    nowD = pNowTm->tm_mday;

    // 2. 解析存储的捡拾日期
    if (sscanf(targetDate, "%d-%d-%d", &tarY, &tarM, &tarD) != 3)
    {
        printf("警告：日期格式错误 %s\n", targetDate);
        return -1;
    }

    // 3. 合法性校验
    if (!checkDateValid(tarY, tarM, tarD) || !checkDateValid(nowY, nowM, nowD))
    {
        printf("警告：存在非法日期记录 %s\n", targetDate);
        return -1;
    }

    // 4. 计算总天数差值
    totalNow = calcTotalDay(nowY, nowM, nowD);
    totalTar = calcTotalDay(tarY, tarM, tarD);
    return totalNow - totalTar;
}

/**
 * @brief 清理超过30天的过期失物记录（原有业务逻辑不变）
 */
void clearOver30Days(void)
{
    int newCnt = 0;
    int delCount = 0;
    int diff;
    int i; // C89要求变量全部写在函数开头
    for (i = 0; i < currentCount; i++)
    {
        diff = getDateInterval(lostList[i].findTime);
        // 差值有效且不超过30天才保留，超过则丢弃
        if (diff != -1 && diff <= 30)
        {
            lostList[newCnt++] = lostList[i];
        }
        else
        {
            delCount++;
        }
    }
    currentCount = newCnt;
    saveData();
    printf("过期清理完成，共删除 %d 条超过30天的过期/非法日期记录\n", delCount);
    flushBuffer();
}

