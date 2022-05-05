# How to run the code
Forked from: Bjoern Wendland


To run:
   * modify input file path in the 00_setup.sh
     - in input path location folder structure should be 
       ```
       /mc16a /mc16d /mc16e
       under this folders you can keeps samples downloaded from the grid (its fine if it the samples are in folders)

       ```
   * to change the selection for example met cut, edit the met cut in the ../include/parallelProc.C file
   * **don't forget to build by running make**
   
   `source  00_setup.sh`
   ` make`
   ` source whole_process_fake.sh` **change which selection region to use(1bgt70...)**
