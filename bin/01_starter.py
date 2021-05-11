import sys
sys.path.append('/afs/cern.ch/work/b/bmondal/python_packages/tqdm')

import os,sys,click 
import multiprocessing as mp
from functools import partial
from tqdm.auto import tqdm
from datetime import datetime


def process(ftp, stype, campaign, selection, channel):
    os.system(f"mkdir -p ../ohists/{stype}/{campaign}/{selection}_{channel}/{ftp[1]}")
    os.system(f"mkdir -p ../logs/{stype}/{campaign}/{selection}_{channel}/{ftp[1]}")
    if "Efficiencies" in selection: 
        os.system(f"parallelProc.exe {stype} {campaign} {selection} {channel} {ftp[0]} {ftp[1]} {ftp[2]} > ../logs/{stype}/{campaign}/{selection}_{channel}/{ftp[1]}/{ftp[2]}.log 2>&1")
        #print(f"parallelProc.exe {stype} {campaign} {selection} {channel} {ftp[0]} {ftp[1]} {ftp[2]} > ../logs/{stype}/{campaign}/{selection}_{channel}/{ftp[1]}/{ftp[2]}.log 2>&1")
    else: 
        print("Currently not supported! \n Exiting.")
        sys.exit(1)
        os.system(f"parallelProc.exe {campaign} {selection} {channel} {ftp[0]} {ftp[1]} {ftp[2]} > ../logs/{selection}_{channel}/{ftp[1]}/{ftp[2]}.log 2>&1")
        
@click.command()
@click.option("--campaign", required=True, type=click.Choice(["mc16a","mc16d", "mc16e", "fR2"]), help="Specify the campaign that you want to process")
@click.option("--nworkers", default=1, required=False, help="Specify the number of workers that you want to use for processing")
@click.option("--selection", required=True,type=click.Choice(["4jgt1b70","1j1b70","1j1b701b85", "1j0b701b85","1j1b702b85"]), help="Specify the selection that you want to apply to retrieve the fake weights")
@click.option("--channel", required=True, type=click.Choice(["el","mu"]), help="Selection electron or muon channel")
@click.option("--stype", required=True, type=click.Choice(["real","fake"]), help="Process real or fake Ntuples")
def main(campaign, nworkers, selection, channel, stype):
    selection = "Efficiencies_Selection_"+selection
    campaigns = [campaign]
    if "fR2" == campaign: campaigns = ["mc16a","mc16d", "mc16e"]
    for camp in campaigns:
        print(f"Preparing run for {camp}")
        indir = os.environ["LFAKEDIR"]
        if stype == "real": indir = os.environ["REALDIR"]
        ftp = []  # files to process
        os.system(f"mkdir -p ../ohists/{stype}/{camp}/{selection}_{channel}")
        os.system(f"rm -rf ../ohists/{stype}/{camp}/{selection}_{channel}/*")
        for sample in os.listdir(f"{indir}/{camp}"):
            mcID = 0 
            if not "AllYear" in sample: mcID = int(sample.split(".")[2])
            if "grp16" in sample: mcID = 1
            if mcID==410389 or (mcID>=364522 and mcID<=364535) or (mcID>=366140 and mcID<=366154): continue
            for tfile in os.listdir(f"{indir}/{camp}/{sample}"):
                ftp.append([f"{indir}/{camp}/{sample}/{tfile}", mcID, tfile.split("_")[-1].split(".")[0]])
        now = datetime.now()
        current_time = now.strftime("%H:%M:%S")
        print(f"Finished preparation. Starting at: {current_time}".format(current_time))
        print(f"Processing {len(ftp)} files for {camp} with {nworkers} workers")
        p = mp.Pool(nworkers)
        for _ in tqdm(p.imap_unordered(partial(process, stype=stype, campaign=camp, selection=selection, channel=channel), ftp), total=len(ftp)):
            pass
        p.close()
        p.join()
        now = datetime.now()
        current_time = now.strftime("%H:%M:%S")
        print(f"Successfully finished at: {current_time}")
        print("------------------------------------------------------")
    
if __name__ == "__main__":
    main()
