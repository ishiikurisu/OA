oapath = -I"../src"
options = -lm -O2 -ansi -pipe -Wall

pack.exe: lempelziv.h pack.c
	gcc pack.c -o pack.exe $(oapath) $(options)
unpack.exe: lempelziv.h unpack.c
	gcc unpack.c -o unpack.exe $(oapath) $(options)
