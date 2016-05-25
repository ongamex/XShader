cls
@rem --noline --c++ 

C:\win_flex_bison\win_flex.exe --wincompat --outfile=lang.lex.yy.cpp -noline lang.l 
C:\win_flex_bison\win_bison.exe lang.y --defines=lang.tab.h --output=lang.tab.cpp
