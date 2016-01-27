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

#ifndef COMMON_H
#define COMMON_H

/* Maximum MAP area */
#define MAX_ROWS 240
#define MAX_COLS 50

/* Maximum shapes */
#define MAX_SHAPES 100
#define MAX_TXT 160

/* Node's type */
enum { BOX=1, IFF=2 };

/* map point */
struct point{ size_t x, y;};
struct shape
{
    size_t id;             /* progressive 1..N_SHAPES */
    int type;
    int align;             /* -/0/+ */
    struct point N,S,W,E;  /* cardinal direction */
    size_t height,width;   
    char txt[MAX_TXT];     /* the text */
};
#define NEWLINE ';'

/* some extern */
extern struct shape SHAPE[MAX_SHAPES];
extern char MAP[MAX_ROWS][MAX_COLS];
extern size_t CURS_Y, CURS_X;
extern size_t N_SHAPES,LARGEST;

/* write to map area */
#if 1
#define PUTC(c)       MAP[CURS_Y][CURS_X++]=((c))
#define PUTC_N(c,n)   do{size_t _n=(n);while(_n--)PUTC((c));}while(0)
#define PUTSPC(n)     CURS_X+=(n)
#define PUTS(s)       do{char *_x=s;while(*_x)PUTC(*_x++);}while(0)
#define PRINT_NEWLINE do{CURS_Y++,CURS_X=0;}while(0)
#else
#define PUTC(c)       putchar((c))
#define PUTC_N(c,n)   do{size_t _n=(n);while(_n--)PUTC((c));}while(0)
#define PUTSPC(n)     PUTC_N(' ',(n))
#define PUTS(s)       fputs(s,stdout);
#define PRINT_NEWLINE PUTC('\n')
#endif 
#endif /* COMMON_H */
