CanvasSizeXY
2000	2000

IconData
BEGIN_BLOCK

logic_notbbx
_
1	0	0	0
_
_
This is a logical inverter.
LogicNot
_
375	135	425	180
1	0
inputport

0	0	375	165	0	0	1	mandatory= 0	0	1


Run_LogicNot	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
outputport

1	0	425	165	0	0	1	mandatory= 0	0	1


Run_LogicNot	2	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
startport

2	0	375	145	0	1	1	mandatory= 0	0	1


Run_LogicNot	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	0	425	145	0	0	1	mandatory= 0	0	1


Run_LogicNot	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

logic_nand2bbx
_
2	0	0	0
_
_
This is a 2-input logical NAND.
LogicTwoInputNand
_
250	100	300	160
1	0
inputport

0	0	250	130	0	0	1	mandatory= 0	0	1


Run_LogicTwoInputNand	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	0	250	145	1	0	1	mandatory= 0	0	1


Run_LogicTwoInputNand	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
outputport

1	0	300	130	0	0	1	mandatory= 0	0	1


Run_LogicTwoInputNand	3	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
startport

2	0	250	110	0	0	1	mandatory= 0	0	1


Run_LogicTwoInputNand	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	0	300	110	0	0	1	mandatory= 0	0	1


Run_LogicTwoInputNand	4	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
END_OF_BLOCKS
