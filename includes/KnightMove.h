/*
 * KnightMove.h
 *
 *  Created on	:	Apr 26, 2017
 *  Author		:	I309980
 * 
 *  === SOURCE === 
 *
 *  === QUESTION ===
 *
 *
 *	=== SOLUTION APPROACH ===
 */

#ifndef INCLUDES_KNIGHTMOVE_H_
#define INCLUDES_KNIGHTMOVE_H_

#include<vector>
using namespace std;
class KnightMove{
	vector<vector<int> > *board;
	int N;
	int path;
public:

	KnightMove(int N);
	vector<vector<int> > getBoard();
	bool canMove(int r, int c);
	bool solve(int r, int c, int index, int path);
	static void KnightMoveSolution(int);

};



#endif /* INCLUDES_KNIGHTMOVE_H_ */
