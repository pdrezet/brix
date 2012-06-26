/** @file target_dtv.c
 * Definitions for target-specific dtv-related functions. 
 *
 * @author: Andrew Coombes
 * @version: $Revision: 1105 $
 * @date: $Date$
 * 
 * Copyright (c) Ncapsa Ltd, 2007. All rights reserved.
 */


/**
 * @page Verification Verification report
 * @section target_timer
 * @anchor target_timer
 * @subsection misra MISRA compliance:
 * test.c demonstrated MISRA compliant on 
 * Last modified on $Date:$
 *
 * This file contained no derogations to the MISRA standard.
 */


/**
 * Provides access to the target-specific declarations of header files
 */
#define EHS_TARGET_CODE

/*****************************************************************************/
/* Included files */
#include "hal_dtv.h"
#include "hal_string.h"
#include "messages.h"

#include <io.h>
#include <windows.h>
#include <tchar.h>

/*****************************************************************************/
/* Declare macros and local typedefs used by this file */

/**
 * Specifies where the root of the playback media folder can be found
 * NOTE: no trailing /
 */
#define EHS_TGT_DTV_FILES_ROOT "media"

/**
 * Path separator for this target
 */
#define EHS_TGT_DTV_FILES_SEPARATOR '\\'

/**
 * Check for any errors and report them if appropriate
 */
#define EHS_TGT_DTV_REPORT_ERRORS(err,func) if ((err) != ST_NO_ERROR) { EhsError(EHS_MSG_TGT_STAPI(func,GetErrorText(err))); } else {printf("-\t%s ok\n",func);}

/**
 * Indicates that the search for files isn't currently taking place
 */
#define EHS_TGT_DTV_FILES_SEARCH_INVALID -1

/**
 * Indicates the state that the playback is currently in
 */
typedef enum {EHS_TGT_DTV_STATE_NOT_LOADED,
	EHS_TGT_DTV_STATE_LOADED,
	EHS_TGT_DTV_STATE_PLAYING
	} EhsTgtDtvStateEnum;

/**
 * Indicates the properties contained within the target viewport type
 */
struct EhsTgtDtvPlaybackStruct
{
	EhsTgtDtvStateEnum xPlaybackState;		/**< What state is the playback in? */
	ehs_sint32 nPlaySpeed;					/**< What speed are we playing at the current time? */
};



/*****************************************************************************/
/* Declare prototypes of local functions */
/*****************************************************************************/
/* Variables defined with file-scope */

EHS_LOCAL EhsTgtDtvPlaybackClass EhsTgtDtvPlayback;
EHS_LOCAL EhsTgtDtvFilesClass EhsTgtDtvFiles;

/*****************************************************************************/
/* Variables defined with global-scope */

/**
 * Main playback structure
 * @todo Handle initialization in a funciton */
EhsTgtDtvPlaybackClass* EhsTgtDtvPlaybackRef = &EhsTgtDtvPlayback;

EhsTgtDtvFilesClass* EhsTgtDtvFilesRef = &EhsTgtDtvFiles;

/**
 * Callback structure to indicate when playback finishes
 * @todo initialise this correctly
 */
EhsCallbackQueueType EhsTgtDtvPlayEndCallback;

/*****************************************************************************/
/* Function definitions */

EHS_GLOBAL ehs_bool EhsTgtMainSetWorkingDirectory(const ehs_char* szChildDir);

/**
 * Initialise the DTV playback structure
 * @param[in] pPlayback Playback structure
 * @return true if successful
 */
ehs_bool EhsTgtDtvPlayback_init(EhsTgtDtvPlaybackClass* pPlayback)
{
	pPlayback->xPlaybackState = EHS_TGT_DTV_STATE_NOT_LOADED;
	pPlayback->nPlaySpeed = 0;
	return EHS_TRUE;
}

/**
 * Load the file to start playing. The specified file must exist in the current folder.
 * @param[in] pPlayback Playback structure
 * @param[in] pFiles Specifies folder where file is to be loaded from
 * @param[in] szFilename Name of file to play (including extension)
 * @return true if successful
 */
ehs_bool EhsTgtDtvPlayback_loadFile(EhsTgtDtvPlaybackClass* pPlayback, EhsTgtDtvFilesClass* pFiles, const ehs_char* szFilename)
{
//	EhsError(EHS_MSG_ERROR_NOT_YET_IMPLEMENTED("EhsTgtDtvPlayback_loadFile"));
	return EHS_FALSE;
}

/**
 * Set the playback position for the currently loaded file.
 * @param[in] pPlayback playback structure
 * @param[in] nPos index into the file
 * @return true if the index has been set successfully
 */
ehs_bool EhsTgtDtvPlayback_setPos(EhsTgtDtvPlaybackClass* pPlayback, ehs_uint32 nPos)
{
//	EhsError(EHS_MSG_ERROR_NOT_YET_IMPLEMENTED("EhsTgtDtvPlayback_setPos"));
	return EHS_FALSE;
}

/**
 * Get the playback position for the currently loaded file.
 * @param[in] pPlayback playback structure
 * @param[out] pnPos The current position of playback. 0 if no file is loaded, or playback hasn't started
 * @return true if the index has been read successfully
 */
ehs_bool EhsTgtDtvPlayback_getPos(EhsTgtDtvPlaybackClass* pPlayback, ehs_uint32* pnPos)
{
//	EhsError(EHS_MSG_ERROR_NOT_YET_IMPLEMENTED("EhsTgtDtvPlayback_getPos"));
	return EHS_FALSE;	
}

/**
 * Get the playback speed for the currently loaded file.
 * @param[in] pPlayback playback structure
 * @param[out] pnSpeed The current speed of playback (as a percentage of normal speed). 0 means that the file isn't playing.
 * 100 is playing at normal speed, negative values indicate playing backwards
 * @return true if the index has been read successfully
 */
ehs_bool EhsTgtDtvPlayback_getSpeed(EhsTgtDtvPlaybackClass* pPlayback, ehs_sint32* pnSpeed)
{
	*pnSpeed = pPlayback->nPlaySpeed;
	return EHS_TRUE;
}

/**
 * Set the playback speed for the currently loaded file.
 * @param[in] pPlayback playback structure
 * @param[in] nSpeed The current speed of playback (as a percentage of normal speed). 0 pause the file
 * 100 is playing at normal speed, negative values indicate playing backwards
 * @return true if the speed has been set successfully
 */
ehs_bool EhsTgtDtvPlayback_setSpeed(EhsTgtDtvPlaybackClass* pPlayback, ehs_sint32 nSpeed)
{
	return EHS_FALSE;
}

/**
 * Start video playback at the specified speed/change playback to the specified speed.
 * This function is called with speed 0 to pause the playback.
 * @param[in] pPlayback playback structure
 * @param[in] nSpeed The speed to play the file.
 * @return true if the video playback has started running at that speed
 */
ehs_bool EhsTgtDtvPlayback_play(EhsTgtDtvPlaybackClass* pPlayback, ehs_sint32 nSpeed)
{
	MessageBox(NULL,_T("Playback"),_T("play file"),MB_OK);
//	EhsError(EHS_MSG_ERROR_NOT_YET_IMPLEMENTED("EhsTgtDtvPlayback_play"));
	return EHS_FALSE;	
}

/**
 * Terminate video playback. This causes the screen to clear
 * @param[in] pPlayback The item to stop
 * @return true if playback structure was valid, and video was stopped
 */
ehs_bool EhsTgtDtvPlayback_stop(EhsTgtDtvPlaybackClass* pPlayback)
{
//	EhsError(EHS_MSG_ERROR_NOT_YET_IMPLEMENTED("EhsTgtDtvPlayback_stop"));
	return EHS_FALSE;	
}

/**
 * Initialise the EhsTgtDtvFilesClass structure. Sets the path to the root of the 
 * media "filesystem" (i.e. EhsTgtDtvFiles_getDir returns "empty"). Resets any
 * searches.
 */
void EhsTgtDtvFiles_init(EhsTgtDtvFilesClass* pFiles)
{
	EhsStrcpy(pFiles->szPath,EHS_TGT_DTV_FILES_ROOT);
	pFiles->pSearchHandle = EHS_TGT_DTV_FILES_SEARCH_INVALID;
}

/**
 * Return the directory we are curently looking at.
 * @param[in] pFiles Context for the file operation
 * @param[out] szDir Text containing the current path. Caller must pass in an array of length EHS_TGT_DTV_FILES_MAX_PATH
 * @return true if successful
 */
ehs_bool EhsTgtDtvFiles_getDir(EhsTgtDtvFilesClass* pFiles, ehs_char* szDir)
{
	ehs_bool bRet = EHS_FALSE; /* assume failure */
	
	if (0 == EhsStrncmp(pFiles->szPath,EHS_TGT_DTV_FILES_ROOT,EhsStrlen(EHS_TGT_DTV_FILES_ROOT)))
	{
		/* if the path begins with EHS_TGT_DTV_FILES_ROOT, it must be valid! */
		/* Return only the part of the path that doesn't include EHS_TGT_DTV_FILES_ROOT */
		EhsStrcpy(szDir,&pFiles->szPath[EhsStrlen(EHS_TGT_DTV_FILES_ROOT)]);
		bRet = EHS_TRUE;
	}
	else
	{
		/* invalid path - reset the pFiles structure, and return and empty string */
		*szDir = '\0';
		EhsTgtDtvFiles_init(pFiles);
	}
	
	return bRet;
}

/**
 * Change the directory we will use for DTV file operations
 * @param[in] pFiles Context for the file operation
 * @param[in] szDir Directory to change to. "/" represents the root of the DTV file system (which might
 * not be the root of the underlying OS file system). Absolute and relative paths are supported.
 * @return true if successful.
 */
ehs_bool EhsTgtDtvFiles_setDir(EhsTgtDtvFilesClass* pFiles, const ehs_char* szDir)
{
	ehs_bool bRet = EHS_FALSE; /* assume this fails */
	
	/* determine full version of new path */
	if (*szDir == EHS_TGT_DTV_FILES_SEPARATOR)
	{
		/* need to prefix root */
		EhsStrcpy(pFiles->szPath,EHS_TGT_DTV_FILES_ROOT);
		EhsStrcpy(&(pFiles->szPath[EhsStrlen(EHS_TGT_DTV_FILES_ROOT)+1]),szDir);
		bRet = EHS_TRUE;
	}
	else
	{ 
		/* path is relative to current directory */
		EhsError(EHS_MSG_ERROR_NOT_YET_IMPLEMENTED("EhsTgtDtvFiles_setDir"));
		EhsStrcpy(pFiles->szPath,EHS_TGT_DTV_FILES_ROOT);
		bRet = EHS_TRUE;
	}
	
	return bRet;
}

/**
 * Start retrieving files from the current directory
 * @param[in] pFiles Context for the file operation
 * @param[in] eFlags Indicates which types of things to report files, directories or both
 * @param[out] szName Text containing the name of the retrieved object. Caller must pass in an array
 * of length EHS_TGT_DTV_FILES_MAX_FILENAME
 * @return true if a file name has been obtained
 */
ehs_bool EhsTgtDtvFiles_listFirst(EhsTgtDtvFilesClass* pFiles, EhsTgtDtvFileFlagEnum eFlags, ehs_char* szName)
{
	ehs_bool bRet = EHS_FALSE;
	ehs_char szFileSpec[EHS_TGT_DTV_FILES_MAX_PATH];
	EhsStrcpy(szFileSpec,pFiles->szPath);
	EhsStrcat(szFileSpec,"\\*.*");
	EhsTgtMainSetWorkingDirectory(NULL);
	pFiles->pSearchHandle = _findfirst(szFileSpec,&(pFiles->xFileInfo));
	pFiles->eSearch = eFlags;
	
	if (pFiles->pSearchHandle != EHS_TGT_DTV_FILES_SEARCH_INVALID)
	{
		bRet = EhsTgtDtvFiles_listNext(pFiles,szName);
	}
	
	return bRet;
}

/**
 * Continue retrieving files from the current directory. Keep calling this function until
 * it returns false.
 * @param[in] pFiles Context for the file operation
 * @param[out] szName Text containing the name of the retrieved object. Caller must pass in an array
 * of length EHS_TGT_DTV_FILES_MAX_FILENAME
 * @return true if a file name has been obtained
 */
ehs_bool EhsTgtDtvFiles_listNext(EhsTgtDtvFilesClass* pFiles, ehs_char* szName)
{
	ehs_bool bRet = EHS_FALSE;
	
	if (pFiles->pSearchHandle != EHS_TGT_DTV_FILES_SEARCH_INVALID)
	{
		/* there is file info held in pFiles - we need to check that it matches
		 * with the flags set in pFiles->eSearch. If not get another, and try again
		 */
		do
		{
			/* are we looking for a directory? is the file a directory? */
			if ((pFiles->eSearch & EHS_TGT_DTV_FILEFLAG_FOLDER) == EHS_TGT_DTV_FILEFLAG_FOLDER)
			{
				if ((pFiles->xFileInfo.attrib & (_A_SUBDIR | _A_HIDDEN | _A_SYSTEM)) == _A_SUBDIR)
				{
					bRet = EHS_TRUE;
				}
			}
			/* are we looking for a regular file? is the file a regular file? */
			else if ((pFiles->eSearch & EHS_TGT_DTV_FILEFLAG_FILE) == EHS_TGT_DTV_FILEFLAG_FILE)
			{
				if ((pFiles->xFileInfo.attrib & (_A_SUBDIR | _A_HIDDEN | _A_SYSTEM)) == 0)
				{
					bRet = EHS_TRUE;
				}
			}
		} while ((!bRet) && (EHS_TGT_DTV_FILES_SEARCH_INVALID != _findnext(pFiles->pSearchHandle, &(pFiles->xFileInfo))));
		
		if (bRet)
		{
			/* success - copy the name of the found file to szName */
			EhsStrcpy(szName,pFiles->xFileInfo.name);
			/* get the next file in ready for the next read */
			if (EHS_TGT_DTV_FILES_SEARCH_INVALID == _findnext(pFiles->pSearchHandle, &(pFiles->xFileInfo)))
				pFiles->pSearchHandle = EHS_TGT_DTV_FILES_SEARCH_INVALID;
		}
		else
		{
			/* end of search reached - can't call findnext any more */
			pFiles->pSearchHandle = EHS_TGT_DTV_FILES_SEARCH_INVALID;
		}
	}
	return bRet;
}

