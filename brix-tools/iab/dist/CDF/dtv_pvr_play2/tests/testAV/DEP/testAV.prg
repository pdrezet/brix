CanvasSizeXY
2390	2060

IconData
BEGIN_BLOCK

dtv_pvr_play2
_
1	0	0	0
_
_
Plays local files & streams remote URLs, presents to the video viewport. \n Ports:-\nSetinput: loads the input URL and configures the decoder.\nsetpos: Plyback position in % \nsettime set playback position on seconds \nget: get the current input, position
DtvPvrPlay2
_
590	230	720	539
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

0	3	590	250	0	0	1	mandatory= 0	0	1
path/URL

setinput	1	EndOfFunc
BEGIN_LINE
1	4	0	0	-1	0
550	235
550	250
END_LINE
inputport

0	1	590	290	1	0	1	mandatory= 0	0	1
(%)

setpos	1	EndOfFunc
BEGIN_LINE
1	13	0	0	-1	0
570	330
570	290
END_LINE
inputport

0	1	590	315	2	0	1	mandatory= 0	0	1
(s)

settime	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	590	520	3	0	1	mandatory= 0	0	1
(%)

vol	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	590	440	4	0	1	mandatory= 0	0	1
off.x

setWindow	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	590	450	5	0	1	mandatory= 0	0	1
off.y

setWindow	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	590	460	6	0	1	mandatory= 0	0	1
w

setWindow	3	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	590	470	7	0	1	mandatory= 0	0	1
h

setWindow	4	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
outputport

1	3	720	250	0	0	1	mandatory= 0	0	1
meta

get	1	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	720	290	2	0	1	mandatory= 0	0	1
---info

get	2	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	720	315	4	0	1	mandatory= 0	0	1
---info

get	3	EndOfFunc
BEGIN_LINE
0	14	5	1	-1	0
END_LINE
outputport

1	1	720	405	3	0	1	mandatory= 0	0	1
length info

get	4	EndOfFunc
BEGIN_LINE
0	14	5	1	-1	0
END_LINE
outputport

1	1	720	415	1	0	1	mandatory= 0	0	1
speed info

get	5	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	720	440	5	0	1	mandatory= 0	0	1
abs x

setWindow	5	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	720	450	6	0	1	mandatory= 0	0	1
abs y

setWindow	6	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	720	460	7	0	1	mandatory= 0	0	1
w

setWindow	7	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	720	470	8	0	1	mandatory= 0	0	1
h

setWindow	8	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
startport

2	-1	590	240	0	1	1	mandatory= 0	0	1
set input

setinput	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	1	590	280	2	0	1	mandatory= 0	0	1
set pos

setpos	0	EndOfFunc
BEGIN_LINE
1	5	5	2	-1	0
530	540
530	280
END_LINE
startport

2	3	590	305	1	0	1	mandatory= 0	0	1
set time

settime	0	EndOfFunc
BEGIN_LINE
0	-1	5	2	-1	0
END_LINE
startport

2	-1	590	395	4	0	1	mandatory= 0	0	1
getinfo

get	0	EndOfFunc
BEGIN_LINE
1	26	0	2	-1	0
555	630
555	395
END_LINE
startport

2	1	590	265	5	0	1	mandatory= 0	0	1
play

play	0	EndOfFunc
BEGIN_LINE
1	24	5	2	-1	0
375	345
375	265
END_LINE
startport

2	1	590	330	4	0	1	mandatory= 0	0	1
pause

pause	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	1	590	340	6	0	1	mandatory= 0	0	1
reverse

reverse	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	1	590	350	7	0	1	mandatory= 0	0	1
faster

faster	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	1	590	360	8	0	1	mandatory= 0	0	1
slower

slower	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	1	590	370	9	0	1	mandatory= 0	0	1
stop

stop	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	1	590	510	10	0	1	mandatory= 0	0	1
setVol

vol	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	1	590	430	11	0	1	mandatory= 0	0	1
setWindow

setWindow	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	1	590	485	12	0	1	mandatory= 0	0	1
to front

toFront	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	1	590	495	13	0	1	mandatory= 0	0	1
to back

toBack	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	3	720	240	0	0	1	mandatory= 0	0	1
----------

setinput	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	720	280	1	0	1	mandatory= 0	0	1
------------

setpos	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	720	305	3	0	1	mandatory= 0	0	1
------------

settime	2	EndOfFunc
BEGIN_LINE
0	14	4	3	-1	0
END_LINE
finishport

3	1	720	395	2	0	1	mandatory= 0	0	1
----------

get	6	EndOfFunc
BEGIN_LINE
0	14	4	3	-1	0
END_LINE
finishport

3	1	720	265	4	0	1	mandatory= 0	0	1
----------

play	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	720	330	5	0	1	mandatory= 0	0	1
----------

pause	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	720	340	6	0	1	mandatory= 0	0	1
----------

reverse	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	720	350	7	0	1	mandatory= 0	0	1
----------

faster	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	720	360	8	0	1	mandatory= 0	0	1
----------

slower	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	720	370	9	0	1	mandatory= 0	0	1
----------

stop	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	720	380	10	0	1	mandatory= 0	0	1
ended

setinput	3	play	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	720	1430	11	0	1	mandatory= 0	0	1
----------

setWindow	9	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	720	485	12	0	1	mandatory= 0	0	1
----------

toFront	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	720	495	13	0	1	mandatory= 0	0	1
----------

toBack	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	720	510	14	0	1	mandatory= 0	0	1
----------

vol	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

playlist_manager
_
2	0	0	0
_
_
Manages parsing playlists and controlling media players
PlayManager
_
1020	230	1150	529
1	0
parameter
Start Behaviour	1	0	2	0
EndOfValues
EndOfLabels
0:CLEAR_ALL, 1:KEEP_EARLIERTHANNEW, 2:KEEP_ALL

inputport

0	3	1020	250	0	0	1	mandatory= 0	0	1
Playlist path

Next_Playlist	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	3	1020	415	1	0	1	mandatory= 0	0	1
URL

Got	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	3	1020	425	2	0	1	mandatory= 0	0	1
Local File

Got	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	3	1020	460	3	0	1	mandatory= 0	0	1
DL URL

Set_Paths	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	3	1020	470	4	0	1	mandatory= 0	0	1
DL local

Set_Paths	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	1020	480	5	0	1	mandatory= 0	0	1
start mode

Set_Paths	3	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	1020	285	6	0	1	mandatory= 0	0	1
ID

Started	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	1020	310	7	0	1	mandatory= 0	0	1
ID

Played	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	1020	405	8	0	1	mandatory= 0	0	1
ID

Got	3	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
outputport

1	3	1150	305	0	0	1	mandatory= 0	0	1
Media File

Tick	1	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	3	1150	250	1	0	1	mandatory= 0	0	1
Playlist path

Next_Playlist	2	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	3	1150	375	2	0	1	mandatory= 0	0	1
URL

Next_Playlist	3	Next_URL	1	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	3	1150	415	3	0	1	mandatory= 0	0	1
------------

Got	4	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	3	1150	425	4	0	1	mandatory= 0	0	1
------------

Got	5	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	3	1150	405	5	0	1	mandatory= 0	0	1
Local File

Next_Playlist	4	Next_URL	2	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	3	1150	460	6	0	1	mandatory= 0	0	1
-------------

Set_Paths	4	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	3	1150	470	7	0	1	mandatory= 0	0	1
--------------

Set_Paths	5	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	3	1150	500	8	0	1	mandatory= 0	0	1
start time

Tick	6	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	3	1150	325	9	0	1	mandatory= 0	0	1
class

Tick	2	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	3	1150	335	10	0	1	mandatory= 0	0	1
Text

Tick	3	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	3	1150	315	11	0	1	mandatory= 0	0	1
Type

Tick	4	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	1150	295	12	0	1	mandatory= 0	0	1
ID

Tick	5	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	1150	385	13	0	1	mandatory= 0	0	1
ID

Next_Playlist	5	Next_URL	3	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	3	1150	510	14	0	1	mandatory= 0	0	1
Stop time

Tick	7	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
startport

2	3	1020	240	0	0	1	mandatory= 0	0	1
New Playlist

Next_Playlist	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	3	1020	300	1	0	1	mandatory= 0	0	1
Last Ended

Played	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	3	1020	355	2	0	1	mandatory= 0	0	1
Next URL

Next_URL	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	3	1020	395	3	0	1	mandatory= 0	0	1
Got

Got	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	3	1020	450	4	0	1	mandatory= 0	0	1
Set Paths

Set_Paths	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	3	1020	275	5	0	1	mandatory= 0	0	1
Started Play

Started	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	3	1150	265	0	0	1	mandatory= 0	0	1
------------

Played	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	1150	240	1	0	1	mandatory= 0	0	1
--------------

Next_Playlist	6	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	1150	275	2	0	1	mandatory= 0	0	1
Play Now

Tick	8	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	1150	355	3	0	1	mandatory= 0	0	1
------------

Next_URL	4	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	1150	365	4	0	1	mandatory= 0	0	1
Get

Next_Playlist	7	Next_URL	5	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	1150	395	5	0	1	mandatory= 0	0	1
------------

Got	6	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	1150	450	6	0	1	mandatory= 0	0	1
------------

Set_Paths	6	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	1150	285	7	0	1	mandatory= 0	0	1
play remote

Tick	9	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	1150	490	8	0	1	mandatory= 0	0	1
Earliest

Tick	10	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
internalport

4	-1	0	0	0	0	0	mandatory= 0	0	1


Tick	0	EndOfFunc
BEGIN_LINE
0	-1	0	4	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

devman_player
_
3	0	0	0
_
_
This component provides contact with a devman server to enable the exchange of playlists and player status information. The component detects new playlists made available on the devman server, downloads them and notifies the application that it is availab
DevmanPlayer
_
1220	225	1351	564
1	0
parameter
Devman Server URL	3	_	_	_
EndOfValues
EndOfLabels
devman server url

parameter
Playlist Path	3	_	_	_
EndOfValues
EndOfLabels
playlist path

parameter
Devman Ping Period	1	1	3600	60
EndOfValues
EndOfLabels
devman ping period in seconds

parameter
Use Devman Core URL	0	_	_	1
EndOfValues
EndOfLabels
Use the URL specified by devman.url

parameter
Start on Init	0	_	_	1
EndOfValues
EndOfLabels
Start checking on init

inputport

0	3	1220	280	0	0	1	mandatory= 0	0	1
URL

changeurl	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	3	1220	320	1	0	1	mandatory= 0	0	1
plylst path

reconfigure	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	1220	335	2	0	1	mandatory= 0	0	1
update rate

reconfigure	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	1220	390	3	0	1	mandatory= 0	0	1
plylst index

trackchanged	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	3	1220	405	4	0	1	mandatory= 0	0	1
curr. media

trackchanged	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	3	1220	420	5	0	1	mandatory= 0	0	1
start time

trackchanged	3	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	1220	435	6	0	1	mandatory= 0	0	1
media duration

trackchanged	4	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	3	1220	375	7	0	1	mandatory= 0	0	1
playlist

trackchanged	5	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	1220	450	8	0	1	mandatory= 0	0	1
player state

trackchanged	6	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
outputport

1	3	1350	320	0	0	1	mandatory= 0	0	1
plylst URL

out	1	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	3	1350	340	1	0	1	mandatory= 0	0	1
media/ URL

out	2	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	3	1350	380	2	0	1	mandatory= 0	0	1
files

out	3	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	3	1350	440	3	0	1	mandatory= 0	0	1
track url

out	4	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	1350	470	4	0	1	mandatory= 0	0	1
volume

out	5	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	1350	485	5	0	1	mandatory= 0	0	1
channels

out	6	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	0	1350	515	6	0	1	mandatory= 0	0	1
on/off

out	7	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	1350	540	7	0	1	mandatory= 0	0	1
state

out	8	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	3	1350	350	8	0	1	mandatory= 0	0	1
media /path

out	9	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	3	1350	330	9	0	1	mandatory= 0	0	1
X-playlist

out	10	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	3	1350	555	10	0	1	mandatory= 0	0	1
Raw XML

out	11	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	3	1350	280	11	0	1	mandatory= 0	0	1
URL

changeurl	2	out	12	startchecking	1	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
startport

2	-1	1220	235	0	0	0	mandatory= 0	0	1
Activate

startchecking	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	1220	250	1	0	0	mandatory= 0	0	1
De-activate

stopchecking	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	1220	265	2	0	0	mandatory= 0	0	1
Set url

changeurl	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	3	1220	295	3	0	0	mandatory= 0	0	1
Config

reconfigure	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	1	1220	360	4	0	0	mandatory= 0	0	1
track info

trackchanged	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	-1	1350	235	0	0	1	mandatory= 0	0	1
------------

startchecking	2	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	-1	1350	250	1	0	1	mandatory= 0	0	1
------------

stopchecking	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	1350	265	2	0	1	mandatory= 0	0	1
------------

changeurl	3	startchecking	3	out	21	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	1350	295	3	0	1	mandatory= 0	0	1
------------

reconfigure	3	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	1350	310	4	0	1	mandatory= 0	0	1
new playlist

out	13	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	1350	370	5	0	1	mandatory= 0	0	1
rem. list

out	15	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	1350	395	6	0	1	mandatory= 0	0	1
rem. unused

out	14	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	1350	410	7	0	1	mandatory= 0	0	1
rem. all

out	16	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	1350	425	8	0	1	mandatory= 0	0	1
Override

out	17	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	3	1350	455	9	0	1	mandatory= 0	0	1
media parms

out	18	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	1350	500	10	0	1	mandatory= 0	0	1
set mute

out	19	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	0	1350	530	11	0	1	mandatory= 0	0	1
status

out	20	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
internalport

4	-1	0	0	0	0	1	mandatory= 0	0	1


out	0	EndOfFunc
BEGIN_LINE
0	-1	0	4	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

const_s1
_
4	0	0	0
_
_
This is a string constant.
Constant_String1
_
405	205	505	250
1	0
parameter
String Constant	3	_	_	../userdata/The Simpsons Movie - 1080p Trailer.mp4
EndOfValues
EndOfLabels
string constant

outputport

1	3	505	235	0	0	1	mandatory= 0	0	1


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

gui_text_string2
_
5	0	0	0
other
_
This widget displays an string to the GUI output.
gui_text_string2
_
250	480	350	654
1	0
parameter
Widget Tag	5	_	_	other
EndOfValues
EndOfLabels
widget tag

parameter
Widget-Group	4	_	_	default
EndOfValues
EndOfLabels
widget group

inputport

0	1	250	585	0	0	1	mandatory= 0	0	1
off.x

update	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	250	595	1	0	1	mandatory= 0	0	1
off.y

update	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	250	605	2	0	1	mandatory= 0	0	1
wid

update	3	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	250	615	3	0	1	mandatory= 0	0	1
ht

update	4	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	250	630	4	0	1	mandatory= 0	0	1
alpha

update	5	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	3	250	645	5	0	1	mandatory= 0	0	1
data

update	6	EndOfFunc
BEGIN_LINE
1	12	0	0	-1	0
190	570
190	645
END_LINE
outputport

1	1	350	585	0	0	1	mandatory= 0	0	1
abs x

create	1	update	7	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	350	595	1	0	1	mandatory= 0	0	1
abs y

create	2	update	8	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	350	605	2	0	1	mandatory= 0	0	1
wid

create	3	update	9	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	350	615	3	0	1	mandatory= 0	0	1
ht

create	4	update	10	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
startport

2	-1	250	490	0	1	0	mandatory= 0	0	1
create

create	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	250	500	1	0	0	mandatory= 0	0	1
destroy

destroy	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	250	515	2	1	0	mandatory= 0	0	1
show

show	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	250	525	3	0	0	mandatory= 0	0	1
hide

hide	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	250	570	4	1	0	mandatory= 0	0	1
update

update	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	1	350	490	0	0	1	mandatory= 0	0	1
--

create	5	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	350	500	1	0	1	mandatory= 0	0	1
--

destroy	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	350	515	2	0	1	mandatory= 0	0	1
--

show	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	350	525	3	0	1	mandatory= 0	0	1
--

hide	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	350	570	4	0	1	mandatory= 0	0	1
--

update	11	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	0	350	540	0	0	1	mandatory= 0	0	1
click

create	6	EndOfFunc
BEGIN_LINE
0	1	1	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

const_s1
_
12	0	0	0
_
_
This is a string constant.
Constant_String1
_
70	540	170	585
1	0
parameter
String Constant	3	_	_	OTHER
EndOfValues
EndOfLabels
string constant

outputport

1	3	170	570	0	0	1	mandatory= 0	0	1


Run_ConstantString	1	EndOfFunc
BEGIN_LINE
0	5	5	1	-1	0
END_LINE
internalport

4	-1	0	0	0	0	0	mandatory= 0	0	1


Run_ConstantString	0	EndOfFunc
BEGIN_LINE
0	-1	0	4	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

const_i1
_
13	0	0	0
_
_
This is an integer constant.
Constant_Int1
_
390	300	490	345
1	0
parameter
Integer Value	1	-2147483648	2147483647	50
EndOfValues
EndOfLabels
integer constant

outputport

1	1	490	330	0	0	1	mandatory= 0	0	1


Run_ConstantInt	1	EndOfFunc
BEGIN_LINE
0	14	5	1	-1	0
END_LINE
internalport

4	-1	0	0	0	0	0	mandatory= 0	0	1


Run_ConstantInt	0	EndOfFunc
BEGIN_LINE
0	-1	0	4	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

gui_text_int2
_
14	0	0	0
_
_
This widget displays an integer to the GUI output (to save you converting to a string!).
gui_text_int2
_
820	490	920	664
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

0	1	820	595	0	0	1	mandatory= 0	0	1
off.x

update	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	820	605	1	0	1	mandatory= 0	0	1
off.y

update	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	820	615	2	0	1	mandatory= 0	0	1
wid

update	3	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	820	625	3	0	1	mandatory= 0	0	1
ht

update	4	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	820	640	4	0	1	mandatory= 0	0	1
alpha

update	5	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	820	655	5	0	1	mandatory= 0	0	1
data

update	6	EndOfFunc
BEGIN_LINE
1	1	2	0	-1	0
760	315
760	655
END_LINE
outputport

1	1	920	595	0	0	1	mandatory= 0	0	1
abs x

create	1	update	7	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	920	605	1	0	1	mandatory= 0	0	1
abs y

create	2	update	8	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	920	615	2	0	1	mandatory= 0	0	1
wid

create	3	update	9	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	920	625	3	0	1	mandatory= 0	0	1
ht

create	4	update	10	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
startport

2	-1	820	500	0	1	0	mandatory= 0	0	1
create

create	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	820	510	1	0	0	mandatory= 0	0	1
destroy

destroy	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	820	525	2	1	0	mandatory= 0	0	1
show

show	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	820	535	3	0	0	mandatory= 0	0	1
hide

hide	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	1	820	580	3	0	0	mandatory= 0	0	1
update

update	0	EndOfFunc
BEGIN_LINE
1	1	3	2	-1	0
775	395
775	580
END_LINE
finishport

3	1	920	500	0	0	1	mandatory= 0	0	1
--

create	5	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	920	510	1	0	1	mandatory= 0	0	1
--

destroy	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	920	525	2	0	1	mandatory= 0	0	1
--

show	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	920	535	3	0	1	mandatory= 0	0	1
--

hide	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	920	580	4	0	1	mandatory= 0	0	1
--

update	11	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	920	550	5	0	1	mandatory= 0	0	1
click

create	6	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

gui_text_string2
_
24	0	0	0
play
_
This widget displays an string to the GUI output.
gui_text_string2
_
250	285	350	459
1	0
parameter
Widget Tag	5	_	_	widget4
EndOfValues
EndOfLabels
widget tag

parameter
Widget-Group	4	_	_	default
EndOfValues
EndOfLabels
widget group

inputport

0	1	250	390	0	0	1	mandatory= 0	0	1
off.x

update	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	250	400	1	0	1	mandatory= 0	0	1
off.y

update	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	250	410	2	0	1	mandatory= 0	0	1
wid

update	3	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	250	420	3	0	1	mandatory= 0	0	1
ht

update	4	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	1	250	435	4	0	1	mandatory= 0	0	1
alpha

update	5	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	3	250	450	5	0	1	mandatory= 0	0	1
data

update	6	EndOfFunc
BEGIN_LINE
1	25	0	0	-1	0
190	375
190	450
END_LINE
outputport

1	1	350	390	0	0	1	mandatory= 0	0	1
abs x

create	1	update	7	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	350	400	1	0	1	mandatory= 0	0	1
abs y

create	2	update	8	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	350	410	2	0	1	mandatory= 0	0	1
wid

create	3	update	9	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
outputport

1	1	350	420	3	0	1	mandatory= 0	0	1
ht

create	4	update	10	EndOfFunc
BEGIN_LINE
0	-1	0	1	-1	0
END_LINE
startport

2	-1	250	295	0	1	0	mandatory= 0	0	1
create

create	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	250	305	1	0	0	mandatory= 0	0	1
destroy

destroy	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	250	320	2	1	0	mandatory= 0	0	1
show

show	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	250	330	3	0	0	mandatory= 0	0	1
hide

hide	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	-1	250	375	4	1	0	mandatory= 0	0	1
update

update	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	1	350	295	0	0	1	mandatory= 0	0	1
--

create	5	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	350	305	1	0	1	mandatory= 0	0	1
--

destroy	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	350	320	2	0	1	mandatory= 0	0	1
--

show	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	350	330	3	0	1	mandatory= 0	0	1
--

hide	1	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	350	375	4	0	1	mandatory= 0	0	1
--

update	11	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	1	350	345	5	0	1	mandatory= 0	0	1
click

create	6	EndOfFunc
BEGIN_LINE
0	1	4	3	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

const_s1
_
25	0	0	0
_
_
This is a string constant.
Constant_String1
_
70	345	170	390
1	0
parameter
String Constant	3	_	_	PLAY
EndOfValues
EndOfLabels
string constant

outputport

1	3	170	375	0	0	1	mandatory= 0	0	1


Run_ConstantString	1	EndOfFunc
BEGIN_LINE
0	5	5	1	-1	0
END_LINE
internalport

4	-1	0	0	0	0	0	mandatory= 0	0	1


Run_ConstantString	0	EndOfFunc
BEGIN_LINE
0	-1	0	4	-1	0
END_LINE
END_BLOCK
BEGIN_BLOCK

time_clock
_
26	0	0	0
_
_
Creates periodic timed events.
time_clock
_
485	590	545	680
1	0
parameter
Time Interval (uSecs)	1	1	2147483647	500000
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

0	1	485	635	0	0	1	mandatory= 0	0	1
period

start	1	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	0	485	650	1	0	1	mandatory= 0	0	1
rpt

start	2	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
inputport

0	0	485	665	2	0	1	mandatory= 0	0	1
retrig

start	3	EndOfFunc
BEGIN_LINE
0	-1	0	0	-1	0
END_LINE
startport

2	-1	485	600	0	1	1	mandatory= 0	0	1
start

start	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
startport

2	0	485	615	1	0	1	mandatory= 0	0	1
stop

stop	0	EndOfFunc
BEGIN_LINE
0	-1	0	2	-1	0
END_LINE
finishport

3	1	545	630	5	0	1	mandatory= 0	0	1
clk

tick	1	EndOfFunc
BEGIN_LINE
0	1	3	3	-1	0
END_LINE
finishport

3	0	545	600	1	0	1	mandatory= 0	0	1


start	4	EndOfFunc
BEGIN_LINE
0	-1	0	3	-1	0
END_LINE
finishport

3	0	545	615	2	0	1	mandatory= 0	0	1


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
END_OF_BLOCKS
