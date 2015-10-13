#!/bin/sh

RUN=$1

LOGDIR=/afs/cern.ch/user/j/jaehyeok/work/BatchLog

cat list_$RUN.txt | while read rawfile  
do 

    PFGTUPLE=`echo $rawfile | sed 's/\//_/g' `
    PFGTUPLE=`echo $PFGTUPLE | sed 's/_eos/PFGtuple_eos/g' `
    LOGERR=`echo $PFGTUPLE | sed 's/root/err/g' `
    LOGOUT=`echo $PFGTUPLE | sed 's/root/out/g' `

    echo "bsub -q 8nh -e $LOGDIR/$LOGERR -o $LOGDIR/$LOGOUT SubmitOneJob.sh $rawfile -1 $RUN"
    bsub -q 8nh -e $LOGDIR/$LOGERR -o $LOGDIR/$LOGOUT SubmitOneJob.sh $rawfile -1 $RUN

done
