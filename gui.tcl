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
###########
#Assembler#
###########

#create frame for input file name
set filename1 ""
frame .assm -borderwidth 10
pack .assm -side top -fill x
label .assm.lbl -text "File Name:" -padx 0
entry .assm.fpath1 -width 20 -relief sunken -textvariable filename1
pack .assm.lbl -side left
pack .assm.fpath1 -side left -fill x -expand true

#create frame for assemble button
frame .assmframe -borderwidth 10
pack .assmframe -side top -fill x

#add assemble button
button .assmframe.clear1 -text Clear -command {set filename1 ""}
button .assmframe.assm -text Assemble -command assemble
pack .assmframe.assm -side right
pack .assmframe -side top -fill both -expand true
pack .assmframe.clear1 -side left

#############
#LinkerLoder#
#############

#create frame for input file name
frame .lnkldr -borderwidth 10
pack .lnkldr -side top -fill x
label .lnkldr.lbl -text "File Names:" -padx 0
entry .lnkldr.fpath2 -width 20 -relief sunken -textvariable filename2
pack .lnkldr.lbl -side left
pack .lnkldr.fpath2 -side left -fill x -expand true

#create frame for assemble button
frame .lnkldrframe -borderwidth 10
pack .lnkldrframe -side top -fill x

#add assemble button
button .lnkldrframe.clear2 -text Clear -command {set filename2 ""}
button .lnkldrframe.lnkldr -text "Link and Load" -command linknload
pack .lnkldrframe.lnkldr -side right
pack .lnkldrframe -side top -fill both -expand true
pack .lnkldrframe.clear2 -side left


###########
#Simulator#
###########

#create frame for input file name
frame .top -borderwidth 10
pack .top -side top -fill x
label .top.l -text "File Path:" -padx 0
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
button .simframe.clear3 -text Clear -command {set filepath ""}
button .simframe.simulate -text Simulate -command simulate
pack .simframe.simulate -side right
pack .simframe -side top -fill both -expand true
pack .simframe.clear3 -side left
#debug frame
frame .dframe -borderwidth 20
pack .dframe -side bottom -fill x
entry .dframe.debug -width 20 -relief groove -textvariable debug
pack .dframe.debug -side left -fill x -expand true


proc assemble {} {
    .dframe.debug insert end "-"
}

proc linknload {} {

}

proc simulate {} {
    global option
    set fname [.top.fpath get]
    set command $fname$option
    .dframe.debug insert end $command
}
 
