#include "tetris.h"
#include <ncurses.h>

static struct sigaction act, oact;

int main(){
	int exit=0;
	createRankList(); // 시작할 때 score data 만들어주기
	initscr();
	noecho();
	keypad(stdscr, TRUE);	

	srand((unsigned int)time(NULL));

	while(!exit){
		clear();
		switch(menu()){
		case MENU_PLAY: play(); break;
		case MENU_RANK: rank(); break;
		case MENU_EXIT: exit=1; break;
		default: break;
		}
	}
	writeRankFile();

	endwin();
	system("clear");
	return 0;
}

void InitTetris(){
	int i,j;

	for(j=0;j<HEIGHT;j++)
		for(i=0;i<WIDTH;i++)
			field[j][i]=0;

	nextBlock[0]=rand()%7;
	nextBlock[1]=rand()%7;
	nextBlock[2]=rand()%7;
	blockRotate=0;
	blockY=-1;
	blockX=WIDTH/2-2;
	score=0;	
	gameOver=0;
	timed_out=0;

    //recRoot의 동적할당
    Node* recRoot = (Node*)malloc(sizeof(Node));
    recRoot->level = 0;
    recRoot->accumulatedScore = 0;
    for(int i=0; i<HEIGHT; i++)
    {
        for(int j=0; j<WIDTH; j++)
        {
            recRoot->recField[i][j]=field[i][j];
        }
    }
    
    recommend(Root); // recRoot는 recommend를 통해서 할당, 해제를 반복
    
	DrawOutline();
	DrawField();
	DrawBlock(blockY,blockX,nextBlock[0],blockRotate,' ');
	DrawNextBlock(nextBlock);
	PrintScore(score);
}

void DrawOutline(){	
	int i,j;
	/* 블럭이 떨어지는 공간의 태두리를 그린다.*/
	DrawBox(0,0,HEIGHT,WIDTH);

	/* next block을 보여주는 공간의 태두리를 그린다.*/
	move(2,WIDTH+10);
	printw("NEXT BLOCK");
	DrawBox(3,WIDTH+10,4,8);
	DrawBox(9, WIDTH+10, 4, 8); // newblock[2]를 위한 공간
	/* score를 보여주는 공간의 태두리를 그린다.*/
	move(15,WIDTH+10);
	printw("SCORE");
	DrawBox(16,WIDTH+10,1,8);
}

int GetCommand(){
	int command;
	command = wgetch(stdscr);
	switch(command){
	case KEY_UP:
		break;
	case KEY_DOWN:
		break;
	case KEY_LEFT:
		break;
	case KEY_RIGHT:
		break;
	case ' ':	/* space key*/
		/*fall block*/
		break;
	case 'q':
	case 'Q':
		command = QUIT;
		break;
	default:
		command = NOTHING;
		break;
	}
	return command;
}

int ProcessCommand(int command){
	int ret=1;
	int drawFlag=0;
	switch(command){
	case QUIT:
		ret = QUIT;
		break;
	case KEY_UP:
		if((drawFlag = CheckToMove(field,nextBlock[0],(blockRotate+1)%4,blockY,blockX)))
			blockRotate=(blockRotate+1)%4;
		break;
	case KEY_DOWN:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY+1,blockX)))
			blockY++;
		break;
	case KEY_RIGHT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX+1)))
			blockX++;
		break;
	case KEY_LEFT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX-1)))
			blockX--;
		break;
	default:
		break;
	}
	if(drawFlag) DrawChange(field,command,nextBlock[0],blockRotate,blockY,blockX);
	return ret;	
}

void DrawField(){
	int i,j;
	for(j=0;j<HEIGHT;j++){
		move(j+1,1);
		for(i=0;i<WIDTH;i++){
			if(field[j][i]==1){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(".");
		}
	}
}


void PrintScore(int score){
	move(17,WIDTH+11);
	printw("%8d",score);
}

void DrawNextBlock(int *nextBlock){
	int i, j;
	for( i = 0; i < 4; i++ ){
		move(4+i,WIDTH+13);
		for( j = 0; j < 4; j++ ){
			if( block[nextBlock[1]][0][i][j] == 1 ){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(" ");
		}
	}
	for(i=0; i<4; i++)
	{
		move(10+i, WIDTH+13);
		for(j=0; j<4; j++)
		{
			if(block[nextBlock[2]][0][i][j] == 1)
			{
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(" ");
		}
	}
}

void DrawBlock(int y, int x, int blockID,int blockRotate,char tile){
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++){
			if(block[blockID][blockRotate][i][j]==1 && i+y>=0){
				move(i+y+1,j+x+1);
				attron(A_REVERSE);
				printw("%c",tile);
				attroff(A_REVERSE);
			}
		}

	move(HEIGHT,WIDTH+10);
}

void DrawBox(int y,int x, int height, int width){
	int i,j;
	move(y,x);
	addch(ACS_ULCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_URCORNER);
	for(j=0;j<height;j++){
		move(y+j+1,x);
		addch(ACS_VLINE);
		move(y+j+1,x+width+1);
		addch(ACS_VLINE);
	}
	move(y+j+1,x);
	addch(ACS_LLCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_LRCORNER);
}

void play(){
	
	int command;
	clear();
	act.sa_handler = BlockDown;
	sigaction(SIGALRM,&act,&oact);
	InitTetris();
	do{
		if(timed_out==0){
			alarm(1);
			timed_out=1;
		}

		command = GetCommand();
		if(ProcessCommand(command)==QUIT){
			alarm(0);
			DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
			move(HEIGHT/2,WIDTH/2-4);
			printw("Good-bye!!");
			refresh();
			getch();

			return;
		}
	}while(!gameOver);

	alarm(0);
	getch();
	DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
	move(HEIGHT/2,WIDTH/2-4);
	printw("GameOver!!");
	refresh();
	getch();
	newRank(score);
}

char menu(){
	printw("1. play\n");
	printw("2. rank\n");
	printw("3. recommended play\n");
	printw("4. exit\n");
	return wgetch(stdscr);
}

/////////////////////////첫주차 실습에서 구현해야 할 함수/////////////////////////

int CheckToMove(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX)
{
	for(int i=0; i<4; i++) // x의 최대는 9(0~9), 최소는 0 segfault 를 발생시키지 않기 위해 먼저 test
    {
        for(int j=0; j<4; j++)
        {
            if(block[currentBlock][blockRotate][i][j]==1 && (blockX+j<0 || blockX+j>9))
            {
                return 0;
            }
        }
    }
	
	for(int i=0; i<4; i++) // y의 최대는 21 (0~21) / 22부터 x
    {
        for(int j=0; j<4; j++)
        {
            if(block[currentBlock][blockRotate][i][j]==1 && blockY+i>21)
            {
                return 0;
            }
        }
    }

	for(int i=0; i<4; i++) // 이미 블록이 쌓여져 있는 경우
    {
        for(int j=0; j<4; j++)
        {
            if(block[currentBlock][blockRotate][i][j]==1 && f[blockY+i][blockX+j]==1)
            {
                return 0;
            }
        }
    }
        
    return 1;
}

void DrawChange(char f[HEIGHT][WIDTH],int command,int currentBlock,int blockRotate, int blockY, int blockX)
{
	DrawField();
	switch(command){
    
    case KEY_UP:
            blockRotate = blockRotate - 1;
            if(blockRotate == -1)
            {
                blockRotate = 3;
            }
            for(int i=0; i<4; i++)
			{
				for(int j=0; j<4; j++)
				{
					if(block[currentBlock][blockRotate][i][j]==1)
					{
						move(i+blockY+1, j+blockX+1);
						printw(".");
					}
				}
			}
            
            blockRotate = (blockRotate + 1)%4;
            DrawBlockWithFeatures(blockY,blockX,nextBlock[0],blockRotate);
            break;
            
    case KEY_DOWN:
            blockY--;
            for(int i=0; i<4; i++)
			{
				for(int j=0; j<4; j++)
				{
					if(block[currentBlock][blockRotate][i][j]==1&&i+blockY>=0)
					{
						move(i+blockY+1, j+blockX+1);
						printw(".");
					}
				}
			}
            blockY++;
            DrawBlockWithFeatures(blockY,blockX,nextBlock[0],blockRotate);
            break;
            
    case KEY_RIGHT:
            blockX--;
            for(int i=0; i<4; i++)
			{
				for(int j=0; j<4; j++)
				{
					if(block[currentBlock][blockRotate][i][j]==1)
					{
						move(i+blockY+1, j+blockX+1);
						printw(".");
					}
				}
			}
            blockX++;
            DrawBlockWithFeatures(blockY,blockX,nextBlock[0],blockRotate);
            break;
            
    case KEY_LEFT:
            blockX++;
            for(int i=0; i<4; i++)
    		{
        		for(int j=0; j<4; j++)
        		{
            		if(block[currentBlock][blockRotate][i][j]==1)
            		{
                		move(i+blockY+1, j+blockX+1);
						printw(".");
            		}
        		}
    		}	
            blockX--;
            DrawBlockWithFeatures(blockY,blockX,nextBlock[0],blockRotate);
            break;
            
    default:
            break;
	}
	// user code

	//1. 이전 블록 정보를 찾는다. ProcessCommand의 switch문을 참조할 것
	//2. 이전 블록 정보를 지운다. DrawBlock함수 참조할 것.
	//3. 새로운 블록 정보를 그린다. 
}

void BlockDown(int sig){
	if(CheckToMove(field, nextBlock[0], blockRotate, blockY+1, blockX))
	{
		blockY++;
		DrawChange(field, KEY_DOWN, nextBlock[0], blockRotate, blockY, blockX);
	}
	else
	{
		if(blockY==-1)
		{
			gameOver = 1;
		}
		else
		{
			score += 10*AddBlockToField(field, nextBlock[0], blockRotate, blockY, blockX);
			nextBlock[0] = nextBlock[1];
			nextBlock[1] = nextBlock[2];
			nextBlock[2] = rand()%7;
			DrawNextBlock(nextBlock);
			blockY = -1;
			blockX = (WIDTH/2)-2;
			blockRotate = 0;
			score += DeleteLine(field);
			PrintScore(score);
			DrawField();
            
            //recommend를 위한 작업
            Node* recRoot = (Node*)malloc(sizeof(Node));
            recRoot->level = 0;
            recRoot->accumulatedScore = 0;
            for(int i=0; i<HEIGHT; i++)
            {
                for(int j=0; j<WIDTH; j++)
                {
                    recRoot->recField[i][j]=field[i][j];
                }
            }
            
            recommend(Root); // recRoot는 recommend를 통해서 할당, 해제를 반복
            
			DrawBlockWithFeatures(blockY,blockX,nextBlock[0],blockRotate);
            
		}
	}
	timed_out = 0;

}

int AddBlockToField(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
	// user code
	int touched = 0;

	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(block[currentBlock][blockRotate][i][j]==1 && blockY+i==21)
			{
				touched++;
			}
			else if(block[currentBlock][blockRotate][i][j]==1 && f[blockY+i+1][blockX+j]==1)
			{
				touched++;
			}
		}
	}
	for(int i=0; i<4; i++)
	{
		 for(int j=0; j<4; j++)
		 {
			 if(block[currentBlock][blockRotate][i][j]==1 && blockY+i>=0)
			 {
				 f[blockY+i][blockX+j] = 1;
			 }
		 }
	}
	
	return touched;
}

int DeleteLine(char f[HEIGHT][WIDTH])
{
	int isfull[22] = {0};
    int count = 0;
    
    for(int i=0; i<22; i++)
    {
        for(int j=0; j<10; j++)
        {
            if(f[i][j]!=1)
            {
                break;
            }
            else if(j==9 && f[i][j]==1)
            {
                isfull[i] = 1;
            }
        }
    }
    
    for(int i=0; i<22; i++)
    {
        if(isfull[i]==1) // i가 0일때 예외처리 해주어야 할까?
        {
            count++;
            for(int k=i-1; k>=0; k--)
            {
                for(int j=0; j<10; j++)
                {
                    f[k+1][j] = f[k][j];
                }
            }
            for(int j=0; j<10; j++)
            {
                f[0][j]=0;
            }
        }
    }
    //1. 필드를 탐색하여, 꽉 찬 구간이 있는지 탐색한다.
    //2. 꽉 찬 구간이 있으면 해당 구간을 지운다. 즉, 해당 구간으로 필드값을 한칸씩 내린다.
    return count*count*100;
	// user code

	//1. 필드를 탐색하여, 꽉 찬 구간이 있는지 탐색한다.
	//2. 꽉 찬 구간이 있으면 해당 구간을 지운다. 즉, 해당 구간으로 필드값을 한칸씩 내린다.
}

///////////////////////////////////////////////////////////////////////////

void DrawShadow(int y, int x, int blockID, int blockRotate){
	// user code
	while(CheckToMove(field, blockID, blockRotate, y, x))
	{
		y++;
	}
	y--;
	DrawBlock(y, x, blockID, blockRotate, '/');
}

void DrawBlockWithFeatures(int y, int x, int blockID, int blockRotate)
{
	DrawShadow(y, x, blockID, blockRotate);
	DrawBlock(y, x, blockID, blockRotate, ' ');

	return;
}

void createRankList(){
	int data_num;
	Node* saveptr;
	FILE* rank = fopen("rank.txt", "r");
	fscanf(rank, "%d\n", &data_num);
	if(data_num>0)
	{
		node_num = data_num;
		headptr = (Node*)malloc(sizeof(Node)); // 첫 node 할당해주기
		fscanf(rank, "%s %d\n", headptr->name, &(headptr->score));
		headptr->nextpoint = NULL;
		saveptr = headptr;

		for(int i=1; i<data_num; i++)
		{
			headptr->nextpoint = (Node*)malloc(sizeof(Node));
			headptr = headptr->nextpoint;
			fscanf(rank, "%s %d\n", headptr->name, &(headptr->score));
			headptr->nextpoint = NULL;
		}
		
		headptr = saveptr;
	}
	else
	{
		node_num = 0;
	}
	fclose(rank);

	return;
}

void rank(){
	clear();
	refresh();
	
	int x = 0;
	int y = 0;
	int counter = 0;
	char name[NAMELEN];
	Node* nowptr = headptr;

	printw("1. list ranks from X to Y\n");
	printw("2. list ranks by a specific name\n");
	printw("3. delete a specific rank\n");
	refresh();
	switch(getch())
	{
		case '1':
			echo();
			printw("X: ");
			scanw("%d", &x);
			printw("Y: ");
			scanw("%d", &y);
			if(x==0&&y==0)
			{
				x=1;
				y=5;
			}
			else if(x==0)
			{
				x=1;
			}
			else if(y==0)
			{
				y=5;
			}
			printw("%-15s|%-10s\n", "name", "score");
			printw("--------------------------\n");
			if(x>y)
			{
				printw("search failure: no rank in the list\n");
			}
			else
			{
				for(int i=1; i<=y&&i<=node_num; i++)
				{
					if(nowptr==NULL)
					{
						break;
					}
					
					if(i>=x)
					{
						printw("%-15s|%-10d\n", nowptr->name, nowptr->score);
					}
					
					nowptr = nowptr->nextpoint;
				}
			}

			getch();
			noecho();
			break;

		case '2':
			echo();

			printw("Input the name: ");
			getstr(name);
			printw("%-15s|%-10s\n", "name", "score");
			printw("--------------------------\n");

			for(int i=0; i<node_num; i++)
			{
				if(strcmp(nowptr->name, name)==0)
				{
					printw("%-15s|%-10d\n", nowptr->name, nowptr->score);
					counter++;
				}
				nowptr = nowptr->nextpoint;
			}
			if(counter == 0)
			{
				printw("search failure: no name in the list\n");
			}
			getch();
			noecho();
			break;

		case '3':
			echo();
			printw("input the rank: ");
			scanw("%d", &x);
			printw("\n");
			if(x<=0||x>node_num)
			{
				printw("search failure: the rank not in the list\n");
			}
			else
			{
				Node* saveptr;
				for(int i=1; i<x; i++)
				{
					nowptr = nowptr->nextpoint;
				}
				saveptr = nowptr;
				nowptr = nowptr->nextpoint;
				if(x==1)
				{
					headptr = nowptr;
				}
				free(saveptr);
				node_num--;
				printw("result: the rank deleted\n");
			}
			getch();
			noecho();
			break;
			
		default:
			break;
	}
	return;
}

void writeRankFile(){
	FILE* rank = fopen("rank.txt", "w");
	fprintf(rank, "%d\n", node_num);
	Node* nowptr = headptr;
	Node* freeptr;

	for(int i=0; i<node_num; i++)
	{
		fprintf(rank, "%s %d\n", nowptr->name, nowptr->score);
		freeptr = nowptr;
		nowptr = nowptr->nextpoint;
		free(freeptr);
	}

	fclose(rank);
	return;
}

void newRank(int score){
	clear();
	refresh();
	char input_name[NAMELEN];
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->nextpoint = NULL;
	int i;
	echo(); // getstr을 보이기 위해
	printw("please input your name: ");
	refresh();
	getstr(input_name);

	new_node->score = score;
	strcpy(new_node->name, input_name);
	Node* headsave = headptr;

	for(i=0;;i++)
	{
		if(headptr==NULL)
		{
			headptr = new_node;
			break;
		}
		else
		{
			if(headptr->score<new_node->score)
			{
				new_node->nextpoint = headptr;
				headptr = new_node;
				break;
			}
			else if((headptr->score)==(new_node->score)&&(strcmp(headptr->name, new_node->name)>-1))
			{
				new_node->nextpoint = headptr;
				headptr = new_node;
				break;
			}
		}
	}
	if(i!=0)
	{
		headptr = headsave;
	}
	node_num++;
	
	noecho();
	return;

}

void DrawRecommend(int y, int x, int blockID,int blockRotate){
	// user code
}

int recommend(RecNode *root){
	int max=0; // 미리 보이는 블럭의 추천 배치까지 고려했을 때 얻을 수 있는 최대 점수

	// user code
    

	return max;
}

void recommendedPlay(){
	// user code
}
