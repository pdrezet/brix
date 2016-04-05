#
# Makefile fragment to build the common hardware abstraction layer files for EHS.

# Called by ../../Makefile
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

include $(EHS_COMMON_HAL_PATH)/include/deps.mk

include $(EHS_COMMON_HAL_PATH)/graphics/graphics.mk
include $(EHS_COMMON_HAL_PATH)/string/string.mk
include $(EHS_COMMON_HAL_PATH)/tcp/tcp.mk

INC_DIRS += $(EHS_COMMON_HAL_PATH)/include


