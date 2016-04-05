#
# deps.mk - dependencies for the current makefile
# 
# Automatically Generated. DO NOT EDIT
# 
# Created by makedeps.sh on Wed Mar  5 16:28:06 GMTST 2008


font.h : ehs_types.h target_config.h globals.h

graphics.h : ehs_types.h

widget.h : hal_viewport.h target_config.h graphics.h widget_textbox.h widget_image.h widget_patch.h ehs_fb_types.h

widget_image.h : ehs_types.h globals.h graphics.h widget_image_gif.h widget_image_png.h

widget_image_png.h : hal_viewport.h

widget_patch.h : ehs_types.h globals.h graphics.h

widget_textbox.h : ehs_types.h globals.h graphics.h

font.$(OBJ) : font.h hal_file.h hal_string.h messages.h mem.h

graphics.$(OBJ) : graphics.h

widget.$(OBJ) : widget.h messages.h utils.h hal_string.h

widget_image.$(OBJ) : widget.h messages.h hal_string.h

widget_image_gif.$(OBJ) : ehs_types.h widget.h mem.h messages.h target.h

widget_image_png.$(OBJ) : ehs_types.h widget.h target.h png/png.h mem.h graphics.h messages.h

widget_patch.$(OBJ) : widget.h messages.h hal_string.h

widget_textbox.$(OBJ) : widget.h messages.h hal_string.h