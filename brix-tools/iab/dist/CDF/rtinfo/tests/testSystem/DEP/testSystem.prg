CanvasSizeXY
2210	2420

IconData
BEGIN_BLOCK

rtinfo
_
3	0	0	0
_
_
Device ID: MAC address, Network Address: IP addr, SODL Type: SODL format version, SODL name: Name of application,
RuntimeInfo
_
385	525	485	724
1	0
outputport

1	3	485	550	3	0	1	mandatory= 0	0	1
Device ID

getstat	1	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	485	565	2	0	1	mandatory= 0	0	1
RAM (KB)

getstat	2	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	485	580	9	0	1	mandatory= 0	0	1
Storage (KB)

getstat	3	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	3	485	595	6	0	1	mandatory= 0	0	1
EHS version

getstat	4	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	3	485	610	4	0	1	mandatory= 0	0	1
ModuleList

getstat	5	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	3	485	625	5	0	1	mandatory= 0	0	1
Install Dir

getstat	6	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	3	485	660	6	0	1	mandatory= 0	0	1
IP Addre

getdyn	1	EndOfFunc
BEGIN_LINE
0	20	5	1	-1	0
END_LINE
outputport

1	1	485	675	7	0	1	mandatory= 0	0	1
RAM Avail (KB)

getdyn	2	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	485	690	8	0	1	mandatory= 0	0	1
Stor Avail (KB)

getdyn	3	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	485	705	1	0	1	mandatory= 0	0	1
CPU

getdyn	4	EndOfFunc
BEGIN_LINE
0	21	5	1	-1	0
END_LINE
startport

2	-1	385	535	0	0	0	mandatory= 0	0	1
GetSatic

getstat	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	385	645	0	0	0	mandatory= 0	0	1
GetDynamic

getdyn	0	EndOfFunc
BEGIN_LINE
1	10	5	2	-1	0
380	335
380	645
END_LINE
finishport

3	3	485	535	1	0	1	mandatory= 0	0	1


getstat	7	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	-1	485	645	0	0	1	mandatory= 0	0	1


getdyn	5	EndOfFunc
BEGIN_LINE
0	21	4	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

system_exec
_
4	0	0	0
_
_
This function block runs the executable specified by the parameter with the arguments specified by the input. It outputs the output of the executable
Exec
_
390	735	440	780
1	0
parameter
Executable	3	_	_	_
EndOfValues
EndOfLabels
The executable to run

inputport

0	3	390	765	0	0	1	mandatory= 0	0	1
args

run	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
outputport

1	3	440	765	0	0	1	mandatory= 0	0	1
out

run	2	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
startport

2	3	390	745	0	0	1	mandatory= 0	0	1


run	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	3	440	745	0	0	1	mandatory= 0	0	1


run	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

wall_clock
_
5	0	0	0
_
_
CSets and Retrieves the current system time.
wall_clock
_
385	795	489	916
1	0
inputport

0	3	385	880	0	0	1	mandatory= 0	0	1
time

set	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
outputport

1	3	490	820	0	0	1	mandatory= 0	0	1
Date String

get	1	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	490	835	1	0	1	mandatory= 0	0	1
Mins 1970

get	2	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	490	850	2	0	1	mandatory= 0	0	1
& secs

get	3	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
startport

2	3	385	805	1	0	1	mandatory= 0	0	1
get

get	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	3	385	865	1	0	1	mandatory= 0	0	1
set

set	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	3	490	805	0	0	1	mandatory= 0	0	1
------

get	4	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	490	835	1	0	1	mandatory= 0	0	1
-----

set	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

const_s1
_
9	0	0	0
_
_
This is a string constant.
Constant_String1
_
10	455	110	500
1	0
parameter
String Constant	3	_	_	test
EndOfValues
EndOfLabels
string constant

outputport

1	3	110	485	0	0	1	mandatory= 0	0	1


Run_ConstantString	1	EndOfFunc
BEGIN_LINE
0	10	5	1	-1	0
END_LINE
internalport

4	-1	0	0	0	0	0	mandatory= 0	0	1


Run_ConstantString	0	EndOfFunc
BEGIN_LINE
0	-1	0	4	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

gui_text_string2
_
10	0	0	0
test
_
This widget displays an string to the GUI output.
gui_text_string2
_
245	275	345	449
1	0
parameter
Widget Tag	5	_	_	test
EndOfValues
EndOfLabels
widget tag

parameter
Widget-Group	4	_	_	default
EndOfValues
EndOfLabels
widget group

inputport

0	1	245	380	0	0	1	mandatory= 0	0	1
off.x

update	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	245	390	1	0	1	mandatory= 0	0	1
off.y

update	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	245	400	2	0	1	mandatory= 0	0	1
wid

update	3	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	245	410	3	0	1	mandatory= 0	0	1
ht

update	4	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	245	425	4	0	1	mandatory= 0	0	1
alpha

update	5	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	3	245	440	5	0	1	mandatory= 0	0	1
data

update	6	EndOfFunc
BEGIN_LINE
1	9	0	0	-1	0
185	485
185	440
END_LINE
outputport

1	1	345	380	0	0	1	mandatory= 0	0	1
abs x

create	1	update	7	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	345	390	1	0	1	mandatory= 0	0	1
abs y

create	2	update	8	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	345	400	2	0	1	mandatory= 0	0	1
wid

create	3	update	9	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	345	410	3	0	1	mandatory= 0	0	1
ht

create	4	update	10	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
startport

2	-1	245	285	0	1	0	mandatory= 0	0	1
create

create	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	245	295	1	0	0	mandatory= 0	0	1
destroy

destroy	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	245	310	2	1	0	mandatory= 0	0	1
show

show	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	245	320	3	0	0	mandatory= 0	0	1
hide

hide	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	245	365	4	1	0	mandatory= 0	0	1
update

update	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	1	345	285	0	0	1	mandatory= 0	0	1
--

create	5	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	345	295	1	0	1	mandatory= 0	0	1
--

destroy	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	345	310	2	0	1	mandatory= 0	0	1
--

show	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	345	320	3	0	1	mandatory= 0	0	1
--

hide	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	345	365	4	0	1	mandatory= 0	0	1
--

update	11	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	345	335	5	0	1	mandatory= 0	0	1
click

create	6	EndOfFunc
BEGIN_LINE
0	1	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

gui_text_string2
_
20	0	0	0
output
_
This widget displays an string to the GUI output.
gui_text_string2
_
650	295	750	469
1	0
parameter
Widget Tag	5	_	_	output
EndOfValues
EndOfLabels
widget tag

parameter
Widget-Group	4	_	_	default
EndOfValues
EndOfLabels
widget group

inputport

0	1	650	400	0	0	1	mandatory= 0	0	1
off.x

update	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	650	410	1	0	1	mandatory= 0	0	1
off.y

update	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	650	420	2	0	1	mandatory= 0	0	1
wid

update	3	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	650	430	3	0	1	mandatory= 0	0	1
ht

update	4	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	650	445	4	0	1	mandatory= 0	0	1
alpha

update	5	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	3	650	460	5	0	1	mandatory= 0	0	1
data

update	6	EndOfFunc
BEGIN_LINE
1	3	6	0	-1	0
590	660
590	460
END_LINE
outputport

1	1	750	400	0	0	1	mandatory= 0	0	1
abs x

create	1	update	7	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	750	410	1	0	1	mandatory= 0	0	1
abs y

create	2	update	8	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	750	420	2	0	1	mandatory= 0	0	1
wid

create	3	update	9	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	750	430	3	0	1	mandatory= 0	0	1
ht

create	4	update	10	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
startport

2	-1	650	305	0	1	0	mandatory= 0	0	1
create

create	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	650	315	1	0	0	mandatory= 0	0	1
destroy

destroy	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	650	330	2	1	0	mandatory= 0	0	1
show

show	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	650	340	3	0	0	mandatory= 0	0	1
hide

hide	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	650	385	4	0	0	mandatory= 0	0	1
update

update	0	EndOfFunc
BEGIN_LINE
1	3	1	2	-1	0
605	645
605	385
END_LINE
finishport

3	1	750	305	0	0	1	mandatory= 0	0	1
--

create	5	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	750	315	1	0	1	mandatory= 0	0	1
--

destroy	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	750	330	2	0	1	mandatory= 0	0	1
--

show	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	750	340	3	0	1	mandatory= 0	0	1
--

hide	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	750	385	4	0	1	mandatory= 0	0	1
--

update	11	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	750	355	5	0	1	mandatory= 0	0	1
click

create	6	EndOfFunc
BEGIN_LINE
0	1	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

gui_text_int2
_
21	0	0	0
output2
_
This widget displays an integer to the GUI output (to save you converting to a string!).
gui_text_int2
_
720	505	820	679
1	0
parameter
Widget Tag	5	_	_	output2
EndOfValues
EndOfLabels
widget tag

parameter
Widget-Group	4	_	_	default
EndOfValues
EndOfLabels
widget group

inputport

0	1	720	610	0	0	1	mandatory= 0	0	1
off.x

update	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	720	620	1	0	1	mandatory= 0	0	1
off.y

update	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	720	630	2	0	1	mandatory= 0	0	1
wid

update	3	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	720	640	3	0	1	mandatory= 0	0	1
ht

update	4	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	720	655	4	0	1	mandatory= 0	0	1
alpha

update	5	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	720	670	5	0	1	mandatory= 0	0	1
data

update	6	EndOfFunc
BEGIN_LINE
1	3	9	0	-1	0
660	705
660	670
END_LINE
outputport

1	1	820	610	0	0	1	mandatory= 0	0	1
abs x

create	1	update	7	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	820	620	1	0	1	mandatory= 0	0	1
abs y

create	2	update	8	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	820	630	2	0	1	mandatory= 0	0	1
wid

create	3	update	9	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	820	640	3	0	1	mandatory= 0	0	1
ht

create	4	update	10	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
startport

2	-1	720	515	0	1	0	mandatory= 0	0	1
create

create	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	720	525	1	0	0	mandatory= 0	0	1
destroy

destroy	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	720	540	2	1	0	mandatory= 0	0	1
show

show	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	720	550	3	0	0	mandatory= 0	0	1
hide

hide	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	720	595	4	0	0	mandatory= 0	0	1
update

update	0	EndOfFunc
BEGIN_LINE
1	3	1	2	-1	0
675	645
675	595
END_LINE
finishport

3	1	820	515	0	0	1	mandatory= 0	0	1
--

create	5	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	820	525	1	0	1	mandatory= 0	0	1
--

destroy	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	820	540	2	0	1	mandatory= 0	0	1
--

show	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	820	550	3	0	1	mandatory= 0	0	1
--

hide	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	820	595	4	0	1	mandatory= 0	0	1
--

update	11	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	820	565	5	0	1	mandatory= 0	0	1
click

create	6	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
END_OF_BLOCKS
