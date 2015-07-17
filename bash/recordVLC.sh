#!/bin/sh
alias vlc='/Applications/VLC.app/Contents/MacOS/VLC'
vlc -I dummy ${1} --sout=#std{'access=file,mux=mp4,dst='${2}${3}'.mp4'}