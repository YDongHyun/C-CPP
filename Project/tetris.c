#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int rotate=0;
int weight=0;
int height=0;
int board[26][13]={0,0,};
int tmp_board[4][4]={0,0,};
int shape=0;
int score=0;

bool left=true;
bool right=true;

void gotoxy(int x, int y){
	COORD pos = {x*2,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void game_frame(){
	for(int i=0;i<25;i++){
		gotoxy(0,i+4);printf("▩");
		gotoxy(10,i+4);printf("▩");
	}
	for(int j=0;j<11;j++){
		gotoxy(j,29);
		printf("▩");
	}
	gotoxy(15,5);printf("Score  ");printf("%d",score);
}

int block_move(){
	char c;
        if (_kbhit()) {               
            c = _getch();         
            if (c == -32) {          
                c = _getch();       
                switch (c) {           
                case LEFT:
                	if (left==true){
                		weight-=1;
                    	break;
					}
               		else{
               		 	break;
					}
                case RIGHT:
                	if (right==true){
                		weight+=1;
                    	break;
					}
                	
               		 else{
               		 	break;
					}
                case UP:
                	if(rotate<3){
                		rotate++;
					}
					else{
						rotate=0;
					}
                    break;
                case DOWN:
             
                    break;
                }
            }
    }
    return 0;
}

void board_set(){
	for(int i=0;i<25;i++){
		board[i][0]=1;
		board[i][1]=1;
		board[i][11]=1;
		board[i][12]=1;
	}
	for(int j=0;j<13;j++){
		board[25][j]=1;
	}
}

void print_board(){
	for(int i=0;i<25;i++){
		for(int j=2;j<11;j++){
			gotoxy(j-1,i+4);
			if(board[i][j]==1){
				printf("■");
			}else if (board[i][j]==0){
				printf("  ");
			}
		}
	}
	return;
}

void change_num(){
	for(int i=0;i<25;i++){
		for(int j=0;j<13;j++){
			if(board[i][j]==2){
				board[i][j]=1;
			}
		}
	}
}

void block_set(){
	int bar_block[7][4][4][4]={{{{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0}},
							{{0,0,0,0},{0,0,0,0},{0,0,0,0},{1,1,1,1}},
							{{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0}},
							{{0,0,0,0},{0,0,0,0},{0,0,0,0},{1,1,1,1}}},
							{{{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},
							{{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},
							{{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},
							{{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}}},
							{{{0,0,0,0},{0,1,0,0},{1,1,1,0},{0,0,0,0}},
							{{0,0,0,0},{0,1,0,0},{0,1,1,0},{0,1,0,0}},
							{{0,0,0,0},{1,1,1,0},{0,1,0,0},{0,0,0,0}},
							{{0,0,0,0},{0,0,1,0},{0,1,1,0},{0,0,1,0}}},
							{{{0,0,0,0},{0,1,1,0},{0,0,1,0},{0,0,1,0}},
							{{0,0,0,0},{0,0,0,1},{0,1,1,1},{0,0,0,0}},
							{{0,0,0,0},{0,0,1,0},{0,0,1,0},{0,0,1,1}},
							{{0,0,0,0},{0,1,1,1},{0,1,0,0},{0,0,0,0}}},
							{{{0,0,0,0},{0,1,1,0},{0,1,0,0},{0,1,0,0}},
							{{0,0,0,0},{1,1,1,0},{0,0,1,0},{0,0,0,0}},
							{{0,0,0,0},{0,0,1,0},{0,0,1,0},{0,1,1,0}},
							{{0,0,0,0},{1,0,0,0},{1,1,1,0},{0,0,0,0}}},
							{{{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}},
							{{0,0,0,0},{0,0,1,1},{0,1,1,0},{0,0,0,0}},
							{{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}},
							{{0,0,0,0},{0,0,1,1},{0,1,1,0},{0,0,0,0}}},
							{{{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
							{{0,0,0,0},{0,1,1,0},{0,0,1,1},{0,0,0,0}},
							{{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
							{{0,0,0,0},{0,1,1,0},{0,0,1,1},{0,0,0,0}}}};
	
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			tmp_board[i][j]=0;
		}
	}
	
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(bar_block[shape][rotate][i][j]==1){
				tmp_board[i][j]=2;
		}
		}
	}
}
	
void block_down(){	
	height=0;
	weight=1;
	while(1){
		block_set();
		block_move();
		for(int i=0;i<4;i++){			
			for(int j=0;j<4;j++){
				if(tmp_board[i][j]==2){
					board[i+height][j+4+weight]=tmp_board[i][j];
					gotoxy(3+j+weight,i+height+4);
					printf("■");
				}
			}
		}
		Sleep(150);
	
		for(int i=25;i>0;i--){
			for(int j=2;j<11;j++){
				if((board[i][j]==2&&board[i+1][j]==1)){
					change_num();
					return;
				}
				else if (board[i][j]==2&&board[i+1][j-1]==1){
					left=false;
				}
				
				else if (board[i][j]==2&&board[i+1][j+1]==1){
					right=false;
					
				}
				else if (board[i][j]==2&&board[i][j+1]==0){
					right=true;	
				}
				else if (board[i][j]==2&&board[i][j-1]==0){
					left=true;	
				}
				
			}
		}
		for(int i=0;i<25;i++){
			for(int j=2;j<11;j++){				
				if(board[i][j]==2){
					gotoxy(j-1,i+4);
					printf("  ");
					board[i][j]=0;	
				}
			}
		}
		height++;
	}
}

void blockshell_move(int row){
	for(int j=1;j<10;j++){
		for(int k=2;k<11;k++){
					board[row-j+1][k]=board[row-j][k];
					board[row-j][k]=0;
}
	}
					
	return;
}


void block_del(){
	int cnt=0;
	for(int i=24;i>0;i--){
		for(int j=2;j<11;j++){
			if (board[i][j]==1){
				cnt++;
				if(j==10&&cnt>=9){
					score+=100;
					for(int k=2;k<11;k++){
					board[i][k]=0;
					cnt=0;
				}
				blockshell_move(i);
				i=25;
				}
			}
			if(j==10&&cnt<9){
				cnt=0;
			}			

		}
	}
	return;
}


int main(){
	board_set();
	while(1){	
		srand(time(NULL));
		shape = rand()%7; 
		game_frame();
		block_down();
		block_del();
		print_board();
	}
}
