CanvasSizeXY
2000	3610

IconData
BEGIN_BLOCK

buffer_fifobbq
_
1	0	0	0
_
_
This is a boolean fifo buffer.
FIFO_Bool
_
40	70	140	159
1	0
parameter
Max. length	1	0	1000000	5
EndOfValues
EndOfLabels
maximum buffer length

inputport

0	0	40	145	0	0	1	mandatory= 0	0	1
data

Run_PushFIFOBool	1	EndOfFunc
BEGIN_LINE
1	1	0	0	-1	0
155	145
155	190
15	190
15	145
END_LINE
outputport

1	0	140	145	0	0	1	mandatory= 0	0	1
data

Run_PopFIFOBool	1	EndOfFunc
BEGIN_LINE
0	1	0	1	-1	0
END_LINE
startport

2	0	40	80	0	0	1	mandatory= 0	0	1
pop

Run_PopFIFOBool	0	EndOfFunc
BEGIN_LINE
1	2	0	2	-1	0
330	75
330	15
5	15
5	80
END_LINE
startport

2	0	40	105	1	0	1	mandatory= 0	0	1
push

Run_PushFIFOBool	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	0	40	130	2	0	1	mandatory= 0	0	1
flush

Run_FlushFIFOBool	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	0	140	80	0	0	1	mandatory= 0	0	1
pop

Run_PopFIFOBool	2	EndOfFunc
BEGIN_LINE
0	2	2	3	-1	0
END_LINE
finishport

3	0	140	90	1	0	1	mandatory= 0	0	1
err

Run_PopFIFOBool	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	0	140	105	2	0	1	mandatory= 0	0	1
push

Run_PushFIFOBool	2	EndOfFunc
BEGIN_LINE
0	3	0	3	-1	0
END_LINE
finishport

3	0	140	115	3	0	1	mandatory= 0	0	1
err

Run_PushFIFOBool	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	0	140	130	4	0	1	mandatory= 0	0	1
flush

Run_FlushFIFOBool	1	EndOfFunc
BEGIN_LINE
0	2	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

buffer_fifoiiq
_
2	0	0	0
_
_
This is an integer fifo buffer.
FIFO_Int
_
175	65	275	154
1	0
parameter
Max. length	1	0	1000000	5
EndOfValues
EndOfLabels
maximum buffer length

inputport

0	1	175	140	0	0	1	mandatory= 0	0	1
data

Run_PushFIFOInt	1	EndOfFunc
BEGIN_LINE
1	2	0	0	-1	0
295	140
295	185
160	185
160	140
END_LINE
outputport

1	1	275	140	0	0	1	mandatory= 0	0	1
data

Run_PopFIFOInt	1	EndOfFunc
BEGIN_LINE
0	2	0	1	-1	0
END_LINE
startport

2	1	175	75	0	0	1	mandatory= 0	0	1
pop

Run_PopFIFOInt	0	EndOfFunc
BEGIN_LINE
1	1	4	2	-1	0
160	130
160	75
END_LINE
startport

2	1	175	100	1	0	1	mandatory= 0	0	1
push

Run_PushFIFOInt	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	1	175	125	2	0	1	mandatory= 0	0	1
flush

Run_FlushFIFOInt	0	EndOfFunc
BEGIN_LINE
1	1	0	2	-1	0
155	80
155	125
END_LINE
finishport

3	1	275	75	0	0	1	mandatory= 0	0	1
pop

Run_PopFIFOInt	2	EndOfFunc
BEGIN_LINE
0	1	0	3	-1	0
END_LINE
finishport

3	1	275	85	1	0	1	mandatory= 0	0	1
err

Run_PopFIFOInt	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	275	100	2	0	1	mandatory= 0	0	1
push

Run_PushFIFOInt	2	EndOfFunc
BEGIN_LINE
0	18	0	3	-1	0
END_LINE
finishport

3	1	275	110	3	0	1	mandatory= 0	0	1
err

Run_PushFIFOInt	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	275	125	4	0	1	mandatory= 0	0	1
flush

Run_FlushFIFOInt	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

ArrayReal1
_
16	0	0	0
_
_
Arrays of real value (floating point) variables can be stored in the component\nThe index must fall between 0 and the maximum size -1. No Error is generated for out of range indexes.
ArrayReal1
_
65	195	165	292
1	0
parameter
size	1	2	1024	1024
EndOfValues
EndOfLabels
Memory allocated for array

parameter
default value	2	_	_	NaN
EndOfValues
EndOfLabels
default value for uninitialised values

inputport

0	1	65	215	0	0	1	mandatory= 0	0	1
index

Run_ArrayRealWrite	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	65	250	1	0	1	mandatory= 0	0	1
index

Run_ArrayRealRead	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	2	65	225	2	0	1	mandatory= 0	0	1
data

Run_ArrayRealWrite	1	EndOfFunc
BEGIN_LINE
1	16	0	0	-1	0
205	260
205	305
30	305
30	225
END_LINE
outputport

1	2	165	260	0	0	1	mandatory= 0	0	1
data

Run_ArrayRealRead	2	EndOfFunc
BEGIN_LINE
0	16	2	1	-1	0
END_LINE
startport

2	-1	65	275	0	0	1	mandatory= 0	0	1
clear

Run_ArrayRealClear	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	65	205	1	0	1	mandatory= 0	0	1
write

Run_ArrayRealWrite	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	65	240	2	0	1	mandatory= 0	0	1
read

Run_ArrayRealRead	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	2	165	275	0	0	1	mandatory= 0	0	1
clear

Run_ArrayRealClear	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	2	165	205	1	0	1	mandatory= 0	0	1
write

Run_ArrayRealWrite	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	2	165	240	2	0	1	mandatory= 0	0	1
read

Run_ArrayRealRead	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	2	165	215	3	0	1	mandatory= 0	0	1
err

Run_ArrayRealWrite	4	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	2	165	250	4	0	1	mandatory= 0	0	1
err

Run_ArrayRealRead	4	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

buffer_fifossq
_
18	0	0	0
_
_
This is a string fifo buffer.
FIFO_String
_
220	205	320	294
1	0
parameter
Max. length	1	0	1000000	5
EndOfValues
EndOfLabels
maximum buffer length

inputport

0	3	220	280	0	0	1	mandatory= 0	0	1
data

Run_PushFIFOString	1	EndOfFunc
BEGIN_LINE
1	18	0	0	-1	0
380	280
380	195
185	195
185	280
END_LINE
outputport

1	3	320	280	0	0	1	mandatory= 0	0	1
data

Run_PopFIFOString	1	EndOfFunc
BEGIN_LINE
0	18	0	1	-1	0
END_LINE
startport

2	3	220	215	0	0	1	mandatory= 0	0	1
pop

Run_PopFIFOString	0	EndOfFunc
BEGIN_LINE
0	-1	2	2	-1	0
END_LINE
startport

2	3	220	240	1	0	1	mandatory= 0	0	1
push

Run_PushFIFOString	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	3	220	265	2	0	1	mandatory= 0	0	1
flush

Run_FlushFIFOString	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	3	320	215	0	0	1	mandatory= 0	0	1
pop

Run_PopFIFOString	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	320	225	1	0	1	mandatory= 0	0	1
err

Run_PopFIFOString	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	320	240	2	0	1	mandatory= 0	0	1
push

Run_PushFIFOString	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	320	250	3	0	1	mandatory= 0	0	1
err

Run_PushFIFOString	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	320	265	4	0	1	mandatory= 0	0	1
flush

Run_FlushFIFOString	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
END_OF_BLOCKS
