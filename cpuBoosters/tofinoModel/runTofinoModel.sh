# Run the tofino model on an input PCAP, collect the output PCAP.
K=3
H=3

INPUT_PCAP=$1
OUTPUT_PCAP=$(dirname "$INPUT_PCAP")/tofinoProcessed_$(basename "$INPUT_PCAP")

if ! [ $(id -u) = 0 ]; then
   echo "The script need to be run as root." >&2
   exit 1
fi
if [ $SUDO_USER ]; then
    real_user=$SUDO_USER
else
    real_user=$(whoami)
fi

# bring up veth pairs. 
# networkVeth = network side of cable. 
# deviceVeth = tofino side of cable.
ip link add networkVeth type veth peer name deviceVeth
sysctl net.ipv6.conf.networkVeth.disable_ipv6=1
sysctl net.ipv6.conf.deviceVeth.disable_ipv6=1
ifconfig networkVeth up promisc
ifconfig deviceVeth up promisc

# start tofino model: reads and writes to deviceVeth.
echo "starting tofino model..."
./tofinoModel deviceVeth $K $H &

# start tcpdump to collect the packets that come back into the network from the device.
echo "starting tcpdump..."
rm $OUTPUT_PCAP
tcpdump -Q in -i networkVeth -w $OUTPUT_PCAP &
sleep 1

# start tcpreplay to send input from network to device (at 1k pps).
echo "starting tcpreplay..."
tcpreplay --preload-pcap --quiet -p 1000 -i networkVeth $INPUT_PCAP
sleep 1

# cleanup
chown $real_user:$real_user $OUTPUT_PCAP
killall tcpdump
killall tofinoModel
ip link delete networkVeth

