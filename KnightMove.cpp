/*
 * Position of Knight is given on a chessboard.
 * Return me something (adjacency matrix or list or anything) which shows all
 * the positions the knight can reach upto from a given position.
 * I must be able to tell, from what is returned, if the position is reachable or not
 * and if reachable I must be able to trace the path from given position to target position
 * */
//+--------------------------------------+
//| == ADJACENCY MATRIX BASED SOLUTION ==|
//+--------------------------------------+

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cassert>
#include<cstring>

using namespace std;

#define MAX_MOVES 8
struct coord
{
  int row;
  int col;
};

coord possibleMoves[] = {	{-2, +1},
				{-1, +2},
				{+1, +2},
				{+2, +1},
				{+2, -1},
				{+1, -2},
				{-1, -2},
				{-2, -1}
			};
                        
int isValid(int r, int c)
{
	if((r >= 0 && r <= 7)&&
	   (c >= 0 && c <= 7))
		return 1;
	return 0;
}

void getValidMoves(int r, int c, coord *lst, int *size)
{
	assert(lst);
	assert(size);
	*size = 0;
	for(size_t i = 0; i<sizeof(possibleMoves)/sizeof(possibleMoves[0]); i++)
	{
		if(isValid(r + possibleMoves[i].row, c + possibleMoves[i].col))
		{
			lst[*size].row = r + possibleMoves[i].row;
			lst[*size].col = c + possibleMoves[i].col;
			(*size)++;
		}
	}

	return ;
}

int ChessBoard[MAX_MOVES*MAX_MOVES][MAX_MOVES*MAX_MOVES];

void backTrack(int row, int col)
{
	int size = 0;
	coord moves[MAX_MOVES] = {{0, 0}};
	getValidMoves(row, col, moves, &size);
	for(int i = 0; i < size; i++)
	{
		if(ChessBoard[row*8+col][moves[i].row*8 + moves[i].col] != 1)
		{
			ChessBoard[row*8+col][moves[i].row*8 + moves[i].col] = 1;
			backTrack(moves[i].row, moves[i].col);
		}
	}
}

void getAllPositions()
{
	int r = 0, c = 0;

	cout << "Cell's row index = ";
	cin >> r;
	cout << "Cell's column index = ";
	cin >> c;

	//r = 3, c = 3;
	backTrack(r, c);
	cout << "   " ;
	for(int i = 0; i < MAX_MOVES*MAX_MOVES; i++)
		printf("%2d ", i);
	cout << endl;

	for(int i = 0; i < MAX_MOVES*MAX_MOVES; i++)
	{
		printf("%2d ", i);
		for(int j = 0; j < MAX_MOVES*MAX_MOVES; j++)
			printf("%2d ", ChessBoard[i][j]); // << endl;
		cout << endl;
	}
	return;
}
/////////////////////////////////////////////////////////////////////////
//+------------------------------------+
//| == ADJACENCY LIST BASED SOLUTION ==|
//+------------------------------------+
#define MAX_CHILDREN 8
#define POSITIONS 8


class graphNode
{
	static bool bChessBoard[POSITIONS][POSITIONS];
public:
	coord pos;
	graphNode* children[MAX_CHILDREN];
	int count;
	static bool isOccupied(int r, int c)
	{
		if(isValid(r, c))
			return bChessBoard[r][c];
		return false;
	}

	static void setOccupied(int r, int c)
	{
		if(isValid(r, c))
			bChessBoard[r][c] = 1;
	}

	graphNode():count(0)
	{
		pos.row = -1;
		pos.col = -1;
	}

	graphNode(int r, int c):count(0)
	{
		pos.row = r;
		pos.col = c;
	}


	static graphNode *getGraphNode(int r, int c)
	{
		graphNode *aNode = new graphNode(r, c);
		memset(aNode->children, 0, MAX_CHILDREN*sizeof(graphNode*));
		return aNode;
	}
};

bool graphNode::bChessBoard[POSITIONS][POSITIONS];

void backTrackAdjList(graphNode *root, int row, int col)
{
	assert(root);
	int size = 0;
	coord moves[MAX_MOVES] = {{0, 0}};
	getValidMoves(row, col, moves, &size);
	for(int i = 0; i < size; i++)
	{
		if(!graphNode::isOccupied(moves[i].row, moves[i].col) )
		{
			graphNode *g = graphNode::getGraphNode(moves[i].row, moves[i].col);
			root->children[root->count++] = g;
			graphNode::setOccupied(moves[i].row, moves[i].col);
			backTrackAdjList(g, moves[i].row, moves[i].col);
		}
	}
}

void dfsVisit(graphNode* root)
{
	if(!root)
		return;
	cout << "row = " << root->pos.row << " col = " << root->pos.col << endl;

	for(int i = 0; i < root->count; i++)
		dfsVisit(root->children[i]);

	return;
}

void freeGraph(graphNode* root)
{
	if(!root)
		return;

	for(int i = 0; i < root->count; i++)
		freeGraph(root->children[i]);
	free(root);
	root = NULL;
	return;
}

void getAllPositionsAdjList()
{
	int r = 0, c = 0;

	cout << "Cell's row index = ";
	cin >> r;
	cout << "Cell's column index = ";
	cin >> c;

	//r = 3, c = 3;
	if(!isValid(r, c))
		return;

	graphNode *root = graphNode::getGraphNode(r, c);
	graphNode::setOccupied(r, c);
	backTrackAdjList(root, r, c);

	dfsVisit(root);

	freeGraph(root);
	return;
}
