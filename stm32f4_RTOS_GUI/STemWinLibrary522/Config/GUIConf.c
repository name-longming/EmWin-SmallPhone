#include "GUI.h"


//设置EMWIN内存大小
#define GUI_NUMBYTES  (100*1024)
#define GUI_BLOCKSIZE 0X50


//GUI_X_Config
//初始化的时候调用,用来设置emwin所使用的内存
void GUI_X_Config(void)
{
	static U32 aMemory[GUI_NUMBYTES / 4];
	GUI_ALLOC_AssignMemory((U32 *)aMemory, GUI_NUMBYTES); //为存储管理系统分配一个存储块
	GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE); //设置存储快的平均尺寸,该区越大,可用的存储快数量越少
}
