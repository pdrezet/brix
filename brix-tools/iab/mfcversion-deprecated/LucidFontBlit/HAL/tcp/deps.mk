#
# deps.mk - dependencies for the current makefile
# 
# Automatically Generated. DO NOT EDIT
# 
# Created by makedeps.sh on Wed Mar  5 16:28:15 GMTST 2008


console_server.h : target_tcp.h

console_server.$(OBJ) : target_tcp.h console_server.h globals.h hal_time.h hal_process.h hal_console.h