#ifndef  INTERPRETER_TAB_H
#define  INTERPRETER_TAB_H

#define	Key_CREATE	257
#define	Key_DROP	258
#define	Key_SELECT	259
#define	Key_INSERT	260
#define	Key_DELETE	261
#define	Key_TABLE	262
#define	Key_INDEX	263
#define	Key_INTO	264
#define	Key_FROM	265
#define	Key_WHERE	266
#define	Key_AND	267
#define	Key_ON	268
#define	Key_VALUES	269
#define	Key_UNIQUE	270
#define	Key_PRIMARY	271
#define	Key_KEY	272
#define	Type_FILE	273
#define	Key_EXECFILE	274
#define	Key_INTEGER	275
#define	Key_FLOAT	276
#define	Key_CHAR	277
#define	Key_EXIT	278
#define	Type_LT	279
#define	Type_GT	280
#define	Type_GE	281
#define	Type_LE	282
#define	Type_EQ	283
#define	Type_NE	284
#define	Type_INT	285
#define	Type_REAL	286
#define	Type_STRING	287
#define	Type_DQSTRING	288
#define	Type_BSSTRING	289



#include "ParseHelp.h"

/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C

	  Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

   /* As a special exception, you may create a larger work that contains
	  part or all of the Bison parser skeleton and distribute that work
	  under terms of your choice, so long as that work isn't itself a
	  parser generator using the skeleton or a modified version thereof
	  as a parser skeleton.  Alternatively, if you modify or redistribute
	  the parser skeleton itself, you may (at your option) remove this
	  special exception, which will cause the skeleton and the resulting
	  Bison output files to be licensed under the GNU General Public
	  License without this special exception.

	  This special exception was added by the Free Software Foundation in
	  version 2.2 of Bison.  */

#ifndef YY_YY_SQL_TAB_H_INCLUDED
# define YY_YY_SQL_TAB_H_INCLUDED
	  /* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */


# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif
extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse(void *YYPARSE_PARAM);
#else
int yyparse();
#endif
#else /* ! YYPARSE_PARAM */

#if defined __STDC__ || defined __cplusplus
#ifdef __cplusplus
extern "C"
#endif
int yyparse(void);
#else
int yyparse();
#endif
#endif /* ! YYPARSE_PARAM */
#endif