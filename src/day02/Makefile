OBJS=\
	main.o\
	ReadFile.o\
	StrUtils.o

CFLGS=-c -mconsole -O2

LIBS=

day2.exe : $(OBJS) $(INCS)
	g++ -o day2.exe -mconsole $(OBJS) $(LIBS)

main.o : main.cpp $(INCS)
	g++ $(CFLGS) main.cpp

ReadFile.o : ReadFile.cpp $(INCS)
	g++ $(CFLGS) ReadFile.cpp

StrUtils.o : StrUtils.cpp $(INCS)
	g++ $(CFLGS) StrUtils.cpp

clean :
	rm *.o
