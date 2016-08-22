#!/bin/zsh
for ip in 172.16.67.154.{1..254}; do
  ping -c 1 -W 1 $ip | grep "64 bytes" &
done
