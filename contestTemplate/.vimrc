sy on
se nu ru rnu cin cul sc so=4 ls=2 bs=2 ts=2 sw=2

map <F7> :w<CR>:!g++ "%" -o run -DOWO -fsanitize=undefined<CR>
map <F8> :w<CR>:!cat in.in && echo ------------ && ./run < in.in<CR>
