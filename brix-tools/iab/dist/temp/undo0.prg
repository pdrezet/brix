CanvasSizeXY
2000	2000

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
65	30	125	120
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

0	1	65	75	0	0	1	mandatory= 0	0	1
period

start	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	0	65	90	1	0	1	mandatory= 0	0	1
rpt

start	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	0	65	105	2	0	1	mandatory= 0	0	1
retrig

start	3	EndOfFunc
BEGIN_LINE
1	3	0	0	-1	0
310	130
310	10
30	10
30	105
END_LINE
startport

2	-1	65	40	0	0	1	mandatory= 0	0	1
start

start	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	0	65	55	1	0	1	mandatory= 0	0	1
stop

stop	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	0	125	70	0	0	1	mandatory= 0	0	1
clk

tick	1	EndOfFunc
BEGIN_LINE
0	3	2	3	-1	0
END_LINE
finishport

3	0	125	40	1	0	1	mandatory= 0	0	1


start	4	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	0	125	55	2	0	1	mandatory= 0	0	1


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
3	0	0	0
_
_
This is a boolean fifo buffer.
FIFO_Bool
_
180	55	280	144
1	0
parameter
Max. length	1	0	1000000	5
EndOfValues
EndOfLabels
maximum buffer length

inputport

0	0	180	130	0	0	1	mandatory= 0	0	1
data

Run_PushFIFOBool	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
outputport

1	0	280	130	0	0	1	mandatory= 0	0	1
data

Run_PopFIFOBool	1	EndOfFunc
BEGIN_LINE
0	1	2	1	-1	0
END_LINE
startport

2	0	180	65	0	0	1	mandatory= 0	0	1
pop

Run_PopFIFOBool	0	EndOfFunc
BEGIN_LINE
1	4	4	2	-1	0
160	190
160	65
END_LINE
startport

2	0	180	90	1	0	1	mandatory= 0	0	1
push

Run_PushFIFOBool	0	EndOfFunc
BEGIN_LINE
1	4	2	2	-1	0
165	165
165	90
END_LINE
startport

2	0	180	115	2	0	1	mandatory= 0	0	1
flush

Run_FlushFIFOBool	0	EndOfFunc
BEGIN_LINE
1	1	0	2	-1	0
155	70
155	115
END_LINE
finishport

3	0	280	65	0	0	1	mandatory= 0	0	1
pop

Run_PopFIFOBool	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	0	280	75	1	0	1	mandatory= 0	0	1
err

Run_PopFIFOBool	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	0	280	90	2	0	1	mandatory= 0	0	1
push

Run_PushFIFOBool	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	0	280	100	3	0	1	mandatory= 0	0	1
err

Run_PushFIFOBool	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	0	280	115	4	0	1	mandatory= 0	0	1
flush

Run_FlushFIFOBool	1	EndOfFunc
BEGIN_LINE
0	7	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

buffer_fifossq
_
4	0	0	0
_
_
This is a string fifo buffer.
FIFO_String
_
45	130	145	219
1	0
parameter
Max. length	1	0	1000000	5
EndOfValues
EndOfLabels
maximum buffer length

inputport

0	3	45	205	0	0	1	mandatory= 0	0	1
data

Run_PushFIFOString	1	EndOfFunc
BEGIN_LINE
1	4	0	0	-1	0
160	205
160	270
25	270
25	205
END_LINE
outputport

1	3	145	205	0	0	1	mandatory= 0	0	1
data

Run_PopFIFOString	1	EndOfFunc
BEGIN_LINE
0	4	0	1	-1	0
END_LINE
startport

2	3	45	140	0	0	1	mandatory= 0	0	1
pop

Run_PopFIFOString	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	3	45	165	1	0	1	mandatory= 0	0	1
push

Run_PushFIFOString	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	3	45	190	2	0	1	mandatory= 0	0	1
flush

Run_FlushFIFOString	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	3	145	140	0	0	1	mandatory= 0	0	1
pop

Run_PopFIFOString	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	145	150	1	0	1	mandatory= 0	0	1
err

Run_PopFIFOString	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	145	165	2	0	1	mandatory= 0	0	1
push

Run_PushFIFOString	2	EndOfFunc
BEGIN_LINE
0	3	1	3	-1	0
END_LINE
finishport

3	3	145	175	3	0	1	mandatory= 0	0	1
err

Run_PushFIFOString	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	145	190	4	0	1	mandatory= 0	0	1
flush

Run_FlushFIFOString	1	EndOfFunc
BEGIN_LINE
0	3	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

buffer_fiforrq
_
5	0	0	0
_
_
This is a real fifo buffer.
FIFO_Real
_
270	200	370	289
1	0
parameter
Max. length	1	0	1000000	5
EndOfValues
EndOfLabels
maximum buffer length

inputport

0	2	270	275	0	0	1	mandatory= 0	0	1
data

Run_PushFIFOReal	1	EndOfFunc
BEGIN_LINE
1	8	0	0	-1	0
250	200
250	275
END_LINE
outputport

1	2	370	275	0	0	1	mandatory= 0	0	1
data

Run_PopFIFOReal	1	EndOfFunc
BEGIN_LINE
0	8	0	1	-1	0
END_LINE
startport

2	2	270	210	0	0	1	mandatory= 0	0	1
pop

Run_PopFIFOReal	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	2	270	235	1	0	1	mandatory= 0	0	1
push

Run_PushFIFOReal	0	EndOfFunc
BEGIN_LINE
1	8	0	2	-1	0
260	180
260	235
END_LINE
startport

2	2	270	260	2	0	1	mandatory= 0	0	1
flush

Run_FlushFIFOReal	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	2	370	210	0	0	1	mandatory= 0	0	1
pop

Run_PopFIFOReal	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	2	370	220	1	0	1	mandatory= 0	0	1
err

Run_PopFIFOReal	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	2	370	235	2	0	1	mandatory= 0	0	1
push

Run_PushFIFOReal	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	2	370	245	3	0	1	mandatory= 0	0	1
err

Run_PushFIFOReal	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	2	370	260	4	0	1	mandatory= 0	0	1
flush

Run_FlushFIFOReal	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

operator_absix
_
7	0	0	0
_
_
This is an absolute integer.
AbsInt
_
335	60	385	105
1	0
inputport

0	1	335	90	0	0	1	mandatory= 0	0	1


Run_AbsInt	1	EndOfFunc
BEGIN_LINE
1	7	0	0	-1	0
400	90
400	145
315	145
315	90
END_LINE
outputport

1	1	385	90	0	0	1	mandatory= 0	0	1


Run_AbsInt	2	EndOfFunc
BEGIN_LINE
0	7	0	1	-1	0
END_LINE
startport

2	1	335	70	0	0	1	mandatory= 0	0	1


Run_AbsInt	0	EndOfFunc
BEGIN_LINE
1	3	4	2	-1	0
300	115
300	70
END_LINE
finishport

3	1	385	70	0	0	1	mandatory= 0	0	1


Run_AbsInt	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

operator_exprx
_
8	0	0	0
_
_
This is the exponential function.
ExponentialReal
_
185	170	235	215
1	0
inputport

0	2	185	200	0	0	1	mandatory= 0	0	1


Run_ExponentialReal	1	EndOfFunc
BEGIN_LINE
1	5	0	0	-1	0
395	275
395	320
155	320
155	200
END_LINE
outputport

1	2	235	200	0	0	1	mandatory= 0	0	1


Run_ExponentialReal	2	EndOfFunc
BEGIN_LINE
0	5	0	1	-1	0
END_LINE
startport

2	2	185	180	0	0	1	mandatory= 0	0	1


Run_ExponentialReal	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	2	235	180	0	0	1	mandatory= 0	0	1


Run_ExponentialReal	3	EndOfFunc
BEGIN_LINE
0	5	1	3	-1	0
END_LINE
END_BLOCK
END_OF_BLOCKS
