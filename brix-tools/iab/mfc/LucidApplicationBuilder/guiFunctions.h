/* guiFunctions.h
 * 
 * function prototypes for guiFunctions.c
 *
 * Lucid project stage one - NcapsaLtd - March 2005 - MDD 
 *
 */

#ifndef _GUI_FUNCTIONS_H
#define _GUI_FUNCTIONS_H

#include <Pt.h>
#include <Ph.h>

#include "types.h"

//typedef int CALLBACK;
#define GUI_READ_TEXTBOX_INT "GUI_InputTextBoxInt\n"
#define GUI_WRITE_TEXTBOX_INT "GUI_OutputTextBoxInt\n"
#define GUI_READ_TEXTBOX_REAL "GUI_InputTextBoxReal\n"
#define GUI_WRITE_TEXTBOX_REAL "GUI_OutputTextBoxReal\n"
#define GUI_READ_TEXTBOX_STRING "GUI_InputTextBoxString\n"
#define GUI_WRITE_TEXTBOX_STRING "GUI_OutputTextBoxString\n"
#define GUI_WRITE_TEXTBOX_BOOL "GUI_OutputTextBoxBool\n"
#define GUI_INPUT_IMAGE "GUI_Image\n"
#define GUI_INPUT_BUTTON "GUI_Button\n"
#define GUI_INPUT_LATCHING_BUTTON "GUI_LatchingButton\n"
#define GUI_INDICATOR_BOOL "GUI_IndicatorBool\n"

#define GUI_TEXTBOX "GUI_TextBox"
#define GUI_BITMAP "GUI_Bitmap"
#define GUI_BUTTON "GUI_Button"
#define GUI_LATCHING_BUTTON "GUI_LatchingButton"
#define MAIN_WINDOW "MainWindow\n"



void GenericCreateGUI_TextBox(structFuncArg* pByte,BOOL bCallBack);
//void CreateGUI_Button(BYTE* pByte);

void IdentifyGUI_Button(char* pParams, int* pBytesRequired, int* pPriority);
void InitGUI_Button(char* pParams, BYTE* pByte);
void CreateGUI_Button(structFuncArg* pByte);
void DestroyGUI_Button(BYTE** pByte);
CALLBACK ReadGUI_Button(PtWidget_t *widget, void *ptr, PtCallbackInfo_t *callbackInfo);

void IdentifyGUI_LatchingButton(char* pParams, int* pBytesRequired, int* pPriority);
void InitGUI_LatchingButton(char* pParams, BYTE* pByte);
void CreateGUI_LatchingButton(structFuncArg* pByte);
void DestroyGUI_LatchingButton(BYTE** pByte);
CALLBACK ReadGUI_LatchingButton(PtWidget_t *widget, void *ptr, PtCallbackInfo_t *callbackInfo);



void IdentifyGUI_ReadTextBoxInt(char* pParams, int* pBytesRequired, int* pPriority);
void InitGUI_ReadTextBoxInt(char* pParams, BYTE* pByte);
void CreateGUI_ReadTextBoxInt(structFuncArg* pByte);
void DestroyGUI_ReadTextBoxInt(BYTE** pByte);
CALLBACK RunGUI_ReadTextBoxInt(PtWidget_t *widget, void *ptr, PtCallbackInfo_t *callbackInfo);

void IdentifyGUI_ReadTextBoxReal(char* pParams, int* pBytesRequired, int* pPriority);
void InitGUI_ReadTextBoxReal(char* pParams, BYTE* pByte);
void CreateGUI_ReadTextBoxReal(structFuncArg* pByte);
void DestroyGUI_ReadTextBoxReal(BYTE** pByte);
CALLBACK RunGUI_ReadTextBoxReal(PtWidget_t *widget, void *ptr, PtCallbackInfo_t *callbackInfo);

void IdentifyGUI_ReadTextBoxString(char* pParams, int* pBytesRequired, int* pPriority);
void InitGUI_ReadTextBoxString(char* pParams, BYTE* pByte);
void CreateGUI_ReadTextBoxString(structFuncArg* pByte);
void DestroyGUI_ReadTextBoxString(BYTE** pByte);
CALLBACK RunGUI_ReadTextBoxString(PtWidget_t *widget, void *ptr, PtCallbackInfo_t *callbackInfo);


void IdentifyGUI_WriteTextBoxInt(char* pParams, int* pBytesRequired, int* pPriority);
void InitGUI_WriteTextBoxInt(char* pParams, BYTE* pByte);
void CreateGUI_WriteTextBoxInt(structFuncArg* pByte);
void DestroyGUI_WriteTextBoxInt(BYTE** pByte);
void RunGUI_WriteTextBoxInt(structFuncArg* pByte);

void IdentifyGUI_WriteTextBoxReal(char* pParams, int* pBytesRequired, int* pPriority);
void InitGUI_WriteTextBoxReal(char* pParams, BYTE* pByte);
void CreateGUI_WriteTextBoxReal(structFuncArg* pByte);
void DestroyGUI_WriteTextBoxReal(BYTE** pByte);
void RunGUI_WriteTextBoxReal(structFuncArg* pByte);

void IdentifyGUI_WriteTextBoxString(char* pParams, int* pBytesRequired, int* pPriority);
void InitGUI_WriteTextBoxString(char* pParams, BYTE* pByte);
void RunGUI_WriteTextBoxString(structFuncArg* pByte);
void CreateGUI_WriteTextBoxString(structFuncArg* pByte);
void DestroyGUI_WriteTextBoxString(BYTE** pByte);


void IdentifyGUI_WriteTextBoxBool(char* pParams, int* pBytesRequired, int* pPriority);
void InitGUI_WriteTextBoxBool(char* pParams, BYTE* pByte);
void RunGUI_WriteTextBoxBool(structFuncArg* pByte);
void CreateGUI_WriteTextBoxBool(structFuncArg* pByte);;
void DestroyGUI_WriteTextBoxBool(BYTE** pByte);

void IdentifyGUI_IndicatorBool(char* pParams, int* pBytesRequired, int* pPriority);
void InitGUI_IndicatorBool(char* pParams, BYTE* pByte);
void RunGUI_IndicatorBool(structFuncArg* pByte);
void CreateGUI_IndicatorBool(structFuncArg* pByte);;
void DestroyGUI_IndicatorBool(BYTE** pByte);

void Identify_MainWindow(char* pParams, int* pBytesRequired, int* pPriority);
void Init_MainWindow(char* pParams, BYTE* pByte);
void RunEdit_MainWindow(BYTE** pByte);


void IdentifyGUI_Image(char* pParams, int* pBytesRequired, int* pPriority);
void InitGUI_Image(char* pParams, BYTE* pByte);
void RunGUI_LoadImage(structFuncArg* pByte);
void CreateGUI_Image(structFuncArg* pByte);
void DestroyGUI_Image(BYTE** pByte);
void RunGUI_MoveImage(structFuncArg* pByte);
void RealizeGUI_Image(structFuncArg* pByte);
void UnrealizeGUI_Image(structFuncArg* pByte);

void* memory_allocate(long nbytes, int type);
void* memory_free(void* memory, int type);
void* warning(char *msg);
void* error(char *msg);
void* progress(int percent);

#endif
