@SET CC="D:\Portable\tcc-win32\tcc.exe"
@SET CC64="D:\Portable\tcc-win64\tcc.exe"
@ECHO *** making debug 32-bit executable ***
@%CC% -D_DTEST -Wall -o chess32d.exe chess.c >>compile.log
@ECHO *** making debug 64-bit executable ***
@%CC64% -D_DTEST -Wall -o chess64d.exe chess.c >>compl64.log
@SET CC=
@SET CC64=
@DIR *.log *d.exe
@PAUSE