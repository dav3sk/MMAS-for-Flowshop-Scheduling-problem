
@SETLOCAL

@SET ACO="ACO"
@SET N_FORMIGAS=20
@SET TAXA_EVAPORACAO=0.8
@SET GERACOES=5000
@SET PROB_GLOBAL=0.1
@SET ARQUIVO="ta001.txt"

@SET MSG= ========================== EXECUCAO #
@echo off
@FOR /l %%i in (1, 1, 50) DO (
	echo .
	echo %MSG%%%i ==========================
	%ACO% %N_FORMIGAS% %TAXA_EVAPORACAO% %GERACOES% %PROB_GLOBAL% %ARQUIVO%
	echo .
)

pause
@EXIT /B %ERRORLEVEL%