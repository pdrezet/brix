/* guiFunctions.c
 * 
 * src file for GUI functions.  These functoins are appropriate for the 
 * QNX Photon microGUI windowing system.  Any function appearing in 
 * this file must also be listed in objRefTable.c for it to be included in the 
 * list of functions available to the EHS. 
 * 
 * For definition of arguments in Ncapsa functions (Identify_, Init_ and Run_)
 * please see types.h.  For definition of arguments in CALLBACK functions 
 * please see QNX Photon microGUI documentation.
 * 
 * Lucid project stage one - NcapsaLtd - March 2005 - MDD 
*/
 

#include <string.h>
#include <photon/PxImage.h>
#include <Pt.h>
#include <Ph.h>

#include "guiFunctions.h"
#include "guiUtilities.h"
#include "CBUtils.h"
#include "setCompletes.h"
#include "types.h"


extern PtWidget_t* pWin;

// Edit Main Window
void Identify_MainWindow(char* pParams, int* pBytesRequired, int* pPriority)
{
	*pBytesRequired = sizeof(structMainWinObj) ;
}

void Init_MainWindow(char* pParams, BYTE* pByte)
{
	int nRed, nGreen, nBlue, nHeight, nWidth;
	PgColor_t pColour;
	char szTitle[MAX_STRING_LEN]={'\0'}; 
	structMainWinObj* pMainWinObj = NULL;
	/* cast the input pointer to the correct pointer type...*/
	pMainWinObj = (structMainWinObj*)pByte;
	
	/* extract the params*/
	sscanf(pParams, "%d %d %d %d %d %s", &nRed, &nGreen, &nBlue, &nHeight, &nWidth, szTitle);
	pColour = PgRGB(nRed, nGreen, nBlue);
	pMainWinObj->pColour = pColour;
	pMainWinObj->nHeight = nHeight;
	pMainWinObj->nWidth = nWidth;
	strcpy(pMainWinObj->szTitle, szTitle);
	return;
}

void RunEdit_MainWindow(BYTE** pByte)
{
	//PgColor_t pColour;
	structMainWinObj* pMainWinObj = NULL;	
	
	if (!pWin) return;
	pMainWinObj = (structMainWinObj*)NCAPSA_pObjData;
	
	PtEnter(0);
		PtSetResource(pWin, Pt_ARG_FILL_COLOR, pMainWinObj->pColour, 0); 
		PtSetResource(pWin, Pt_ARG_MIN_HEIGHT, pMainWinObj->nHeight, 0);	
		PtSetResource(pWin, Pt_ARG_MIN_WIDTH, pMainWinObj->nWidth, 0);	
		PtSetResource(pWin, Pt_ARG_WINDOW_TITLE, pMainWinObj->szTitle, 0);
	PtLeave(0);
}

/* =============================================================================
 * GUI_Button
 * 
 * functions for a regular push button on a GUI.  The button calls a callback 
 * when pressed which may be used to set other trigger completes. 
 * */
void IdentifyGUI_Button(char* pParams, int* pBytesRequired, int* pPriority)
{
	/* require space for a GUI type object and its associated event handling information...*/
	*pBytesRequired = sizeof(structGUIObjData) ;//+ sizeof(int); //data is stored as a reference to a call back function in the call back function table.
}

void InitGUI_Button(char* pParams, BYTE* pByte) 
{
	structGUIObjData* pGUIObjData = NULL;
	/* cast the input pointer to the correct pointer type...*/
	pGUIObjData = (structGUIObjData*)pByte;
	/* copy the widget state params for subsequent widget creation...*/
	strcpy(pGUIObjData->szParams, pParams);
	return;
}

//the following prototype is defined by the device (photon)
CALLBACK ReadGUI_Button(PtWidget_t *pWidget, void *ptr, PtCallbackInfo_t *callbackInfo)
{
	BYTE** pByte = NULL;
	//structGUIObjData* pGUIObjData = NULL;
	
	/* the pointer passed into the callback routine is of type void - cast to correct type... */
	pByte = (BYTE**)ptr;
	//pGUIObjData = (structGUIObjData*)pByte[0];
	/* access the state event data structure directly here...*/
	//pByte = (BYTE**)&pGUIObjData[1];
	SetCompletes1(pByte);
	return TRUE;
}
//create the widget 
void CreateGUI_Button(structFuncArg* pByte)
{
	int nRet;
	PtArg_t arg[4];
	char sTextString [MAX_PARAM_STR_LEN]= {'\0'};
	PtWidget_t* pWidget = NULL;
	structGUIObjData* pGUIObjData = (structGUIObjData*)(((structFuncArg*)(pByte))->pObjData); //carefull here we want the object state data  not the entire function data
	if (pGUIObjData->pWidget) return;
	GenericCreateGeometryArgs(pGUIObjData, arg,sTextString);
	PtEnter(0);
	PtSetArg(&arg[2], Pt_ARG_TEXT_STRING, sTextString, 0);
	PtSetArg(&arg[3], Pt_ARG_LABEL_TYPE, Pt_Z_STRING, 0);
	pWidget = PtCreateWidget(PtButton, pWin, 4, arg);
	nRet=PtRealizeWidget(pWidget);
	if (nRet==0) { 
		pGUIObjData->pWidget = pWidget;
		GuiInstallCallback(1,pByte); //install call back number 1
		PtLeave(0);
		SetCompletes((BYTE**)pByte); // If it fails it doesn't call the completes!
	}
	else PtLeave(0);
	return;
}

void DestroyGUI_Button(BYTE** pByte) {
	GenericDestroyWidget(pByte);
}

/* =================================================================================
 * GUI_LatchingButton
 * 
 * A GUI button that maintains its state in persistent memory (state data).  
 * Activating the button on a GUI causes its state to toggle.  A latching button 
 * widget is created using the above create GUi_Button routine.
 * */
void IdentifyGUI_LatchingButton(char* pParams, int* pBytesRequired, int* pPriority)
{
	*pBytesRequired = sizeof(structGUIObjData) + sizeof(int);
}
void InitGUI_LatchingButton(char* pParams, BYTE* pB) 
{
	structGUIObjData* pGUIObjData = NULL;
	int* state = NULL;
	/* cast the input pointers to the correct pointer type...*/
	pGUIObjData = (structGUIObjData*)pB;
	state = (int*)&pGUIObjData[1];//gfins the address of the next bit of memory for the sate data.
	
	/* copy the widget state params for subsequent widget creation...*/
	strcpy(pGUIObjData->szParams, pParams);
	/* make sure the object latching state is initially false...*/
	*state=0;
	//NCAPSA_bOut(0) = FALSE;
	return;
}

void CreateGUI_LatchingButton(structFuncArg* pByte)
{
	int nRet;
	PtArg_t arg[4];
	char sTextString [MAX_PARAM_STR_LEN]= {'\0'};
	PtWidget_t* pWidget = NULL;
	structGUIObjData* pGUIObjData = (structGUIObjData*)(((structFuncArg*)(pByte))->pObjData); //carefull here we want the object state data  not the entire function data
	if (pGUIObjData->pWidget) return;
	GenericCreateGeometryArgs(pGUIObjData, arg,sTextString);
	PtEnter(0);
	PtSetArg(&arg[2], Pt_ARG_TEXT_STRING, sTextString, 0);
	PtSetArg(&arg[3], Pt_ARG_LABEL_TYPE, Pt_Z_STRING, 0);
	pWidget = PtCreateWidget(PtButton, pWin, 4, arg);
	nRet=PtRealizeWidget(pWidget);
	(*((int*)&pGUIObjData[1]))=0;
	if (nRet==0) { 
		pGUIObjData->pWidget = pWidget;
		GuiInstallCallback(1,pByte); //install call back number 1
		PtSetResource(pGUIObjData->pWidget, Pt_ARG_FILL_COLOR, Pg_GREEN, 0); 
		PtLeave(0);
		SetCompletes((BYTE**)pByte); // If it fails it doesn't call the completes!
	}
	else PtLeave(0);
	return;
}

CALLBACK ReadGUI_LatchingButton(PtWidget_t *pWidget, void *ptr, PtCallbackInfo_t *callbackInfo)
{
	structFuncArg* pByte = NULL;
	structGUIObjData* pGUIObjData = NULL;
	BOOL bBOOL;
	
	
	pByte = (structFuncArg*)ptr;
	pGUIObjData = (structGUIObjData*)pByte->pObjData;
	bBOOL = (*((BOOL*)&pGUIObjData[1]));
	/* reverse the logic of the latching state...*/
	bBOOL = !bBOOL;
	NCAPSA_bOut(0) = bBOOL;
	/* set the completes...*/
	PtEnter(0);
	if (bBOOL) {
		PtSetResource(pGUIObjData->pWidget, Pt_ARG_FILL_COLOR, Pg_GREEN, 0); 
	} else
	{
		PtSetResource(pGUIObjData->pWidget, Pt_ARG_FILL_COLOR, Pg_RED, 0); 
	}
	PtLeave(0);
	(*((BOOL*)&pGUIObjData[1]))=bBOOL;
	SetCompletes( (BYTE**)pByte );
	return TRUE;
}

void DestroyGUI_LatchingButton(BYTE** pByte) {
	GenericDestroyWidget(pByte);
}




/* =================================================================================
 * GUI_WriteTextBoxInt
 * 
 * A GUI text box that will accept and integer data type and display it on the 
 * screen this GUI object does not have a callback - it is a read only type object
 * */
void IdentifyGUI_WriteTextBoxInt(char* pParams, int* pBytesRequired, int* pPriority)
{
	/* don't need the event handling structure this time...*/
	*pBytesRequired = sizeof(structGUIObjData);
	return;	
}
void InitGUI_WriteTextBoxInt(char* pParams, BYTE* pByte) 
{
	structGUIObjData* pGUIObjData = NULL;

	/* cast the input pointer to the correct pointer type...*/
	pGUIObjData = (structGUIObjData*)pByte;
	/* copy the widget state params for subsequent widget creation...*/
	strcpy(pGUIObjData->szParams, pParams);
	return;
}


void GenericCreateGUI_TextBox(structFuncArg* pByte,BOOL bCallBack)
{
	int nRet;
	int nX, nY, nW, nH;
	PtArg_t arg[7];
	char sTextString [MAX_PARAM_STR_LEN]= {'\0'};
	char szParams[MAX_PARAM_STR_LEN]={'\0'};
	int	nBGRed, nBGGreen, nBGBlue, nFGRed, nFGGreen, nFGBlue;
	int nBevel = 0;

	PtWidget_t* pWidget = NULL;
	structGUIObjData* pGUIObjData = (structGUIObjData*)(((structFuncArg*)(pByte))->pObjData); //carefull here we want the object state data  not the entire function data
	if (pGUIObjData->pWidget) return;//this is a little risky but quick for now



	strcpy(szParams, (pGUIObjData->szParams));
	sscanf(szParams, "%*s %*s %d %d %d %d %*d %*d %s   %d%d%d  %d%d%d  %d",
	 		&nX, &nY, &nW, &nH, sTextString, 
	 		&nBGRed, &nBGGreen, &nBGBlue, &nFGRed, &nFGGreen, &nFGBlue,   &nBevel );

	
	
	pGUIObjData->pLabel = GenericWidgetTextLabel(nX,nY-20,nW,20,sTextString,PgRGB( nBGRed, nBGGreen, nBGBlue ),  PgRGB( nFGRed, nFGGreen, nFGBlue ));
	
	
	GenericCreateGeometryArgs(pGUIObjData, arg,sTextString);
	PtEnter(0);
	
	PtSetArg(&arg[2], Pt_ARG_FILL_COLOR, PgRGB( nBGRed, nBGGreen, nBGBlue ),0);
	PtSetArg(&arg[3], Pt_ARG_FLAGS, Pt_FALSE, Pt_HIGHLIGHTED  );	
	PtSetArg(&arg[4], Pt_ARG_BEVEL_WIDTH, 0, 0  );
	PtSetArg(&arg[5], Pt_ARG_COLOR, PgRGB( nFGRed, nFGGreen, nFGBlue ),0);
	PtSetArg(&arg[6], Pt_ARG_HORIZONTAL_ALIGNMENT, Pt_CENTER, 0  );	
	

	
	pWidget = PtCreateWidget(PtText, pWin, 7, arg);
	nRet=PtRealizeWidget(pWidget);
	if (nRet==0) { 
		pGUIObjData->pWidget = pWidget;
		if (bCallBack) 
			GuiInstallCallback(1,pByte); //install call back number 1
		PtLeave(0);
		SetCompletes((BYTE**)pByte); // If it fails it doesn't call the completes!
	}
	else PtLeave(0);
	return;
}

void RunGUI_WriteTextBoxInt(structFuncArg* pByte)
{
	int nData;
	PtWidget_t* pWidget = NULL;
	structGUIObjData* pGUIObjData = NULL;
//	structFuncArg* pReadEventHandlerInfo = NULL;
	char szData[MAX_STRING_LEN] = {'\0'};
	char* pData = &szData[0];
	int nRet;
	
	/* there is one input simply write it to the widget...*/
	pGUIObjData = (structGUIObjData*)pByte->pObjData;
	pWidget = pGUIObjData->pWidget;
	if (!pWidget) return;//this is a little risky but quick for now
	
	nData = NCAPSA_nIn(0);	
	pData = itoa(nData, pData, 10);
	
	nRet = PtEnter(0);
		PtSetResource(pWidget, Pt_ARG_TEXT_STRING, pData, 0);
	nRet = PtLeave(0);
	
	SetCompletes( (BYTE**)pByte );
	return;
}

/* =================================================================================
 * GUI_WriteTextBoxReal
 * 
 * A GUI text box that will accept and integer data type and display it on the 
 * screen this GUI object does not have a callback - it is a read only type object
 * */
void IdentifyGUI_WriteTextBoxReal(char* pParams, int* pBytesRequired, int* pPriority)
{
	/* don't need the event handling structure this time...*/
	*pBytesRequired = sizeof(structGUIObjData);
	return;	
}
void InitGUI_WriteTextBoxReal(char* pParams, BYTE* pByte) 
{
	structGUIObjData* pGUIObjData = NULL;

	/* cast the input pointer to the correct pointer type...*/
	pGUIObjData = (structGUIObjData*)pByte;
	/* copy the widget state params for subsequent widget creation...*/
	strcpy(pGUIObjData->szParams, pParams);
	return;
}

void RunGUI_WriteTextBoxReal(structFuncArg* pByte)
{
	int nRet;
	PtWidget_t* pWidget = NULL;
	structGUIObjData* pGUIObjData = NULL;
//	structFuncArg* pReadEventHandlerInfo = NULL;
	char szData[MAX_STRING_LEN] = {'\0'};
	char* pData = &szData[0];
	
	/* there is one input simply write it to the widget...*/
	nRet = PtEnter(0);
	pGUIObjData = (structGUIObjData*)pByte->pObjData;
	pWidget = pGUIObjData->pWidget;
	if (!pWidget) return;//this is a little risky but quick for now
	
	sprintf(pData, "%f", NCAPSA_dIn(0));
	
		PtSetResource(pWidget, Pt_ARG_TEXT_STRING, pData, 0);
	nRet = PtLeave(0);
	
	SetCompletes( (BYTE**)pByte );
	return;
}




/* =================================================================================
 * GUI_WriteTextBoxString
 * 
 * A GUI text box that will accept and integer data type and display it on the 
 * screen this GUI object does not have a callback - it is a read only type object
 * */
void IdentifyGUI_WriteTextBoxString(char* pParams, int* pBytesRequired, int* pPriority)
{
	/* don't need the event handling structure this time...*/
	*pBytesRequired = sizeof(structGUIObjData);
	return;	
}
void InitGUI_WriteTextBoxString(char* pParams, BYTE* pByte) 
{
	structGUIObjData* pGUIObjData = NULL;

	/* cast the input pointer to the correct pointer type...*/
	pGUIObjData = (structGUIObjData*)pByte;
	/* copy the widget state params for subsequent widget creation...*/
	strcpy(pGUIObjData->szParams, pParams);
	return;
}
void RunGUI_WriteTextBoxString(structFuncArg* pByte)
{
	PtWidget_t* pWidget = NULL;
	structGUIObjData* pGUIObjData = NULL;
//	structFuncArg* pReadEventHandlerInfo = NULL;
	char szData[MAX_STRING_LEN] = {'\0'};
	char* pData = &szData[0];
	int nRet;
	
	/* there is one input simply write it to the widget...*/
	pGUIObjData = (structGUIObjData*)pByte->pObjData;
	pWidget = pGUIObjData->pWidget;
	if (!pWidget) return;//this is a little risky but quick for now

	nRet = PtEnter(0);
	strcpy(pData, NCAPSA_szIn(0));	
	
		PtSetResource(pWidget, Pt_ARG_TEXT_STRING, pData, 0);
	nRet = PtLeave(0);
	
	SetCompletes( (BYTE**)pByte );
	return;
}

/*
void GenericCreateGUI_TextBox(BYTE* pByte)
{
	int nRet;
	PtArg_t arg[2];
	char temp[MAX_PARAM_STR_LEN] = {'\0'};
	PtWidget_t* pWidget = NULL;
	structGUIObjData* pGUIObjData = (structGUIObjData*)pByte[0];
	GenericCreateGeometryArgs(pGUIObjData, arg,temp);
	pWidget = PtCreateWidget(PtText, pWin, 2, arg);
	PtEnter(0);
	nRet=PtRealizeWidget(pWidget);
	PtLeave(0);
	if (nRet==0) { 
		pGUIObjData->pWidget = pWidget;
		GuiInstallCallback(1,pByte); //install call back number 1
		SetCompletes(pByte); // If it fails it doesn't call the completes!
	}
//    GenericCreateCallbackWidget(pByte); //Got rid of this for now
	return;
	
	
	
	// / OLD VERSION
	PtWidget_t* pWidget = NULL;
	PhArea_t phArea;
	//PtArg_t pArgs[2];
	int nX, nY, nW, nH;
	int nRet;

	// get the parameters from the parameter string...
	sscanf(szParams, "%*s %*s %d %d %d %d", &nX, &nY, &nW, &nH);
	phArea.pos.x = nX;
	phArea.pos.y = nY;
	phArea.size.w = nW;
	phArea.size.h = nH;
	
	nRet = PtEnter(0);
		pWidget = PtCreateWidget(PtText, pWin, 0, NULL); DOES IT NEED TO BE THIS WAY AROUND?
		PtSetResource(pWidget, Pt_ARG_POS, &phArea.pos, 0);
    	PtSetResource(pWidget, Pt_ARG_DIM, &phArea.size, 0);
	nRet = PtLeave(0);

	return pWidget;
	// 
}
*/

// Create functions
void CreateGUI_ReadTextBoxInt(structFuncArg* pByte) {
	GenericCreateGUI_TextBox(pByte,TRUE);
}

void CreateGUI_ReadTextBoxReal(structFuncArg* pByte) {
	GenericCreateGUI_TextBox(pByte,TRUE);
}

void CreateGUI_ReadTextBoxString(structFuncArg* pByte) {
	GenericCreateGUI_TextBox(pByte,TRUE);
}

void CreateGUI_WriteTextBoxInt(structFuncArg* pByte) {
	GenericCreateGUI_TextBox(pByte,FALSE);
}

void CreateGUI_WriteTextBoxReal(structFuncArg* pByte) {
	GenericCreateGUI_TextBox(pByte,FALSE);
}

void CreateGUI_WriteTextBoxString(structFuncArg* pByte) {
	GenericCreateGUI_TextBox(pByte,FALSE);
}

void CreateGUI_WriteTextBoxBool(structFuncArg* pByte) {
	GenericCreateGUI_TextBox(pByte,FALSE);
}

void CreateGUI_IndicatorBool(structFuncArg* pByte) {
	GenericCreateGUI_TextBox(pByte,FALSE);
}

// destroy functions
void DestroyGUI_ReadTextBoxInt(BYTE** pByte) {
	GenericDestroyWidget(pByte);
}

void DestroyGUI_ReadTextBoxReal(BYTE** pByte) {
	GenericDestroyWidget(pByte);
}

void DestroyGUI_ReadTextBoxString(BYTE** pByte) {
	GenericDestroyWidget(pByte);
}

void DestroyGUI_WriteTextBoxInt(BYTE** pByte) {
	GenericDestroyWidget(pByte);
}

void DestroyGUI_WriteTextBoxReal(BYTE** pByte) {
	GenericDestroyWidget(pByte);
}

void DestroyGUI_WriteTextBoxString(BYTE** pByte) {
	GenericDestroyWidget(pByte);
}

void DestroyGUI_WriteTextBoxBool(BYTE** pByte) {
	GenericDestroyWidget(pByte);
}

void DestroyGUI_IndicatorBool(BYTE** pByte) {
	GenericDestroyWidget(pByte);
}

/* =================================================================================
 * GUI_WriteTextBoxBool
 * 
 * outputs TRUE/FALSE to a GUI widget displayed on the screen.  A Boolena GUI text 
 * box is created with the above CreateGUI_TextBox
 * 
 */
void IdentifyGUI_WriteTextBoxBool(char* pParams, int* pBytesRequired, int* pPriority)
{
	*pBytesRequired = sizeof(structGUIObjData);
	return;	
}

void InitGUI_WriteTextBoxBool(char* pParams, BYTE* pByte) 
{
	structGUIObjData* pGUIObjData = NULL;

	/* cast the input pointer to the correct pointer type...*/
	pGUIObjData = (structGUIObjData*)pByte;
	/* copy the widget state params for subsequent widget creation...*/
	strcpy(pGUIObjData->szParams, pParams);
	return;
}

void RunGUI_WriteTextBoxBool(structFuncArg* pByte)
{
	BOOL bData;
	PtWidget_t* pWidget = NULL;
	structGUIObjData* pGUIObjData = NULL;
	char szData[MAX_STRING_LEN] = {'\0'};
	char* pData = &szData[0];
	int nRet;
	

	/* there is one input simply write it to the widget...*/
	pGUIObjData = (structGUIObjData*)pByte->pObjData;
	pWidget = pGUIObjData->pWidget;
	if (!pWidget) return;//this is a little risky but quick for now

	nRet = PtEnter(0);
	bData = NCAPSA_bIn(0);
	if (bData)
	{
		pData = strcpy(pData, "TRUE");
	}
	else
	{
		pData = strcpy(pData, "FALSE");
	}

		PtSetResource(pWidget, Pt_ARG_TEXT_STRING, pData, 0);
	nRet = PtLeave(0);
	
	SetCompletes( (BYTE**)pByte );
	return;
}

/* =================================================================================
 * GUI_IndicatorBool
 * 
 * outputs red if true and green if false
 * 
 */
void IdentifyGUI_IndicatorBool(char* pParams, int* pBytesRequired, int* pPriority)
{
	*pBytesRequired = sizeof(structGUIObjData);
	return;	
}

void InitGUI_IndicatorBool(char* pParams, BYTE* pByte) 
{
	structGUIObjData* pGUIObjData = NULL;

	/* cast the input pointer to the correct pointer type...*/
	pGUIObjData = (structGUIObjData*)pByte;
	/* copy the widget state params for subsequent widget creation...*/
	strcpy(pGUIObjData->szParams, pParams);
	return;
}

void RunGUI_IndicatorBool(structFuncArg* pByte)
{
	BOOL bData;
	PtWidget_t* pWidget = NULL;
	structGUIObjData* pGUIObjData = NULL;
	int nRet;
	

	/* there is one input simply write it to the widget...*/
	pGUIObjData = (structGUIObjData*)pByte->pObjData;
	pWidget = pGUIObjData->pWidget;
	if (!pWidget) return;//this is a little risky but quick for now

	nRet = PtEnter(0);
	bData = NCAPSA_bIn(0);
	if (bData) {
		PtSetResource(pWidget, Pt_ARG_FILL_COLOR, Pg_RED, 0); 
	} 
	else
	{
		PtSetResource(pWidget, Pt_ARG_FILL_COLOR, Pg_GREEN, 0); 
	}
	nRet = PtLeave(0);
	
	SetCompletes( (BYTE**)pByte );
	return;
}

/* =================================================================================
 * GUI_ReadTextBoxInt
 * 
 * A text box on the GUI that can read an integer number.  In fact any text may be read
 * but only integers generate the correct input.  Any character not in the range
 * 0-9 id read as zero.
 *  
 * */
void IdentifyGUI_ReadTextBoxInt(char* pParams, int* pBytesRequired, int* pPriority)
{
	*pBytesRequired = sizeof(structGUIObjData) + sizeof(structFuncArg);
	return;
}
void InitGUI_ReadTextBoxInt(char* pParams, BYTE* pByte) 
{
	structGUIObjData* pGUIObjData = NULL;
	/* cast the input pointer to the correct pointer type...*/
	pGUIObjData = (structGUIObjData*)pByte;
	/* copy the widget state params for subsequent widget creation...*/
	strcpy(pGUIObjData->szParams, pParams);
	return;
}

CALLBACK RunGUI_ReadTextBoxInt(PtWidget_t *pWidget, void *ptr, PtCallbackInfo_t *callbackInfo)
{
	//structGUIObjData* pGUIObjData = NULL;
	BYTE** pByte = NULL;
	
	int nInputData;
	char szString[MAX_STRING_LEN] = {'\0'};
	char* pString = &szString[0];
	
	PtGetResource(pWidget, Pt_ARG_TEXT_STRING, &pString, 0);
	nInputData = atoi(pString);
	/* clear the last input line...*/
	//PtSetResource(pWidget, Pt_ARG_TEXT_STRING, "", 0);	
	
	/* put the data into its propper place...*/
	pByte = (BYTE**)ptr;
	//pGUIObjData = (structGUIObjData*)&pByte[0];
	//pByte = (BYTE**)&pGUIObjData[1];
	NCAPSA_nOut(0) = nInputData;

	/* set the completes...*/		
	SetCompletes(pByte);
	return TRUE;
}


/* =================================================================================
 * GUI_ReadTextBoxReal
 * 
 * A text box on the GUI that can read an integer number.  In fact any text may be read
 * but only integers generate the correct input.  Any character not in the range
 * 0-9 id read as zero.
 *  
 * */
void IdentifyGUI_ReadTextBoxReal(char* pParams, int* pBytesRequired, int* pPriority)
{
	*pBytesRequired = sizeof(structGUIObjData) + sizeof(structFuncArg);
	return;
}
void InitGUI_ReadTextBoxReal(char* pParams, BYTE* pByte) 
{
	structGUIObjData* pGUIObjData = NULL;

	/* cast the input pointer to the correct pointer type...*/
	pGUIObjData = (structGUIObjData*)pByte;
	/* copy the widget state params for subsequent widget creation...*/
	strcpy(pGUIObjData->szParams, pParams);
	return;
}

CALLBACK RunGUI_ReadTextBoxReal(PtWidget_t *pWidget, void *ptr, PtCallbackInfo_t *callbackInfo)
{
	//structGUIObjData* pGUIObjData = NULL;
	BYTE** pByte = NULL;
	
	double dInputData;
	char szString[MAX_STRING_LEN] = {'\0'};
	char* pString = &szString[0];
	
	PtGetResource(pWidget, Pt_ARG_TEXT_STRING, &pString, 0);
	dInputData = atof(pString);
	/* clear the last input line...*/
	//PtSetResource(pWidget, Pt_ARG_TEXT_STRING, "", 0);	
	
	/* put the data into its propper place...*/
	pByte = (BYTE**)ptr;
	//pGUIObjData = (structGUIObjData*)&pByte[0];
	//pByte = (BYTE**)&pGUIObjData[1];
	NCAPSA_dOut(0) = dInputData;

	/* set the completes...*/		
	SetCompletes(pByte);
	return TRUE;
}

/* =================================================================================
 * GUI_ReadTextBoxString
 * 
 * A text box on the GUI that can read an integer number.  In fact any text may be read
 * but only integers generate the correct input.  Any character not in the range
 * 0-9 id read as zero.
 *  
 * */
void IdentifyGUI_ReadTextBoxString(char* pParams, int* pBytesRequired, int* pPriority)
{
	*pBytesRequired = sizeof(structGUIObjData) + sizeof(structFuncArg);
	return;
}
void InitGUI_ReadTextBoxString(char* pParams, BYTE* pByte) 
{
	structGUIObjData* pGUIObjData = NULL;

	/* cast the input pointer to the correct pointer type...*/
	pGUIObjData = (structGUIObjData*)pByte;
	/* copy the widget state params for subsequent widget creation...*/
	strcpy(pGUIObjData->szParams, pParams);
	return;
}

CALLBACK RunGUI_ReadTextBoxString(PtWidget_t *pWidget, void *ptr, PtCallbackInfo_t *callbackInfo)
{
	//structGUIObjData* pGUIObjData = NULL;
	BYTE** pByte = NULL;
	
	char szString[MAX_STRING_LEN] = {'\0'};
	char* pString = &szString[0];
	
	PtGetResource(pWidget, Pt_ARG_TEXT_STRING, &pString, 0);
	/* clear the last input line...*/
	//PtSetResource(pWidget, Pt_ARG_TEXT_STRING, "", 0);	
	
	/* put the data into its propper place...*/
	pByte = (BYTE**)ptr;
	//pGUIObjData = (structGUIObjData*)&pByte[0];
	//pByte = (BYTE**)&pGUIObjData[1];
	strcpy(NCAPSA_szOut(0), pString);

	/* set the completes...*/		
	SetCompletes(pByte);
	return TRUE;
}

/* =================================================================================
 * GUI_Image
 * 
 * An image displayed on the target GUI...  This function reads a graphic file 
 * into memory. Photon supports at least the BMP, GIF, JPEG, PCX, PNG, and SGI 
 * file formats; for a list of the supported formats, see /usr/photon/dll/pi_io_*. 
 * 
 * For further information please see PxLoadImage in the QNX Photon microGUI 
 * documentation.  For example for descriptions of the void* functions below, 
 * which are QNX functions, please see the documentation.
 * */
void IdentifyGUI_Image(char* pParams, int* pBytesRequired, int* pPriority)
{
	*pBytesRequired = sizeof(structGUIObjData);
	return;
}
void InitGUI_Image(char* pParams, BYTE* pByte)
{
	structGUIObjData* pGUIObjData = NULL;
	
	pGUIObjData = (structGUIObjData*)pByte;
	strcpy(pGUIObjData->szParams, pParams);
	return;
}
void CreateGUI_Image(structFuncArg* pByte)
{
	static PhArea_t phArea;
	int nX, nY, nW, nH;
	int nOrder = 0;
	char szParams[MAX_PARAM_STR_LEN]= {'\0'};
	
	//int nRet;
	PtArg_t arg[4];
	PxMethods_t methods;
	char szImageFilename[MAX_PARAM_STR_LEN]= {'\0'};
	PtWidget_t* pWidget = NULL;
	PhImage_t* pImage = NULL;
	structGUIObjData* pGUIObjData;
	
	pGUIObjData = (structGUIObjData*)pByte->pObjData;
	if (pGUIObjData->pWidget) return;//this is a little risky but quick for now
	
	PtEnter(0);
	memset(&methods, 0, sizeof( PxMethods_t ));
	/* initialise the PxMeathods structure with function names...*/
	methods.flags = PX_LOAD;
    methods.px_alloc    = memory_allocate;
    methods.px_free     = memory_free;
    methods.px_warning  = warning;
    methods.px_error    = error;
    methods.px_progress = progress;

	strcpy(szParams, (pGUIObjData->szParams));
//BitmapN	GUI_Bitmap	0	0	100	30	1	1	screen.bmp	-1
	sscanf(szParams, "%*s %*s %d %d %d %d %*d %*d %s %d", &nX, &nY, &nW, &nH, szImageFilename, &nOrder);
	phArea.pos.x = nX;
	phArea.pos.y = nY;
	phArea.size.w = nW;
	phArea.size.h = nH;
		PtSetArg(&arg[0], Pt_ARG_POS, &phArea.pos, 0);
		PtSetArg(&arg[1], Pt_ARG_DIM, &phArea.size, 0);



	pImage = PxLoadImage(szImageFilename, &methods);

		PtSetArg(&arg[2], Pt_ARG_LABEL_TYPE, Pt_IMAGE, 0);
    	PtSetArg(&arg[3], Pt_ARG_LABEL_IMAGE, pImage, 0);
        pWidget = PtCreateWidget(PtLabel, pWin, 4, arg);
      	if (nOrder > 0)
        {	PtWidgetToFront(pWidget);
        }
       	if (nOrder < 0)
        {	PtWidgetToBack(pWidget);
        }
       
        PtRealizeWidget(pWidget);
        //PtWidgetToBack(pWidget);
		//if (nRet==0) 
			pGUIObjData->pWidget = pWidget;
		//GenericInstallCallback(1,pByte); //install call back number 1
	PtLeave(0);
	
	//}
//    GenericCreateCallbackWidget(pByte); //Got rid of this for now
	return;
	
	
	/*
	PtWidget_t* pWidget = NULL;
	PhImage_t* pImage = NULL;
	int nX, nY, nW, nH;
	char szImageFilename[MAX_FILENAME_LEN]={'\0'};
	char szParams[MAX_PARAM_STR_LEN]={'\0'};
	PhArea_t phArea;
	PxMethods_t methods;
	PtArg_t arg[4];
	
	
	// the contents fo the PxMethods structure...
	memset(&methods, 0, sizeof( PxMethods_t ));
	// initialise the PxMeathods structure with function names...
	methods.flags = PX_LOAD;
    methods.px_alloc    = memory_allocate;
    methods.px_free     = memory_free;
    methods.px_warning  = warning;
    methods.px_error    = error;
    methods.px_progress = progress;
    
    // get the GUI properties from the object's state data...
    strcpy(szParams, (pGUIObjData->szParams));
	sscanf(szParams, "%*s %*s %d %d %d %d %*d %*d %s", &nX, &nY, &nW, &nH, szImageFilename);

    phArea.pos.x = nX;
	phArea.pos.y = nY;
	phArea.size.w = nW;
	phArea.size.h = nH;
    
    
	pImage = PxLoadImage(szImageFilename, &methods);
	PtEnter(0);
		PtSetArg(&arg[0], Pt_ARG_LABEL_TYPE, Pt_IMAGE, 0);
    	PtSetArg(&arg[1], Pt_ARG_LABEL_IMAGE, pImage, 0);
    	PtSetArg(&arg[2], Pt_ARG_POS, &phArea.pos, 0);
    	PtSetArg(&arg[3], Pt_ARG_DIM, &phArea.size, 0);
	    pWidget = PtCreateWidget(PtLabel, pWin, 4, arg);
	PtLeave(0);
	
	
	return pWidget;
	*/
}

void DestroyGUI_Image(BYTE** pByte) {
	GenericDestroyWidget(pByte);
}

//void RunGUI_LoadImage(structFuncArg* pByte) {} //nothing to do?
void RunGUI_MoveImage(structFuncArg* pByte)
{
	PtWidget_t* pWidget = NULL;
	structGUIObjData* pGUIObjData = NULL;
	PhPoint_t phPos;
	int nRet;
	
	pGUIObjData = (structGUIObjData*)pByte->pObjData;
	pWidget = pGUIObjData->pWidget;
	if (!pWidget) return;//this is a little risky but quick for now
	
	nRet = PtEnter(0);
		phPos = (pWidget->area).pos;
		phPos.x = phPos.x + NCAPSA_nIn(0);
		phPos.y = phPos.y + NCAPSA_nIn(1);
		PtSetResource(pWidget, Pt_ARG_POS, &phPos, 0);
	nRet = PtLeave(0);
	
	return;
}


void RealizeGUI_Image(structFuncArg* pByte)
{
	structGUIObjData* pGUIObjData;
	pGUIObjData = (structGUIObjData*)pByte->pObjData;
	if(!(pGUIObjData->pWidget)) return;
	
	PtEnter(0);

        PtRealizeWidget(pGUIObjData->pWidget);

	PtLeave(0);
	return;	
}

void UnrealizeGUI_Image(structFuncArg* pByte)
{
	structGUIObjData* pGUIObjData;
	pGUIObjData = (structGUIObjData*)pByte->pObjData;
	if (!(pGUIObjData->pWidget)) return;
	
	PtEnter(0);

        PtUnrealizeWidget(pGUIObjData->pWidget);

	PtLeave(0);
	return;	
}




void* memory_allocate(long nbytes, int type)
{
	void* mem = NULL;
	/* allocate space for image...*/
	mem = calloc(1, nbytes);
	return mem;
}
void* memory_free(void* memory, int type)
{
    free(memory);
    return NULL;
}
void* warning(char *msg)
{
    printf( "%s\n", msg );
    return NULL;
}
void* error(char *msg)
{
    printf( "%s\n", msg );
    PtExit( EXIT_FAILURE );
    return NULL;
}
void* progress(int percent)
{
    printf( "Load Status:  %d.%d percent\n",
             percent >> 16, percent & 0xffff );
    return NULL;
}







