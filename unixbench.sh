#! /bin/bash
#==============================================================#
#   Description:  Unixbench script, copy from :https://raw.githubusercontent.com/teddysun/across/master/unixbench.sh, change to v5.1.5   #
#   Author: Teddysun <i@teddysun.com>                          #
#   Intro:  https://teddysun.com/245.html                      #
#==============================================================#
cur_dir=/opt/unixbench

# Check System
[[ $EUID -ne 0 ]] && echo 'Error: This script must be run as root!' && exit 1
[[ -f /etc/redhat-release ]] && os='centos'
[[ ! -z "`egrep -i debian /etc/issue`" ]] && os='debian'
[[ ! -z "`egrep -i ubuntu /etc/issue`" ]] && os='ubuntu'
[[ "$os" == '' ]] && echo 'Error: Your system is not supported to run it!' && exit 1

# Install necessary libaries
if [ "$os" == 'centos' ]; then
    yum -y install make automake gcc autoconf gcc-c++ time perl-Time-HiRes
else
    apt-get -y update
    apt-get -y install make automake gcc autoconf time perl
fi

# Create new soft download dir
mkdir -p ${cur_dir}
cd ${cur_dir}

# Download UnixBench5.1.5
if [ -s UnixBench-5.1.5.tar.gz ]; then
    echo "UnixBench-5.1.5.tar.gz [found]"
else
    echo "UnixBench-5.1.5.tar.gz not found!!!download now..."
    if ! wget -c https://github.com/aliyun/byte-unixbench/releases/download/v5.1.5/UnixBench-5.1.5.tar.gz; then
        echo "Failed to download UnixBench-5.1.5.tar.gz, please download it to ${cur_dir} directory manually and try again."
        exit 1
    fi
fi
tar -zxvf UnixBench-5.1.5.tar.gz && rm -f UnixBench-5.1.5.tar.gz
cd UnixBench/

#Run unixbench
make
./Run

echo
echo
echo "======= Script description and score comparison completed! ======= "
echo
echo
