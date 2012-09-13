CanvasSizeXY
2070	2000

IconData
BEGIN_BLOCK

time_clock
_
1	0	0	0
_
_
Creates periodic timed events.
time_clock
_
195	80	255	170
1	0
parameter
Time Interval (uSecs)	1	1	2147483647	1000000
EndOfValues
EndOfLabels
Time interval between events.

parameter
Periodic Flag	0	_	_	1
EndOfValues
EndOfLabels
Periodic if TRUE, single delay only if FALSE.

parameter
Retriggerable Flag	0	_	_	1
EndOfValues
EndOfLabels
Retriggerable if TRUE.

inputport

0	1	195	125	0	0	1	mandatory= 0	0	1
period

start	1	EndOfFunc
BEGIN_LINE
1	5	0	0	-1	0
170	245
170	125
END_LINE
inputport

0	0	195	140	1	0	1	mandatory= 0	0	1
rpt

start	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	0	195	155	2	0	1	mandatory= 0	0	1
retrig

start	3	EndOfFunc
BEGIN_LINE
1	4	0	0	-1	0
445	120
445	20
160	20
160	155
END_LINE
startport

2	-1	195	90	0	0	1	mandatory= 0	0	1
start

start	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	0	195	105	1	0	1	mandatory= 0	0	1
stop

stop	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	0	255	120	0	0	1	mandatory= 0	0	1
clk

tick	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	0	255	90	1	0	1	mandatory= 0	0	1


start	4	EndOfFunc
BEGIN_LINE
0	4	0	3	-1	0
END_LINE
finishport

3	0	255	105	2	0	1	mandatory= 0	0	1


stop	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
internalport

4	-1	0	0	0	0	0	mandatory= 0	0	1


tick	0	EndOfFunc
BEGIN_LINE
0	-1	0	4	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

buffer_fifobbq
_
4	0	0	0
_
_
This is a boolean fifo buffer.
FIFO_Bool
_
305	45	405	134
1	0
parameter
Max. length	1	0	1000000	5
EndOfValues
EndOfLabels
maximum buffer length

inputport

0	0	305	120	0	0	1	mandatory= 0	0	1
data

Run_PushFIFOBool	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
outputport

1	0	405	120	0	0	1	mandatory= 0	0	1
data

Run_PopFIFOBool	1	EndOfFunc
BEGIN_LINE
0	1	2	1	-1	0
END_LINE
startport

2	0	305	55	0	0	1	mandatory= 0	0	1
pop

Run_PopFIFOBool	0	EndOfFunc
BEGIN_LINE
1	1	1	2	-1	0
270	90
270	55
END_LINE
startport

2	0	305	80	1	0	1	mandatory= 0	0	1
push

Run_PushFIFOBool	0	EndOfFunc
BEGIN_LINE
1	6	1	2	-1	0
280	45
280	80
END_LINE
startport

2	0	305	105	2	0	1	mandatory= 0	0	1
flush

Run_FlushFIFOBool	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	0	405	55	0	0	1	mandatory= 0	0	1
pop

Run_PopFIFOBool	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	0	405	65	1	0	1	mandatory= 0	0	1
err

Run_PopFIFOBool	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	0	405	80	2	0	1	mandatory= 0	0	1
push

Run_PushFIFOBool	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	0	405	90	3	0	1	mandatory= 0	0	1
err

Run_PushFIFOBool	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	0	405	105	4	0	1	mandatory= 0	0	1
flush

Run_FlushFIFOBool	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

buffer_fifoiiq
_
5	0	0	0
_
_
This is an integer fifo buffer.
FIFO_Int
_
40	170	140	259
1	0
parameter
Max. length	1	0	1000000	5
EndOfValues
EndOfLabels
maximum buffer length

inputport

0	1	40	245	0	0	1	mandatory= 0	0	1
data

Run_PushFIFOInt	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
outputport

1	1	140	245	0	0	1	mandatory= 0	0	1
data

Run_PopFIFOInt	1	EndOfFunc
BEGIN_LINE
0	1	0	1	-1	0
END_LINE
startport

2	1	40	180	0	0	1	mandatory= 0	0	1
pop

Run_PopFIFOInt	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	1	40	205	1	0	1	mandatory= 0	0	1
push

Run_PushFIFOInt	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	1	40	230	2	0	1	mandatory= 0	0	1
flush

Run_FlushFIFOInt	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	1	140	180	0	0	1	mandatory= 0	0	1
pop

Run_PopFIFOInt	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	140	190	1	0	1	mandatory= 0	0	1
err

Run_PopFIFOInt	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	140	205	2	0	1	mandatory= 0	0	1
push

Run_PushFIFOInt	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	140	215	3	0	1	mandatory= 0	0	1
err

Run_PushFIFOInt	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	140	230	4	0	1	mandatory= 0	0	1
flush

Run_FlushFIFOInt	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

buffer_fiforrq
_
6	0	0	0
_
_
This is a real fifo buffer.
FIFO_Real
_
30	25	130	114
1	0
parameter
Max. length	1	0	1000000	5
EndOfValues
EndOfLabels
maximum buffer length

inputport

0	2	30	100	0	0	1	mandatory= 0	0	1
data

Run_PushFIFOReal	1	EndOfFunc
BEGIN_LINE
1	6	0	0	-1	0
155	100
155	10
10	10
10	100
END_LINE
outputport

1	2	130	100	0	0	1	mandatory= 0	0	1
data

Run_PopFIFOReal	1	EndOfFunc
BEGIN_LINE
0	6	0	1	-1	0
END_LINE
startport

2	2	30	35	0	0	1	mandatory= 0	0	1
pop

Run_PopFIFOReal	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	2	30	60	1	0	1	mandatory= 0	0	1
push

Run_PushFIFOReal	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	2	30	85	2	0	1	mandatory= 0	0	1
flush

Run_FlushFIFOReal	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	2	130	35	0	0	1	mandatory= 0	0	1
pop

Run_PopFIFOReal	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	2	130	45	1	0	1	mandatory= 0	0	1
err

Run_PopFIFOReal	3	EndOfFunc
BEGIN_LINE
0	4	1	3	-1	0
END_LINE
finishport

3	2	130	60	2	0	1	mandatory= 0	0	1
push

Run_PushFIFOReal	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	2	130	70	3	0	1	mandatory= 0	0	1
err

Run_PushFIFOReal	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	2	130	85	4	0	1	mandatory= 0	0	1
flush

Run_FlushFIFOReal	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

buffer_fifossq
_
7	0	0	0
_
_
This is a string fifo buffer.
FIFO_String
_
185	185	285	274
1	0
parameter
Max. length	1	0	1000000	5
EndOfValues
EndOfLabels
maximum buffer length

inputport

0	3	185	260	0	0	1	mandatory= 0	0	1
data

Run_PushFIFOString	1	EndOfFunc
BEGIN_LINE
1	8	0	0	-1	0
465	220
465	295
160	295
160	260
END_LINE
outputport

1	3	285	260	0	0	1	mandatory= 0	0	1
data

Run_PopFIFOString	1	EndOfFunc
BEGIN_LINE
0	8	0	1	-1	0
END_LINE
startport

2	3	185	195	0	0	1	mandatory= 0	0	1
pop

Run_PopFIFOString	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	3	185	220	1	0	1	mandatory= 0	0	1
push

Run_PushFIFOString	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	3	185	245	2	0	1	mandatory= 0	0	1
flush

Run_FlushFIFOString	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	3	285	195	0	0	1	mandatory= 0	0	1
pop

Run_PopFIFOString	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	285	205	1	0	1	mandatory= 0	0	1
err

Run_PopFIFOString	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	285	220	2	0	1	mandatory= 0	0	1
push

Run_PushFIFOString	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	285	230	3	0	1	mandatory= 0	0	1
err

Run_PushFIFOString	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	285	245	4	0	1	mandatory= 0	0	1
flush

Run_FlushFIFOString	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

buffer_fifossq
_
8	0	0	0
_
_
This is a string fifo buffer.
FIFO_String
_
320	145	420	234
1	0
parameter
Max. length	1	0	1000000	5
EndOfValues
EndOfLabels
maximum buffer length

inputport

0	3	320	220	0	0	1	mandatory= 0	0	1
data

Run_PushFIFOString	1	EndOfFunc
BEGIN_LINE
1	7	0	0	-1	0
300	260
300	220
END_LINE
outputport

1	3	420	220	0	0	1	mandatory= 0	0	1
data

Run_PopFIFOString	1	EndOfFunc
BEGIN_LINE
0	7	0	1	-1	0
END_LINE
startport

2	3	320	155	0	0	1	mandatory= 0	0	1
pop

Run_PopFIFOString	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	3	320	180	1	0	1	mandatory= 0	0	1
push

Run_PushFIFOString	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	3	320	205	2	0	1	mandatory= 0	0	1
flush

Run_FlushFIFOString	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	3	420	155	0	0	1	mandatory= 0	0	1
pop

Run_PopFIFOString	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	420	165	1	0	1	mandatory= 0	0	1
err

Run_PopFIFOString	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	420	180	2	0	1	mandatory= 0	0	1
push

Run_PushFIFOString	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	420	190	3	0	1	mandatory= 0	0	1
err

Run_PushFIFOString	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	420	205	4	0	1	mandatory= 0	0	1
flush

Run_FlushFIFOString	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
END_OF_BLOCKS
