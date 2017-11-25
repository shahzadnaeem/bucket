#!/bin/bash

# Use tweaked version of wget to get DNS and Connect times in results.log

#
# Needs some option parsing to supply count and size
# Always outputs/downloads to $MYHOME
#
# gunzip wget.gz (Fedora 26 binary) and place somewhere that is in PATH before std wget
# ./wget-test.sh 
#   test.log     current wget output
#   results.log  historical log of all runs

MYHOME="$HOME/wget"

if [[ ! -d $MYHOME ]]
then
  set -e
  mkdir $MYHOME
fi

LOG=$MYHOME/test.log             # wget log - this run only
TRIES=3
TIMEOUT=10
OUTPUT=$MYHOME/downloaded.file
RESULTS=$MYHOME/results.log      # This script's log

URL="http://ipv4.download.thinkbroadband.com"

SMALL="10MB.zip"
MEDIUM="50MB.zip"
LARGE="200MB.zip"
HUGE="1GB.zip"

size=$MEDIUM
count=2

WGETOPTS="--output-file=$LOG --verbose --tries=$TRIES --timeout=$TIMEOUT --server-response"
TIMEOPTS="--format %Es"

getFile="${URL}/${size}"
outputFile="${OUTPUT}.${size}"

command="time $TIMEOPTS wget $WGETOPTS --output-document=$outputFile $getFile"


# ==============================================================================

function do_test
{
  echo -e "\n# Starting '${count}' wgets of size '$size' ...\n";
  sleep 1 

  i=1

  while [[ $i -le $count ]]
  do

    result=`$command 2>&1`

    status=$?

    echo -e "START: `date`\n  CMD: $command\n  STATUS: $status\n  SIZE: $size\n  TIME: $result" >> $RESULTS
    if [[ $status -eq 0 ]]
    then
      dnsTime=`grep '^+ DNS' $LOG | sed -e 's/^[^=]*= //'`
      connectTime=`grep '^+ Connect' $LOG | sed -e 's/^[^=]*= //'`

      bandwidth=`grep saved $LOG | sed -e 's/^.*(\([^)]*\)).*$/\1/'`

      echo "  DNS: $dnsTime"          >> $RESULTS
      echo "  CONNECT: $connectTime"  >> $RESULTS
      echo "  RATE: $bandwidth"       >> $RESULTS
      echo "  COUNT: ${i}/${count}"   >> $RESULTS
    fi

    if [[ $status -eq 0 ]]
    then
      echo -e "#${i} Test ran successfully for '$getFile' in $result"
    else
      echo -e "Failure running test - see '$LOG' for details\n  $result"
      exit $status
    fi

    ((i++))
  done
}

# ==============================================================================

do_test

# ==============================================================================
