OBJS=\
	main.o\
	ReadFile.o\
	StrUtils.o

CFLGS=-c -mconsole -O3 -std=gnu++20

LIBS=..\..\..\png\lib\libmypng.a -lpng

INCDIR=-I ..\..\..\png\include

day16.exe : $(OBJS) $(INCS)
	g++ -o day16.exe -mconsole $(OBJS) $(LIBS)

main.o : main.cpp $(INCS)
	g++ $(CFLGS) $(INCDIR) main.cpp

ReadFile.o : ReadFile.cpp $(INCS)
	g++ $(CFLGS) ReadFile.cpp

StrUtils.o : StrUtils.cpp $(INCS)
	g++ $(CFLGS) StrUtils.cpp

clean :
	rm *.o
