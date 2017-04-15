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

//It is NOT recommended to change W to greater than 9.
//Because column numbering system has a shifting problem for double numbers
#define W 7 //width
#define H 6 //height
#define connect 4 //how many connected part will be required?
#define engineversion "0.2"
#include <cstdlib>

//function prototypes
void clearall(int [][W]);
bool play(int [][W],int,int);
int checkgame(int [][W],int=connect);
void grid_copy(int [][W], const int [][W]);
void remove(int [][W], int);
int ai_think(int [][W],int);
int random(int,int);
bool checkpossibilities(int [][W], int, int, int=3);
