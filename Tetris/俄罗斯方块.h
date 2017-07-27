
#include <Windows.h>
#include <time.h>

#define BLOCK_KINDS		7//方块的种类
#define BLOCK_ROTATES	4//旋转方式
#define BLOCK_WIDTH		4//方块边长
#define BLOCK_SIZE		16//一块方块占用界面的大小

#define CONTAINER_WIDTH 15//界面宽
#define CONTAINER_HIGH   30//界面高
//整个界面矩形坐标(左上角和右下角)
RECT ContainerRect;
//存储下一个方块的矩形坐标
RECT NextBlockRect;

//窗口大小
#define WINDOW_WIDTH 500
#define WINDOW_HIGH  700

HINSTANCE hinst; /// HINSTANCE是用来表示程序运行实例的句柄，某些API函数会使用到这个变量。
typedef struct Tetris
{
	int TimerId;//计时器ID
	int GameState;// 游戏状态，0，游戏运行； 1，游戏开始；2，游戏暂停 
	int initalSpeed;//最初速度
	int speed;//速度
	int score;//分数

			  /*当前方块*/
	char *current_block;
	int kind;
	int rotate;
	int left;
	int top;
	int top_destinnation;//当前位置
	/*下一方块*/
	char *next_block;
	int next_kind;
	int next_rotate;

	int min_left;
	int max_right;
	int min_top;
	int max_bottom;
}Tetris;
Tetris tetris;
char Container[CONTAINER_HIGH][CONTAINER_WIDTH];
char BlockSets[CONTAINER_HIGH*CONTAINER_WIDTH*BLOCK_SIZE];
void CheckGameOver();//判断游戏结束
void CopyToConTainer();//复制到容器中
void CaculateScore();
void CaculateBlockBoundary();
void GenerateBlock();//产生方块
int DetectCollision(char *block, int left, int top);
void StepLeft();
void StepRight();
int StepDown();
void UpdateCurrBlockDestinationPosition();//更新当前方块位置
void StepRotate();

void OnDrawBorder(HDC hdc_mem);//画边界
void OnDrawSpeedSelect(HDC hdc_mem);//选择速度
void OnDrawBlock(HDC hdc_mem);//画方块
void OnDrawResult(HDC hdc_mem);//输出界面文字
void OnPaint(HDC hdc);//创建画笔
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevlnstance, PSTR lpCmdLine, INT iCmdShow);



