#!/bin/bash

hdr="+-----------------------+"

CaseOfHeader()
{
        echo $hdr
        echo "+ $1 cars in $2 frame +"
}

syscall()
{
        CaseOfHeader $1 $2
        { time bin/$3 $1 $2 >/dev/null; } 2>&1 | grep real
        echo $hdr
}

cluster()
{
        syscall 2560 144 $1
        syscall 5120 144 $1
        syscall 10240 144 $1
        syscall 20480 144 $1
}

# main
echo ++++++Section of OOD+++++
cluster ood
echo ++++++Section of DOD+++++
cluster dod