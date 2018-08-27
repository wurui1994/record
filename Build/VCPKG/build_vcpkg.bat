for /f %%f in ('dir /b ports') do (
	@vcpkg install %%~nf --x-use-aria2
	IF ERRORLEVEL 0 (
		@echo %%~nf build success.
		@echo %%~nf >> success.txt
	) else (
		@echo %%~nf build error.
		@echo %%~nf >> error.txt
	)
)