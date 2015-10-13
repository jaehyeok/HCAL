#!/bin/sh

RUN=$1

LOGDIR=/afs/cern.ch/user/j/jaehyeok/work/BatchLog

cat list_PFGtuple_$RUN.txt | while read PFGTUPLE  
do 
    LOGERR=`echo $PFGTUPLE | sed 's/.root/_skim.err/g' `
    LOGOUT=`echo $PFGTUPLE | sed 's/.root/_skim.out/g' `

    EOSDIR=/eos/cms/store/user/jaehyeok/PFGtuples_run$RUN

    echo "bsub -q 1nh -e $LOGDIR/$LOGERR -o $LOGDIR/$LOGOUT SubmitOneSkim.sh $EOSDIR $PFGTUPLE $RUN"
    bsub -q 1nh -e $LOGDIR/$LOGERR -o $LOGDIR/$LOGOUT SubmitOneSkim.sh $EOSDIR $PFGTUPLE $RUN

done
