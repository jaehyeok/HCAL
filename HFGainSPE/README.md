Code for measuring SPE gain 
=== 

There are two steps 

(1) Extract information from EDM 

```
$ ./runOnUxc.sh [RUN NUMBER]  
$ cmsRun run_[RUN NUMBER]_cfg.py
```

As the arguments shows, it runs for one run. For the study on 28 Aug 2015, I manually put one more file in the config file after making the config file. 

(2) Fit and extract gain (+ other information)  

```
$ cd Fit
$ root -b -q SPEFit_UXC_Ana_V2.C++\([RUN NUMBER],\"test\",false,1\)  
```

Then you will have a text file and a ROOT file. 

```
Text file : SPEconstants_Run_[RUN NUMBER]_test_mode_1.txt 
ROOT file : test_mode_1.root 
```

They have the same information, but in different formats. 

Then, I used the following two scripts for further analyses :  

```
* SPESummary.C : to make summary plots 
* SPECompare.C : to make comparison between Katrinas and my result 
``` 

The gain measurement from Katrina is in the `Fit/PMTGainDB` directory.
