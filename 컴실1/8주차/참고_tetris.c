#include "tetris.h"

static struct sigaction act, oact;
int B,count,score_number;

typedef struct _Node {
	int level;
	int accumulatedScore;
	char recField[HEIGHT][WIDTH];
	int recField_block[HEIGHT][WIDTH];
	struct _Node **child;
	int childsize;
	int curBlockID;
	int recBlockX,recBlockY,recBlockRotate;
	struct _Node *parent;
}Node;
Node *Root;
Node* maxScoreP;

typedef struct _RecNode{
	int lv,score;
	char (*f)[WIDTH];
	int recBlockX,recBlockY,recBlockRotate;
	struct _RecNode *parent;
	struct _RecNode *c[CHILDREN_MAX];
} RecNode;

RecNode *recRoot;

int main(){

}

void InitTetris(){
	int i,j;

	for(j=0;j<HEIGHT;j++)
		for(i=0;i<WIDTH;i++){
			field[j][i]=0;
			field_block[j][i] = 0;
		}

	start_color();

	for ( i = 1 ; i < 8 ; i++ )
		init_pair(i,i,0);
	nextBlock[0]=rand()%7;
	nextBlock[1]=rand()%7;
	nextBlock[2]=rand()%7;
	blockRotate=0;
	blockY=-1;
	blockX=WIDTH/2-2;
	score=0;
	gameOver=0;
	timed_out=0;

	// Node 구조체 메모리 할당과 구조체 멤버 초기화
	Root = (Node *)malloc(sizeof(Node));
	Root->level = 0;
	Root->accumulatedScore = 0;
	for ( i = 0; i <HEIGHT ; i++)
		for (j = 0; j <WIDTH ; j++) {
			Root->recField[i][j] = field[i][j];
			Root->recField_block[i][j] = 0;
		}
	Root->child = (Node **)malloc(sizeof(Node *)*Root->childsize);
	Root->childsize = 40;
	Root->curBlockID = nextBlock[0];
	Root->parent = NULL;
	Root->recBlockX = 0;
	Root->recBlockY = 0;
	Root->recBlockRotate = 0;

	recommend(Root);

	DrawOutline();
	DrawField();
	DrawBlockWithFeatures(blockY,blockX,nextBlock[0],blockRotate);
	DrawNextBlock(nextBlock);
	PrintScore(score);
}

void DrawOutline(){

}

int GetCommand(){

}

int ProcessCommand(int command){

}

void DrawField(){

}


void PrintScore(int score){

}

void DrawNextBlock(int *nextBlock){


}
void DrawBlockWithFeatures(int y,int x,int blockID,int blockRotate) {
	DrawShadow(y,x,blockID,blockRotate);
// Recommend추가
	DrawRecommend(y,x,blockID,blockRotate);
	DrawBlock(y,x,blockID,blockRotate,' ');

}
void DrawBlock(int y, int x, int blockID,int blockRotate,char tile){

}

void DrawBox(int y,int x, int height, int width){

}

void play(){

}

char menu(){

}

int CheckToMove(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){

}

void DrawChange(char f[HEIGHT][WIDTH],int command,int currentBlock,int blockRotate, int blockY, int blockX){


}

void BlockDown(int sig){
 // 고치기
}

int AddBlockToField(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){

}

int DeleteLine(char f[HEIGHT][WIDTH]){

}

void DrawShadow(int y, int x, int blockID,int blockRotate){

}

void createRankList(){

}

void rank(){

}

void writeRankFile(){

}

void newRank(int score){

}
//DrawBlock을 이용한 추천 블록 그리기
void DrawRecommend(int y, int x, int blockID,int blockRotate){
	DrawBlock( , , , ,'R');
}

int recommend(Node *root, int lv){
	/*
	input: Node *root(parent노드의 주소 저장하는 포인터)
	output: tree의 최종 score, 블록 위치
	*/
}

void recommendedPlay(){
	//  과제
}
