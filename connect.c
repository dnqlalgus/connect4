/***************************************************************************
 *   Copyright (C) 2004 by [alp, cgty]                                     *
 *   alperen@users.sourceforge.net                                         *
 *   cgty@users.sourceforge.net                                            *
 *                                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "engine.h"

void clearall(int grid[][W])
{
	for (int i=0;i<H;i++)
		for (int k=0;k<W;k++)
			grid[i][k]=0;
}

int random(int from, int to)
{
	return from + rand()%(to-from+1);
}


bool play(int grid[][W],int id,int col)
{
	col--;
	int counter=0;
	for (int i=H-1;i>=0;i--)
	{
		counter++;
		if (grid[i][col]==0)
		{
			grid[i][col]=id;
			return true;
		}
	}

	//This column is full. Please choose another.
	return false;
}

int checkgame(int grid[][W], int conn)
{
	/*************************************************
	this function returns 0, if nobody finished.
	this function returns 1, if player 1 finished.
	this function returns 2, if player 2 finished.
	this function returns -1, if game is ended as drawn.
	**************************************************/

	int i,k,m,check=0;
	//Check the game for player 1 firstly
	//now check for horizontal posibilities
	for (i=0;i<H;i++)
	{
		for (k=0;k<W;k++)
		{
			if (grid[i][k]==1)
				check++;
			else
				check=0;
			if (check==conn)
				return 1;
		}
		check=0;
	}
	//now check for vertical posibilities
	check=0;
	for (i=0;i<W;i++)
	{
		for (k=0;k<H;k++)
		{
			if (grid[k][i]==1)
				check++;
			else
				check=0;
			if (check==conn)
				return 1;
		}
		check=0;
	}

	//now check for crosswise posibilities
	//from top-left to bottom-right control
	check=0;
	for (i=0;i<H;i++)
		for (k=0;k<W;k++)
		{
			if (grid[i][k]==1)
			{
				check++;
				for (m=1;m<conn;m++)
				{
					if (i+m<H && k+m<W)
						if (grid[i+m][k+m]==1)
							check++;
						else
							break;
					if (check==conn)
						return 1;
				}
				check=0;
			}
		}
	//from top-right to bottom-left control
	check=0;
	for (i=0;i<H;i++)
		for (k=0;k<W;k++)
		{
			if (grid[i][k]==1)
			{
				check++;
				for (m=1;m<conn;m++)
				{
					if (i+m<H && k-m>=0)
						if (grid[i+m][k-m]==1)
							check++;
						else
							break;
					if (check==conn)
						return 1;
				}
				check=0;
			}
		}

	//Check the game for player 2
	//now check for horizontal posibilities
	for (i=0;i<H;i++)
	{
		for (k=0;k<W;k++)
		{
			if (grid[i][k]==2)
				check++;
			else
				check=0;
			if (check==conn)
				return 2;
		}
		check=0;
	}
	//now check for vertical posibilities
	check=0;
	for (i=0;i<W;i++)
	{
		for (k=0;k<H;k++)
		{
			if (grid[k][i]==2)
				check++;
			else
				check=0;
			if (check==conn)
				return 2;
		}
		check=0;
	}

	//now check for crosswise posibilities
	//from top-left to bottom-right control
	check=0;
	for (i=0;i<H;i++)
		for (k=0;k<W;k++)
		{
			if (grid[i][k]==2)
			{
				check++;
				for (m=1;m<conn;m++)
				{
					if (i+m<H && k+m<W)
						if (grid[i+m][k+m]==2)
							check++;
						else
							break;
					if (check==conn)
						return 2;
				}
				check=0;
			}
		}
	//from top-right to bottom-left control
	check=0;
	for (i=0;i<H;i++)
		for (k=0;k<W;k++)
		{
			if (grid[i][k]==2)
			{
				check++;
				for (m=1;m<conn;m++)
				{
					if (i+m<H && k-m>=0)
						if (grid[i+m][k-m]==2)
							check++;
						else
							break;
					if (check==conn)
						return 2;
				}
				check=0;
			}
		}

	//at this point, there is no winner.
	//function must decide if game draws(return -1) or continues(return 0)
	for (i=0;i<W;i++)
		for (k=0;k<H;k++)
			if (grid[k][i]==0)
				return 0;//game continues

	return -1;//game finished as drawn

}

void grid_copy(int temp[][W], const int grid[][W])
{
	int i,k;
	for (i=0;i<H;i++)
		for(k=0;k<W;k++)
			temp[i][k]=grid[i][k];
}

void remove(int grid[][W], int col)
{
	col--;
	int i;
	for (i=0; i<H; i++)
		if ( grid[i][col] != 0 )
		{
			grid[i][col] = 0;
			break;
		}
}

int ai_think(int grid[][W],int id)
{
	int temp[H][W];
	grid_copy(temp,grid);

	int op=(id==1 ? 2 : 1);
	int i,k;
	//for offence
	for (i=1;i<=W;i++)
		if (play(temp,id,i))
			if (checkgame(temp)==id)
				return i;
			else
				remove(temp,i);
	//for defence 
	for (i=1;i<=W;i++)
		if (play(temp,op,i))
			if (checkgame(temp)==op)
				return i;
			else
				remove(temp,i);

	//blacklist holds columns that will NOT be played
	int blacklist[W];
	int blacklist_size=0;
	bool can_play=true;

	for (i=1;i<=W;i++)
		if (play(temp,id,i))
		{
			for (k=1;k<=W;k++)
				if (play(temp,op,k))
				{
					if (checkgame(temp)==op)
						blacklist[blacklist_size++]=i;
					remove(temp,k);
				}
			remove(temp,i);
		}


	//for making triple(connect-1)
	for (i=1;i<=W;i++)
		if (play(temp,id,i))
		{
			if (checkpossibilities(temp,i,id))
			{
				can_play=true;
				for (k=0;k<blacklist_size;k++)
					if (blacklist[k]==i)
						can_play=false;

				if (can_play)
					return i;
			}
			remove(temp,i);
		}

	if (blacklist_size==7)
		return random(1,W);
	else
		while (true)
		{
			can_play=true;
			int chosen=random(1,W);
			for (i=0;i<blacklist_size;i++)
				if (chosen==blacklist[i])
					can_play=false;
			if (can_play)
				return chosen;
		}
}

bool checkpossibilities(int grid[][W], int col, int id, int conn)
{
	col--;
	// find in which row the last played piece located at the given col
	int i,j,row=0;
	for (i=0;i<H;i++)
	{
		if (grid[i][col]!=0)
			break;
		row++;
	}

	// start point has become [row,col]

	
	int counter = 1;

	// vertical control
	// it is enough to think from start to bottom
	for (i=row+1; i<H; i++)
		if (grid[i][col] == id)
			counter++;
		else
			break;
	
	if ( counter == conn )
		return true;

	counter = 1;

	// horizontal control
	// from start to right
	for (j=col+1; j<W; j++)
		if (grid[row][j] == id)
			counter++;
		else
			break;
	// from start to left
	for (j=col-1; j>=0; j--)
		if (grid[row][j] == id)
			counter++;
		else
			break;

	if ( counter == conn )
		return true;

	counter = 1;



	// top-left to bottom-right crosswise control
	// from start to bottom-right
	for (i=row+1, j=col+1; i<H && j<W; i++, j++)
		if (grid[i][j] == id)
			counter++;
		else
			break;
	// from start to top-left
	for (i=row-1, j=col-1; i<=0 && j<=0; i--, j--)
		if (grid[i][j] == id)
			counter++;
		else
			break;

	if ( counter == conn )
		return true;

	counter = 1;


	// top-right to bottom-left crosswise control
	// from start to bottom-left
	for (i=row+1, j=col-1; i<H, j>=0; i++, j--)
		if (grid[i][j] == id)
			counter++;
		else
			break;
	// from start to top-right
	for (i=row-1, j=col+1; i>=0, j<W; i--, j++)
		if (grid[i][j] == id)
			counter++;
		else
			break;

	if ( counter == conn )
		return true;

	return false;

}
