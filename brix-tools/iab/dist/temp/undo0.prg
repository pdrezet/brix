CanvasSizeXY
1	1

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
105	125	105	125
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

0	1	45	80	0	0	1	mandatory= 0	0	1
period

start	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	0	45	95	1	0	1	mandatory= 0	0	1
rpt

start	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	0	45	110	2	0	1	mandatory= 0	0	1
retrig

start	3	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
startport

2	-1	45	45	0	0	1	mandatory= 0	0	1
start

start	0	EndOfFunc
BEGIN_LINE
1	2	2	2	-1	0
420	160
420	-5
40	-5
40	45
END_LINE
startport

2	0	45	60	1	0	1	mandatory= 0	0	1
stop

stop	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	0	105	75	0	0	1	mandatory= 0	0	1
clk

tick	1	EndOfFunc
BEGIN_LINE
0	2	1	3	-1	0
END_LINE
finishport

3	0	105	45	1	0	1	mandatory= 0	0	1


start	4	EndOfFunc
BEGIN_LINE
0	2	0	3	-1	0
END_LINE
finishport

3	0	105	60	2	0	1	mandatory= 0	0	1


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

time_clock
_
2	0	0	0
_
_
Creates periodic timed events.
time_clock
_
415	225	415	225
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

0	1	355	180	0	0	1	mandatory= 0	0	1
period

start	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	0	355	195	1	0	1	mandatory= 0	0	1
rpt

start	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	0	355	210	2	0	1	mandatory= 0	0	1
retrig

start	3	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
startport

2	-1	355	145	0	0	1	mandatory= 0	0	1
start

start	0	EndOfFunc
BEGIN_LINE
1	1	1	2	-1	0
310	45
310	145
END_LINE
startport

2	0	355	160	1	0	1	mandatory= 0	0	1
stop

stop	0	EndOfFunc
BEGIN_LINE
1	1	0	2	-1	0
300	75
300	160
END_LINE
finishport

3	0	415	175	0	0	1	mandatory= 0	0	1
clk

tick	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	0	415	145	1	0	1	mandatory= 0	0	1


start	4	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	0	415	160	2	0	1	mandatory= 0	0	1


stop	1	EndOfFunc
BEGIN_LINE
0	1	0	3	-1	0
END_LINE
internalport

4	-1	0	0	0	0	0	mandatory= 0	0	1


tick	0	EndOfFunc
BEGIN_LINE
0	-1	0	4	-1	0
END_LINE
END_BLOCK
END_OF_BLOCKS
