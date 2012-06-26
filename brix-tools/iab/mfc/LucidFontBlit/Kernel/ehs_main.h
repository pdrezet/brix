/** @file ehs_main.h
 * In this file, all of the hardware abstraction layer functions provided for EHS are given.
 * 
 * @author: Dr Andrew Coombes
 * @version: $Revision: 905 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#ifndef EHS_MAIN_H
#define EHS_MAIN_H

#include "ehs_types.h"

/**
 * EHS Entry point. Initialise EHS, then start running EHS & handling console
 * input.
 */
EHS_GLOBAL void EhsMain(void);

/**
 * Perform one step of main EHS loop
 */
EHS_GLOBAL void EhsMainLoop(void);


#endif /* EHS_MAIN_H */
