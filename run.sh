#!/bin/sh

data_dir=/home/sendai/fakedata/kek
sleep=100000

./psd_replay -v -h 192.168.0.101 -p 23 -s $sleep ${data_dir}/fake-t0.16.dat &
./psd_replay -v -h 192.168.0.102 -p 23 -s $sleep /home/sendai/17.dat        &
./psd_replay -v -h 192.168.0.103 -p 23 -s $sleep /home/sendai/18.dat        &
./psd_replay -v -h 192.168.0.104 -p 23 -s $sleep ${data_dir}/fake-t0.19.dat &
./psd_replay -v -h 192.168.0.105 -p 23 -s $sleep ${data_dir}/fake-t0.20.dat &
