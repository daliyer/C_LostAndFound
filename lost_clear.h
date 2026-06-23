#ifndef LOST_CLEAR_H
#define LOST_CLEAR_H

#include "file_io.h"

// 外部调用接口
int getDateInterval(char targetDate[]);
void clearOver30Days(void);

// 内部辅助工具函数声明
static int isLeapYear(int year);
static int getMonthDay(int year, int month);
static int calcTotalDay(int y, int m, int d);
static int checkDateValid(int y, int m, int d);

#endif

