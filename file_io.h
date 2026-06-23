#ifndef FILE_IO_H
#define FILE_IO_H
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//全局存储常量 
#define MAX_ITEM 100
#define DATA_FILE "lost_record.txt"
//失物信息结构体定义，全项目共用 
typedef struct LostItem
{
	char goodsName[50];	//物品名称 
	char findTime[20];	//捡拾日期 格式yyyy-MM-dd 
	char findPlace[50];	//捡拾地点 
	int status;	//0=未认领 1=已认领 
}LostItem;
//全局数据外部声明，所有模块均可访问 
extern LostItem lostList[MAX_ITEM];
extern int currentCount;
extern int isShowAllFlag; 
//函数声明 加载数据 -> 保存数据 
void loadData(void);
void saveData(void);
#endif
