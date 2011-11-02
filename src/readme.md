# x.bee programmer for mac 

Created for a project in Smart Systems IV, semester 2, 2011 in the final semester of the Bachelor of Creative Technologies
It attempts to form the starting ground of an xbee programmer utilising xml for parameter loading 
and built on openFrameworks 007 under os x lion.

## installation

1. download and install openframeworks 007
2. move this folder to applications/(any subdirectory)/ 'move here'
3. build and run in xcode

## usage
I used a uART and xbee on serial port [0] - this can be changed in the source (havent incorporated switching just yet, its in the changelog though
Press 'spacebar' to enter command mode
Chose options onscreen
Press enter to send to xbee
You should receive an "OK" from the xbee; or ERROR ; or various results

## note 
If you need to add custom parameters and/or commands not supported JUST TYPE IT. There is a keyboard logger involved and press enter to send

## additional note
It doesnt write to firmware by default. You must add "WR" to store

## another note
Full command list can be found in the xbee datasheet

