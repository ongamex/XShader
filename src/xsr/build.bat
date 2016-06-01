cls
@rem --noline --c++ 

@rem C:\win_flex_bison\win_flex.exe --outfile=lang.lex.yy.cpp lang.l
@rem C:\win_flex_bison\win_bison.exe lang.y --defines=lang.tab.h --output=lang.tab.cpp


C:\win_flex_bison\win_flex.exe --outfile=lang.lex.yy.cpp lang.l 
C:\win_flex_bison\win_bison.exe lang.y --defines=lang.tab.h --output=lang.tab.cpp
