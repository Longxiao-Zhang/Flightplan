#!/bin/bash
OUT=$1
LABEL=$2
PCAP=$3
RATES=$4

if [[ $LABEL == "" ]]; then
    echo "usage $0 OUT LABEL PCAP RATES "
    exit -1
fi

if [[ $RATES == "" ]]; then
    RATES="1 3 8 9";
fi

SHR=../../Shremote/shremote.py
CFG=cfgs/snort_cfg.yml

mkdir -p $OUT/$LABEL

run_booster () {
    python3 $SHR $CFG ${LABEL}_$1 --out $OUT/$LABEL --args="rate:$1;tcpreplay_rate:$2;loop:$3;dataplane_flags:-f;pcap_file:$PCAP" ;
    RTN=$?
    RETRIES=1
    while [[ $RTN != 0 ]]; do
        echo "Trying again... $RETRIES"
        sleep 5
        python3 $SHR $CFG ${LABEL}_$1 --out $OUT/$LABEL --args="rate:$1;tcpreplay_rate:$2;loop:$3;dataplane_flags:-f;pcap_file:$PCAP" ;
        RTN=$?
        RETRIES=$(( $RETRIES + 1 ))
    done
    echo "SUCCESS!";
    sleep 5
}

for rate in $RATES; do
	VAR_R=$(bc<<<"scale=0;$rate * 12500")
	VAR_LOOP=$(bc<<<"scale=0;$rate * 125")
	run_booster $rate $VAR_R $VAR_LOOP;
done
