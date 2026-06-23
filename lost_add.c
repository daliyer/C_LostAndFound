#include "lost_add.h"
#include "menu_ui.h"
#include <stdio.h>
#include <string.h>
void inputNewLost(void)
{
    if (currentCount >= MAX_ITEM)
    {
        printf("记录已满，无法新增失物！\n");
        return;
    }
    LostItem temp;
    memset(&temp, 0, sizeof(LostItem));
    temp.status = 0; // 默认未认领

    printf("=====录入新失物信息=====\n");
    // 物品名称
    printf("请输入物品名称：");
    flushBuffer(); // 先清上次残留，再读取
    fgets(temp.goodsName, 50, stdin);
    temp.goodsName[strcspn(temp.goodsName, "\n")] = '\0';

    // 日期
    printf("请输入捡拾日期(格式yyyy-MM-dd)：");
    fgets(temp.findTime, 20, stdin);
    temp.findTime[strcspn(temp.findTime, "\n")] = '\0';

    // 地点
    printf("请输入捡拾地点：");
    fgets(temp.findPlace, 50, stdin);
    temp.findPlace[strcspn(temp.findPlace, "\n")] = '\0';

    lostList[currentCount] = temp;
    currentCount++;
    saveData();
    printf("失物信息录入成功！\n");
}

