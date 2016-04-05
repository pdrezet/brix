CanvasSizeXY
2000	2000

IconData
BEGIN_BLOCK

GUIIMAGE
_
1	0	0	0
_
_
This is a GUI image.
GUI_Image
_
60	55	160	175
1	0
parameter
tag	5	_	_	widget0
EndOfValues
EndOfLabels
widget tag

parameter
Widget-Group	4	_	_	default
EndOfValues
EndOfLabels
widget group

inputport

0	1	60	145	0	0	1	0	1
x

RunGUI_MoveImage	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1
END_LINE
inputport

0	1	60	160	1	0	1	0	1
y

RunGUI_MoveImage	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1
END_LINE
startport

2	-1	60	65	0	1	0	0	1
create

RunGUI_LoadImage	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1
END_LINE
startport

2	-1	60	80	1	0	0	0	1
destroy

DestroyGUI_Image	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1
END_LINE
startport

2	-1	60	95	2	0	0	0	1
show

RealizeGUI_Image	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1
END_LINE
startport

2	-1	60	110	3	0	0	0	1
hide

UnrealizeGUI_Image	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1
END_LINE
startport

2	-1	60	125	4	0	0	0	1
move

RunGUI_MoveImage	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1
END_LINE
END_BLOCK
BEGIN_BLOCK

guitextbox_s
_
2	0	0	0
_
_
This is a string GUI output.
GUI_OutputTextBoxString
_
310	135	410	210
1	0
parameter
Widget Tag	5	_	_	widget1
EndOfValues
EndOfLabels
widget tag

parameter
Widget-Group	4	_	_	default
EndOfValues
EndOfLabels
widget group

inputport

0	3	310	195	0	0	1	0	1


RunGUI_WriteTextBoxString	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1
END_LINE
startport

2	-1	310	145	0	1	0	0	1
create

CreateGUI_WriteTextBoxString	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1
END_LINE
startport

2	-1	310	160	1	0	0	0	1
destroy

DestroyGUI_WriteTextBoxString	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1
END_LINE
startport

2	-1	310	175	2	0	0	0	1
write

RunGUI_WriteTextBoxString	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1
END_LINE
finishport

3	3	410	145	0	0	1	0	1
updated

RunGUI_WriteTextBoxString	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1
END_LINE
END_BLOCK
END_OF_BLOCKS
