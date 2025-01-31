#!/bin/sh

LOG_DIR=regression_test_output

mkdir -p ${LOG_DIR}

do_test() {
  TITLE=$1
  FILENAME=$2
  CMD=$3
  echo "${TITLE}"
  if [ -z ${VISIBLE} ]
  then
    eval ${CMD} > ${LOG_DIR}/${FILENAME}.stdout 2> ${LOG_DIR}/${FILENAME}.stderr
  else
    eval ${CMD}
  fi
  if [ $? -eq 0 ]; then
      echo "SUCCESS";
  else
      echo "FAILED";
  fi
}

do_test "FEC_E2E" "FEC_E2E" "bash $WHARF_REPO/bmv2/complete_fec_e2e.sh $WHARF_REPO/bmv2/pcaps/tcp_100.pcap"
do_test "FEC_E2E_2-1 (TWO_HALVES=1)" "FEC_E2E_2-1" "TWO_HALVES=1 bash $WHARF_REPO/bmv2/complete_fec_e2e.sh $WHARF_REPO/bmv2/pcaps/tcp_100.pcap"
do_test "FEC_E2E_2-2 (TWO_HALVES=2)" "FEC_E2E_2-2" "TWO_HALVES=2 bash $WHARF_REPO/bmv2/complete_fec_e2e.sh $WHARF_REPO/bmv2/pcaps/tcp_100.pcap"
do_test "MCD_E2E" "MCD_E2E" "bash $WHARF_REPO/bmv2/complete_mcd_e2e.sh $WHARF_REPO/bmv2/pcaps/Memcached_in_short.pcap $WHARF_REPO/bmv2/pcaps/Memcached_expected_short.pcap"
# NOTE from isaac-ped: "HC test does only returns non-zero in the case where the mininet setup crashes. It requires manual inspection of the traffic counts to assess whether compression is happening, so directing this output to a file could cover up behavior."
do_test "HC_E2E" "HC_E2E" "bash $WHARF_REPO/bmv2/compressor_e2e.sh $WHARF_REPO/bmv2/pcaps/collidingFlows.pcap"
