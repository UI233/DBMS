
/*  A Bison parser, made from interpreter.y
	by GNU Bison version 1.28  */

#define YYBISON 1  /* Identify Bison output.  */

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

#line 3 "interpreter.y"


#include <iostream>
#include <string>
#include <cstdlib>
#include "Interpreter.h"
#include "ParseHelp.h"
#include "interpreter.tab.h"

int yylex();
void yyerror(char *s, ...);

#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		99
#define	YYFLAG		-32768
#define	YYNTBASE	41

#define YYTRANSLATE(x) ((unsigned)(x) <= 289 ? yytranslate[x] : 68)

static const char yytranslate[] = { 0,
	 2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	 2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	 2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	 2,     2,     2,     2,     2,     2,     2,     2,     2,    37,
	38,    39,     2,    40,     2,     2,     2,     2,     2,     2,
	 2,     2,     2,     2,     2,     2,     2,     2,    36,     2,
	 2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	 2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	 2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	 2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	 2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	 2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	 2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	 2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	 2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	 2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	 2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	 2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	 2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	 2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	 2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	 2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	 2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	 2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	 2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
	 2,     2,     2,     2,     2,     1,     3,     4,     5,     6,
	 7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
	17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
	27,    28,    29,    30,    31,    32,    33,    34,    35
};

#if YYDEBUG != 0
static const short yyprhs[] = { 0,
	 0,     3,     5,     7,     9,    11,    13,    15,    17,    19,
	21,    23,    25,    28,    36,    45,    49,    53,    58,    64,
	72,    79,    81,    84,    86,    90,    92,    96,    98,   100,
   105,   107,   109,   113,   115,   119,   123,   125,   127,   129,
   131,   133,   135,   137,   139,   141,   143,   145,   147,   149,
   151,   153
};

static const short yyrhs[] = { 42,
	36,     0,    66,     0,    43,     0,    44,     0,    45,     0,
	52,     0,    51,     0,    50,     0,    46,     0,    47,     0,
	48,     0,    49,     0,    20,    19,     0,     3,     8,    33,
	37,    55,    53,    38,     0,     3,     9,    33,    14,    33,
	37,    33,    38,     0,     4,     8,    33,     0,     4,     9,
	33,     0,     7,    11,    65,    54,     0,     5,    39,    11,
	65,    54,     0,     6,    10,    65,    15,    37,    61,    38,
	 0,    40,    17,    18,    37,    65,    38,     0,    67,     0,
	12,    59,     0,    67,     0,    55,    40,    56,     0,    56,
	 0,    33,    57,    58,     0,    21,     0,    22,     0,    23,
	37,    31,    38,     0,    16,     0,    67,     0,    59,    13,
	60,     0,    60,     0,    65,    63,    62,     0,    61,    40,
	62,     0,    62,     0,    31,     0,    32,     0,    64,     0,
	25,     0,    28,     0,    26,     0,    27,     0,    29,     0,
	30,     0,    34,     0,    33,     0,    35,     0,    33,     0,
	24,     0,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   101,   103,   104,   105,   106,   109,   110,   111,   114,   115,
   116,   117,   121,   130,   141,   152,   162,   172,   183,   194,
   204,   209,   215,   220,   226,   231,   239,   248,   249,   250,
   253,   254,   257,   263,   270,   278,   283,   290,   292,   293,
   296,   298,   299,   300,   301,   302,   305,   307,   310,   312,
   315,   319
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = { "$","error","$undefined.","Key_CREATE",
"Key_DROP","Key_SELECT","Key_INSERT","Key_DELETE","Key_TABLE","Key_INDEX","Key_INTO",
"Key_FROM","Key_WHERE","Key_AND","Key_ON","Key_VALUES","Key_UNIQUE","Key_PRIMARY",
"Key_KEY","Type_FILE","Key_EXECFILE","Key_INTEGER","Key_FLOAT","Key_CHAR","Key_EXIT",
"Type_LT","Type_GT","Type_GE","Type_LE","Type_EQ","Type_NE","Type_INT","Type_REAL",
"Type_STRING","Type_DQSTRING","Type_BSSTRING","';'","'('","')'","'*'","','",
"top_sentence","top_stmt","dml","ddl","exec_file","create_table","create_index",
"drop_table","drop_index","delete_operation","query","insert","op_primary_key",
"op_where","attr_definition","attr_pair","attr_type","op_unique","condition_list",
"condition","value_list","value","operator","Type_ASTRING","Type_BSTRING","exit",
"nothing", NULL
};
#endif

static const short yyr1[] = { 0,
	41,    42,    42,    42,    42,    43,    43,    43,    44,    44,
	44,    44,    45,    46,    47,    48,    49,    50,    51,    52,
	53,    53,    54,    54,    55,    55,    56,    57,    57,    57,
	58,    58,    59,    59,    60,    61,    61,    62,    62,    62,
	63,    63,    63,    63,    63,    63,    64,    64,    65,    65,
	66,    67
};

static const short yyr2[] = { 0,
	 2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
	 1,     1,     2,     7,     8,     3,     3,     4,     5,     7,
	 6,     1,     2,     1,     3,     1,     3,     1,     1,     4,
	 1,     1,     3,     1,     3,     3,     1,     1,     1,     1,
	 1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
	 1,     0
};

static const short yydefact[] = { 0,
	 0,     0,     0,     0,     0,     0,    51,     0,     3,     4,
	 5,     9,    10,    11,    12,     8,     7,     6,     2,     0,
	 0,     0,     0,     0,     0,     0,    13,     1,     0,     0,
	16,    17,     0,    50,    49,     0,    52,     0,     0,    52,
	 0,     0,    18,    24,     0,    52,    26,     0,    19,     0,
	23,    34,     0,    28,    29,     0,    52,     0,     0,    22,
	 0,    38,    39,    48,    47,     0,    37,    40,     0,    41,
	43,    44,    42,    45,    46,     0,     0,    31,    27,    32,
	 0,    25,    14,     0,    20,     0,    33,    35,     0,     0,
	15,    36,    30,     0,     0,    21,     0,     0,     0
};

static const short yydefgoto[] = { 97,
	 8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
	18,    59,    43,    46,    47,    57,    79,    51,    52,    66,
	67,    76,    68,    53,    19,    44
};

static const short yypact[] = { -1,
	29,    31,   -22,    11,    22,    16,-32768,     5,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    10,
	12,    13,    14,    33,   -11,   -11,-32768,-32768,    15,    28,
-32768,-32768,   -11,-32768,-32768,    34,    36,    17,    18,    36,
	19,   -11,-32768,-32768,     9,    20,-32768,    21,-32768,    -5,
	40,-32768,   -14,-32768,-32768,    24,    38,    -8,    25,-32768,
	26,-32768,-32768,-32768,-32768,    -4,-32768,-32768,   -11,-32768,
-32768,-32768,-32768,-32768,-32768,    -5,    35,-32768,-32768,-32768,
	37,-32768,-32768,    27,-32768,    -5,-32768,-32768,    30,    39,
-32768,-32768,-32768,   -11,    32,-32768,    57,    62,-32768
};

static const short yypgoto[] = { -32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,    41,-32768,     6,-32768,-32768,-32768,    -2,-32768,
   -66,-32768,-32768,   -25,-32768,   -39
};


#define	YYLAST		81


static const short yytable[] = { 36,
	37,     1,     2,     3,     4,     5,    60,    40,    81,    88,
	70,    71,    72,    73,    74,    75,    24,    80,     6,    92,
	25,    34,     7,    35,    45,    62,    63,    64,    65,    54,
	55,    56,    26,    85,    27,    86,    20,    21,    22,    23,
	28,    39,    29,    33,    30,    31,    32,    42,    41,    45,
	48,    38,    69,    78,    90,    50,    98,    61,    84,    58,
	77,    99,    83,    82,    91,    89,    87,    93,    95,    96,
	 0,     0,     0,     0,     0,    94,     0,     0,     0,     0,
	49
};

static const short yycheck[] = { 25,
	26,     3,     4,     5,     6,     7,    46,    33,    17,    76,
	25,    26,    27,    28,    29,    30,    39,    57,    20,    86,
	10,    33,    24,    35,    33,    31,    32,    33,    34,    21,
	22,    23,    11,    38,    19,    40,     8,     9,     8,     9,
	36,    14,    33,    11,    33,    33,    33,    12,    15,    33,
	33,    37,    13,    16,    18,    37,     0,    37,    33,    40,
	37,     0,    38,    58,    38,    31,    69,    38,    94,    38,
	-1,    -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,    -1,
	40
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/local/share/bison.simple"
/* This file comes from bison-1.28.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

   /* As a special exception, when this file is copied by Bison into a
	  Bison output file, you may use that output file without restriction.
	  This special exception was added by the Free Software Foundation
	  in version 1.24 of Bison.  */

	  /* This is the parser code that is written into each bison parser
		when the %semantic_parser declaration is not specified in the grammar.
		It was written by Richard Stallman by simplifying the hairy parser
		used when %semantic_parser is specified.  */

#ifndef YYSTACK_USE_ALLOCA
#ifdef alloca
#define YYSTACK_USE_ALLOCA
#else /* alloca not defined */
#ifdef __GNUC__
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#define YYSTACK_USE_ALLOCA
#include <alloca.h>
#else /* not sparc */
		/* We think this test detects Watcom and Microsoft C.  */
		/* This used to test MSDOS, but that is a bad idea
		   since that symbol is in the user namespace.  */
#if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#if 0 /* No need for malloc.h, which pollutes the namespace;
	 instead, just don't use alloca.  */
#include <malloc.h>
#endif
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
		   /* I don't know what this was needed for, but it pollutes the namespace.
			  So I turned it off.   rms, 2 May 1997.  */
			  /* #include <malloc.h>  */
#pragma alloca
#define YYSTACK_USE_ALLOCA
#else /* not MSDOS, or __TURBOC__, or _AIX */
#if 0
#ifdef __hpux /* haible@ilog.fr says this works for HPUX 9.05 and up,
		 and on HPUX 10.  Eventually we can turn this on.  */
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#endif /* __hpux */
#endif
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc */
#endif /* not GNU C */
#endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#ifdef YYSTACK_USE_ALLOCA
#define YYSTACK_ALLOC alloca
#else
#define YYSTACK_ALLOC malloc
#endif

		 /* Note: there must be only one dollar sign in this file.
			It is replaced by the list of actions, each action
			as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
			/* Like YYERROR except do call yyerror.
			   This remains here temporarily to ease the
			   transition to the new meaning of YYERROR, for GCC.
			   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

			   /* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

   /*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
	(effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

	/* Define __yy_memcpy.  Note that the size argument
	   should be passed with type unsigned int, because that is what the non-GCC
	   definitions require.  With GCC, __builtin_memcpy takes an arg
	   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

	   /* This is the most reliable way to avoid incompatibilities
		  in available built-in functions on various systems.  */
static void
__yy_memcpy(to, from, count)
char *to;
char *from;
unsigned int count;
{
	register char *f = from;
	register char *t = to;
	register int i = count;

	while (i-- > 0)
		*t++ = *f++;
}

#else /* __cplusplus */

	   /* This is the most reliable way to avoid incompatibilities
		  in available built-in functions on various systems.  */
static void
__yy_memcpy(char *to, char *from, unsigned int count)
{
	register char *t = to;
	register char *f = from;
	register int i = count;

	while (i-- > 0)
		*t++ = *f++;
}

#endif
#endif

#line 217 "/usr/local/share/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

   /* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
#ifdef YYPARSE_PARAM
int yyparse(void *);
#else
int yyparse(void);
#endif
#endif

int
yyparse(YYPARSE_PARAM_ARG)
YYPARSE_PARAM_DECL
{
	register int yystate;
	register int yyn;
	register short *yyssp;
	register YYSTYPE *yyvsp;
	int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
	int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

	short	yyssa[YYINITDEPTH];	/*  the state stack			*/
	YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

	short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
	YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
	YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
	YYLTYPE *yyls = yylsa;
	YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

	int yystacksize = YYINITDEPTH;
	int yyfree_stacks = 0;

#ifdef YYPURE
	int yychar;
	YYSTYPE yylval;
	int yynerrs;
#ifdef YYLSP_NEEDED
	YYLTYPE yylloc;
#endif
#endif

	YYSTYPE yyval;		/*  the variable used to return		*/
				  /*  semantic values from the action	*/
				  /*  routines				*/

	int yylen;

#if YYDEBUG != 0
	if (yydebug)
		fprintf(stderr, "Starting parse\n");
#endif

	yystate = 0;
	yyerrstatus = 0;
	yynerrs = 0;
	yychar = YYEMPTY;		/* Cause a token to be read.  */

	/* Initialize stack pointers.
	   Waste one element of value and location stack
	   so that they stay on the same level as the state stack.
	   The wasted elements are never initialized.  */

	yyssp = yyss - 1;
	yyvsp = yyvs;
#ifdef YYLSP_NEEDED
	yylsp = yyls;
#endif

	/* Push a new state, which is found in  yystate  .  */
	/* In all cases, when you get here, the value and location stacks
	   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

	*++yyssp = yystate;

	if (yyssp >= yyss + yystacksize - 1)
	{
		/* Give user a chance to reallocate the stack */
		/* Use copies of these so that the &'s don't force the real ones into memory. */
		YYSTYPE *yyvs1 = yyvs;
		short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
		YYLTYPE *yyls1 = yyls;
#endif

		/* Get the current used size of the three stacks, in elements.  */
		int size = yyssp - yyss + 1;

#ifdef yyoverflow
		/* Each stack pointer address is followed by the size of
	   the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
	   /* This used to be a conditional around just the two extra args,
	  but that might be undefined if yyoverflow is a macro.  */
		yyoverflow("parser stack overflow",
			&yyss1, size * sizeof(*yyssp),
			&yyvs1, size * sizeof(*yyvsp),
			&yyls1, size * sizeof(*yylsp),
			&yystacksize);
#else
		yyoverflow("parser stack overflow",
			&yyss1, size * sizeof(*yyssp),
			&yyvs1, size * sizeof(*yyvsp),
			&yystacksize);
#endif

		yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
		yyls = yyls1;
#endif
#else /* no yyoverflow */
		/* Extend the stack our own way.  */
		if (yystacksize >= YYMAXDEPTH)
		{
			std::cout<<"parser stack overflow";
			if (yyfree_stacks)
			{
				free(yyss);
				free(yyvs);
#ifdef YYLSP_NEEDED
				free(yyls);
#endif
			}
			return 2;
		}
		yystacksize *= 2;
		if (yystacksize > YYMAXDEPTH)
			yystacksize = YYMAXDEPTH;
#ifndef YYSTACK_USE_ALLOCA
		yyfree_stacks = 1;
#endif
		yyss = (short *)YYSTACK_ALLOC(yystacksize * sizeof(*yyssp));
		__yy_memcpy((char *)yyss, (char *)yyss1,
			size * (unsigned int) sizeof(*yyssp));
		yyvs = (YYSTYPE *)YYSTACK_ALLOC(yystacksize * sizeof(*yyvsp));
		__yy_memcpy((char *)yyvs, (char *)yyvs1,
			size * (unsigned int) sizeof(*yyvsp));
#ifdef YYLSP_NEEDED
		yyls = (YYLTYPE *)YYSTACK_ALLOC(yystacksize * sizeof(*yylsp));
		__yy_memcpy((char *)yyls, (char *)yyls1,
			size * (unsigned int) sizeof(*yylsp));
#endif
#endif /* no yyoverflow */

		yyssp = yyss + size - 1;
		yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
		yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
		if (yydebug)
			fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

		if (yyssp >= yyss + yystacksize - 1)
			YYABORT;
	}

#if YYDEBUG != 0
	if (yydebug)
		fprintf(stderr, "Entering state %d\n", yystate);
#endif

	goto yybackup;
yybackup:

	/* Do appropriate processing given the current state.  */
	/* Read a lookahead token if we need one and don't already have one.  */
	/* yyresume: */

	  /* First try to decide what to do without reference to lookahead token.  */

	yyn = yypact[yystate];
	if (yyn == YYFLAG)
		goto yydefault;

	/* Not known => get a lookahead token if don't already have one.  */

	/* yychar is either YYEMPTY or YYEOF
	   or a valid token in external form.  */

	if (yychar == YYEMPTY)
	{
#if YYDEBUG != 0
		if (yydebug)
			fprintf(stderr, "Reading a token: ");
#endif
		yychar = YYLEX;
	}

	/* Convert token to internal form (in yychar1) for indexing tables with */

	if (yychar <= 0)		/* This means end of input. */
	{
		yychar1 = 0;
		yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
		if (yydebug)
			fprintf(stderr, "Now at end of input.\n");
#endif
	}
	else
	{
		yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
		if (yydebug)
		{
			fprintf(stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
			/* Give the individual parser a way to print the precise meaning
			   of a token, for further debugging info.  */
#ifdef YYPRINT
			YYPRINT(stderr, yychar, yylval);
#endif
			fprintf(stderr, ")\n");
		}
#endif
	}

	yyn += yychar1;
	if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
		goto yydefault;

	yyn = yytable[yyn];

	/* yyn is what to do for this token type in this state.
	   Negative => reduce, -yyn is rule number.
	   Positive => shift, yyn is new state.
		 New state is final state => don't bother to shift,
		 just return success.
	   0, or most negative number => error.  */

	if (yyn < 0)
	{
		if (yyn == YYFLAG)
			goto yyerrlab;
		yyn = -yyn;
		goto yyreduce;
	}
	else if (yyn == 0)
		goto yyerrlab;

	if (yyn == YYFINAL)
		YYACCEPT;

	/* Shift the lookahead token.  */

#if YYDEBUG != 0
	if (yydebug)
		fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

	/* Discard the token being shifted unless it is eof.  */
	if (yychar != YYEOF)
		yychar = YYEMPTY;

	*++yyvsp = yylval;
#ifdef YYLSP_NEEDED
	*++yylsp = yylloc;
#endif

	/* count tokens shifted since error; after three, turn off error status.  */
	if (yyerrstatus) yyerrstatus--;

	yystate = yyn;
	goto yynewstate;

	/* Do the default action for the current state.  */
yydefault:

	yyn = yydefact[yystate];
	if (yyn == 0)
		goto yyerrlab;

	/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
	yylen = yyr2[yyn];
	if (yylen > 0)
		yyval = yyvsp[1 - yylen]; /* implement default value of the action */

#if YYDEBUG != 0
	if (yydebug)
	{
		int i;

		fprintf(stderr, "Reducing via rule %d (line %d), ",
			yyn, yyrline[yyn]);

		/* Print the symbols being reduced, and their result.  */
		for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
			fprintf(stderr, "%s ", yytname[yyrhs[i]]);
		fprintf(stderr, " -> %s\n", yytname[yyr1[yyn]]);
	}
#endif


	switch (yyn) {

	case 1:
#line 101 "interpreter.y"
	{ YYACCEPT; ;
	break; }
	case 13:
#line 122 "interpreter.y"
	{
		auto exec_file_query = new ExecFileQuery();
		exec_file_query->file_name = yyvsp[0].str;

		query = exec_file_query;
		;
		break; }
	case 14:
#line 131 "interpreter.y"
	{
		auto create_table_query = new CreateTableQuery();
		create_table_query->table_name = yyvsp[-4].str;
		create_table_query->attr_list = yyvsp[-2].attr_list;
		create_table_query->primary_key_name = yyvsp[-1].str;

		query = create_table_query;
		;
		break; }
	case 15:
#line 142 "interpreter.y"
	{
		auto create_index_query = new CreateIndexQuery();
		create_index_query->index_name = yyvsp[-5].str;
		create_index_query->table_name = yyvsp[-3].str;
		create_index_query->attr_name = yyvsp[-1].str;

		query = create_index_query;
		;
		break; }
	case 16:
#line 153 "interpreter.y"
	{
		auto drop_table_query = new DropTableQuery();
		drop_table_query->table_name = yyvsp[0].str;

		query = drop_table_query;
		;
		break; }
	case 17:
#line 163 "interpreter.y"
	{
		auto drop_index_query = new DropIndexQuery();
		drop_index_query->index_name = yyvsp[0].str;

		query = drop_index_query;
		;
		break; }
	case 18:
#line 173 "interpreter.y"
	{
		auto delete_query = new DeleteQuery();
		delete_query->table_name = yyvsp[-1].str;
		delete_query->condition_list = yyvsp[0].condition_list;

		query = delete_query;
		;
		break; }
	case 19:
#line 184 "interpreter.y"
	{
		auto select_query = new SelectQuery();
		select_query->table_name = yyvsp[-1].str;
		select_query->condition_list = yyvsp[0].condition_list;

		query = select_query;
		;
		break; }
	case 20:
#line 195 "interpreter.y"
	{
		auto insert_query = new InsertQuery();
		insert_query->table_name = yyvsp[-4].str;
		insert_query->value_list = yyvsp[-1].value_list;

		query = insert_query;
		;
		break; }
	case 21:
#line 205 "interpreter.y"
	{
		yyval.str = yyvsp[-1].str;
		;
		break; }
	case 22:
#line 210 "interpreter.y"
	{
		yyval.str = "";
		;
		break; }
	case 23:
#line 216 "interpreter.y"
	{
		yyval.condition_list = yyvsp[0].condition_list;
		;
		break; }
	case 24:
#line 221 "interpreter.y"
	{
		yyval.condition_list = std::vector<Condition>();
		;
		break; }
	case 25:
#line 227 "interpreter.y"
	{
		yyval.attr_list = yyvsp[-2].attr_list;
		yyval.attr_list.push_back(yyvsp[0].attr);
		;
		break; }
	case 26:
#line 232 "interpreter.y"
	{
		yyval.attr_list = std::vector<attrValue>();
		yyval.attr_list.push_back(yyvsp[0].attr);
		;
		break; }
	case 27:
#line 240 "interpreter.y"
	{
		yyval.attr = yyvsp[-1].attr;
		yyval.attr.attrName = yyvsp[-2].str;
		/*true or false*/
		yyval.attr.unique = yyvsp[0].b;
		;
		break; }
	case 28:
#line 248 "interpreter.y"
	{ yyval.attr.type = SQLValueType::INT; ;
	break; }
	case 29:
#line 249 "interpreter.y"
	{ yyval.attr.type = SQLValueType::FLOAT; ;
	break; }
	case 30:
#line 250 "interpreter.y"
	{ yyval.attr.type = SQLValueType::STRING; yyval.attr.charSize = yyvsp[-1].i; ;
	break; }
	case 31:
#line 253 "interpreter.y"
	{ yyval.b = true; ;
	break; }
	case 32:
#line 254 "interpreter.y"
	{ yyval.b = false; ;
	break; }
	case 33:
#line 258 "interpreter.y"
	{
		yyvsp[-2].condition_list.push_back(yyvsp[0].cond);
		yyval.condition_list = yyvsp[-2].condition_list;
		;
		break; }
	case 34:
#line 264 "interpreter.y"
	{
		yyval.condition_list = std::vector<Condition>();
		yyval.condition_list.push_back(yyvsp[0].cond);
		;
		break; }
	case 35:
#line 271 "interpreter.y"
	{
		yyval.cond.name = yyvsp[-2].str;
		yyval.cond.op = yyvsp[-1].op;
		yyval.cond.val = yyvsp[0].val;
		;
		break; }
	case 36:
#line 279 "interpreter.y"
	{
		yyvsp[-2].value_list.push_back(yyvsp[0].val);
		yyval.value_list = yyvsp[-2].value_list;
		;
		break; }
	case 37:
#line 284 "interpreter.y"
	{
		yyval.value_list = std::vector<SQLValue>();
		yyval.value_list.push_back(yyvsp[0].val);
		;
		break; }
	case 38:
#line 291 "interpreter.y"
	{ yyval.val.type = SQLValueType::INT; yyval.val.i = yyvsp[0].i; ;
	break; }
	case 39:
#line 292 "interpreter.y"
	{ yyval.val.type = SQLValueType::FLOAT; yyval.val.r = yyvsp[0].r; ;
	break; }
	case 40:
#line 293 "interpreter.y"
	{ yyval.val.type = SQLValueType::STRING; yyval.val.str = yyvsp[0].str; ;
	break; }
	case 41:
#line 297 "interpreter.y"
	{   yyval.op = Operator::LESS_THAN; ;
	break; }
	case 42:
#line 298 "interpreter.y"
	{ yyval.op = Operator::LESS_EQUAL; ;
	break; }
	case 43:
#line 299 "interpreter.y"
	{ yyval.op = Operator::GREATER_THAN; ;
	break; }
	case 44:
#line 300 "interpreter.y"
	{ yyval.op = Operator::GREAT_EQUAL; ;
	break; }
	case 45:
#line 301 "interpreter.y"
	{ yyval.op = Operator::EQUAL; ;
	break; }
	case 46:
#line 302 "interpreter.y"
	{ yyval.op = Operator::NOT_EQUAL; ;
	break; }
	case 51:
#line 316 "interpreter.y"
	{ isExit = true; ;
	break; }
	}
	/* the action file gets copied in in place of this dollarsign */
#line 543 "/usr/local/share/bison.simple"

	yyvsp -= yylen;
	yyssp -= yylen;
#ifdef YYLSP_NEEDED
	yylsp -= yylen;
#endif

#if YYDEBUG != 0
	if (yydebug)
	{
		short *ssp1 = yyss - 1;
		fprintf(stderr, "state stack now");
		while (ssp1 != yyssp)
			fprintf(stderr, " %d", *++ssp1);
		fprintf(stderr, "\n");
	}
#endif

	*++yyvsp = yyval;

#ifdef YYLSP_NEEDED
	yylsp++;
	if (yylen == 0)
	{
		yylsp->first_line = yylloc.first_line;
		yylsp->first_column = yylloc.first_column;
		yylsp->last_line = (yylsp - 1)->last_line;
		yylsp->last_column = (yylsp - 1)->last_column;
		yylsp->text = 0;
	}
	else
	{
		yylsp->last_line = (yylsp + yylen - 1)->last_line;
		yylsp->last_column = (yylsp + yylen - 1)->last_column;
	}
#endif

	/* Now "shift" the result of the reduction.
	   Determine what state that goes to,
	   based on the state we popped back to
	   and the rule number reduced by.  */

	yyn = yyr1[yyn];

	yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
	if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
		yystate = yytable[yystate];
	else
		yystate = yydefgoto[yyn - YYNTBASE];

	goto yynewstate;

yyerrlab:   /* here on detecting error */

	if (!yyerrstatus)
		/* If not already recovering from an error, report this error.  */
	{
		++yynerrs;

#ifdef YYERROR_VERBOSE
		yyn = yypact[yystate];

		if (yyn > YYFLAG && yyn < YYLAST)
		{
			int size = 0;
			char *msg;
			int x, count;

			count = 0;
			/* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
			for (x = (yyn < 0 ? -yyn : 0);
				x < (sizeof(yytname) / sizeof(char *)); x++)
				if (yycheck[x + yyn] == x)
					size += strlen(yytname[x]) + 15, count++;
			msg = (char *)malloc(size + 15);
			if (msg != 0)
			{
				strcpy(msg, "parse error");

				if (count < 5)
				{
					count = 0;
					for (x = (yyn < 0 ? -yyn : 0);
						x < (sizeof(yytname) / sizeof(char *)); x++)
						if (yycheck[x + yyn] == x)
						{
							strcat(msg, count == 0 ? ", expecting `" : " or `");
							strcat(msg, yytname[x]);
							strcat(msg, "'");
							count++;
						}
				}
				yyerror(msg);
				free(msg);
			}
			else
				yyerror("parse error; also virtual memory exceeded");
		}
		else
#endif /* YYERROR_VERBOSE */
		std::cout<<"Syntax error! Please check your command.";
	}

	goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

	if (yyerrstatus == 3)
	{
		/* if just tried and failed to reuse lookahead token after an error, discard it.  */

		/* return failure if at end of input */
		if (yychar == YYEOF)
			YYABORT;

#if YYDEBUG != 0
		if (yydebug)
			fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

		yychar = YYEMPTY;
	}

	/* Else will try to reuse lookahead token
	   after shifting the error token.  */

	yyerrstatus = 3;		/* Each real token shifted decrements this */

	goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
	 should shift them.  */
	yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
	if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

	if (yyssp == yyss) YYABORT;
	yyvsp--;
	yystate = *--yyssp;
#ifdef YYLSP_NEEDED
	yylsp--;
#endif

#if YYDEBUG != 0
	if (yydebug)
	{
		short *ssp1 = yyss - 1;
		fprintf(stderr, "Error: state stack now");
		while (ssp1 != yyssp)
			fprintf(stderr, " %d", *++ssp1);
		fprintf(stderr, "\n");
	}
#endif

yyerrhandle:

	yyn = yypact[yystate];
	if (yyn == YYFLAG)
		goto yyerrdefault;

	yyn += YYTERROR;
	if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
		goto yyerrdefault;

	yyn = yytable[yyn];
	if (yyn < 0)
	{
		if (yyn == YYFLAG)
			goto yyerrpop;
		yyn = -yyn;
		goto yyreduce;
	}
	else if (yyn == 0)
		goto yyerrpop;

	if (yyn == YYFINAL)
		YYACCEPT;

#if YYDEBUG != 0
	if (yydebug)
		fprintf(stderr, "Shifting error token, ");
#endif

	*++yyvsp = yylval;
#ifdef YYLSP_NEEDED
	*++yylsp = yylloc;
#endif

	yystate = yyn;
	goto yynewstate;

yyacceptlab:
	/* YYACCEPT comes here.  */
	if (yyfree_stacks)
	{
		free(yyss);
		free(yyvs);
#ifdef YYLSP_NEEDED
		free(yyls);
#endif
	}
	return 0;

yyabortlab:
	/* YYABORT comes here.  */
	if (yyfree_stacks)
	{
		free(yyss);
		free(yyvs);
#ifdef YYLSP_NEEDED
		free(yyls);
#endif
	}
	return 1;
}
#line 323 "interpreter.y"

void yyerror(char *s, ...)
{
	std::cerr << "Error: ";
	std::cerr << s << std::endl;
}

