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
#include "box.h"
#include "iff.h"
#include "path.h"

/* map */
char MAP[MAX_ROWS][MAX_COLS];
size_t CURS_Y, CURS_X;

/* shape */
struct shape SHAPE[MAX_SHAPES];
size_t N_SHAPES, LARGEST;

/* links */
char LINK[MAX_SHAPES][MAX_SHAPES];

#define MEMORY (sizeof(SHAPE)+sizeof(LINK)+sizeof(MAP))

void show_memory()
{
    printf ("Used memory:%luK\n",MEMORY/1024);
}

void build_links ()
{
    size_t i,j,r,c;
    size_t d1=((MAX_COLS/2)-(LARGEST/2))-5;
    size_t d2=((MAX_COLS/2)+(LARGEST/2))+6;

    i=N_SHAPES-1;
    j=0;
    while (i)
    {
        j++;
        for (r=0;r<i;r++)
        {
            c=r+j;
            if (LINK[r][c]==1)
                join(&SHAPE[r],&SHAPE[c],&d1,&d2);
            if (LINK[c][r]==1)
                join(&SHAPE[c],&SHAPE[r],&d1,&d2);
        }
        i--;
    }

}

void build_shapes()
{
    size_t i;

    /* clear map */
    CURS_Y = 1; CURS_X = 0;
    memset(MAP,32,MAX_ROWS*MAX_COLS);
    for (i=0;i<MAX_ROWS;i++)
        MAP[i][MAX_COLS-1]='\n';
    
    for (i=0;i<N_SHAPES;i++)
    {
        if (SHAPE[i].type == BOX )
            box(&SHAPE[i]);
        else if (SHAPE[i].type == IFF)
            iff(&SHAPE[i]);
        /* TODO else error */
    }

    CURS_Y-=1;
    MAP[CURS_Y][CURS_X]=0; /* zero term */
}

size_t count_chars(const char *s, const char c)
{
    size_t n=1;
    const char *p=s;
    while ((p=strchr(p,c)))
        n++,p++;

    return n;
}

void load_data (const char *filename)
{
    char *p,buf[128];
    int type;
    size_t len,height;

    FILE *fp=fopen (filename,"r");
    if (!fp) { perror ("fopen"); exit(1); }

    while (fgets(buf,sizeof(buf),fp))
    {
        if ((p=strchr(buf,'\n')))
            *p=0;

        if ((len=strlen(buf))==0)
            break;

        /* cont NEWLINE */
        height = count_chars(buf,NEWLINE);

        if (buf[len-1]=='?')
        {
            type = IFF;
            height=3;
        }
        else
        {
            type = BOX;
        }
        len+=2; 
        if (len>LARGEST) LARGEST=len;

        SHAPE[N_SHAPES].id = N_SHAPES+1;
        SHAPE[N_SHAPES].type = type;
        SHAPE[N_SHAPES].align = 0; /* center */
        SHAPE[N_SHAPES].height = height;
        SHAPE[N_SHAPES].width = len;
        strcpy(SHAPE[N_SHAPES].txt,buf);
        N_SHAPES++;
    }

    int r;
    size_t a,b;
    while (fgets(buf,sizeof(buf),fp))
    {
        if ((p=strtok(buf," ,")))
            r=sscanf(p,"%zu",&a); 
        while (p) {
            p=strtok(NULL," ,");
            if (p && (r=sscanf(p,"%zu",&b))==1)
            {
                LINK[a-1][b-1]=1;
                a=b;
            } 
        };
    }
    
}

void ruler(size_t n)
{
    int i,d=n/10;
   
    for (putchar(' '),i=0;i<d;i++)
        printf ("%*c",10,'1'+i);
    for (putchar('\n'),i=0;i<=n;i++)
        putchar('0'+i%10);
    putchar('\n');
}

int main (int argc, char **argv)
{

    load_data(argv[1]);
    build_shapes();
    build_links();
    
    ruler(MAX_COLS);
/*
    puts("          1         2         3         4         5          ");
    puts("0123456789012345678901234567890123456789012345678901234567890");
*/
    fputs (&MAP[0][0],stdout);       

    show_memory();

    return 0;
}
