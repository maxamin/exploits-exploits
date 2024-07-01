#!/bin/bash
GREEN='\033[0;32m'
RED='\033[0;31m'
WHITE='\033[1;37m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color
ropper="python Ropper-master/Ropper.py "
ropgadget="python ROPgadget-master/ROPgadget.py "
if [ "$EUID" -ne 0 ]
  then printf "${RED}[!] Sorry, I need root privileges!${NC}\n"
  exit
fi

rm programs.list > /dev/null 2>&1
rm arguments.list > /dev/null 2>&1
printf "${GREEN}[*] BAM BAM Fuzzer/Exploiter - Author: <jsacco>\n"
printf "[?] Package or meta-package to install: ${NC}\n"
ulimit -c > /dev/null
read program
apt-cache search $program | grep -v "^lib" | awk '{print $1}' > output/programs.list
printf "${GREEN}[*] Starting fuzzer for a set of: $(cat output/programs.list|wc -l)\n"
for i in `cat output/programs.list`;
do	
	printf "${WHITE}[`date '+%H:%M:%S'`]${GREEN} [*] Trying to apt-get: $i${NC}\n" 
	timeout -s 15 2 apt-get install -y $i > /dev/null 2>&1
	printf "${WHITE}[`date '+%H:%M:%S'`]${GREEN} [*] Package: $i installed\n"

	dpkg-query -L $i |grep bin/ > output/bins_from_package
	for bins_from_package in `cat output/bins_from_package`;
	do
		timeout -s 9 2 $strings bins_from_package | grep "^-" | sort -u  > output/arguments.list
		printf "\n${WHITE}[`date '+%H:%M:%S'`] ${GREEN}[*] Fuzzing: $bins_from_package ${RED} NoArgs\n"
		printf "${WHITE}[`date '+%H:%M:%S'`] ${YELLOW}[!] Running: $bins_from_package AAAA..${NC}\n\n" 
		timeout -s 9 2 bash -c "$bins_from_package `python2 -c 'print "A"*9000'`"	
		if [ $? -eq 139 ]; then
                        zenity --info --text="Found: Segfault: $bins_from_package AAAA.."
			echo "Found segfaul: $bins_from_package " > output/$i.crash
			$ropper --file $bins_from_package --chain execve > output/$i.ropperchain
			$ropgadget --binary $bins_from_package --ropchain  > output/$i.ropgadgetchain
        	fi
		for args in `cat output/arguments.list`;
		do
			printf "\n${WHITE}[`date '+%H:%M:%S'`] ${GREEN} [*] Fuzzing: $bins_from_package ${RED} Arguments: $args\n"
			printf "${WHITE}[`date '+%H:%M:%S'`] ${YELLOW} [!] Running: $bins_from_package $args AAAA..${NC}\n\n" 
			timeout -s 9 2 bash -c "$bins_from_package $args `python2 -c 'print "A"*9000'`"
			if [ $? -eq 139 ]; then
 				zenity --info --text="Found: Segfault: $bins_from_package $args AAAA.."
				echo "Found segfaul: $bins_from_package $args" > output/$i.crash
                        	$ropper --file `which $bins_from_package` --chain execve > output/$i.ropperchain
				$ropgadget --binary `which $bins_from_package` --ropchain  > output/$i.ropgadgetchain
			fi
		done;

	done;

done;