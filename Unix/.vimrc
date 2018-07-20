" Don't try to be vi compatible
set nocompatible

" Turn on syntax highlighting
syntax on
set background=dark
filetype on

" Show line numbers
set number
" Auto-Indent still use gg=G
set smartindent
set shiftwidth=2
set autoindent
set shiftround
"autocmd BufRead,BufWritePre *.sh normal gg=G

" Show file stats
set ruler


" Encoding
set encoding=utf-8

" Last line
set showmode
set showcmd


" Visualize tabs and newlines
set listchars=tab:t\ ,eol:¬
" Uncomment this to enable by default:
" set list " To enable by default


" Reads the template file replacing the tags by the actual
" information and insert the result at the beginning of the buffer. At
" the end, creates two blank lines at the end of the file and
" position the cursor at the first one.
function! s:insert_description()
    let template = $HOME . "/.vim/template/cpp.template"
    let file_name = expand("%:t") " Get file name without path
    let date = strftime("%D") " Get Big American time
    let i = 0
    for line in readfile(template)
        let line = substitute(line, "<file_name>", file_name, "ge")
        let line = substitute(line, "<date>", date, "ge")
        call append(i, line)
        let i += 1
    endfor
    execute "normal! Go\<Esc>k"
endfunction

" Same caveman code to template sh files.
function! s:insert_shabang()
    let template = $HOME . "/.vim/template/sh.template"
    let file_name = expand("%:t") " Get file name without path
    let date = strftime("%D") " Get Big American time
    let i = 0
    for line in readfile(template)
        let line = substitute(line, "<file_name>", file_name, "ge")
        let line = substitute(line, "<date>", date, "ge")
        call append(i, line)
        let i += 1
    endfor
    execute "normal! Go\<Esc>k"
endfunction

autocmd BufNewFile *.{c++,cpp,cc,c,h,hpp} call <SID>insert_description()
autocmd BufNewFile *.sh call <SID>insert_shabang()

" END VIMRC <3 JP
