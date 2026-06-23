#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lostfound.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int op;
	int needPause = 1;
	//1.系统初始化，读取本地文件历史数据
	loadData();
	printf("校园失物招领系统初始化完成！\n");
	//2.展示菜单
	while(1) {
		showMainMenu();
		op = getUserChoice();
		switch(op) {
			case 1:
				inputNewLost();
				break;
			case 2:
				searchByGoods();
				break;
			case 3:
				searchByLocation();
				break;
			case 4:
				setClaimed();
				break;
			case 5:
				clearOver30Days();
				break;
			case 6:
				showAllItems();
				break;
			case 0:
				flushBuffer(); 
				goto sys_exit;
			default:
				printf("输入无效，请选择0-6功能！\n");
				flushBuffer();
				needPause = 0;
				break;
		}
		// 判断是否是查看全部功能
		if (isShowAllFlag == 0) {
			// 功能1~5：统一等待回车，再清屏
			printf("\n按下回车键返回主菜单...");
			flushBuffer();
			system("cls");
		}
// 功能6已经在函数内完成等待+清屏，main什么都不做
// 重置标记
		isShowAllFlag = 0;

	}
	//3.系统退出分支，保存数据后结束运行
sys_exit:
	saveData();
	printf("数据已自动保存，系统正常退出\n");
	system("pause");
	return 0;
}
