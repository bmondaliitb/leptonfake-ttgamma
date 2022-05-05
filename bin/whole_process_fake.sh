#!/usr/bin/env bash
run1(){
	python3 01_starter.py --campaign $3 --nworkers 16 --selection $1 --channel $4  --stype $2
	#python3 01_starter.py --campaign $3 --nworkers 16 --selection $1 --channel mu  --stype $2
}

run2(){
	python3 02_plotter.py --merge yes --campaign $3 --nworkers 16 --selection $1 --channel $4 --stype $2
	#python3 02_plotter.py --merge yes --campaign $3  --nworkers 16 --selection $1 --channel mu --stype $2
}

run2_nomerge(){
	python3 02_plotter.py --merge no --campaign $3 --nworkers 16 --selection $1 --channel $4 --stype $2 
	#python3 02_plotter.py --merge no --campaign $3 --nworkers 16 --selection $1 --channel mu --stype $2 
}

run3(){
	python3 03_dataMCPlotter.py --merge no --campaign $3 --nworkers 16 --selection $1 --channel $4 --stype $2
	#python3 03_dataMCPlotter.py --merge no --campaign $3 --nworkers 16 --selection $1 --channel mu --stype $2 
}

DISPLAY=0
run_el(){
  #selection='4jgt1b77' #1jgt1b77
  selection='4jgt1b70' #1jgt1b77
  fake='fake'
  camp='fR2' # fR2/mc16a/mc16d/mc16e
  channel='el' # el/mu
  run1 $selection $fake $camp $channel
  run2 $selection $fake $camp $channel
  ##pushd ../ohists/fake
  #source not_merged_samples.sh
  ##popd
  #run2_nomerge $selection $fake
  run3 $selection $fake $camp $channel
}

run_mu(){
  selection='4jgt1b70' #1jgt1b77
  fake='fake'
  camp='fR2' # fR2/mc16a/mc16d/mc16e
  channel='mu' # el/mu
  run1 $selection $fake $camp $channel
  run2 $selection $fake $camp $channel
  ##pushd ../ohists/fake
  #source not_merged_samples.sh
  ##popd
  #run2_nomerge $selection $fake
  run3 $selection $fake $camp $channel
}

run_el
run_mu
