%{
	#include "access.h"
	#include "logo.tab.h"
%}

%%
"FORWARD"	{return FORWARD;}
"RIGHT"		{return RIGHT;}
"LEFT"		{return LEFT;}
"REPEAT"	{return REPEAT;}
"["			{return '[';}
"]"			{return ']';}
[0-9]+		{yylval.number = atoi(yytext); return NUMBER;}
[ \t]		;
\n			;
.			{return yy_accept;}
%%