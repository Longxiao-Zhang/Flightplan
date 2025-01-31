#!/bin/bash

if [[ $# != 3 && $# != 4 ]]; then
    echo "Usage: $0 encoded.pcap rules_table.txt input.pcap [filter]"
    exit 1;
fi

ENCODED_PCAP=$1
RULES_TABLE=$2
INPUT_PCAP=$3
# Set to 'tcp' or 'udp' if you want only those packets considered
PROTOCOL_FILTER=$4

DELAY=3

if ! [ $(id -u) = 0 ]; then
   echo "The script need to be run as root." >&2
   exit 1
fi
if [ $SUDO_USER ]; then
    real_user=$SUDO_USER
else
    real_user=$(whoami)
fi

# run the empty booster.
FORWARD_NAME=forwardingNonbooster
DECODER_NAME=fecDecodeBooster

MAX_SPEED=2000

INPUT_BASENAME=$(basename $ENCODED_PCAP .pcap)

TEST_DIR=test_output
OUTDIR=$TEST_DIR/${INPUT_BASENAME}
mkdir -p $OUTDIR

echo Outputting to $OUTDIR

OUT_PCAP=$OUTDIR/${INPUT_BASENAME}_out.pcap
ENC_PCAP=$OUTDIR/${INPUT_BASENAME}_enc.pcap
IN_PCAP=$OUTDIR/${INPUT_BASENAME}_in.pcap
REIN_PCAP=$OUTDIR/${INPUT_BASENAME}_rein.pcap

cp $INPUT_PCAP $IN_PCAP
cp $ENCODED_PCAP $ENC_PCAP

OUT_TXT=$OUTDIR/${INPUT_BASENAME}_out.txt
IN_TXT=$OUTDIR/${INPUT_BASENAME}_in.txt

IN_SRT=$OUTDIR/sorted_in.txt
OUT_SRT=$OUTDIR/sorted_out.txt

FORWARD_OUT=$OUTDIR/forward.txt
DECODER_OUT=$OUTDIR/decoder.txt

peer_link() {
    ip link add $1 type veth peer name $2;
    sysctl net.ipv6.conf.$1.disable_ipv6=1;
    sysctl net.ipv6.conf.$2.disable_ipv6=1;
    ifconfig $1 up promisc;
    ifconfig $2 up promisc;
}

# bring up veth pairs.
# frontVeth1 = network side of cable.
# backVeth1 = booster side of cable.
peer_link frontVeth1 backVeth1
peer_link frontVeth2 backVeth2
peer_link frontVeth3 backVeth3

echo "**** STARTING $FORWARD_NAME > $FORWARD_OUT"
./$FORWARD_NAME -i backVeth1 -o frontVeth2 2> $FORWARD_OUT &
echo "**** STARTING $DECODER_NAME > $DECODER_OUT "
./$DECODER_NAME -i backVeth2 -o frontVeth3 -r $RULES_TABLE 2> $DECODER_OUT &

sleep 1
echo "Starting tcpdump to $OUT_PCAP"
rm $OUT_PCAP
tcpdump -Q in -i backVeth3 -w $OUT_PCAP &
tcpdump -Q out -i frontVeth2 -w $REIN_PCAP "$PROTOCOL_FILTER" &
sleep 1

echo "Starting tcpreplay $i of $INPUT_PCAP"
tcpreplay -p $MAX_SPEED -i frontVeth1 $ENCODED_PCAP
echo "Sleeping for $DELAY"
sleep $DELAY

# cleanup

echo "Killing everything"
killall tcpdump
killall $FORWARD_NAME
killall $DECODER_NAME

echo "Outputting encountered errors::"
grep --color=always -b1 -a1 "ERROR" $FORWARD_OUT
grep --color=always -b1 -a1 "ERROR" $DECODER_OUT
echo "Done outputting errors..."

ip link delete frontVeth1
ip link delete frontVeth2
ip link delete frontVeth3

chown $real_user:$real_user -R $TEST_DIR

tcpdump -tenr $INPUT_PCAP "$PROTOCOL_FILTER" > $IN_TXT
tcpdump -tenr $OUT_PCAP "$PROTOCOL_FILTER" > $OUT_TXT

INLINES=$(cat $IN_TXT | wc -l)
OUTLINES=$(cat $OUT_TXT | wc -l)

sort $IN_TXT > $IN_SRT
sort $OUT_TXT > $OUT_SRT

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color


if [[ $INLINES == $OUTLINES ]]; then
    echo "Input and output both contain $INLINES lines"
    echo "Running diff:"
    diff $IN_SRT $OUT_SRT
    echo "Diff complete"

    if [[ `diff $IN_SRT $OUT_SRT | wc -l` != '0' ]]; then
        echo -e ${RED}TEST FAILED${NC}
        exit 1
    else
        echo -e ${GREEN}TEST SUCCEEDED${NC}
        exit 0
    fi
else
    echo -e "Difference between input and output:\n"
    diff $IN_SRT $OUT_SRT
    echo ""

    echo "Input and output contain different number of lines!"
    echo "($INLINES and $OUTLINES)"
    echo "Check $IN_TXT $OUT_TXT to compare"
    echo -e ${RED}TEST FAILED${NC}
    exit 1
fi
