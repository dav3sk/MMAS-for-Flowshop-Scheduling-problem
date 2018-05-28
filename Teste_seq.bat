@SETLOCAL

@SET ACO="ACO"
@SET N_FORMIGAS=5
@SET TAXA_EVAPORACAO=0.75
@SET GERACOES=10000
@SET ARQUIVO="ta001.txt"

@SET MSG= ========================== EXECUCAO #
@echo off
@FOR /l %%i in (1, 1, 30) DO (
	echo .
	echo %MSG%%%i ==========================
	%ACO% %N_FORMIGAS% %TAXA_EVAPORACAO% %GERACOES% %ARQUIVO%
	echo .
)

@EXIT /B %ERRORLEVEL%
pause