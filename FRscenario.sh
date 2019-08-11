#!/bin/bash
VICTIM="testing/test2victim"
ATTACKER="FRtester"
ITERATIONS=50
TARGET="\xc7\x45\xfc\x06\x00"
function sep_line {
	echo
	echo "-------------------------"
	echo
}

function run_victim {
	echo "Initiating Victim"
	echo "Victim Mode:"
	eval $VICTIM
}

function run_attacker {
	sleep 1
	sep_line
	echo "Initiating Attacker"
	eval "$ATTACKER $VICTIM $'$TARGET' 100 $ITERATIONS"
	returnVal=$?
	if [ $returnVal -gt $ITERATIONS ]; then
		echo "Error occured"
		exit
	fi
	echo "[$returnVal/$ITERATIONS] accesses to targeted code identified"
	if [ $returnVal -gt 5 ]; then
		echo "Victim is in 'Even' mode"
	else
		echo "Victim is in 'Odd' mode"
	fi
	echo
	echo
}

echo "-------------------------"
echo
echo "Setting Flush + Reload Attack scenario"
for pid in $(ps -ef | grep $VICTIM | awk '{print $2}'); do kill -9 $pid &> /dev/null; done
sep_line
run_victim & run_attacker