CanvasSizeXY
2000	2000

IconData
BEGIN_BLOCK

fs_dir_list
_
4	0	0	0
_
_
Allows a directory path to be set and outputs files contained in the directory on each get. Separate events are asserted for each type of file or directory.
FileSystemDirList1
_
305	460	405	549
1	0
parameter
Directory	3	_	_	_
EndOfValues
EndOfLabels
Media Directory

parameter
FindFiles	0	_	_	1
EndOfValues
EndOfLabels
Find Files

parameter
FindDirs	0	_	_	0
EndOfValues
EndOfLabels
Find Dirs

inputport

0	3	305	480	0	0	1	mandatory= 0	0	1
dir

set	1	EndOfFunc
BEGIN_LINE
1	16	0	0	-1	0
295	550
295	480
END_LINE
outputport

1	3	405	527	0	0	1	mandatory= 0	0	1
name

get	1	EndOfFunc
BEGIN_LINE
0	126	5	1	-1	0
END_LINE
startport

2	-1	305	470	0	1	1	mandatory= 0	0	1
set dir

set	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	305	497	2	0	1	mandatory= 0	0	1
get entry

get	0	EndOfFunc
BEGIN_LINE
1	8	5	2	-1	0
700	450
700	595
290	595
290	497
END_LINE
startport

2	3	305	538	2	0	1	mandatory= 0	0	1
reset

reset	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	3	405	470	2	0	1	mandatory= 0	0	1
Ready

set	2	EndOfFunc
BEGIN_LINE
0	9	0	3	-1	0
END_LINE
finishport

3	3	405	480	0	0	1	mandatory= 0	0	1
Error

set	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	405	497	0	0	1	mandatory= 0	0	1
file

get	2	EndOfFunc
BEGIN_LINE
0	126	4	3	-1	0
END_LINE
finishport

3	3	405	507	4	0	1	mandatory= 0	0	1
dir

get	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	405	517	1	0	1	mandatory= 0	0	1
no more

get	4	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	405	538	5	0	1	mandatory= 0	0	1
-------

reset	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

const_s1
_
6	0	0	0
_
_
This is a string constant.
Constant_String1
_
105	460	205	505
1	0
parameter
String Constant	3	_	_	/usr
EndOfValues
EndOfLabels
string constant

outputport

1	3	205	490	0	0	1	mandatory= 0	0	1


Run_ConstantString	1	EndOfFunc
BEGIN_LINE
0	1	0	1	-1	0
END_LINE
internalport

4	-1	0	0	0	0	0	mandatory= 0	0	1


Run_ConstantString	0	EndOfFunc
BEGIN_LINE
0	-1	0	4	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

trigger_counter
_
7	0	0	0
_
_
This is an event counter with reset.
EventCounter
_
460	215	510	260
1	0
outputport

1	1	510	245	0	0	1	mandatory= 0	0	1


Count	1	Reset	1	EndOfFunc
BEGIN_LINE
0	127	5	1	-1	0
END_LINE
startport

2	-1	460	225	0	0	1	mandatory= 0	0	1


Count	0	EndOfFunc
BEGIN_LINE
1	4	0	2	-1	0
455	470
455	225
END_LINE
startport

2	-1	460	245	1	0	1	mandatory= 0	0	1
rst

Reset	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	1	510	225	2	0	1	mandatory= 0	0	1


Count	2	Reset	2	EndOfFunc
BEGIN_LINE
0	127	4	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

gui_text_string2
_
8	0	0	0
output
_
This widget displays an string to the GUI output.
gui_text_string2
_
585	390	685	564
1	0
parameter
Widget Tag	5	_	_	dirOut
EndOfValues
EndOfLabels
widget tag

parameter
Widget-Group	4	_	_	default
EndOfValues
EndOfLabels
widget group

inputport

0	1	585	495	0	0	1	mandatory= 0	0	1
off.x

update	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	585	505	1	0	1	mandatory= 0	0	1
off.y

update	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	585	515	2	0	1	mandatory= 0	0	1
wid

update	3	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	585	525	3	0	1	mandatory= 0	0	1
ht

update	4	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	585	540	4	0	1	mandatory= 0	0	1
alpha

update	5	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	3	585	555	5	0	1	mandatory= 0	0	1
data

update	6	EndOfFunc
BEGIN_LINE
1	4	0	0	-1	0
525	527
525	555
END_LINE
outputport

1	1	685	495	0	0	1	mandatory= 0	0	1
abs x

create	1	update	7	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	685	505	1	0	1	mandatory= 0	0	1
abs y

create	2	update	8	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	685	515	2	0	1	mandatory= 0	0	1
wid

create	3	update	9	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	685	525	3	0	1	mandatory= 0	0	1
ht

create	4	update	10	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
startport

2	-1	585	400	0	1	0	mandatory= 0	0	1
create

create	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	585	410	1	0	0	mandatory= 0	0	1
destroy

destroy	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	585	425	2	1	0	mandatory= 0	0	1
show

show	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	585	435	3	0	0	mandatory= 0	0	1
hide

hide	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	585	480	3	0	0	mandatory= 0	0	1
update

update	0	EndOfFunc
BEGIN_LINE
1	4	2	2	-1	0
540	497
540	480
END_LINE
finishport

3	1	685	400	0	0	1	mandatory= 0	0	1
--

create	5	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	685	410	1	0	1	mandatory= 0	0	1
--

destroy	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	685	425	2	0	1	mandatory= 0	0	1
--

show	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	685	435	3	0	1	mandatory= 0	0	1
--

hide	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	685	480	4	0	1	mandatory= 0	0	1
--

update	11	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	685	450	5	0	1	mandatory= 0	0	1
click

create	6	EndOfFunc
BEGIN_LINE
0	2	1	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

gui_text_int2
_
9	0	0	0
setDir
_
This widget displays an integer to the GUI output (to save you converting to a string!).
gui_text_int2
_
575	105	675	279
1	0
parameter
Widget Tag	5	_	_	setDir
EndOfValues
EndOfLabels
widget tag

parameter
Widget-Group	4	_	_	default
EndOfValues
EndOfLabels
widget group

inputport

0	1	575	210	0	0	1	mandatory= 0	0	1
off.x

update	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	575	220	1	0	1	mandatory= 0	0	1
off.y

update	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	575	230	2	0	1	mandatory= 0	0	1
wid

update	3	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	575	240	3	0	1	mandatory= 0	0	1
ht

update	4	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	575	255	4	0	1	mandatory= 0	0	1
alpha

update	5	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	575	270	5	0	1	mandatory= 0	0	1
data

update	6	EndOfFunc
BEGIN_LINE
1	7	0	0	-1	0
515	245
515	270
END_LINE
outputport

1	1	675	210	0	0	1	mandatory= 0	0	1
abs x

create	1	update	7	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	675	220	1	0	1	mandatory= 0	0	1
abs y

create	2	update	8	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	675	230	2	0	1	mandatory= 0	0	1
wid

create	3	update	9	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	675	240	3	0	1	mandatory= 0	0	1
ht

create	4	update	10	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
startport

2	-1	575	115	0	1	0	mandatory= 0	0	1
create

create	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	575	125	1	0	0	mandatory= 0	0	1
destroy

destroy	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	575	140	2	1	0	mandatory= 0	0	1
show

show	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	575	150	3	0	0	mandatory= 0	0	1
hide

hide	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	575	195	4	0	0	mandatory= 0	0	1
update

update	0	EndOfFunc
BEGIN_LINE
1	7	0	2	-1	0
530	225
530	195
END_LINE
finishport

3	1	675	115	0	0	1	mandatory= 0	0	1
--

create	5	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	675	125	1	0	1	mandatory= 0	0	1
--

destroy	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	675	140	2	0	1	mandatory= 0	0	1
--

show	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	675	150	3	0	1	mandatory= 0	0	1
--

hide	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	675	195	4	0	1	mandatory= 0	0	1
--

update	11	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	675	165	5	0	1	mandatory= 0	0	1
click

create	6	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

const_s1
_
16	0	0	0
_
_
This is a string constant.
Constant_String1
_
110	520	210	565
1	0
parameter
String Constant	3	_	_	deleteMe
EndOfValues
EndOfLabels
string constant

outputport

1	3	210	550	0	0	1	mandatory= 0	0	1


Run_ConstantString	1	EndOfFunc
BEGIN_LINE
0	1	0	1	-1	0
END_LINE
internalport

4	-1	0	0	0	0	0	mandatory= 0	0	1


Run_ConstantString	0	EndOfFunc
BEGIN_LINE
0	-1	0	4	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

fs_dir_create_remove
_
17	0	0	0
_
_
Allows a directory to be created or removed. Parametes available to allow complete removal of internal data too.
FileSystemDirCreateRemove
_
305	355	405	444
1	0
parameter
Directory	3	_	_	_
EndOfValues
EndOfLabels
Media Directory

parameter
EmptyOnly	0	_	_	1
EndOfValues
EndOfLabels
Remove contents only

inputport

0	3	305	375	0	0	1	mandatory= 0	0	1
path

create	1	remove	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
startport

2	-1	305	365	0	0	1	mandatory= 0	0	1
create

create	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	3	305	392	1	0	1	mandatory= 0	0	1
remove

remove	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	3	405	365	0	0	1	mandatory= 0	0	1
created

create	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	405	375	1	0	1	mandatory= 0	0	1
error

create	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	405	392	2	0	1	mandatory= 0	0	1
removed

remove	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	405	402	3	0	1	mandatory= 0	0	1
error

remove	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
END_OF_BLOCKS
