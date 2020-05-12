#
# Bulid Make File
# 2019.06.21. Fri
#

####Scalar####
CC = gcc
RM = rm -rf
LIB = -lpcap
EXE = main
LY1 = layer1
LY2 = layer2
LY3 = layer3
HEXA = hexaview

all: start build end run 
	
build:
	@$(CC) -c $(EXE).c
	@$(CC) -c $(HEXA).c
	@$(CC) -c $(LY1).c
	@$(CC) -c $(LY2).c
	@$(CC) -c $(LY3).c
	@$(CC) -o $(EXE) $(EXE).o $(HEXA).o $(LY1).o $(LY2).o $(LY3).o $(LIB)
	@echo Compile complete

rebuild: clean all

start:
	@echo --------------COMPILE START--------------
	

end:
	@echo --------------COMPILE E N D--------------


clean:
	@$(RM) *.o $(EXE)

run:
	sudo ./$(EXE)

backup:clean
	rm -rf packet.tar.gz
	tar -cf packet.tar *
	gzip packet.tar

restore:
	tar -xzvf packet.tar.gz
