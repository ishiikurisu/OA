copy listas/lista1.txt lists/lista1.txt
copy listas/lista2.txt lists/lista2.txt
mingw32-make main
more input.txt | main.exe
del main.exe
