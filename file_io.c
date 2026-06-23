#include "file_io.h"

LostItem lostList[MAX_ITEM];
int currentCount = 0;
int isShowAllFlag = 0;

void loadData(void)
{
    FILE* fp = fopen(DATA_FILE, "rb");
    if (fp == NULL)
    {
        printf("提示：未检测到历史数据文件，当前暂无失物记录\n");
        currentCount = 0;
        return;
    }
    currentCount = 0;
    while (fread(&lostList[currentCount], sizeof(LostItem), 1, fp) == 1
           && currentCount < MAX_ITEM)
    {
        currentCount++;
    }
    fclose(fp);
    printf("数据加载完成，共读取 %d 条失物记录\n", currentCount);
}

void saveData(void)
{
    FILE* fp = fopen(DATA_FILE, "wb");
    if (fp == NULL)
    {
        printf("错误：文件打开失败，数据保存失败！\n");
        return;
    }
    size_t writeCnt = fwrite(lostList, sizeof(LostItem), currentCount, fp);
    fclose(fp);
    if(writeCnt == currentCount)
        printf("所有数据已成功保存至本地文件\n");
    else
        printf("警告：仅写入 %zu/%d 条记录，保存不完整！\n", writeCnt, currentCount);
}

