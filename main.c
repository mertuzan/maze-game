//Suggested console window size width:104 height:36

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FALSE 0
#define TRUE 1

struct lab{
    char data;
    struct lab *up;
    struct lab *down;
    struct lab *right;
    struct lab *left;
};

void display_maze(struct lab **maze,int row,int col);
int find_path(int x, int y,struct lab **maze,int row,int col);
int convert(struct lab **maze,int row,int col);
int connectNodes(struct lab **maze,int row,int col);
int setNodes(int row,int col,struct lab **maze);


int main()
{
    struct lab **maze;
    int row,col,startX,startY,endX,endY;
    again:
    printf("Enter number of rows (MAX 30):");
    scanf("%d",&row);
    printf("Enter number of columns (MAX 55):");
    scanf("%d",&col);
    printf("\n");

    if(row>30 || col>55)
        goto again;
    maze=setNodes(row,col,maze);
    maze=connectNodes(maze,row,col);
	display_maze(maze,row,col);

	again2:
    printf("Enter the start point (x):\n");
    scanf("%d",&startX);
    printf("Enter the start point (y):\n");
    scanf("%d",&startY);
    printf("Enter the end point (x):\n");
    scanf("%d",&endX);
    printf("Enter the end point (y):\n");
    scanf("%d",&endY);

    int c;
    if(maze[startX][startY].data!='1' || maze[endX][endY].data!='1'){
        printf("No path found at entered points. For new coordinates enter 1.");
        scanf("%d",&c);
        if(c==1)
            goto again2;
        else
            exit(0);
    }

    maze[startX][startY].data='S';
    maze[endX][endY].data='G';

	if (find_path(startY,startX,maze,row,col) == TRUE ){
		printf("Success!\n");
        maze[endX][endY].data='y';
        maze=convert(maze,row,col);
        display_maze(maze,row,col);
	}else{
        printf("Path not found.\n");
	}

	return 0;
}

int convert(struct lab **maze,int row,int col){
    int i,j;

    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            if(maze[i][j].data=='1')
                maze[i][j].data='0';
        }
    }
    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            if(maze[i][j].data=='y')
                maze[i][j].data='1';
        }
    }

    return maze;
}

void display_maze(struct lab **maze,int row, int col){
	int i,j;

	printf("MAZE (%c PATH | %c WALL):\n\  ",178,176);

    for(i=0;i<col;i++)
        printf("%d",i);

    printf("\n");
	for ( i = 0; i < row; i++ ){
	    if(i>=10)
            printf("%d",i);
        else
            printf("%d ",i);

        for ( j = 0; j< col; j++ ){
            if(j>=10){
               if(maze[i][j].data=='1')
                printf("%c%c",178,178);
            else
                printf("%c%c",176,176);
            }else{
            if(maze[i][j].data=='1')
                printf("%c",178);
            else
                printf("%c",176);
            }
        }
        printf("\n");
	}
	printf("\n");
}

int find_path(int x, int y,struct lab **maze,int row,int col){

	if ( x < 0 || x > col - 1 || y < 0 || y > row - 1 )
        return FALSE;
	if ( maze[y][x].data == 'G' )
        return TRUE;
	if ( maze[y][x].data != '1' && maze[y][x].data != 'S' )
        return FALSE;

	maze[y][x].data = 'y';


	if ( find_path(x,y-1,maze,row,col) == TRUE ) return TRUE;

	if ( find_path(x +1, y,maze,row,col) == TRUE ) return TRUE;

	if ( find_path(x, y + 1,maze,row,col) == TRUE ) return TRUE;

	if ( find_path(x - 1, y,maze,row,col) == TRUE ) return TRUE;

	maze[y][x].data = '0';

	return FALSE;
}

int connectNodes(struct lab **maze,int row,int col){

    int i,j;

    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
                if(j==col){
                    continue;
                }
            maze[i][j].right=maze[i][j+1].data;

        }
    }

    for(i=row-1;i>0;i--){
        for(j=col-1;j>0;j--){
            if(j==0){
                    continue;
                    }
            maze[i][j].left=maze[i][j-1].data;

        }
    }

    j=0;
    while(j!=col){
        for(i=row-1;i>0;i--){
            maze[i][j].up=maze[i-1][j].data;
        }
        j++;
    }

    j=0;
    while(j!=col){
        for(i=0;i<row-1;i++){
            maze[i][j].down=maze[i+1][j].data;
        }
        j++;
    }

    return maze;
}

int setNodes(int row,int col,struct lab **maze){

    int i,j,a;
    srand(time(NULL));
    char buff;

    maze=(struct lab**)malloc(sizeof(struct lab)*row);
    for(i=0;i<row;i++)
        maze[i]=(struct lab*)malloc(sizeof(struct lab)*col);

    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            a=rand()%2;
            buff=a+'0';
            maze[i][j].data=buff;
        }
    }
    return maze;
}
