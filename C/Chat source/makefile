#
# network build make file
# 2019.06.20. thu
#

CC = gcc
REMOVE = rm -rf

all: server client
	@clear
	@ls -al

server: server.c hrd.h
	@$(CC) -o server server.c
	@echo 서버 파일이 생성되었습니다.

client: client.c hrd.h
	@$(CC) -o client client.c
	@echo 클라이언트 파일이 생성되었습니다.

clean:
	@echo off
	$(REMOVE) server
	$(REMOVE) client
	clear
	@ls -al



