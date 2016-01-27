/**
 *  Copyright (C) 2015, Max Cavallo <ixamit_at_gmail_dot_com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

void join(struct shape *shape_a, struct shape *shape_b, size_t *d1, size_t *d2)
{
    int direction;
    size_t l;
    size_t sy,sx,ty,tx;
    size_t r,c;

    if (shape_a->id > shape_b->id)
    {
        l = shape_a->id - shape_b->id;
        direction = -1;
    }
    else
    {
        l = shape_b->id - shape_a->id;
        direction = 1;
    }

    /* fist step links only adjacent nodes */
    if (l==1 )
    {
        if (direction==1) /* down */
        {
            sy=(shape_a->S.y);
            sx=(shape_a->S.x);

            MAP[sy][sx]='|'; sy++;
            MAP[sy][sx]='v'; 

        } 
        if (direction==-1) /* up */
        {
            sy=(shape_a->N.y);
            sx=(shape_a->N.x);

            if (MAP[sy][sx]!=' ')
                sx--;

            MAP[sy][sx]='|'; sy--;
            MAP[sy][sx]='^'; 
        } 
        return;
    }

    /* next step */
    if (direction==1) /* down left */
    {
        sy=(shape_a->W.y);
        sx=(shape_a->W.x);
        ty=(shape_b->W.y);
        tx=(shape_b->W.x);
        
        r=sy; c=sx;
        for (;c>*d1;c--) 
            MAP[r][c]='-';
        MAP[r++][c]='.';
        for (;r<ty;r++)
            MAP[r][c]='|';
        MAP[r][c++]='\'';
        for (;c<tx;c++) 
            if (MAP[r][c]==' ')
                MAP[r][c]='-';

        MAP[r][c]='>';
        *d1-=2;
    }
    if (direction==-1) /* up */
    {
        sy=(shape_a->E.y);
        sx=(shape_a->E.x);
        ty=(shape_b->E.y);
        tx=(shape_b->E.x);

        r=sy; c=sx;
        for (;c<*d2;c++)
            MAP[r][c]='-';
        MAP[r--][c]='\'';
        for (;r>ty;r--)
            MAP[r][c]='|';
        MAP[r][c--]='.';
        for (;c>tx;c--) 
            if (MAP[r][c]==' ')
                MAP[r][c]='-';

        MAP[r][c]='<';
        *d2+=2;
    }
}
