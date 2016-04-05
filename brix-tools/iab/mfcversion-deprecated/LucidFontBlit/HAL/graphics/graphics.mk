#
# Makefile fragment to build the graphics kernel files for EHS.

# Called by ../kernel.mk
#

# @author: Dr Andrew Coombes
# @version: $Revision: 43 $
# @date: $Date: 2006-10-30 05:05:44 +0000 (Mon, 30 Oct 2006) $
# 
# Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
#
#
# Predefined variables

#  OBJ - File extension for object files

#  NOREV - Defined if no revision number checking is to be performed
# Expected variables

#  OBJECTS - list of object files added by this makefile
#  VPATH - where to look for source code

include $(EHS_COMMON_HAL_PATH)/graphics/png/png.mk

include $(EHS_COMMON_HAL_PATH)/graphics/deps.mk

OBJECTS+= graphics.$(OBJ) widget.$(OBJ) widget_image.$(OBJ) widget_image_png.$(OBJ) widget_textbox.$(OBJ) widget_patch.$(OBJ)
OBJECTS+=widget_image_gif.$(OBJ)  

VPATH+=: $(EHS_COMMON_HAL_PATH)/graphics $(EHS_COMMON_HAL_PATH)/graphics/png

INC_DIRS += $(EHS_COMMON_HAL_PATH)/graphics

