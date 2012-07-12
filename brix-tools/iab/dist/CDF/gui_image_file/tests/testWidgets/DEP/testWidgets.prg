CanvasSizeXY
2220	2040

IconData
BEGIN_BLOCK

gui_text_real2
_
1	0	0	0
_
_
This widget displays an floating point number to the GUI output (to save you converting to a string!).
gui_text_real2
_
200	25	300	199
1	0
parameter
Widget Tag	5	_	_	widget0
EndOfValues
EndOfLabels
widget tag

parameter
Widget-Group	4	_	_	default
EndOfValues
EndOfLabels
widget group

inputport

0	1	200	130	0	0	1	mandatory= 0	0	1
off.x

update	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	200	140	1	0	1	mandatory= 0	0	1
off.y

update	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	200	150	2	0	1	mandatory= 0	0	1
wid

update	3	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	200	160	3	0	1	mandatory= 0	0	1
ht

update	4	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	200	175	4	0	1	mandatory= 0	0	1
alpha

update	5	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	2	200	190	5	0	1	mandatory= 0	0	1
data

update	6	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
outputport

1	1	300	130	0	0	1	mandatory= 0	0	1
abs x

create	1	update	7	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	300	140	1	0	1	mandatory= 0	0	1
abs y

create	2	update	8	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	300	150	2	0	1	mandatory= 0	0	1
wid

create	3	update	9	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	300	160	3	0	1	mandatory= 0	0	1
ht

create	4	update	10	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
startport

2	-1	200	35	0	1	0	mandatory= 0	0	1
create

create	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	200	45	1	0	0	mandatory= 0	0	1
destroy

destroy	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	200	60	2	1	0	mandatory= 0	0	1
show

show	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	200	70	3	0	0	mandatory= 0	0	1
hide

hide	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	200	115	4	0	0	mandatory= 0	0	1
update

update	0	EndOfFunc
BEGIN_LINE
0	-1	5	2	-1	0
END_LINE
finishport

3	1	300	35	0	0	1	mandatory= 0	0	1
--

create	5	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	300	45	1	0	1	mandatory= 0	0	1
--

destroy	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	300	60	2	0	1	mandatory= 0	0	1
--

show	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	300	70	3	0	1	mandatory= 0	0	1
--

hide	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	300	115	4	0	1	mandatory= 0	0	1
--

update	11	EndOfFunc
BEGIN_LINE
0	1	4	3	-1	0
END_LINE
finishport

3	3	300	85	5	0	1	mandatory= 0	0	1
click

create	6	EndOfFunc
BEGIN_LINE
0	4	4	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

gui_patch
_
3	0	0	0
_
_
This widget displays a rectangular patch on the  GUI output.
gui_Patch
_
340	505	440	670
1	0
parameter
Widget Tag	5	_	_	widget2
EndOfValues
EndOfLabels
widget tag

parameter
Widget-Group	4	_	_	default
EndOfValues
EndOfLabels
widget group

inputport

0	1	340	610	0	0	1	mandatory= 0	0	1
off.x

update	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	340	620	1	0	1	mandatory= 0	0	1
off.y

update	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	340	630	2	0	1	mandatory= 0	0	1
wid

update	3	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	340	640	3	0	1	mandatory= 0	0	1
ht

update	4	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	340	655	4	0	1	mandatory= 0	0	1
alpha

update	5	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
outputport

1	1	440	610	0	0	1	mandatory= 0	0	1
abs x

create	1	update	6	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	440	620	1	0	1	mandatory= 0	0	1
abs y

create	2	update	7	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	440	630	2	0	1	mandatory= 0	0	1
wid

create	3	update	8	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	440	640	3	0	1	mandatory= 0	0	1
ht

create	4	update	9	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
startport

2	-1	340	515	0	1	0	mandatory= 0	0	1
create

create	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	340	525	1	0	0	mandatory= 0	0	1
destroy

destroy	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	340	540	2	1	0	mandatory= 0	0	1
show

show	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	340	550	3	0	0	mandatory= 0	0	1
hide

hide	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	340	595	4	0	0	mandatory= 0	0	1
update

update	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	1	440	515	0	0	1	mandatory= 0	0	1
--

create	5	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	440	525	1	0	1	mandatory= 0	0	1
--

destroy	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	440	540	2	0	1	mandatory= 0	0	1
--

show	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	440	550	3	0	1	mandatory= 0	0	1
--

hide	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	440	595	4	0	1	mandatory= 0	0	1
--

update	10	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	440	565	5	0	1	mandatory= 0	0	1
click

create	6	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

gui_viewport
_
4	0	0	0
viewport
_
GUI window position, size, colour and transparency. Edit parameters in IGB.
gui_viewport
_
335	720	435	885
1	0
parameter
Widget Tag	5	_	_	viewport
EndOfValues
EndOfLabels
widget tag

parameter
Widget-Group	4	_	_	default
EndOfValues
EndOfLabels
widget group

inputport

0	1	335	825	0	0	1	mandatory= 0	0	1
off.x

update	1	EndOfFunc
BEGIN_LINE
1	52	0	0	-1	0
300	830
300	805
325	805
325	825
END_LINE
inputport

0	1	335	835	1	0	1	mandatory= 0	0	1
off.y

update	2	EndOfFunc
BEGIN_LINE
1	52	0	0	-1	0
315	830
315	835
END_LINE
inputport

0	1	335	845	2	0	1	mandatory= 0	0	1
wid

update	3	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	335	855	3	0	1	mandatory= 0	0	1
ht

update	4	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	335	870	4	0	1	mandatory= 0	0	1
alpha

update	5	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
outputport

1	1	435	825	0	0	1	mandatory= 0	0	1
abs x

create	1	update	6	EndOfFunc
BEGIN_LINE
0	29	0	1	-1	0
END_LINE
outputport

1	1	435	835	1	0	1	mandatory= 0	0	1
abs y

create	2	update	7	EndOfFunc
BEGIN_LINE
0	17	5	1	-1	0
END_LINE
outputport

1	1	435	845	2	0	1	mandatory= 0	0	1
wid

create	3	update	8	EndOfFunc
BEGIN_LINE
0	26	5	1	-1	0
END_LINE
outputport

1	1	435	855	3	0	1	mandatory= 0	0	1
ht

create	4	update	9	EndOfFunc
BEGIN_LINE
0	28	5	1	-1	0
END_LINE
startport

2	-1	335	730	0	1	0	mandatory= 0	0	1
create

create	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	335	740	1	0	0	mandatory= 0	0	1
destroy

destroy	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	335	755	2	1	0	mandatory= 0	0	1
show

show	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	335	765	3	0	0	mandatory= 0	0	1
hide

hide	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	335	810	4	0	0	mandatory= 0	0	1
update

update	0	EndOfFunc
BEGIN_LINE
1	1	5	2	-1	0
315	85
315	810
END_LINE
finishport

3	1	435	730	0	0	1	mandatory= 0	0	1
--

create	5	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	435	740	1	0	1	mandatory= 0	0	1
--

destroy	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	435	755	2	0	1	mandatory= 0	0	1
--

show	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	435	765	3	0	1	mandatory= 0	0	1
--

hide	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	435	810	5	0	1	mandatory= 0	0	1
--

update	10	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	435	780	5	0	1	mandatory= 0	0	1
click

create	6	EndOfFunc
BEGIN_LINE
0	31	4	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

gui_text_int2
_
9	0	0	0
x
_
This widget displays an integer to the GUI output (to save you converting to a string!).
gui_text_int2
_
705	110	805	284
1	0
parameter
Widget Tag	5	_	_	x
EndOfValues
EndOfLabels
widget tag

parameter
Widget-Group	4	_	_	default
EndOfValues
EndOfLabels
widget group

inputport

0	1	705	200	0	0	1	mandatory= 0	0	1
x

update	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	705	215	1	0	1	mandatory= 0	0	1
y

update	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	705	230	2	0	1	mandatory= 0	0	1
wid

update	3	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	705	245	3	0	1	mandatory= 0	0	1
ht

update	4	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	705	260	4	0	1	mandatory= 0	0	1
alpha

update	5	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	705	275	5	0	1	mandatory= 0	0	1


update	6	EndOfFunc
BEGIN_LINE
1	4	0	0	-1	0
645	825
645	275
END_LINE
outputport

1	1	805	200	0	0	1	mandatory= 0	0	1
x

create	1	update	7	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	805	215	1	0	1	mandatory= 0	0	1
y

create	2	update	8	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	805	230	2	0	1	mandatory= 0	0	1
wid

create	3	update	9	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	805	245	3	0	1	mandatory= 0	0	1
ht

create	4	update	10	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
startport

2	-1	705	120	0	1	0	mandatory= 0	0	1
create

create	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	705	135	1	0	0	mandatory= 0	0	1
destroy

destroy	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	705	150	2	1	0	mandatory= 0	0	1
show

show	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	705	165	3	0	0	mandatory= 0	0	1
hide

hide	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	705	180	4	0	0	mandatory= 0	0	1
update

update	0	EndOfFunc
BEGIN_LINE
1	4	5	2	-1	0
660	780
660	180
END_LINE
finishport

3	1	805	120	0	0	1	mandatory= 0	0	1


create	5	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	805	135	1	0	1	mandatory= 0	0	1


destroy	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	805	150	2	0	1	mandatory= 0	0	1


show	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	805	165	3	0	1	mandatory= 0	0	1


hide	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	805	180	4	0	1	mandatory= 0	0	1


update	11	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	805	190	5	0	1	mandatory= 0	0	1
click

create	6	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

gui_text_int2
_
17	0	0	0
y
_
This widget displays an integer to the GUI output (to save you converting to a string!).
gui_text_int2
_
840	175	940	349
1	0
parameter
Widget Tag	5	_	_	y
EndOfValues
EndOfLabels
widget tag

parameter
Widget-Group	4	_	_	default
EndOfValues
EndOfLabels
widget group

inputport

0	1	840	265	0	0	1	mandatory= 0	0	1
x

update	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	840	280	1	0	1	mandatory= 0	0	1
y

update	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	840	295	2	0	1	mandatory= 0	0	1
wid

update	3	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	840	310	3	0	1	mandatory= 0	0	1
ht

update	4	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	840	325	4	0	1	mandatory= 0	0	1
alpha

update	5	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	840	340	5	0	1	mandatory= 0	0	1


update	6	EndOfFunc
BEGIN_LINE
1	4	1	0	-1	0
780	835
780	340
END_LINE
outputport

1	1	940	265	0	0	1	mandatory= 0	0	1
x

create	1	update	7	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	940	280	1	0	1	mandatory= 0	0	1
y

create	2	update	8	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	940	295	2	0	1	mandatory= 0	0	1
wid

create	3	update	9	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	940	310	3	0	1	mandatory= 0	0	1
ht

create	4	update	10	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
startport

2	-1	840	185	0	1	0	mandatory= 0	0	1
create

create	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	840	200	1	0	0	mandatory= 0	0	1
destroy

destroy	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	840	215	2	1	0	mandatory= 0	0	1
show

show	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	840	230	3	0	0	mandatory= 0	0	1
hide

hide	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	840	245	4	0	0	mandatory= 0	0	1
update

update	0	EndOfFunc
BEGIN_LINE
1	4	5	2	-1	0
795	780
795	245
END_LINE
finishport

3	1	940	185	0	0	1	mandatory= 0	0	1


create	5	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	940	200	1	0	1	mandatory= 0	0	1


destroy	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	940	215	2	0	1	mandatory= 0	0	1


show	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	940	230	3	0	1	mandatory= 0	0	1


hide	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	940	245	4	0	1	mandatory= 0	0	1


update	11	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	940	255	5	0	1	mandatory= 0	0	1
click

create	6	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

gui_text_int2
_
26	0	0	0
width
_
This widget displays an integer to the GUI output (to save you converting to a string!).
gui_text_int2
_
1000	230	1100	404
1	0
parameter
Widget Tag	5	_	_	width
EndOfValues
EndOfLabels
widget tag

parameter
Widget-Group	4	_	_	default
EndOfValues
EndOfLabels
widget group

inputport

0	1	1000	320	0	0	1	mandatory= 0	0	1
x

update	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	1000	335	1	0	1	mandatory= 0	0	1
y

update	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	1000	350	2	0	1	mandatory= 0	0	1
wid

update	3	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	1000	365	3	0	1	mandatory= 0	0	1
ht

update	4	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	1000	380	4	0	1	mandatory= 0	0	1
alpha

update	5	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	1000	395	5	0	1	mandatory= 0	0	1


update	6	EndOfFunc
BEGIN_LINE
1	4	2	0	-1	0
940	845
940	395
END_LINE
outputport

1	1	1100	320	0	0	1	mandatory= 0	0	1
x

create	1	update	7	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	1100	335	1	0	1	mandatory= 0	0	1
y

create	2	update	8	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	1100	350	2	0	1	mandatory= 0	0	1
wid

create	3	update	9	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	1100	365	3	0	1	mandatory= 0	0	1
ht

create	4	update	10	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
startport

2	-1	1000	240	0	1	0	mandatory= 0	0	1
create

create	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	1000	255	1	0	0	mandatory= 0	0	1
destroy

destroy	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	1000	270	2	1	0	mandatory= 0	0	1
show

show	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	1000	285	3	0	0	mandatory= 0	0	1
hide

hide	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	1000	300	4	0	0	mandatory= 0	0	1
update

update	0	EndOfFunc
BEGIN_LINE
1	4	5	2	-1	0
955	780
955	300
END_LINE
finishport

3	1	1100	240	0	0	1	mandatory= 0	0	1


create	5	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	1100	255	1	0	1	mandatory= 0	0	1


destroy	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	1100	270	2	0	1	mandatory= 0	0	1


show	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	1100	285	3	0	1	mandatory= 0	0	1


hide	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	1100	300	4	0	1	mandatory= 0	0	1


update	11	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	1100	310	5	0	1	mandatory= 0	0	1
click

create	6	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

gui_text_int2
_
28	0	0	0
height
_
This widget displays an integer to the GUI output (to save you converting to a string!).
gui_text_int2
_
1150	310	1250	484
1	0
parameter
Widget Tag	5	_	_	height
EndOfValues
EndOfLabels
widget tag

parameter
Widget-Group	4	_	_	default
EndOfValues
EndOfLabels
widget group

inputport

0	1	1150	400	0	0	1	mandatory= 0	0	1
x

update	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	1150	415	1	0	1	mandatory= 0	0	1
y

update	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	1150	430	2	0	1	mandatory= 0	0	1
wid

update	3	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	1150	445	3	0	1	mandatory= 0	0	1
ht

update	4	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	1150	460	4	0	1	mandatory= 0	0	1
alpha

update	5	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	1150	475	5	0	1	mandatory= 0	0	1


update	6	EndOfFunc
BEGIN_LINE
1	4	3	0	-1	0
1090	855
1090	475
END_LINE
outputport

1	1	1250	400	0	0	1	mandatory= 0	0	1
x

create	1	update	7	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	1250	415	1	0	1	mandatory= 0	0	1
y

create	2	update	8	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	1250	430	2	0	1	mandatory= 0	0	1
wid

create	3	update	9	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	1250	445	3	0	1	mandatory= 0	0	1
ht

create	4	update	10	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
startport

2	-1	1150	320	0	1	0	mandatory= 0	0	1
create

create	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	1150	335	1	0	0	mandatory= 0	0	1
destroy

destroy	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	1150	350	2	1	0	mandatory= 0	0	1
show

show	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	1150	365	3	0	0	mandatory= 0	0	1
hide

hide	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	1150	380	4	0	0	mandatory= 0	0	1
update

update	0	EndOfFunc
BEGIN_LINE
1	4	5	2	-1	0
1105	780
1105	380
END_LINE
finishport

3	1	1250	320	0	0	1	mandatory= 0	0	1


create	5	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	1250	335	1	0	1	mandatory= 0	0	1


destroy	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	1250	350	2	0	1	mandatory= 0	0	1


show	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	1250	365	3	0	1	mandatory= 0	0	1


hide	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	1250	380	4	0	1	mandatory= 0	0	1


update	11	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	1250	390	5	0	1	mandatory= 0	0	1
click

create	6	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

const_i1
_
30	0	0	0
_
_
This is an integer constant.
Constant_Int1
_
155	315	255	360
1	0
parameter
Integer Value	1	-2147483648	2147483647	10
EndOfValues
EndOfLabels
integer constant

outputport

1	1	255	345	0	0	1	mandatory= 0	0	1


Run_ConstantInt	1	EndOfFunc
BEGIN_LINE
0	1	0	1	-1	0
END_LINE
internalport

4	-1	0	0	0	0	0	mandatory= 0	0	1


Run_ConstantInt	0	EndOfFunc
BEGIN_LINE
0	-1	0	4	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

gui_image_file
_
31	0	0	0
_
_
Displays an image based on a filename. Use create to load new filenames dynamically.
GUI_Image_File
_
350	280	450	455
1	0
parameter
Widget Tag	5	_	_	widget7
EndOfValues
EndOfLabels
widget tag

parameter
Widget-Group	4	_	_	default
EndOfValues
EndOfLabels
widget group

inputport

0	1	350	400	0	0	1	mandatory= 0	0	1
off.x

update	1	EndOfFunc
BEGIN_LINE
1	30	0	0	-1	0
340	345
340	400
END_LINE
inputport

0	1	350	410	1	0	1	mandatory= 0	0	1
off.y

update	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	350	420	2	0	1	mandatory= 0	0	1
wid

update	3	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	350	430	3	0	1	mandatory= 0	0	1
ht

update	4	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	350	445	4	0	1	mandatory= 0	0	1
alpha

update	5	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	3	350	300	5	0	1	mandatory= 0	0	1
file

create	1	EndOfFunc
BEGIN_LINE
1	32	0	0	-1	0
290	290
290	300
END_LINE
outputport

1	1	450	400	0	0	1	mandatory= 0	0	1
abs x

create	2	update	6	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	450	410	2	0	1	mandatory= 0	0	1
abs y

create	3	update	7	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	450	420	1	0	1	mandatory= 0	0	1
wid

create	4	update	8	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	450	430	3	0	1	mandatory= 0	0	1
ht

create	5	update	9	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
startport

2	-1	350	290	0	1	0	mandatory= 0	0	1
create

create	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	350	315	1	0	0	mandatory= 0	0	1
destroy

destroy	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	350	330	2	1	0	mandatory= 0	0	1
show

show	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	350	340	3	0	0	mandatory= 0	0	1
hide

hide	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	350	385	4	0	0	mandatory= 0	0	1
update

update	0	EndOfFunc
BEGIN_LINE
1	1	5	2	-1	0
305	85
305	385
END_LINE
finishport

3	3	450	290	0	0	1	mandatory= 0	0	1
--

create	6	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	450	315	1	0	1	mandatory= 0	0	1
--

destroy	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	450	330	2	0	1	mandatory= 0	0	1
--

show	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	450	340	3	0	1	mandatory= 0	0	1
--

hide	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	450	380	4	0	1	mandatory= 0	0	1
--

update	10	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	450	355	4	0	1	mandatory= 0	0	1
click

create	7	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

const_s1
_
32	0	0	0
_
_
This is a string constant.
Constant_String1
_
150	260	250	305
1	0
parameter
String Constant	3	_	_	screenshot.jpg
EndOfValues
EndOfLabels
string constant

outputport

1	3	250	290	0	0	1	mandatory= 0	0	1


Run_ConstantString	1	EndOfFunc
BEGIN_LINE
0	31	5	1	-1	0
END_LINE
internalport

4	-1	0	0	0	0	0	mandatory= 0	0	1


Run_ConstantString	0	EndOfFunc
BEGIN_LINE
0	-1	0	4	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

gui_text_bool2
_
34	0	0	0
_
_
This widget displays an boolean to the GUI output - currently as o or 1! (to save you converting to a string!).
gui_text_bool2
_
325	30	425	204
1	0
parameter
Widget Tag	5	_	_	widget8
EndOfValues
EndOfLabels
widget tag

parameter
Widget-Group	4	_	_	default
EndOfValues
EndOfLabels
widget group

inputport

0	1	325	135	0	0	1	mandatory= 0	0	1
off.x

update	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	325	145	1	0	1	mandatory= 0	0	1
off.y

update	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	325	155	2	0	1	mandatory= 0	0	1
wid

update	3	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	325	165	3	0	1	mandatory= 0	0	1
ht

update	4	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	325	180	4	0	1	mandatory= 0	0	1
alpha

update	5	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	0	325	195	5	0	1	mandatory= 0	0	1
data

update	6	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
outputport

1	1	425	135	0	0	1	mandatory= 0	0	1
abs x

create	1	update	7	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	425	145	1	0	1	mandatory= 0	0	1
abs y

create	2	update	8	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	425	155	2	0	1	mandatory= 0	0	1
wid

create	3	update	9	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	425	165	3	0	1	mandatory= 0	0	1
ht

create	4	update	10	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
startport

2	-1	325	40	0	0	0	mandatory= 0	0	1
create

create	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	325	50	1	0	0	mandatory= 0	0	1
destroy

destroy	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	325	65	2	0	0	mandatory= 0	0	1
show

show	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	325	75	3	0	0	mandatory= 0	0	1
hide

hide	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	325	120	4	0	0	mandatory= 0	0	1
update

update	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	1	425	40	0	0	1	mandatory= 0	0	1
--

create	5	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	425	50	1	0	1	mandatory= 0	0	1
--

destroy	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	425	65	2	0	1	mandatory= 0	0	1
--

show	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	425	75	3	0	1	mandatory= 0	0	1
--

hide	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	425	120	4	0	1	mandatory= 0	0	1
--

update	11	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	425	90	5	0	1	mandatory= 0	0	1
click

create	6	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

gui_text_int2
_
36	0	0	0
_
_
This widget displays an integer to the GUI output (to save you converting to a string!).
gui_text_int2
_
450	30	550	204
1	0
parameter
Widget Tag	5	_	_	widget10
EndOfValues
EndOfLabels
widget tag

parameter
Widget-Group	4	_	_	default
EndOfValues
EndOfLabels
widget group

inputport

0	1	450	135	0	0	1	mandatory= 0	0	1
off.x

update	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	450	145	1	0	1	mandatory= 0	0	1
off.y

update	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	450	155	2	0	1	mandatory= 0	0	1
wid

update	3	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	450	165	3	0	1	mandatory= 0	0	1
ht

update	4	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	450	180	4	0	1	mandatory= 0	0	1
alpha

update	5	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	450	195	5	0	1	mandatory= 0	0	1
data

update	6	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
outputport

1	1	550	135	0	0	1	mandatory= 0	0	1
abs x

create	1	update	7	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	550	145	1	0	1	mandatory= 0	0	1
abs y

create	2	update	8	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	550	155	2	0	1	mandatory= 0	0	1
wid

create	3	update	9	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	550	165	3	0	1	mandatory= 0	0	1
ht

create	4	update	10	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
startport

2	-1	450	40	0	0	0	mandatory= 0	0	1
create

create	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	450	50	1	0	0	mandatory= 0	0	1
destroy

destroy	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	450	65	2	0	0	mandatory= 0	0	1
show

show	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	450	75	3	0	0	mandatory= 0	0	1
hide

hide	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	450	120	4	0	0	mandatory= 0	0	1
update

update	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	1	550	40	0	0	1	mandatory= 0	0	1
--

create	5	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	550	50	1	0	1	mandatory= 0	0	1
--

destroy	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	550	65	2	0	1	mandatory= 0	0	1
--

show	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	550	75	3	0	1	mandatory= 0	0	1
--

hide	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	550	120	4	0	1	mandatory= 0	0	1
--

update	11	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	550	90	5	0	1	mandatory= 0	0	1
click

create	6	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

gui_text_string2
_
37	0	0	0
_
_
This widget displays an string to the GUI output.
gui_text_string2
_
565	30	665	204
1	0
parameter
Widget Tag	5	_	_	widget11
EndOfValues
EndOfLabels
widget tag

parameter
Widget-Group	4	_	_	default
EndOfValues
EndOfLabels
widget group

inputport

0	1	565	135	0	0	1	mandatory= 0	0	1
off.x

update	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	565	145	1	0	1	mandatory= 0	0	1
off.y

update	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	565	155	2	0	1	mandatory= 0	0	1
wid

update	3	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	565	165	3	0	1	mandatory= 0	0	1
ht

update	4	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	565	180	4	0	1	mandatory= 0	0	1
alpha

update	5	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	3	565	195	5	0	1	mandatory= 0	0	1
data

update	6	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
outputport

1	1	665	135	0	0	1	mandatory= 0	0	1
abs x

create	1	update	7	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	665	145	1	0	1	mandatory= 0	0	1
abs y

create	2	update	8	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	665	155	2	0	1	mandatory= 0	0	1
wid

create	3	update	9	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	665	165	3	0	1	mandatory= 0	0	1
ht

create	4	update	10	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
startport

2	-1	565	40	0	0	0	mandatory= 0	0	1
create

create	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	565	50	1	0	0	mandatory= 0	0	1
destroy

destroy	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	565	65	2	0	0	mandatory= 0	0	1
show

show	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	565	75	3	0	0	mandatory= 0	0	1
hide

hide	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	565	120	4	0	0	mandatory= 0	0	1
update

update	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	1	665	40	0	0	1	mandatory= 0	0	1
--

create	5	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	665	50	1	0	1	mandatory= 0	0	1
--

destroy	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	665	65	2	0	1	mandatory= 0	0	1
--

show	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	665	75	3	0	1	mandatory= 0	0	1
--

hide	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	665	120	4	0	1	mandatory= 0	0	1
--

update	11	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	665	90	5	0	1	mandatory= 0	0	1
click

create	6	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

const_i1
_
52	0	0	0
_
_
This is an integer constant.
Constant_Int1
_
160	795	260	840
1	0
parameter
Integer Value	1	-2147483648	2147483647	100
EndOfValues
EndOfLabels
integer constant

outputport

1	1	260	830	0	0	1	mandatory= 0	0	1


Run_ConstantInt	1	EndOfFunc
BEGIN_LINE
0	4	1	1	-1	0
END_LINE
internalport

4	-1	0	0	0	0	0	mandatory= 0	0	1


Run_ConstantInt	0	EndOfFunc
BEGIN_LINE
0	-1	0	4	-1	0
END_LINE
END_BLOCK
END_OF_BLOCKS
