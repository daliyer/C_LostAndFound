#include "menu_ui.h"
#include <stdio.h>
//打印系统主菜单功能 
void showMainMenu(void) {
	printf("====================校园失物招领系统====================\n");
	printf("1.录入新的失物信息\n");
	printf("2.根据物品名称查询失物\n");
	printf("3.根据捡拾地点查询失物\n");
	printf("4.修改物品为已认领状态\n");
	printf("5.清理存放超过30天的过期记录\n");
	printf("6.查看全部失物记录\n");
	printf("0.退出系统并保存数据\n");
	printf("========================================\n");
	printf("请输入你要执行的功能编号：");
}
//获得用户输入的菜单选项，返回用户输入的整型数字 
int getUserChoice(void) {
	int op;
	scanf("%d",&op);
	return op;
}

//清空输入缓存区，解决scanf残留的换行符造成的自动跳转问题 
void flushBuffer(void) {
	int ch;
	//只有读到换行/EOF才退出，无输入时不会阻塞等待 
	while((ch = getchar())!= '\n'&&ch != EOF);
}
