syntax on
set hls is
set number
set ruler
set cindent
set tabstop=4
set shiftwidth=4
set softtabstop=4
set autoindent
set smarttab
set smartindent
set cursorline
set nobackup
set noswapfile
set mouse=a
set backspace=indent,eol,start
"--------------------------------------"
func CodeFormat()
	let lineNum = line(".")
	if &filetype == 'c'
		exec "%! astyle -A3Lfpjk3NS\<CR>"
	elseif &filetype == 'cpp'
		exec "%! astyle -A3Lfpjk3NS\<CR>"
	elseif &filetype == 'java'
		exec "%! astyle -A2Lfpjk3NS\<CR>"
	else 
		echo "Can't support".&filetype."file type."
	endif
	exec lineNum
endfunc
"--------------------------------------"
map <S-F> <Esc>:call CodeFormat()<CR>
"--------------------------------------"
func CodeRun()
	exec "w"
	if &filetype=="c"
		exec "!clear&&tcc -run %"
	elseif &filetype=="cpp"
		exec "!clear&&g++ -o %< && ./%<"
	elseif &filetype=="java"
		exec "!clear&&javac % && java %<"
	elseif &filetype=="python"
		exec "!clear&&python %"
	endif
endfunc
"--------------------------------------"
map <F5> <ESC> :call CodeRun()<CR>
imap <F5> <ESC> :call CodeRun()<CR>
vmap <F5> <ESC> :call CodeRun()<CR>
