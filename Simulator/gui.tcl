#!/usr/bin/wish

wm title . {Simulator for Swingle}

#input file pathname here
pack [labelframe .lf1 -text "Input File"]

#create frame for quit button

frame .qframe -borderwidth 10
pack .qframe -side top -fill x

#add quit button

button .qframe.quit -text Quit -command exit
pack .qframe.quit -side right
pack .qframe -side top -fill both -expand true

#create frame for input file name
frame .top -borderwidth 10
pack .top -side top -fill x
label .top.l -text "File Name:" -padx 0
entry .top.fpath -width 20 -relief sunken -textvariable filepath
pack .top.l -side left
pack .top.fpath -side left -fill x -expand true

#input mode here
labelframe .lfmode -text "Mode"
pack .lfmode -side top -fill x
set option " quiet"
pack [radiobutton .lfmode.quiet -text Quiet -value quiet -command {set option " quiet"}]
pack [radiobutton .lfmode.trace -text Trace -value "trace" -command {set option " trace"}]
pack [radiobutton .lfmode.step -text Step -value step -command {set option " step"}]
.lfmode.quiet select

#create frame for simulate button

frame .simframe -borderwidth 10
pack .simframe -side top -fill x

#add simulate button

button .simframe.simulate -text Simulate -command simulate
pack .simframe.simulate -side right
pack .simframe -side top -fill both -expand true
button .simframe.build -text Build -command build

#debug frame
frame .dframe -borderwidth 20
pack .dframe -side bottom -fill x
entry .dframe.debug -width 20 -relief groove -textvariable debug
pack .dframe.debug -side left -fill x -expand true


proc simulate {} {
    global option
    set fname [.top.fpath get]
    set command $fname$option
    .dframe.debug insert end $command
}

