@SET CC="D:\Portable\tcc-win32\tcc.exe"
@SET CC64="D:\Portable\tcc-win64\tcc.exe"
@ECHO *** making release 32-bit executable ***
@%CC% -Wall -o chess32.exe chess.c >>compile.log
@ECHO *** making release 64-bit executable ***
@%CC64% -Wall -o chess64.exe chess.c >>compl64.log
DIR *.log *.exe /B
@SET CC=
@SET CC64=
@PAUSE