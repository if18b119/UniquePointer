uniquepointer.exe: Program.o
		g++ -std=c++14 -static Program.o -o uniquepointer.exe
		
Program.o: U2_SmartPointer.cpp
				g++ -std=c++14 -c U2_SmartPointer.cpp -o Program.o
clean:
				rm -f program.o uniquepointer.exe