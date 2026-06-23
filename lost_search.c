#include "lost_search.h"
#include "menu_ui.h"
#include <stdio.h>
#include <string.h>
void printSingle(LostItem item) {
	printf("物品：%-12s 日期：%s 地点：%-12s 状态：%s\n",
	       item.goodsName,
	       item.findTime,
	       item.findPlace,
	       item.status == 0 ? "未认领" : "已认领");
}


void showAllItems(void) {
	// 标记当前执行查看全部，main不清屏
	isShowAllFlag = 1;
	int i;
	printf("\n====================全部失物记录====================\n");
	printf("当前共有 %d 条失物记录\n", currentCount);
	// 无记录分支直接退出
	if (currentCount == 0) {
		printf("暂无任何失物记录！\n");
		printf("====================================================\n");
		flushBuffer();
		getchar();
		// 用户按下回车后，在这里清屏，再返回main
		system("cls");
		return;
	}
	// 遍历打印所有记录
	for (i = 0; i < currentCount; i++) {
		printSingle(lostList[i]);
	}
	printf("====================================================\n");
	// 停留在列表，等待用户确认
	printf("\n查看完毕，请按下回车键返回菜单...");
	flushBuffer();
	getchar();
	// 用户按下回车后，在这里清屏，再返回main
	system("cls");
}

void searchByGoods(void) {
	int i;
	char key[50];

	flushBuffer();

	printf("请输入要查询的物品名称: ");

	if (fgets(key, sizeof(key), stdin) != NULL) {
		size_t len = strlen(key);
		if (len > 0 && key[len - 1] == '\n') {
			key[len - 1] = '\0';
		}
	}

	int flag = 0;
	printf("====物品名称查询结果====\n");

	for (i = 0; i < currentCount; i++) {
		if (strcmp(lostList[i].goodsName, key) == 0) {
			printSingle(lostList[i]);
			flag = 1;
		}
	}

	if (!flag) {
		printf("未找到该物品相关记录\n");
	}
}


void searchByLocation(void) {
	int i;
	char key[50];
	printf("请输入要查询的捡拾地点：");
	scanf("%s",key);
	flushBuffer();
	int flag = 0;
	printf("=====地点匹配结果=====\n");
	for(i=0; i<currentCount; i++) {
		if(strcmp(lostList[i].findPlace,key)==0) {
			printSingle(lostList[i]);
			flag = 1;
		}
	}
	if(!flag) {
		printf("该地点无失物记录\n");
	}
}
