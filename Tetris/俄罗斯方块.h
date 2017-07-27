
#include <Windows.h>
#include <time.h>

#define BLOCK_KINDS		7//���������
#define BLOCK_ROTATES	4//��ת��ʽ
#define BLOCK_WIDTH		4//����߳�
#define BLOCK_SIZE		16//һ�鷽��ռ�ý���Ĵ�С

#define CONTAINER_WIDTH 15//�����
#define CONTAINER_HIGH   30//�����
//���������������(���ϽǺ����½�)
RECT ContainerRect;
//�洢��һ������ľ�������
RECT NextBlockRect;

//���ڴ�С
#define WINDOW_WIDTH 500
#define WINDOW_HIGH  700

HINSTANCE hinst; /// HINSTANCE��������ʾ��������ʵ���ľ����ĳЩAPI������ʹ�õ����������
typedef struct Tetris
{
	int TimerId;//��ʱ��ID
	int GameState;// ��Ϸ״̬��0����Ϸ���У� 1����Ϸ��ʼ��2����Ϸ��ͣ 
	int initalSpeed;//����ٶ�
	int speed;//�ٶ�
	int score;//����

			  /*��ǰ����*/
	char *current_block;
	int kind;
	int rotate;
	int left;
	int top;
	int top_destinnation;//��ǰλ��
	/*��һ����*/
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
void CheckGameOver();//�ж���Ϸ����
void CopyToConTainer();//���Ƶ�������
void CaculateScore();
void CaculateBlockBoundary();
void GenerateBlock();//��������
int DetectCollision(char *block, int left, int top);
void StepLeft();
void StepRight();
int StepDown();
void UpdateCurrBlockDestinationPosition();//���µ�ǰ����λ��
void StepRotate();

void OnDrawBorder(HDC hdc_mem);//���߽�
void OnDrawSpeedSelect(HDC hdc_mem);//ѡ���ٶ�
void OnDrawBlock(HDC hdc_mem);//������
void OnDrawResult(HDC hdc_mem);//�����������
void OnPaint(HDC hdc);//��������
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevlnstance, PSTR lpCmdLine, INT iCmdShow);



