#!/bin/sh

data_dir=/home/sendai/src/psd_replay_beam
Hz=30
port=5555
byte_data_size_per_shot=128000 # in bytes
forever=
#forever=-F

./psd_replay_beam -h 130.87.234.118 $forever \
-H $Hz -n $byte_data_size_per_shot -p $port ${data_dir}/test.dat

#./psd_replay_beam -h 192.168.0.16 $forever \
#-H $Hz -n $byte_data_size_per_shot -p $port ${data_dir}/16.dat

#./psd_replay_beam -h 192.168.0.17 $forever \
#-H $Hz -n $byte_data_size_per_shot -p $port ${data_dir}/17.dat

#./psd_replay_beam -h 192.168.0.18 $forever \
#-H $Hz -n $byte_data_size_per_shot -p $port ${data_dir}/18.dat

#./psd_replay_beam -h 192.168.0.19 $forever \
#-H $Hz -n $byte_data_size_per_shot -p $port ${data_dir}/19.dat

#./psd_replay_beam -h 192.168.0.20 $forever \
#-H $Hz -n $byte_data_size_per_shot -p $port ${data_dir}/20.dat
