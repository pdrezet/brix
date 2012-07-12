CanvasSizeXY
2050	2000

IconData
BEGIN_BLOCK

trigger_eventrstand4
_
8	0	0	0
_
_
This is a 4-input event latching AND with an internal reset.
EventSelfResetFourInputLatchingAnd
_
750	225	765	290
1	0
startport

2	-1	750	235	0	0	1	mandatory= 0	0	1


And1	0	EndOfFunc
BEGIN_LINE
1	26	3	2	-1	1
650	277
650	235
END_LINE
startport

2	-1	750	250	1	0	1	mandatory= 0	0	1


And2	0	EndOfFunc
BEGIN_LINE
1	26	0	2	-1	1
735	240
735	250
END_LINE
startport

2	-1	750	265	2	0	1	mandatory= 0	0	1


And3	0	EndOfFunc
BEGIN_LINE
1	26	4	2	-1	1
725	287
725	265
END_LINE
startport

2	-1	750	280	3	0	1	mandatory= 0	0	1


And4	0	EndOfFunc
BEGIN_LINE
1	26	5	2	-1	1
715	308
715	280
END_LINE
finishport

3	-1	765	258	0	0	1	mandatory= 0	0	1


And1	1	And2	1	And3	1	And4	1	EndOfFunc
BEGIN_LINE
0	7	2	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

trigger_eventor4
_
9	0	0	0
_
_
This is a 4-input event OR.
EventFourInputOr
_
750	310	770	376
1	0
startport

2	-1	750	320	0	0	1	mandatory= 0	0	1


Or1	0	EndOfFunc
BEGIN_LINE
1	26	1	2	-1	1
700	250
700	320
END_LINE
startport

2	-1	750	335	1	0	1	mandatory= 0	0	1


Or2	0	EndOfFunc
BEGIN_LINE
1	48	1	2	-1	1
355	285
355	410
735	410
735	335
END_LINE
startport

2	-1	750	350	2	0	1	mandatory= 0	0	1


Or3	0	EndOfFunc
BEGIN_LINE
1	61	1	2	-1	1
725	445
725	350
END_LINE
startport

2	-1	750	365	3	0	1	mandatory= 0	0	1


Or4	0	EndOfFunc
BEGIN_LINE
1	29	0	2	-1	1
715	359
715	365
END_LINE
finishport

3	-1	770	344	0	0	1	mandatory= 0	0	1


Or1	1	Or2	1	Or3	1	Or4	1	EndOfFunc
BEGIN_LINE
0	7	3	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

ENCAPSULATE2
TestStatWriter
12	1	1	0
TestStatWriter1
_
_
TestStatWriter
fs_dir_list\
850	355	932	426
1	0
startport

2	-1	844	365	0	0	1	mandatory= 0	0	1
pass

EndOfFunc
BEGIN_LINE
1	8	0	2	0	1
839	258
839	365
END_LINE
startport

2	-1	844	380	1	0	1	mandatory= 0	0	1
fail

EndOfFunc
BEGIN_LINE
1	9	0	2	1	1
829	344
829	380
END_LINE
END_BLOCK
BEGIN_BLOCK

fs_dir_list
_
26	0	0	0
_
_
Allows a directory path to be set and outputs files contained in the directory on each get. Separate events are asserted for each type of file or directory.
FileSystemDirList1
_
395	230	495	319
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

0	3	395	250	0	0	1	mandatory= 0	0	1
dir

set	1	EndOfFunc
BEGIN_LINE
1	47	0	0	-1	1
360	360
360	250
END_LINE
outputport

1	3	495	297	0	0	1	mandatory= 0	0	1
name

get	1	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
startport

2	-1	395	240	0	0	1	mandatory= 0	0	1
set dir

set	0	EndOfFunc
BEGIN_LINE
1	26	5	2	-1	1
510	308
510	253
380	253
380	240
END_LINE
startport

2	3	395	267	1	0	1	mandatory= 0	0	1
get entry

get	0	EndOfFunc
BEGIN_LINE
1	90	0	2	-1	1
550	201
550	165
370	165
370	267
END_LINE
startport

2	3	395	308	2	0	1	mandatory= 0	0	1
reset

reset	0	EndOfFunc
BEGIN_LINE
1	61	0	2	-1	1
365	435
365	308
END_LINE
finishport

3	3	495	240	0	0	1	mandatory= 0	0	1
Ready

set	2	EndOfFunc
BEGIN_LINE
0	90	0	3	-1	0
END_LINE
finishport

3	3	495	250	1	0	1	mandatory= 0	0	1
Error

set	3	EndOfFunc
BEGIN_LINE
0	9	0	3	-1	0
END_LINE
finishport

3	3	495	267	2	0	1	mandatory= 0	0	1
file

get	2	EndOfFunc
BEGIN_LINE
0	29	0	3	-1	0
END_LINE
finishport

3	3	495	277	3	0	1	mandatory= 0	0	1
dir

get	3	EndOfFunc
BEGIN_LINE
0	90	1	3	-1	0
END_LINE
finishport

3	3	495	287	4	0	1	mandatory= 0	0	1
no more

get	4	EndOfFunc
BEGIN_LINE
0	8	2	3	-1	0
END_LINE
finishport

3	3	495	308	5	0	1	mandatory= 0	0	1
-------

reset	1	EndOfFunc
BEGIN_LINE
0	8	3	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

trigger_eventor2
_
27	0	0	0
_
_
This is a 2-input event OR.
EventTwoInputOr
_
130	110	150	150
1	0
startport

2	-1	130	120	0	1	1	mandatory= 0	0	1


Or1	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	130	140	1	0	1	mandatory= 0	0	1


Or2	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	-1	150	131	0	0	1	mandatory= 0	0	1

All
Or1	1	Or2	1	EndOfFunc
BEGIN_LINE
0	26	2	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

trigger_eventor4
_
29	0	0	0
_
_
This is a 4-input event OR.
EventFourInputOr
_
640	325	660	391
1	0
startport

2	-1	640	335	0	0	1	mandatory= 0	0	1


Or1	0	EndOfFunc
BEGIN_LINE
1	26	2	2	-1	1
595	267
595	335
END_LINE
startport

2	-1	640	350	1	0	1	mandatory= 0	0	1


Or2	0	EndOfFunc
BEGIN_LINE
0	-1	3	2	-1	1
END_LINE
startport

2	-1	640	365	2	0	1	mandatory= 0	0	1


Or3	0	EndOfFunc
BEGIN_LINE
0	-1	4	2	-1	1
END_LINE
startport

2	-1	640	380	3	0	1	mandatory= 0	0	1


Or4	0	EndOfFunc
BEGIN_LINE
1	105	4	2	-1	0
605	587
605	380
END_LINE
finishport

3	-1	660	359	0	0	1	mandatory= 0	0	1


Or1	1	Or2	1	Or3	1	Or4	1	EndOfFunc
BEGIN_LINE
0	9	3	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

const_s1
_
47	0	0	0
_
_
This is a string constant.
Constant_String1
_
70	330	170	375
1	0
parameter
String Constant	3	_	_	EXIST
EndOfValues
EndOfLabels
string constant

outputport

1	3	170	360	0	0	1	mandatory= 0	0	1


Run_ConstantString	1	EndOfFunc
BEGIN_LINE
0	105	0	1	-1	0
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
48	0	0	0
_
_
Allows a directory to be created or removed. Parametes available to allow complete removal of internal data too.
FileSystemDirCreateRemove
_
235	265	335	354
1	0
parameter
Directory	3	_	_	EXIST
EndOfValues
EndOfLabels
Media Directory

parameter
EmptyOnly	0	_	_	1
EndOfValues
EndOfLabels
Remove contents only

inputport

0	3	235	285	0	0	1	mandatory= 0	0	1
path

create	1	remove	1	EndOfFunc
BEGIN_LINE
1	47	0	0	-1	1
205	360
205	285
END_LINE
startport

2	3	235	275	1	0	1	mandatory= 0	0	1
create

create	0	EndOfFunc
BEGIN_LINE
1	76	0	2	-1	1
440	376
440	321
220	321
220	275
END_LINE
startport

2	-1	235	302	0	0	1	mandatory= 0	0	1
remove

remove	0	EndOfFunc
BEGIN_LINE
1	27	0	2	-1	1
190	131
190	302
END_LINE
finishport

3	3	335	275	0	0	1	mandatory= 0	0	1
created

create	2	EndOfFunc
BEGIN_LINE
0	61	0	3	-1	0
END_LINE
finishport

3	3	335	285	1	0	1	mandatory= 0	0	1
error

create	3	EndOfFunc
BEGIN_LINE
0	9	1	3	-1	0
END_LINE
finishport

3	3	335	302	2	0	1	mandatory= 0	0	1
removed

remove	2	EndOfFunc
BEGIN_LINE
0	76	0	3	-1	0
END_LINE
finishport

3	3	335	312	3	0	1	mandatory= 0	0	1
error

remove	3	EndOfFunc
BEGIN_LINE
0	76	1	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

fs_dir_create_remove
_
61	0	0	0
_
_
Allows a directory to be created or removed. Parametes available to allow complete removal of internal data too.
FileSystemDirCreateRemove
_
230	425	330	514
1	0
parameter
Directory	3	_	_	EXIST/SOMETHING
EndOfValues
EndOfLabels
Media Directory

parameter
EmptyOnly	0	_	_	1
EndOfValues
EndOfLabels
Remove contents only

inputport

0	3	230	445	0	0	1	mandatory= 0	0	1
path

create	1	remove	1	EndOfFunc
BEGIN_LINE
1	75	0	0	-1	1
200	420
200	445
END_LINE
startport

2	-1	230	435	0	0	1	mandatory= 0	0	1
create

create	0	EndOfFunc
BEGIN_LINE
1	89	0	2	-1	1
410	491
410	420
225	420
225	435
END_LINE
startport

2	-1	230	462	0	0	1	mandatory= 0	0	1
remove

remove	0	EndOfFunc
BEGIN_LINE
1	48	0	2	-1	1
350	275
350	407
215	407
215	462
END_LINE
finishport

3	3	330	435	0	0	1	mandatory= 0	0	1
created

create	2	EndOfFunc
BEGIN_LINE
0	105	2	3	-1	0
END_LINE
finishport

3	3	330	445	1	0	1	mandatory= 0	0	1
error

create	3	EndOfFunc
BEGIN_LINE
0	9	2	3	-1	0
END_LINE
finishport

3	3	330	462	2	0	1	mandatory= 0	0	1
removed

remove	2	EndOfFunc
BEGIN_LINE
0	61	0	3	-1	0
END_LINE
finishport

3	3	330	472	3	0	1	mandatory= 0	0	1
error

remove	3	EndOfFunc
BEGIN_LINE
0	89	1	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

const_s1
_
75	0	0	0
_
_
This is a string constant.
Constant_String1
_
75	390	175	435
1	0
parameter
String Constant	3	_	_	EXIST/SOMETHING
EndOfValues
EndOfLabels
string constant

outputport

1	3	175	420	0	0	1	mandatory= 0	0	1


Run_ConstantString	1	EndOfFunc
BEGIN_LINE
0	61	0	1	-1	0
END_LINE
internalport

4	-1	0	0	0	0	0	mandatory= 0	0	1


Run_ConstantString	0	EndOfFunc
BEGIN_LINE
0	-1	0	4	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

trigger_eventor2
_
76	0	0	0
_
_
This is a 2-input event OR.
EventTwoInputOr
_
405	355	425	395
1	0
startport

2	-1	405	365	0	0	1	mandatory= 0	0	1


Or1	0	EndOfFunc
BEGIN_LINE
1	48	2	2	-1	1
385	302
385	365
END_LINE
startport

2	-1	405	385	1	0	1	mandatory= 0	0	1


Or2	0	EndOfFunc
BEGIN_LINE
1	48	3	2	-1	1
380	312
380	385
END_LINE
finishport

3	-1	425	376	0	0	1	mandatory= 0	0	1


Or1	1	Or2	1	EndOfFunc
BEGIN_LINE
0	48	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

trigger_eventor2
_
89	0	0	0
_
_
This is a 2-input event OR.
EventTwoInputOr
_
385	470	405	510
1	0
startport

2	3	385	480	1	0	1	mandatory= 0	0	1


Or1	0	EndOfFunc
BEGIN_LINE
1	61	2	2	-1	1
370	462
370	480
END_LINE
startport

2	-1	385	500	1	0	1	mandatory= 0	0	1


Or2	0	EndOfFunc
BEGIN_LINE
1	61	3	2	-1	1
365	472
365	500
END_LINE
finishport

3	-1	405	491	0	0	1	mandatory= 0	0	1


Or1	1	Or2	1	EndOfFunc
BEGIN_LINE
0	61	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

trigger_eventor2
_
90	0	0	0
_
_
This is a 2-input event OR.
EventTwoInputOr
_
515	180	535	220
1	0
startport

2	-1	515	190	0	0	1	mandatory= 0	0	1


Or1	0	EndOfFunc
BEGIN_LINE
1	26	0	2	-1	1
510	240
510	190
END_LINE
startport

2	-1	515	210	1	0	1	mandatory= 0	0	1


Or2	0	EndOfFunc
BEGIN_LINE
1	26	3	2	-1	1
500	277
499	212
END_LINE
finishport

3	-1	535	201	0	0	1	mandatory= 0	0	1


Or1	1	Or2	1	EndOfFunc
BEGIN_LINE
0	26	1	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

fs_dir_list
_
105	0	0	0
_
_
Allows a directory path to be set and outputs files contained in the directory on each get. Separate events are asserted for each type of file or directory.
FileSystemDirList1
_
485	530	585	619
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

0	3	485	550	0	0	1	mandatory= 0	0	1
dir

set	1	EndOfFunc
BEGIN_LINE
1	47	0	0	-1	1
475	360
475	550
END_LINE
outputport

1	3	585	597	0	0	1	mandatory= 0	0	1
name

get	1	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
startport

2	-1	485	540	0	0	1	mandatory= 0	0	1
set dir

set	0	EndOfFunc
BEGIN_LINE
1	105	5	2	-1	1
595	608
595	645
470	645
470	540
END_LINE
startport

2	3	485	567	1	0	1	mandatory= 0	0	1
get entry

get	0	EndOfFunc
BEGIN_LINE
1	105	0	2	-1	1
600	540
600	515
470	515
470	567
END_LINE
startport

2	3	485	608	2	0	1	mandatory= 0	0	1
reset

reset	0	EndOfFunc
BEGIN_LINE
1	61	0	2	-1	1
460	435
460	608
END_LINE
finishport

3	3	585	540	0	0	1	mandatory= 0	0	1
Ready

set	2	EndOfFunc
BEGIN_LINE
0	105	1	3	-1	0
END_LINE
finishport

3	3	585	550	1	0	1	mandatory= 0	0	1
Error

set	3	EndOfFunc
BEGIN_LINE
0	9	0	3	-1	0
END_LINE
finishport

3	3	585	567	2	0	1	mandatory= 0	0	1
file

get	2	EndOfFunc
BEGIN_LINE
0	29	0	3	-1	0
END_LINE
finishport

3	3	585	577	3	0	1	mandatory= 0	0	1
dir

get	3	EndOfFunc
BEGIN_LINE
0	90	1	3	-1	0
END_LINE
finishport

3	3	585	587	4	0	1	mandatory= 0	0	1
no more

get	4	EndOfFunc
BEGIN_LINE
0	29	3	3	-1	0
END_LINE
finishport

3	3	585	608	5	0	1	mandatory= 0	0	1
-------

reset	1	EndOfFunc
BEGIN_LINE
0	8	3	3	-1	0
END_LINE
END_BLOCK
END_OF_BLOCKS
