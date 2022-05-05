source /cvmfs/sft.cern.ch/lcg/views/LCG_96bpython3/x86_64-centos7-gcc9-opt/setup.sh
#source /cvmfs/sft.cern.ch/lcg/views/LCG_96b/x86_64-centos7-gcc9-opt/setup.sh
#export ATLAS_STYLE_PATH=$(pwd)/../../ATLAS_Style
export ATLAS_STYLE_PATH=~/work/atlasrootstyle

#setupATLAS
#lsetup "root 6.20.06-x86_64-centos7-gcc8-opt"
#set PYTHONHOME=/usr/bin/python3
#export LFAKEDIR=~/eos/physics_analysis/tty/LeptonFakeStudy/FakeRateSamples/bjorns_way_not_merged/
#export REALDIR=~/eos/physics_analysis/tty/LeptonFakeStudy/RealRateSamples/bjorns_way_not_merged/
export LFAKEDIR=/afs/cern.ch/user/b/bmondal/ntuple_v12/lep-fakes/
export REALDIR=/afs/cern.ch/user/b/bmondal/ntuple_v12/lep-fakes/
#export TESTDIR=/ceph/groups/e4/users/bwendland/private/tqGamma_processing/tqGamma_NN_muTrackIso_23Jun20_systs/lfake
export PATH=$(pwd)/../include:$PATH 
mkdir -p ../kinDists ../ohists ../logs
