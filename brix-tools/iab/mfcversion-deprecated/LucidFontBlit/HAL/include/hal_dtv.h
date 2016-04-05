/** @file hal_dtv.h
 * In this file, all of the hardware abstraction layer functions relating to digital TV functions are given.
 *
 * @author: Dr Andrew Coombes
 * @version: $Revision: 1120 $
 * @date: $Date: 2006-11-06 16:22:28 +0000 (Mon, 06 Nov 2006) $
 * 
 * Copyright (c) Ncapsa Ltd, 2006. All rights reserved.
 */

#ifndef EHS_HAL_DTV_H
#define EHS_HAL_DTV_H

/*****************************************************************************/
/* Included files */
#include "ehs_types.h"
#include "target_dtv.h"
#include "callback_queue.h"

/*****************************************************************************/
/* Define macros  */


/*****************************************************************************/
/* Define types */


/**
 * Indicates the properties contained within the target viewport type
 */
typedef struct EhsTgtDtvPlaybackStruct EhsTgtDtvPlaybackClass;

/**
 * Contains the properties held about the video playback filesystem
 */
typedef struct EhsTgtDtvFilesStruct EhsTgtDtvFilesClass;

typedef enum { EHS_TGT_DTV_FILEFLAG_NONE = 0,
	EHS_TGT_DTV_FILEFLAG_FILE = 1,
	EHS_TGT_DTV_FILEFLAG_FOLDER = 2} EhsTgtDtvFileFlagEnum;



/*****************************************************************************/
/* Declare global variables */

/**
 * Currently we only allow for one, global playback structure
 */
EHS_GLOBAL EhsTgtDtvPlaybackClass* EhsTgtDtvPlaybackRef;

/**
 * Currently we only allow for one, global file context
 */
EHS_GLOBAL EhsTgtDtvFilesClass* EhsTgtDtvFilesRef;

/**
 * Callback structure to indicate when playback finishes
 */
EHS_GLOBAL EhsCallbackQueueType EhsTgtDtvPlayEndCallback;
/*****************************************************************************/
/* Declare function prototypes  */


#ifndef EhsTgtDtvPlayback_init
/**
 * Initialise the DTV playback structure
 * @param[in] pPlayback Playback structure
 * @return true if successful
 */
EHS_GLOBAL ehs_bool EhsTgtDtvPlayback_init(EhsTgtDtvPlaybackClass* pPlayback);
#endif

#ifndef EhsTgtDtvPlayback_loadFile
/**
 * Load the file to start playing. The specified file must exist in the current folder.
 * @param[in] pPlayback Playback structure
 * @param[in] pFiles Specifies folder where file is to be loaded from
 * @param[in] szFilename Name of file to play (including extension)
 * @return true if successful
 */
EHS_GLOBAL ehs_bool EhsTgtDtvPlayback_loadFile(EhsTgtDtvPlaybackClass* pPlayback, EhsTgtDtvFilesClass* pFiles, const ehs_char* szFilename);
#endif

#ifndef EhsTgtDtvPlayback_setPos
/**
 * Set the playback position for the currently loaded file.
 * @param[in] pPlayback playback structure
 * @param[in] nPos index into the file
 * @return true if the index has been set successfully
 */
EHS_GLOBAL ehs_bool EhsTgtDtvPlayback_setPos(EhsTgtDtvPlaybackClass* pPlayback, ehs_uint32 nPos);
#endif

#ifndef EhsTgtDtvPlayback_setSpeed
/**
 * Set the playback speed for the currently loaded file.
 * @param[in] pPlayback playback structure
 * @param[in] nSpeed The current speed of playback (as a percentage of normal speed). 0 pause the file
 * 100 is playing at normal speed, negative values indicate playing backwards
 * @return true if the speed has been set successfully
 */
EHS_GLOBAL ehs_bool EhsTgtDtvPlayback_setSpeed(EhsTgtDtvPlaybackClass* pPlayback, ehs_sint32 nSpeed);
#endif

#ifndef EhsTgtDtvPlayback_getPos
/**
 * Get the playback position for the currently loaded file.
 * @param[in] pPlayback playback structure
 * @param[out] pnPos The current position of playback. 0 if no file is loaded, or playback hasn't started
 * @return true if the index has been read successfully
 */
EHS_GLOBAL ehs_bool EhsTgtDtvPlayback_getPos(EhsTgtDtvPlaybackClass* pPlayback, ehs_uint32* pnPos);
#endif

#ifndef EhsTgtDtvPlayback_getSpeed
/**
 * Get the playback speed for the currently loaded file.
 * @param[in] pPlayback playback structure
 * @param[out] pnSpeed The current speed of playback (as a percentage of normal speed). 0 means that the file isn't playing.
 * 100 is playing at normal speed, negative values indicate playing backwards
 * @return true if the index has been read successfully
 */
EHS_GLOBAL ehs_bool EhsTgtDtvPlayback_getSpeed(EhsTgtDtvPlaybackClass* pPlayback, ehs_sint32* pnSpeed);
#endif

#ifndef EhsTgtDtvPlayback_play
/**
 * Start video playback at the specified speed/change playback to the specified speed.
 * This function is called with speed 0 to pause the playback.
 * @param[in] pPlayback playback structure
 * @param[in] nSpeed The speed to play the file.
 * @return true if the video playback has started running at that speed
 */
EHS_GLOBAL ehs_bool EhsTgtDtvPlayback_play(EhsTgtDtvPlaybackClass* pPlayback, ehs_sint32 nSpeed);
#endif

#ifndef EhsTgtDtvPlayback_stop
/**
 * Terminate video playback. This causes the screen to clear
 * @param[in] pPlayback The item to stop
 * @return true if playback structure was valid, and video was stopped
 */
EHS_GLOBAL ehs_bool EhsTgtDtvPlayback_stop(EhsTgtDtvPlaybackClass* pPlayback);
#endif

#ifndef EhsTgtDtvFiles_init
/**
 * Set up the files strucutre
 * @param[in] pFiles Context for the file operation
 */
EHS_GLOBAL void EhsTgtDtvFiles_init(EhsTgtDtvFilesClass* pFiles);
#endif

#ifndef EhsTgtDtvFiles_getDir
/**
 * Return the directory we are curently looking at.
 * @param[in] pFiles Context for the file operation
 * @param[out] szDir Text containing the current path. Caller must pass in an array of length EHS_TGT_DTV_FILES_MAX_PATH
 * @return true if successful
 */
EHS_GLOBAL ehs_bool EhsTgtDtvFiles_getDir(EhsTgtDtvFilesClass* pFiles, ehs_char* szDir);
#endif

#ifndef EhsTgtDtvFiles_setDir
/**
 * Change the directory we are currently looking at
 * @param[in] pFiles Context for the file operation
 * @param[in] szDir Directory to change to. "/" represents the root of the DTV file system (which might
 * not be the root of the underlying OS file system). Absolute and relative paths are supported.
 * @return true if successful.
 */
EHS_GLOBAL ehs_bool EhsTgtDtvFiles_setDir(EhsTgtDtvFilesClass* pFiles, const ehs_char* szDir);
#endif

#ifndef EhsTgtDtvFiles_listFirst
/**
 * Start retrieving files from the current directory
 * @param[in] pFiles Context for the file operation
 * @param[in] eFlags Indicates which types of things to report files, directories or both
 * @param[out] szName Text containing the name of the retrieved object. Caller must pass in an array
 * of length EHS_TGT_DTV_FILES_MAX_FILENAME
 * @return true if a file name has been obtained
 */
EHS_GLOBAL ehs_bool EhsTgtDtvFiles_listFirst(EhsTgtDtvFilesClass* pFiles, EhsTgtDtvFileFlagEnum eFlags, ehs_char* szName);
#endif

#ifndef EhsTgtDtvFiles_listNext
/**
 * Continue retrieving files from the current directory. Keep calling this function until
 * it returns false.
 * @param[in] pFiles Context for the file operation
 * @param[out] szName Text containing the name of the retrieved object. Caller must pass in an array
 * of length EHS_TGT_DTV_FILES_MAX_FILENAME
 * @return true if a file name has been obtained
 */
EHS_GLOBAL ehs_bool EhsTgtDtvFiles_listNext(EhsTgtDtvFilesClass* pFiles, ehs_char* szName);
#endif

#endif /* EHS_HAL_DTV_H */
