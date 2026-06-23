#include "lost_modify.h"
#include "menu_ui.h"
#include <stdio.h>
#include <string.h>

void setClaimed(void) {
	int i;
	char name[50];
	printf("请输入已找回物品的名称：");
	scanf("%s",name);
	flushBuffer();
	int find = 0;
	for(i=0; i<currentCount; i++) {
		if(strcmp(lostList[i].goodsName,name)==0) {
			lostList[i].status = 1;
			find = 1;
			printf("已将该物品标记为【已认领】\n");
		}
	}
	if(!find) {
		printf("未找到该物品记录，修改失败\n");
		return;
	}
	saveData();
}
