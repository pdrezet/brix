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
35	95	135	215
1	0
parameter
tag	5	_	_	imageWidget1
EndOfValues
EndOfLabels
widget tag

parameter
Widget-Group	4	_	_	default
EndOfValues
EndOfLabels
widget group

inputport

0	1	35	185	0	0	1	0	1
x

RunGUI_MoveImage	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1
END_LINE
inputport

0	1	35	200	1	0	1	0	1
y

RunGUI_MoveImage	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1
END_LINE
startport

2	-1	35	105	0	1	0	0	1
create

RunGUI_LoadImage	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1
END_LINE
startport

2	-1	35	120	1	0	0	0	1
destroy

DestroyGUI_Image	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1
END_LINE
startport

2	-1	35	135	2	0	0	0	1
show

RealizeGUI_Image	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1
END_LINE
startport

2	-1	35	150	3	0	0	0	1
hide

UnrealizeGUI_Image	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1
END_LINE
startport

2	-1	35	165	4	0	0	0	1
move

RunGUI_MoveImage	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1
END_LINE
END_BLOCK
BEGIN_BLOCK

GUIIMAGE
_
4	0	0	0
_
_
This is a GUI image.
GUI_Image
_
190	90	290	210
1	0
parameter
tag	5	_	_	imageWidget2
EndOfValues
EndOfLabels
widget tag

parameter
Widget-Group	4	_	_	default
EndOfValues
EndOfLabels
widget group

inputport

0	1	190	180	0	0	1	0	1
x

RunGUI_MoveImage	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1
END_LINE
inputport

0	1	190	195	1	0	1	0	1
y

RunGUI_MoveImage	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1
END_LINE
startport

2	-1	190	100	0	1	0	0	1
create

RunGUI_LoadImage	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1
END_LINE
startport

2	-1	190	115	1	0	0	0	1
destroy

DestroyGUI_Image	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1
END_LINE
startport

2	-1	190	130	2	0	0	0	1
show

RealizeGUI_Image	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1
END_LINE
startport

2	-1	190	145	3	0	0	0	1
hide

UnrealizeGUI_Image	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1
END_LINE
startport

2	-1	190	160	4	0	0	0	1
move

RunGUI_MoveImage	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1
END_LINE
END_BLOCK
BEGIN_BLOCK

GUIIMAGE
_
6	0	0	0
_
_
This is a GUI image.
GUI_Image
_
330	85	430	205
1	0
parameter
tag	5	_	_	imageWidget3
EndOfValues
EndOfLabels
widget tag

parameter
Widget-Group	4	_	_	default
EndOfValues
EndOfLabels
widget group

inputport

0	1	330	175	0	0	1	0	1
x

RunGUI_MoveImage	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1
END_LINE
inputport

0	1	330	190	1	0	1	0	1
y

RunGUI_MoveImage	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1
END_LINE
startport

2	-1	330	95	0	1	0	0	1
create

RunGUI_LoadImage	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1
END_LINE
startport

2	-1	330	110	1	0	0	0	1
destroy

DestroyGUI_Image	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1
END_LINE
startport

2	-1	330	125	2	0	0	0	1
show

RealizeGUI_Image	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1
END_LINE
startport

2	-1	330	140	3	0	0	0	1
hide

UnrealizeGUI_Image	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1
END_LINE
startport

2	-1	330	155	4	0	0	0	1
move

RunGUI_MoveImage	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1
END_LINE
END_BLOCK
BEGIN_BLOCK

guitextbox_i
_
7	0	0	0
_
_
This is an integer GUI output.
GUI_OutputTextBoxInt
_
450	95	550	170
1	0
parameter
Widget Tag	5	_	_	textWidget
EndOfValues
EndOfLabels
widget tag

parameter
Widget-Group	4	_	_	default
EndOfValues
EndOfLabels
widget group

inputport

0	1	450	155	0	0	1	0	1


RunGUI_WriteTextBoxInt	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1
END_LINE
startport

2	-1	450	105	0	1	0	0	1
create

CreateGUI_WriteTextBoxInt	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1
END_LINE
startport

2	-1	450	120	1	0	0	0	1
destroy

DestroyGUI_WriteTextBoxInt	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1
END_LINE
startport

2	-1	450	135	2	0	0	0	1
write

RunGUI_WriteTextBoxInt	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1
END_LINE
finishport

3	1	550	105	0	0	1	0	1
updated

RunGUI_WriteTextBoxInt	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1
END_LINE
END_BLOCK
END_OF_BLOCKS
