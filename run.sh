#!/bin/bash

#--- This script compiles and runs the simulation -----------------------------#
#--- How to use it: -----------------------------------------------------------#
#--- run.sh -d <simulation-directory> -c <compilation-type> -------------------#

BIN="simulate"
DIRPREFIX="simulation-"
AUX=`ls simulations | grep $DIRPREFIX | tail -1 | sed -e "s/^"$DIRPREFIX"0*//"`
AUX=$((AUX+1))
AUX=`printf "%06d\n" $AUX`
SIMDIR="simulations/"$DIRPREFIX$AUX
NTHREADS=
COMPTYPE=PT   #--- See Makefile: ----------------------------------------------#
                   #--- STD: Standar compilation ------------------------------#
                   #--- FAST: With Ofast optimizations ------------------------#
                   #--- OPT: With O3 optimizations ----------------------------#
                   #--- DBG: With debug options -------------------------------#
                   #--- PT: With PThreads -------------------------------------#
                   #--- OMP: With OpenMP --------------------------------------#
                   #--- FAST_OMP: With Ofast optimizations and OpenMP ---------#
                   #--- O3_OMP: With O3 optimizations and OpenMP --------------#

while getopts "d:n:c:" o; do
case "${o}" in
		d)
			SIMDIR=$OPTARG
			;;
		c)
			COMPTYPE=$OPTARG
			;;
		\?) 
			echo "Invalid option -$OPTARG" >&2
			break
			;;
	esac
done

if [ -d $SIMDIR ]; then
	echo "Error: directory already exists"
	exit 1
elif [ $SIMDIR == "" ]; then
	echo "Error: you must define a directory"
	exit 1
fi

mkdir -p $SIMDIR
mkdir -p $SIMDIR/data
mkdir -p $SIMDIR/src
mkdir -p $SIMDIR/bin
cp src/*.py src/*.c src/*.h src/Makefile $SIMDIR/src/
make COMP_TYPE=$COMPTYPE -C $SIMDIR/src
mv $SIMDIR/src/$BIN $SIMDIR/bin/$BIN-$AUX


# ulimit -s unlimited
cd $SIMDIR/data
#time ../bin/$BIN-$AUX > out.dat &&
../bin/$BIN-$AUX 
#cat dc_e2edr*.csv > dc_e2edr.dat
#sed -i '1 i duty_cycle,mu,s,e,tau,alpha' dc_e2edr.dat
#cat dc_e2ed_*.csv > dc_e2ed.dat
#sed -i '1 i duty_cycle,mu,s,e,tau,alpha' dc_e2ed.dat
#cat tp_e2edr*.csv > tp_e2edr.dat
#sed -i '1 i transmission_power,mu,s,e,tau,alpha' tp_e2edr.dat
#cat tp_e2ed_*.csv > tp_e2ed.dat
#sed -i '1 i transmission_power,mu,s,e,tau,alpha' tp_e2ed.dat
#rm *.csv
#mv dc_e2edr.dat dc_e2edr.csv
#mv dc_e2ed.dat dc_e2ed.csv
#mv tp_e2edr.dat tp_e2edr.csv
#mv tp_e2ed.dat tp_e2ed.csv

#cat duty*.log > duty_cycle_log.dat
#sed -i '1 i duty_cycle,edr_mu,edr_e,eed_mu,eed_s,eed_e' duty_cycle_log.dat
#cat trans*.log > transmission_power_log.dat
#sed -i '1 i due_power,edr_mu,edr_e,eed_mu,eed_s,eed_e' transmission_power_log.dat
#rm *.log
#mv duty*.dat duty_cycle.log
#mv trans*.dat transmission_power.log


#python3 ../src/make_plots.py &
#python3 ../src/plot_map.py &&
#python3 ../src/validation_scripts/plot_e2edr_tp.py &&
#python3 ../src/validation_scripts/plot_e2edr_dc.py &&
#python3 ../src/validation_scripts/plot_e2ed_tp.py &&
#python3 ../src/validation_scripts/plot_e2ed_dc.py &

exit 0
