copy listas\lista1.txt data\lista1.txt
copy listas\lista2.txt data\lista2.txt
del *.ind
del *.sec
del lista12.txt
mingw32-make main
more input.txt | main.exe
del main.exe
