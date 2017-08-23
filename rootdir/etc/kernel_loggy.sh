#!/bin/sh
# kernel_loggy.sh

_date=`date +%F_%H-%M-%S`
cat /dev/kmsg > /cache/kernel_loggy_${_date}.txt 