#
# deps.mk - dependencies for the current makefile
# 
# Automatically Generated. DO NOT EDIT
# 
# Created by makedeps.sh on Wed Mar  5 16:28:12 GMTST 2008


hal_console.h : console_queue.h target_types.h target_console.h

hal_dtv.h : ehs_types.h target_dtv.h callback_queue.h

hal_file.h : target_file.h ehs_types.h

hal_process.h : target_process.h

hal_string.h : ehs_types.h target_string.h

hal_time.h : target_types.h target_time.h

hal_viewport.h : graphics.h target_viewport.h

target.h : target_config.h target_types.h target_specific.h hal_time.h hal_file.h hal_console.h hal_process.h ehs_types.h graphics.h