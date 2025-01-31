#!/usr/bin/env bash
#Test setup for Flightplan
#Nik Sultana, UPenn, March 2020
#
# FIXME various hardcoded paths
# FIXME this and other scripts assume that it's being run in the "Wharf" directory
# FIXME poor naming choices for tests
# NOTE based on splits/ALV_Complete_2_FW/tests.sh

export TOPOLOGY=$WHARF_REPO/splits2/ALV_Complete_All/alv_k=4.yml
START_CFG=": $WHARF_REPO/splits2/ALV_Complete_All/start2.sh"
MODES=(autotest autotest_long interactive_complete complete_fec_e2e complete_mcd_e2e interactive2_complete fwtest complete_all_e2e)
DEFAULT_MODE=autotest

if [ -z "${MODE}" ]
then
  MODE=$DEFAULT_MODE
  echo "Using default MODE from $0"
fi

function interactive_complete {
  FEC_INIT_PCAP=$WHARF_REPO/bmv2/pcaps/lldp_enable_fec.pcap
  sudo -E python $WHARF_REPO/bmv2/start_flightplan_mininet.py ${TOPOLOGY} \
          --pcap-dump $PCAP_DUMPS \
          --log $LOG_DUMPS \
          --verbose \
          --showExitStatus \
     --fg-host-prog "${START_CFG}" \
     --fg-host-prog ": tcpreplay -i dropper-eth0 ${FEC_INIT_PCAP}" \
     --fg-host-prog ": tcpreplay -i dropper-eth1 ${FEC_INIT_PCAP}" \
     --fg-host-prog ": tcpreplay -i dropper2-eth0 ${FEC_INIT_PCAP}" \
     --fg-host-prog ": tcpreplay -i dropper2-eth1 ${FEC_INIT_PCAP}" \
     --cli
}

function autotest {
  if [ -z "${NUM_PINGS}" ]
  then
    NUM_PINGS=1
  fi

  FEC_INIT_PCAP=$WHARF_REPO/bmv2/pcaps/lldp_enable_fec.pcap

  sudo -E python $WHARF_REPO/bmv2/start_flightplan_mininet.py ${TOPOLOGY} \
          --pcap-dump $PCAP_DUMPS \
          --log $LOG_DUMPS \
          --verbose \
          --showExitStatus \
     --fg-host-prog "${START_CFG}" \
     --fg-host-prog ": tcpreplay -i dropper-eth0 ${FEC_INIT_PCAP}" \
     --fg-host-prog ": tcpreplay -i dropper-eth1 ${FEC_INIT_PCAP}" \
     --fg-host-prog ": tcpreplay -i dropper2-eth0 ${FEC_INIT_PCAP}" \
     --fg-host-prog ": tcpreplay -i dropper2-eth1 ${FEC_INIT_PCAP}" \
     --fg-host-prog "p0h0: ping -c $NUM_PINGS 192.0.0.2" \
     --fg-host-prog "p0h0: ping -c $NUM_PINGS 192.0.0.3" \
     --fg-host-prog "p0h0: ping -c $NUM_PINGS 192.0.1.2" \
     --fg-host-prog "p0h0: ping -c $NUM_PINGS 192.0.1.3" \
     --fg-host-prog "p0h0: ping -c $NUM_PINGS 192.1.0.2" \
     --fg-host-prog "p0h0: ping -c $NUM_PINGS 192.1.0.3" \
     --fg-host-prog "p0h0: ping -c $NUM_PINGS 192.1.1.2" \
     --fg-host-prog "p0h0: ping -c $NUM_PINGS 192.1.1.3" \
     --fg-host-prog "p0h0: ping -c $NUM_PINGS 192.2.0.2" \
     --fg-host-prog "p0h0: ping -c $NUM_PINGS 192.2.0.3" \
     --fg-host-prog "p0h0: ping -c $NUM_PINGS 192.2.1.2" \
     --fg-host-prog "p0h0: ping -c $NUM_PINGS 192.2.1.3" \
     --fg-host-prog "p0h0: ping -c $NUM_PINGS 192.3.0.2" \
     --fg-host-prog "p0h0: ping -c $NUM_PINGS 192.3.0.3" \
     --fg-host-prog "p0h0: ping -c $NUM_PINGS 192.3.1.2" \
     --fg-host-prog "p0h0: ping -c $NUM_PINGS 192.3.1.3" \
     --fg-host-prog "p0h1: ping -c $NUM_PINGS 192.0.0.2" \
     --fg-host-prog "p0h1: ping -c $NUM_PINGS 192.0.0.3" \
     --fg-host-prog "p0h1: ping -c $NUM_PINGS 192.0.1.2" \
     --fg-host-prog "p0h1: ping -c $NUM_PINGS 192.0.1.3" \
     --fg-host-prog "p0h1: ping -c $NUM_PINGS 192.1.0.2" \
     --fg-host-prog "p0h1: ping -c $NUM_PINGS 192.1.0.3" \
     --fg-host-prog "p0h1: ping -c $NUM_PINGS 192.1.1.2" \
     --fg-host-prog "p0h1: ping -c $NUM_PINGS 192.1.1.3" \
     --fg-host-prog "p0h1: ping -c $NUM_PINGS 192.2.0.2" \
     --fg-host-prog "p0h1: ping -c $NUM_PINGS 192.2.0.3" \
     --fg-host-prog "p0h1: ping -c $NUM_PINGS 192.2.1.2" \
     --fg-host-prog "p0h1: ping -c $NUM_PINGS 192.2.1.3" \
     --fg-host-prog "p0h1: ping -c $NUM_PINGS 192.3.0.2" \
     --fg-host-prog "p0h1: ping -c $NUM_PINGS 192.3.0.3" \
     --fg-host-prog "p0h1: ping -c $NUM_PINGS 192.3.1.2" \
     --fg-host-prog "p0h1: ping -c $NUM_PINGS 192.3.1.3" \
     --fg-host-prog "p0h2: ping -c $NUM_PINGS 192.0.0.2" \
     --fg-host-prog "p0h2: ping -c $NUM_PINGS 192.0.0.3" \
     --fg-host-prog "p0h2: ping -c $NUM_PINGS 192.0.1.2" \
     --fg-host-prog "p0h2: ping -c $NUM_PINGS 192.0.1.3" \
     --fg-host-prog "p0h2: ping -c $NUM_PINGS 192.1.0.2" \
     --fg-host-prog "p0h2: ping -c $NUM_PINGS 192.1.0.3" \
     --fg-host-prog "p0h2: ping -c $NUM_PINGS 192.1.1.2" \
     --fg-host-prog "p0h2: ping -c $NUM_PINGS 192.1.1.3" \
     --fg-host-prog "p0h2: ping -c $NUM_PINGS 192.2.0.2" \
     --fg-host-prog "p0h2: ping -c $NUM_PINGS 192.2.0.3" \
     --fg-host-prog "p0h2: ping -c $NUM_PINGS 192.2.1.2" \
     --fg-host-prog "p0h2: ping -c $NUM_PINGS 192.2.1.3" \
     --fg-host-prog "p0h2: ping -c $NUM_PINGS 192.3.0.2" \
     --fg-host-prog "p0h2: ping -c $NUM_PINGS 192.3.0.3" \
     --fg-host-prog "p0h2: ping -c $NUM_PINGS 192.3.1.2" \
     --fg-host-prog "p0h2: ping -c $NUM_PINGS 192.3.1.3" \
     --fg-host-prog "p0h3: ping -c $NUM_PINGS 192.0.0.2" \
     --fg-host-prog "p0h3: ping -c $NUM_PINGS 192.0.0.3" \
     --fg-host-prog "p0h3: ping -c $NUM_PINGS 192.0.1.2" \
     --fg-host-prog "p0h3: ping -c $NUM_PINGS 192.0.1.3" \
     --fg-host-prog "p0h3: ping -c $NUM_PINGS 192.1.0.2" \
     --fg-host-prog "p0h3: ping -c $NUM_PINGS 192.1.0.3" \
     --fg-host-prog "p0h3: ping -c $NUM_PINGS 192.1.1.2" \
     --fg-host-prog "p0h3: ping -c $NUM_PINGS 192.1.1.3" \
     --fg-host-prog "p0h3: ping -c $NUM_PINGS 192.2.0.2" \
     --fg-host-prog "p0h3: ping -c $NUM_PINGS 192.2.0.3" \
     --fg-host-prog "p0h3: ping -c $NUM_PINGS 192.2.1.2" \
     --fg-host-prog "p0h3: ping -c $NUM_PINGS 192.2.1.3" \
     --fg-host-prog "p0h3: ping -c $NUM_PINGS 192.3.0.2" \
     --fg-host-prog "p0h3: ping -c $NUM_PINGS 192.3.0.3" \
     --fg-host-prog "p0h3: ping -c $NUM_PINGS 192.3.1.2" \
     --fg-host-prog "p0h3: ping -c $NUM_PINGS 192.3.1.3" \
     --fg-host-prog "p1h0: ping -c $NUM_PINGS 192.0.0.2" \
     --fg-host-prog "p1h0: ping -c $NUM_PINGS 192.0.0.3" \
     --fg-host-prog "p1h0: ping -c $NUM_PINGS 192.0.1.2" \
     --fg-host-prog "p1h0: ping -c $NUM_PINGS 192.0.1.3" \
     --fg-host-prog "p1h0: ping -c $NUM_PINGS 192.1.0.2" \
     --fg-host-prog "p1h0: ping -c $NUM_PINGS 192.1.0.3" \
     --fg-host-prog "p1h0: ping -c $NUM_PINGS 192.1.1.2" \
     --fg-host-prog "p1h0: ping -c $NUM_PINGS 192.1.1.3" \
     --fg-host-prog "p1h0: ping -c $NUM_PINGS 192.2.0.2" \
     --fg-host-prog "p1h0: ping -c $NUM_PINGS 192.2.0.3" \
     --fg-host-prog "p1h0: ping -c $NUM_PINGS 192.2.1.2" \
     --fg-host-prog "p1h0: ping -c $NUM_PINGS 192.2.1.3" \
     --fg-host-prog "p1h0: ping -c $NUM_PINGS 192.3.0.2" \
     --fg-host-prog "p1h0: ping -c $NUM_PINGS 192.3.0.3" \
     --fg-host-prog "p1h0: ping -c $NUM_PINGS 192.3.1.2" \
     --fg-host-prog "p1h0: ping -c $NUM_PINGS 192.3.1.3" \
     --fg-host-prog "p1h1: ping -c $NUM_PINGS 192.0.0.2" \
     --fg-host-prog "p1h1: ping -c $NUM_PINGS 192.0.0.3" \
     --fg-host-prog "p1h1: ping -c $NUM_PINGS 192.0.1.2" \
     --fg-host-prog "p1h1: ping -c $NUM_PINGS 192.0.1.3" \
     --fg-host-prog "p1h1: ping -c $NUM_PINGS 192.1.0.2" \
     --fg-host-prog "p1h1: ping -c $NUM_PINGS 192.1.0.3" \
     --fg-host-prog "p1h1: ping -c $NUM_PINGS 192.1.1.2" \
     --fg-host-prog "p1h1: ping -c $NUM_PINGS 192.1.1.3" \
     --fg-host-prog "p1h1: ping -c $NUM_PINGS 192.2.0.2" \
     --fg-host-prog "p1h1: ping -c $NUM_PINGS 192.2.0.3" \
     --fg-host-prog "p1h1: ping -c $NUM_PINGS 192.2.1.2" \
     --fg-host-prog "p1h1: ping -c $NUM_PINGS 192.2.1.3" \
     --fg-host-prog "p1h1: ping -c $NUM_PINGS 192.3.0.2" \
     --fg-host-prog "p1h1: ping -c $NUM_PINGS 192.3.0.3" \
     --fg-host-prog "p1h1: ping -c $NUM_PINGS 192.3.1.2" \
     --fg-host-prog "p1h1: ping -c $NUM_PINGS 192.3.1.3" \
     --fg-host-prog "p1h2: ping -c $NUM_PINGS 192.0.0.2" \
     --fg-host-prog "p1h2: ping -c $NUM_PINGS 192.0.0.3" \
     --fg-host-prog "p1h2: ping -c $NUM_PINGS 192.0.1.2" \
     --fg-host-prog "p1h2: ping -c $NUM_PINGS 192.0.1.3" \
     --fg-host-prog "p1h2: ping -c $NUM_PINGS 192.1.0.2" \
     --fg-host-prog "p1h2: ping -c $NUM_PINGS 192.1.0.3" \
     --fg-host-prog "p1h2: ping -c $NUM_PINGS 192.1.1.2" \
     --fg-host-prog "p1h2: ping -c $NUM_PINGS 192.1.1.3" \
     --fg-host-prog "p1h2: ping -c $NUM_PINGS 192.2.0.2" \
     --fg-host-prog "p1h2: ping -c $NUM_PINGS 192.2.0.3" \
     --fg-host-prog "p1h2: ping -c $NUM_PINGS 192.2.1.2" \
     --fg-host-prog "p1h2: ping -c $NUM_PINGS 192.2.1.3" \
     --fg-host-prog "p1h2: ping -c $NUM_PINGS 192.3.0.2" \
     --fg-host-prog "p1h2: ping -c $NUM_PINGS 192.3.0.3" \
     --fg-host-prog "p1h2: ping -c $NUM_PINGS 192.3.1.2" \
     --fg-host-prog "p1h2: ping -c $NUM_PINGS 192.3.1.3" \
     --fg-host-prog "p1h3: ping -c $NUM_PINGS 192.0.0.2" \
     --fg-host-prog "p1h3: ping -c $NUM_PINGS 192.0.0.3" \
     --fg-host-prog "p1h3: ping -c $NUM_PINGS 192.0.1.2" \
     --fg-host-prog "p1h3: ping -c $NUM_PINGS 192.0.1.3" \
     --fg-host-prog "p1h3: ping -c $NUM_PINGS 192.1.0.2" \
     --fg-host-prog "p1h3: ping -c $NUM_PINGS 192.1.0.3" \
     --fg-host-prog "p1h3: ping -c $NUM_PINGS 192.1.1.2" \
     --fg-host-prog "p1h3: ping -c $NUM_PINGS 192.1.1.3" \
     --fg-host-prog "p1h3: ping -c $NUM_PINGS 192.2.0.2" \
     --fg-host-prog "p1h3: ping -c $NUM_PINGS 192.2.0.3" \
     --fg-host-prog "p1h3: ping -c $NUM_PINGS 192.2.1.2" \
     --fg-host-prog "p1h3: ping -c $NUM_PINGS 192.2.1.3" \
     --fg-host-prog "p1h3: ping -c $NUM_PINGS 192.3.0.2" \
     --fg-host-prog "p1h3: ping -c $NUM_PINGS 192.3.0.3" \
     --fg-host-prog "p1h3: ping -c $NUM_PINGS 192.3.1.2" \
     --fg-host-prog "p1h3: ping -c $NUM_PINGS 192.3.1.3" \
     --fg-host-prog "p2h0: ping -c $NUM_PINGS 192.0.0.2" \
     --fg-host-prog "p2h0: ping -c $NUM_PINGS 192.0.0.3" \
     --fg-host-prog "p2h0: ping -c $NUM_PINGS 192.0.1.2" \
     --fg-host-prog "p2h0: ping -c $NUM_PINGS 192.0.1.3" \
     --fg-host-prog "p2h0: ping -c $NUM_PINGS 192.1.0.2" \
     --fg-host-prog "p2h0: ping -c $NUM_PINGS 192.1.0.3" \
     --fg-host-prog "p2h0: ping -c $NUM_PINGS 192.1.1.2" \
     --fg-host-prog "p2h0: ping -c $NUM_PINGS 192.1.1.3" \
     --fg-host-prog "p2h0: ping -c $NUM_PINGS 192.2.0.2" \
     --fg-host-prog "p2h0: ping -c $NUM_PINGS 192.2.0.3" \
     --fg-host-prog "p2h0: ping -c $NUM_PINGS 192.2.1.2" \
     --fg-host-prog "p2h0: ping -c $NUM_PINGS 192.2.1.3" \
     --fg-host-prog "p2h0: ping -c $NUM_PINGS 192.3.0.2" \
     --fg-host-prog "p2h0: ping -c $NUM_PINGS 192.3.0.3" \
     --fg-host-prog "p2h0: ping -c $NUM_PINGS 192.3.1.2" \
     --fg-host-prog "p2h0: ping -c $NUM_PINGS 192.3.1.3" \
     --fg-host-prog "p2h1: ping -c $NUM_PINGS 192.0.0.2" \
     --fg-host-prog "p2h1: ping -c $NUM_PINGS 192.0.0.3" \
     --fg-host-prog "p2h1: ping -c $NUM_PINGS 192.0.1.2" \
     --fg-host-prog "p2h1: ping -c $NUM_PINGS 192.0.1.3" \
     --fg-host-prog "p2h1: ping -c $NUM_PINGS 192.1.0.2" \
     --fg-host-prog "p2h1: ping -c $NUM_PINGS 192.1.0.3" \
     --fg-host-prog "p2h1: ping -c $NUM_PINGS 192.1.1.2" \
     --fg-host-prog "p2h1: ping -c $NUM_PINGS 192.1.1.3" \
     --fg-host-prog "p2h1: ping -c $NUM_PINGS 192.2.0.2" \
     --fg-host-prog "p2h1: ping -c $NUM_PINGS 192.2.0.3" \
     --fg-host-prog "p2h1: ping -c $NUM_PINGS 192.2.1.2" \
     --fg-host-prog "p2h1: ping -c $NUM_PINGS 192.2.1.3" \
     --fg-host-prog "p2h1: ping -c $NUM_PINGS 192.3.0.2" \
     --fg-host-prog "p2h1: ping -c $NUM_PINGS 192.3.0.3" \
     --fg-host-prog "p2h1: ping -c $NUM_PINGS 192.3.1.2" \
     --fg-host-prog "p2h1: ping -c $NUM_PINGS 192.3.1.3" \
     --fg-host-prog "p2h2: ping -c $NUM_PINGS 192.0.0.2" \
     --fg-host-prog "p2h2: ping -c $NUM_PINGS 192.0.0.3" \
     --fg-host-prog "p2h2: ping -c $NUM_PINGS 192.0.1.2" \
     --fg-host-prog "p2h2: ping -c $NUM_PINGS 192.0.1.3" \
     --fg-host-prog "p2h2: ping -c $NUM_PINGS 192.1.0.2" \
     --fg-host-prog "p2h2: ping -c $NUM_PINGS 192.1.0.3" \
     --fg-host-prog "p2h2: ping -c $NUM_PINGS 192.1.1.2" \
     --fg-host-prog "p2h2: ping -c $NUM_PINGS 192.1.1.3" \
     --fg-host-prog "p2h2: ping -c $NUM_PINGS 192.2.0.2" \
     --fg-host-prog "p2h2: ping -c $NUM_PINGS 192.2.0.3" \
     --fg-host-prog "p2h2: ping -c $NUM_PINGS 192.2.1.2" \
     --fg-host-prog "p2h2: ping -c $NUM_PINGS 192.2.1.3" \
     --fg-host-prog "p2h2: ping -c $NUM_PINGS 192.3.0.2" \
     --fg-host-prog "p2h2: ping -c $NUM_PINGS 192.3.0.3" \
     --fg-host-prog "p2h2: ping -c $NUM_PINGS 192.3.1.2" \
     --fg-host-prog "p2h2: ping -c $NUM_PINGS 192.3.1.3" \
     --fg-host-prog "p2h3: ping -c $NUM_PINGS 192.0.0.2" \
     --fg-host-prog "p2h3: ping -c $NUM_PINGS 192.0.0.3" \
     --fg-host-prog "p2h3: ping -c $NUM_PINGS 192.0.1.2" \
     --fg-host-prog "p2h3: ping -c $NUM_PINGS 192.0.1.3" \
     --fg-host-prog "p2h3: ping -c $NUM_PINGS 192.1.0.2" \
     --fg-host-prog "p2h3: ping -c $NUM_PINGS 192.1.0.3" \
     --fg-host-prog "p2h3: ping -c $NUM_PINGS 192.1.1.2" \
     --fg-host-prog "p2h3: ping -c $NUM_PINGS 192.1.1.3" \
     --fg-host-prog "p2h3: ping -c $NUM_PINGS 192.2.0.2" \
     --fg-host-prog "p2h3: ping -c $NUM_PINGS 192.2.0.3" \
     --fg-host-prog "p2h3: ping -c $NUM_PINGS 192.2.1.2" \
     --fg-host-prog "p2h3: ping -c $NUM_PINGS 192.2.1.3" \
     --fg-host-prog "p2h3: ping -c $NUM_PINGS 192.3.0.2" \
     --fg-host-prog "p2h3: ping -c $NUM_PINGS 192.3.0.3" \
     --fg-host-prog "p2h3: ping -c $NUM_PINGS 192.3.1.2" \
     --fg-host-prog "p2h3: ping -c $NUM_PINGS 192.3.1.3" \
     --fg-host-prog "p3h0: ping -c $NUM_PINGS 192.0.0.2" \
     --fg-host-prog "p3h0: ping -c $NUM_PINGS 192.0.0.3" \
     --fg-host-prog "p3h0: ping -c $NUM_PINGS 192.0.1.2" \
     --fg-host-prog "p3h0: ping -c $NUM_PINGS 192.0.1.3" \
     --fg-host-prog "p3h0: ping -c $NUM_PINGS 192.1.0.2" \
     --fg-host-prog "p3h0: ping -c $NUM_PINGS 192.1.0.3" \
     --fg-host-prog "p3h0: ping -c $NUM_PINGS 192.1.1.2" \
     --fg-host-prog "p3h0: ping -c $NUM_PINGS 192.1.1.3" \
     --fg-host-prog "p3h0: ping -c $NUM_PINGS 192.2.0.2" \
     --fg-host-prog "p3h0: ping -c $NUM_PINGS 192.2.0.3" \
     --fg-host-prog "p3h0: ping -c $NUM_PINGS 192.2.1.2" \
     --fg-host-prog "p3h0: ping -c $NUM_PINGS 192.2.1.3" \
     --fg-host-prog "p3h0: ping -c $NUM_PINGS 192.3.0.2" \
     --fg-host-prog "p3h0: ping -c $NUM_PINGS 192.3.0.3" \
     --fg-host-prog "p3h0: ping -c $NUM_PINGS 192.3.1.2" \
     --fg-host-prog "p3h0: ping -c $NUM_PINGS 192.3.1.3" \
     --fg-host-prog "p3h1: ping -c $NUM_PINGS 192.0.0.2" \
     --fg-host-prog "p3h1: ping -c $NUM_PINGS 192.0.0.3" \
     --fg-host-prog "p3h1: ping -c $NUM_PINGS 192.0.1.2" \
     --fg-host-prog "p3h1: ping -c $NUM_PINGS 192.0.1.3" \
     --fg-host-prog "p3h1: ping -c $NUM_PINGS 192.1.0.2" \
     --fg-host-prog "p3h1: ping -c $NUM_PINGS 192.1.0.3" \
     --fg-host-prog "p3h1: ping -c $NUM_PINGS 192.1.1.2" \
     --fg-host-prog "p3h1: ping -c $NUM_PINGS 192.1.1.3" \
     --fg-host-prog "p3h1: ping -c $NUM_PINGS 192.2.0.2" \
     --fg-host-prog "p3h1: ping -c $NUM_PINGS 192.2.0.3" \
     --fg-host-prog "p3h1: ping -c $NUM_PINGS 192.2.1.2" \
     --fg-host-prog "p3h1: ping -c $NUM_PINGS 192.2.1.3" \
     --fg-host-prog "p3h1: ping -c $NUM_PINGS 192.3.0.2" \
     --fg-host-prog "p3h1: ping -c $NUM_PINGS 192.3.0.3" \
     --fg-host-prog "p3h1: ping -c $NUM_PINGS 192.3.1.2" \
     --fg-host-prog "p3h1: ping -c $NUM_PINGS 192.3.1.3" \
     --fg-host-prog "p3h2: ping -c $NUM_PINGS 192.0.0.2" \
     --fg-host-prog "p3h2: ping -c $NUM_PINGS 192.0.0.3" \
     --fg-host-prog "p3h2: ping -c $NUM_PINGS 192.0.1.2" \
     --fg-host-prog "p3h2: ping -c $NUM_PINGS 192.0.1.3" \
     --fg-host-prog "p3h2: ping -c $NUM_PINGS 192.1.0.2" \
     --fg-host-prog "p3h2: ping -c $NUM_PINGS 192.1.0.3" \
     --fg-host-prog "p3h2: ping -c $NUM_PINGS 192.1.1.2" \
     --fg-host-prog "p3h2: ping -c $NUM_PINGS 192.1.1.3" \
     --fg-host-prog "p3h2: ping -c $NUM_PINGS 192.2.0.2" \
     --fg-host-prog "p3h2: ping -c $NUM_PINGS 192.2.0.3" \
     --fg-host-prog "p3h2: ping -c $NUM_PINGS 192.2.1.2" \
     --fg-host-prog "p3h2: ping -c $NUM_PINGS 192.2.1.3" \
     --fg-host-prog "p3h2: ping -c $NUM_PINGS 192.3.0.2" \
     --fg-host-prog "p3h2: ping -c $NUM_PINGS 192.3.0.3" \
     --fg-host-prog "p3h2: ping -c $NUM_PINGS 192.3.1.2" \
     --fg-host-prog "p3h2: ping -c $NUM_PINGS 192.3.1.3" \
     --fg-host-prog "p3h3: ping -c $NUM_PINGS 192.0.0.2" \
     --fg-host-prog "p3h3: ping -c $NUM_PINGS 192.0.0.3" \
     --fg-host-prog "p3h3: ping -c $NUM_PINGS 192.0.1.2" \
     --fg-host-prog "p3h3: ping -c $NUM_PINGS 192.0.1.3" \
     --fg-host-prog "p3h3: ping -c $NUM_PINGS 192.1.0.2" \
     --fg-host-prog "p3h3: ping -c $NUM_PINGS 192.1.0.3" \
     --fg-host-prog "p3h3: ping -c $NUM_PINGS 192.1.1.2" \
     --fg-host-prog "p3h3: ping -c $NUM_PINGS 192.1.1.3" \
     --fg-host-prog "p3h3: ping -c $NUM_PINGS 192.2.0.2" \
     --fg-host-prog "p3h3: ping -c $NUM_PINGS 192.2.0.3" \
     --fg-host-prog "p3h3: ping -c $NUM_PINGS 192.2.1.2" \
     --fg-host-prog "p3h3: ping -c $NUM_PINGS 192.2.1.3" \
     --fg-host-prog "p3h3: ping -c $NUM_PINGS 192.3.0.2" \
     --fg-host-prog "p3h3: ping -c $NUM_PINGS 192.3.0.3" \
     --fg-host-prog "p3h3: ping -c $NUM_PINGS 192.3.1.2" \
     --fg-host-prog "p3h3: ping -c $NUM_PINGS 192.3.1.3" \
          2> $LOG_DUMPS/flightplan_mininet_log.err
}

function autotest_long {
  NUM_PINGS=10
  autotest
}

function complete_fec_e2e {
  # Based on bmv2/complete_fec_e2e.sh

  FEC_INIT_PCAP=$WHARF_REPO/bmv2/pcaps/lldp_enable_fec.pcap
  TRAFFIC_PREINPUT=$WHARF_REPO/bmv2/pcaps/tcp_100.pcap
  TRAFFIC_INPUT=/tmp/tcp_100.pcap
  CACHEFILE=/tmp/tcprewrite_cachefile
  # Traffic will be sent from p0h0 to p1h0
  tcpprep --auto=first --pcap=${TRAFFIC_PREINPUT} --cachefile=${CACHEFILE}
  tcprewrite --endpoints=192.0.0.2:192.1.0.2 --cachefile=${CACHEFILE} -i ${TRAFFIC_PREINPUT} -o ${TRAFFIC_INPUT}

  sudo mn -c 2> $LOG_DUMPS/mininet_clean.err

  sudo -E python $WHARF_REPO/bmv2/start_flightplan_mininet.py ${TOPOLOGY} \
          --pcap-dump $PCAP_DUMPS \
          --log $LOG_DUMPS \
          --verbose \
          --showExitStatus \
     --fg-host-prog "${START_CFG}" \
     --fg-host-prog ": tcpreplay -i dropper-eth0 ${FEC_INIT_PCAP}" \
     --fg-host-prog ": tcpreplay -i dropper-eth1 ${FEC_INIT_PCAP}" \
     --fg-host-prog ": tcpreplay -i dropper2-eth0 ${FEC_INIT_PCAP}" \
     --fg-host-prog ": tcpreplay -i dropper2-eth1 ${FEC_INIT_PCAP}" \
     --fg-host-prog "p0h0: tcpreplay -i p0h0-eth1 --pps=10 ${TRAFFIC_INPUT}" \
          2> $LOG_DUMPS/flightplan_mininet_log.err

  mv ${TRAFFIC_INPUT} ${PCAP_DUMPS}/
  mv ${CACHEFILE} ${PCAP_DUMPS}/

  TRAFFIC_INPUT=${PCAP_DUMPS}/`basename ${TRAFFIC_INPUT} `

  if [ -n "${ORDER_MATTERS}" ]
  then
    tcpdump -r ${PCAP_DUMPS}/p1e0_to_p1h0.pcap -XX -S -vv | grep -v " IP (tos " | grep -v 0x0010 | grep -v 0x0000 | grep -v ": Flags" > $OUTDIR/result_pcap_contents.txt
    tcpdump -r ${TRAFFIC_INPUT} -XX -S -vv | grep -v " IP (tos " | grep -v 0x0010 | grep -v 0x0000 | grep -v ": Flags" > $OUTDIR/reference_pcap_contents.txt
  else
    tcpdump -r ${PCAP_DUMPS}/p1e0_to_p1h0.pcap -XX -S -vv | grep -v " IP (tos " | grep -v 0x0010 | grep -v 0x0000 | grep -v ": Flags" | sort | uniq > $OUTDIR/result_pcap_contents.txt
    tcpdump -r ${TRAFFIC_INPUT} -XX -S -vv | grep -v " IP (tos " | grep -v 0x0010 | grep -v 0x0000 | grep -v ": Flags" | sort | uniq > $OUTDIR/reference_pcap_contents.txt
  fi

  CMD="diff -q $OUTDIR/result_pcap_contents.txt $OUTDIR/reference_pcap_contents.txt"
  echo $CMD
  eval $CMD
  if [[ $? == 0 ]]
  then
      echo "Test succeeded"
      exit 0
  else
      echo "Test failed"
      exit 1
  fi
}

function complete_mcd_e2e {
  # Based on bmv2/complete_mcd_e2e.sh

  FEC_INIT_PCAP=$WHARF_REPO/bmv2/pcaps/lldp_enable_fec.pcap
  PCAP_TOOLS=$WHARF_REPO/bmv2/pcap_tools/

  TRAFFIC_PREINPUT=$WHARF_REPO/bmv2/pcaps/Memcached_in_short.pcap

  SIP="192.0.0.2"
  DIP="192.1.0.2"
  SMAC="02:00:00:d8:c2:6b"
  DMAC="02:00:00:9c:a8:79"

  INPUT_PCAP=$OUTDIR/${BASENAME}_in.pcap
  echo "Putting pcap in $INPUT_PCAP"
  python2 ${PCAP_TOOLS}/pcap_sub.py $TRAFFIC_PREINPUT $INPUT_PCAP\
      --sip="$SIP" --dip="$DIP" --smac="$SMAC" --dmac="$DMAC"

  sudo mn -c 2> $LOG_DUMPS/mininet_clean.err

  sudo -E python $WHARF_REPO/bmv2/start_flightplan_mininet.py ${TOPOLOGY} \
          --pcap-dump $PCAP_DUMPS \
          --log $LOG_DUMPS \
          --verbose \
          --showExitStatus \
     --fg-host-prog "${START_CFG}" \
     --fg-host-prog ": tcpreplay -i dropper-eth0 ${FEC_INIT_PCAP}" \
     --fg-host-prog ": tcpreplay -i dropper-eth1 ${FEC_INIT_PCAP}" \
     --fg-host-prog ": tcpreplay -i dropper2-eth0 ${FEC_INIT_PCAP}" \
     --fg-host-prog ": tcpreplay -i dropper2-eth1 ${FEC_INIT_PCAP}" \
     --fg-host-prog "p1h0: memcached -u $USER -U 11211 -B ascii -vv &" \
     --fg-host-prog "p0h0: tcpreplay -i p0h0-eth1 --pps=10 ${INPUT_PCAP}" \
          2> $LOG_DUMPS/flightplan_mininet_log.err

  # FIXME The target log's name might change -- this is brittle!
  TARGET_LOG=${LOG_DUMPS}/p1h0_prog_19.log
  echo "Using TARGET_LOG=`ls -lh ${TARGET_LOG}`"

  grep --text -E '^[<>]' ${TARGET_LOG} | grep --text -v "server" | grep --text -v "buffer" | sed -E 's/^([<>])[0-9]+/\1/' | grep --text -v STORED | grep --text -v "sending key" | grep --text -v END > ${LOG_DUMPS}/mcd_log

  #if [ -n "${UNIQUE_MATTERS}" ]
  #then
  #  CMD="diff -q <(sort ${LOG_DUMPS}/mcd_log) <(sort mcd_log_withoutcache.expected)"
  #else
  #  CMD="diff -q <(sort ${LOG_DUMPS}/mcd_log | uniq) <(sort mcd_log_withoutcache.expected | uniq)"
  #fi
  #echo $CMD
  #eval $CMD
  #if [[ $? == 0 ]]
  #then
  #    echo "Test conclusive: cache was NOT used"
  #    exit 0
  #fi
  #
  #if [ -n "${UNIQUE_MATTERS}" ]
  #then
  #  CMD="diff -q <(sort ${LOG_DUMPS}/mcd_log) <(sort mcd_log_withcache.expected)"
  #else
  #  CMD="diff -q <(sort ${LOG_DUMPS}/mcd_log | uniq) <(sort mcd_log_withcache.expected | uniq)"
  #fi
  #echo $CMD
  #eval $CMD
  #if [[ $? == 0 ]]
  #then
  #    echo "Test conclusive: cache was used"
  #    exit 0
  #fi
  #
  #echo "Test inconclusive"
  #exit 1

  STATUS=0

  SETS_experiment=$(grep set ${LOG_DUMPS}/mcd_log | wc -l)
  SETS_reference=$(grep set $WHARF_REPO/mcd_log_withoutcache.expected | wc -l)
  if [ "$SETS_experiment" -eq "$SETS_reference" ]
  then
      echo "#SETS: OK ($SETS_experiment vs $SETS_reference)"
  else
      echo "#SETS: Different than reference ($SETS_experiment vs $SETS_reference)"
      STATUS=1
  fi

  GETS_experiment=$(grep get ${LOG_DUMPS}/mcd_log | wc -l)
  GETS_reference=$(grep get $WHARF_REPO/mcd_log_withoutcache.expected | wc -l)
  if [ "$GETS_experiment" -eq "$GETS_reference" ]
  then
      echo "#GETS: OK (same as reference -- no cache is being used)"
  elif [ "$GETS_experiment" -lt "$GETS_reference" ]
  then
      echo "#GETS: OK (less than reference: ($GETS_experiment vs $GETS_reference))"
  else
      echo "#GETS: Different than reference ($GETS_experiment vs $GETS_reference)"
      STATUS=1
  fi

  exit $STATUS
}

function interactive2_complete {
  FEC_INIT_PCAP=$WHARF_REPO/bmv2/pcaps/lldp_enable_fec.pcap
  sudo -E python $WHARF_REPO/bmv2/start_flightplan_mininet.py ${TOPOLOGY} \
          --pcap-dump $PCAP_DUMPS \
          --log $LOG_DUMPS \
          --verbose \
          --showExitStatus \
     --host-prog "p0h0: iperf3 -s -B 192.0.0.2 -p 5201" \
     --host-prog "p0h1: iperf3 -s -B 192.0.0.3 -p 5201" \
     --host-prog "p0h2: iperf3 -s -B 192.0.1.2 -p 5201" \
     --host-prog "p0h3: iperf3 -s -B 192.0.1.3 -p 5201" \
     --host-prog "p1h0: iperf3 -s -B 192.1.0.2 -p 5201" \
     --host-prog "p1h1: iperf3 -s -B 192.1.0.3 -p 5201" \
     --host-prog "p1h2: iperf3 -s -B 192.1.1.2 -p 5201" \
     --host-prog "p1h3: iperf3 -s -B 192.1.1.3 -p 5201" \
     --host-prog "p2h0: iperf3 -s -B 192.2.0.2 -p 5201" \
     --host-prog "p2h1: iperf3 -s -B 192.2.0.3 -p 5201" \
     --host-prog "p2h2: iperf3 -s -B 192.2.1.2 -p 5201" \
     --host-prog "p2h3: iperf3 -s -B 192.2.1.3 -p 5201" \
     --host-prog "p3h0: iperf3 -s -B 192.3.0.2 -p 5201" \
     --host-prog "p3h1: iperf3 -s -B 192.3.0.3 -p 5201" \
     --host-prog "p3h2: iperf3 -s -B 192.3.1.2 -p 5201" \
     --host-prog "p3h3: iperf3 -s -B 192.3.1.3 -p 5201" \
     --fg-host-prog "${START_CFG}" \
     --fg-host-prog ": tcpreplay -i dropper-eth0 ${FEC_INIT_PCAP}" \
     --fg-host-prog ": tcpreplay -i dropper-eth1 ${FEC_INIT_PCAP}" \
     --fg-host-prog ": tcpreplay -i dropper2-eth0 ${FEC_INIT_PCAP}" \
     --fg-host-prog ": tcpreplay -i dropper2-eth1 ${FEC_INIT_PCAP}" \
          --cli
}

function fwtest {
  if [ -z "${NUM_PINGS}" ]
  then
    NUM_PINGS=1
  fi

  FEC_INIT_PCAP=$WHARF_REPO/bmv2/pcaps/lldp_enable_fec.pcap
  sudo -E python $WHARF_REPO/bmv2/start_flightplan_mininet.py ${TOPOLOGY} \
          --pcap-dump $PCAP_DUMPS \
          --log $LOG_DUMPS \
          --verbose \
          --showExitStatus \
     --host-prog "p0h0: iperf3 -s -B 192.0.0.2 -p 5201" \
     --host-prog "p0h1: iperf3 -s -B 192.0.0.3 -p 5201" \
     --host-prog "p0h2: iperf3 -s -B 192.0.1.2 -p 5201" \
     --host-prog "p0h3: iperf3 -s -B 192.0.1.3 -p 5201" \
     --host-prog "p1h0: iperf3 -s -B 192.1.0.2 -p 5201" \
     --host-prog "p1h1: iperf3 -s -B 192.1.0.3 -p 5201" \
     --host-prog "p1h2: iperf3 -s -B 192.1.1.2 -p 5201" \
     --host-prog "p1h3: iperf3 -s -B 192.1.1.3 -p 5201" \
     --host-prog "p2h0: iperf3 -s -B 192.2.0.2 -p 5201" \
     --host-prog "p2h1: iperf3 -s -B 192.2.0.3 -p 5201" \
     --host-prog "p2h2: iperf3 -s -B 192.2.1.2 -p 5201" \
     --host-prog "p2h3: iperf3 -s -B 192.2.1.3 -p 5201" \
     --host-prog "p3h0: iperf3 -s -B 192.3.0.2 -p 5201" \
     --host-prog "p3h1: iperf3 -s -B 192.3.0.3 -p 5201" \
     --host-prog "p3h2: iperf3 -s -B 192.3.1.2 -p 5201" \
     --host-prog "p3h3: iperf3 -s -B 192.3.1.3 -p 5201" \
     --fg-host-prog "${START_CFG}" \
     --fg-host-prog ": tcpreplay -i dropper-eth0 ${FEC_INIT_PCAP}" \
     --fg-host-prog ": tcpreplay -i dropper-eth1 ${FEC_INIT_PCAP}" \
     --fg-host-prog ": tcpreplay -i dropper2-eth0 ${FEC_INIT_PCAP}" \
     --fg-host-prog ": tcpreplay -i dropper2-eth1 ${FEC_INIT_PCAP}" \
     --fg-host-prog "p1h3: hping3 -c $NUM_PINGS -S -p 5201 192.1.1.2" \
     --fg-host-prog "p1h2: ! hping3 -c $NUM_PINGS -S -p 5201 192.1.1.3" \
     --fg-host-prog "p1h1: ! hping3 -c $NUM_PINGS -S -p 5201 192.1.1.3" \
     --fg-host-prog "p1h3: hping3 -c $NUM_PINGS -S -p 5201 192.1.0.3" \
     --fg-host-prog "p1h2: hping3 -c $NUM_PINGS -S -p 5201 192.1.0.3" \
     --fg-host-prog "p1h3: hping3 -c $NUM_PINGS -S -p 5201 192.2.0.3" \
     --fg-host-prog "p1h3: hping3 -c $NUM_PINGS -S -p 5201 192.3.1.2" \
     --fg-host-prog "p1h3: hping3 -c $NUM_PINGS -S -p 5201 192.0.1.2" \
     --fg-host-prog "p1h3: ! hping3 -c $NUM_PINGS -S -p 5201 192.1.1.3" \
     --fg-host-prog "p1h3: ! hping3 -c $NUM_PINGS -S -p 5201 192.1.1.3" \
     --fg-host-prog "p1h3: ! hping3 -c $NUM_PINGS -S -p 5201 192.1.1.3" \
     --fg-host-prog "p1h3: ! hping3 -c $NUM_PINGS -S -p 5201 192.0.1.3" \
     --fg-host-prog "p0h3: hping3 -c $NUM_PINGS -S -p 5201 192.1.1.2" \
     --fg-host-prog "p1h2: ! hping3 -c $NUM_PINGS -S -p 5201 192.1.1.3" \
     --fg-host-prog "p1h1: ! hping3 -c $NUM_PINGS -S -p 5201 192.1.1.3" \
     --fg-host-prog "p0h3: hping3 -c $NUM_PINGS -S -p 5201 192.1.0.3" \
     --fg-host-prog "p1h2: hping3 -c $NUM_PINGS -S -p 5201 192.1.0.3" \
     --fg-host-prog "p0h3: hping3 -c $NUM_PINGS -S -p 5201 192.2.0.3" \
     --fg-host-prog "p0h3: hping3 -c $NUM_PINGS -S -p 5201 192.3.1.2" \
     --fg-host-prog "p0h3: hping3 -c $NUM_PINGS -S -p 5201 192.0.1.2" \
     --fg-host-prog "p0h3: ! hping3 -c $NUM_PINGS -S -p 5201 192.1.1.3" \
     --fg-host-prog "p0h3: ! hping3 -c $NUM_PINGS -S -p 5201 192.1.1.3" \
     --fg-host-prog "p0h3: ! hping3 -c $NUM_PINGS -S -p 5201 192.1.1.3" \
     --fg-host-prog "p0h3: ! hping3 -c $NUM_PINGS -S -p 5201 192.1.1.3" \
          2> $LOG_DUMPS/flightplan_mininet_log.err
     # where:
     #   p1h2 = 192.1.1.2
     #   p1h3 = 192.1.1.3
     #   p1h1 = 192.1.0.3
     #   p2h1 = 192.2.0.3
     #   p3h2 = 192.3.1.2
     #   p0h2 = 192.0.1.2
     #   p0h3 = 192.0.1.3
}


function complete_all_e2e {

  # Based on bmv2/complete_mcd_e2e.sh

  FEC_INIT_PCAP=$WHARF_REPO/bmv2/pcaps/lldp_enable_fec.pcap
  PCAP_TOOLS=$WHARF_REPO/bmv2/pcap_tools/

  TRAFFIC_PREINPUT=$WHARF_REPO/bmv2/pcaps/Memcached_in_short.pcap

  SIP="192.0.0.2"
  DIP="192.1.0.2"
  SMAC="02:00:00:d8:c2:6b"
  DMAC="02:00:00:9c:a8:79"

  INPUT_PCAP=$OUTDIR/${BASENAME}_in.pcap
  echo "Putting pcap in $INPUT_PCAP"
  python2 ${PCAP_TOOLS}/pcap_sub.py $TRAFFIC_PREINPUT $INPUT_PCAP\
      --sip="$SIP" --dip="$DIP" --smac="$SMAC" --dmac="$DMAC"

  TRAFFIC_PREINPUT=$WHARF_REPO/bmv2/pcaps/tcp_100.pcap
  TRAFFIC_INPUT=/tmp/tcp_100.pcap
  CACHEFILE=/tmp/tcprewrite_cachefile
  # Traffic will be sent from p0h0 to p1h0
  tcpprep --auto=first --pcap=${TRAFFIC_PREINPUT} --cachefile=${CACHEFILE}
  tcprewrite --endpoints=192.0.0.2:192.1.0.2 --cachefile=${CACHEFILE} -i ${TRAFFIC_PREINPUT} -o ${TRAFFIC_INPUT}

  sudo mn -c 2> $LOG_DUMPS/mininet_clean.err

  sudo -E python $WHARF_REPO/bmv2/start_flightplan_mininet.py ${TOPOLOGY} \
          --pcap-dump $PCAP_DUMPS \
          --log $LOG_DUMPS \
          --verbose \
          --showExitStatus \
     --fg-host-prog "${START_CFG}" \
     --fg-host-prog ": tcpreplay -i dropper-eth0 ${FEC_INIT_PCAP}" \
     --fg-host-prog ": tcpreplay -i dropper-eth1 ${FEC_INIT_PCAP}" \
     --fg-host-prog ": tcpreplay -i dropper2-eth0 ${FEC_INIT_PCAP}" \
     --fg-host-prog ": tcpreplay -i dropper2-eth1 ${FEC_INIT_PCAP}" \
     --fg-host-prog "p1h0: memcached -u $USER -U 11211 -B ascii -vv &" \
     --fg-host-prog "p0h0: tcpreplay -i p0h0-eth1 --pps=10 ${INPUT_PCAP}" \
     --fg-host-prog "p0h0: tcpreplay -i p0h0-eth1 ${TRAFFIC_INPUT}" \
          2> $LOG_DUMPS/flightplan_mininet_log.err

  # FIXME The target log's name might change -- this is brittle!
  TARGET_LOG=${LOG_DUMPS}/p1h0_prog_19.log
  echo "Using TARGET_LOG=`ls -lh ${TARGET_LOG}`"

  grep --text -E '^[<>]' ${TARGET_LOG} | grep --text -v "server" | grep --text -v "buffer" | sed -E 's/^([<>])[0-9]+/\1/' | grep --text -v STORED | grep --text -v "sending key" | grep --text -v END > ${LOG_DUMPS}/mcd_log

  #if [ -n "${UNIQUE_MATTERS}" ]
  #then
  #  CMD="diff -q <(sort ${LOG_DUMPS}/mcd_log) <(sort mcd_log_withoutcache.expected)"
  #else
  #  CMD="diff -q <(sort ${LOG_DUMPS}/mcd_log | uniq) <(sort mcd_log_withoutcache.expected | uniq)"
  #fi
  #echo $CMD
  #eval $CMD
  #if [[ $? == 0 ]]
  #then
  #    echo "Test conclusive: cache was NOT used"
  #    exit 0
  #fi
  #
  #if [ -n "${UNIQUE_MATTERS}" ]
  #then
  #  CMD="diff -q <(sort ${LOG_DUMPS}/mcd_log) <(sort mcd_log_withcache.expected)"
  #else
  #  CMD="diff -q <(sort ${LOG_DUMPS}/mcd_log | uniq) <(sort mcd_log_withcache.expected | uniq)"
  #fi
  #echo $CMD
  #eval $CMD
  #if [[ $? == 0 ]]
  #then
  #    echo "Test conclusive: cache was used"
  #    exit 0
  #fi
  #
  #echo "Test inconclusive"
  #exit 1

  STATUS=0

  SETS_experiment=$(grep set ${LOG_DUMPS}/mcd_log | wc -l)
  SETS_reference=$(grep set $WHARF_REPO/mcd_log_withoutcache.expected | wc -l)
  if [ "$SETS_experiment" -eq "$SETS_reference" ]
  then
      echo "#SETS: OK ($SETS_experiment vs $SETS_reference)"
  else
      echo "#SETS: Different than reference ($SETS_experiment vs $SETS_reference)"
      STATUS=1
  fi

  GETS_experiment=$(grep get ${LOG_DUMPS}/mcd_log | wc -l)
  GETS_reference=$(grep get $WHARF_REPO/mcd_log_withoutcache.expected | wc -l)
  if [ "$GETS_experiment" -eq "$GETS_reference" ]
  then
      echo "#GETS: OK (same as reference -- no cache is being used)"
  elif [ "$GETS_experiment" -lt "$GETS_reference" ]
  then
      echo "#GETS: OK (less than reference: ($GETS_experiment vs $GETS_reference))"
  else
      echo "#GETS: Different than reference ($GETS_experiment vs $GETS_reference)"
      STATUS=1
  fi

  exit $STATUS
}

source `dirname "$0"`/../../run_alv.sh
