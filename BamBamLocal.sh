#!/bin/bash
# Author: Juan Sacco <jsacco@exploitpack.com>
# Exploit Pack - https://exploitpack.com
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color
ropper="python3 libs/Ropper/Ropper.py "
ropgadget="python3 libs/ROPgadget/ROPgadget.py "

clear
printf "${GREEN}[*] BAM BAM Local Fuzzer/Exploiter - Author: Juan Sacco <jsacco@exploitpack.com>\n"
printf "[*] Description: Yet another simple arguments fuzzer for Linux.\n\n"
printf "${YELLOW}"
echo "                                         , /(.                                 " 
echo "               ./(#(/,  /%%/           .     ,.#                               " 
echo "            .((.        //*%**//**%**%%***#, .%*                               " 
echo "         (%               %***&(*(*/*****/**%.                                 " 
echo "       /(                   %%*(**/(#&%(***/*#*                                " 
echo "      ( .  #                    *#%#%#**//**%%%.                               " 
echo "      %* #.(             (./          .%(*//***%.(.                            " 
echo "       #/*.#           ,(..%     %../      .,. .*/*(*                          " 
echo "       .%,.,%          %....%  *(../            /, /                           " 
echo "        (/...%, (     */......,/.,#             %  /                           " 
echo "         %./...#%,#    %(,.......%              %                              " 
echo "          %........./%. %.......%,              %                              " 
echo "           /....................%           *  .%                              " 
echo "           *% ......*  #........%    ,     (   %*             .(#%%#(,         " 
echo "           ,,,.//(/.#%, ,.......%  ,%    %    %/        .%%((/((#######((((    " 
echo "         %........*,,,...........*/.##%**   /%     .#%#(//(#//((/(/(///(/((((  " 
echo "         *#...*....,%*.................%  *%   #%#(((((/#////((//(((((/(/(/((. " 
echo "           #(...#&&/%............#/(*,,#, (%((/(/(((//((/((///(#%%%%%(/((/((,  " 
echo "              .%*.,.........*%%,    *%#((//(/(/((((//((%((/(/(((#(#(/((((#/    " 
echo "                    (......./%##(((//((((/((/(((//((((((##/((((/((//%((%.      " 
echo "                  /%(.,.#(/(((((((//((((/((((/(/(/(((/((//(///(//%(#%,         " 
echo "             .%(/((/,....((//((((&#(((/(////(#((//(/(/((/(/((((%%(             " 
echo "         #/((((((/((%,....,(,.../,*                    .,*/*.                  " 
echo "          ###*  %.(.%%..........%..%.                                          " 
echo "               ./.,*.%%*.......%....*%                                         " 
echo "               (...%.*&%&#.../%.,...../#***%(                                  " 
echo "      #..#     (....%.*%%&%%..,    #..,(***%%*##                               " 
echo "   /%....*/   ,/...% ./,&#&..    ,(%%/**&*******%                              " 
echo "   %#./...,%,/.,,..*(.    %&&%&#(#%#/(&******(/%(#                             " 
echo "    /,..*../,#(....,/., %*#......(*******(&(**#& .                             " 
echo "     (#.............*#.(..%......*%%/**********%                               " 
echo "       /#..*%%%%#(#(/...*.,/.......,/#%*/%**((*,                               " 
echo "                   %....../.....,,...#***/*# *                                 " 
echo "                    %....,..#%.    **##, ,                                     " 
echo "                      %*(%/                                                   " 
printf "                   BAMM, BAMM RUBBLE!!! ~~~~ Son of Barney and Betty Rubble\n\n"

if [ "$(ulimit -c)" -eq "0" ]; then
	ulimit -c unlimited
	echo "[*] Setting ulimit to drop cores into the output folder"
fi

if [ "$(cat /proc/sys/kernel/core_pattern)" != "output/cores/core.%e.%p.%h.%t" ]; then
	echo "[!] Trying to set core pattern - BamBam needs root to set the core_pattern file"
	sudo sh -c "echo 'output/cores/core.%e.%p.%h.%t' > /proc/sys/kernel/core_pattern"
fi
	echo -e "[*] Cores pattern set correctly"
#	echo -e "[*] Ropper loaded correctly"
#	echo -e "[*] ROPGadget loaded correctly"
if [ $# -eq 0 ]
  then
    echo "[!] No arguments supplied"
    echo "[?] Please specify a PATH with binaries to test. "
    exit
fi
printf "${RED}"
read -n 1 -s -rep "`printf '[?] Press any key to start the fuzzer CTRL+C to quit\n'`"
printf "${NC}"
path_fuzz=$1
ls $path_fuzz > output/listbins
for file in `cat output/listbins`
do
	file `which $file` |grep ELF |awk '{print $1}'|tr -d : >> output/listbinaries
done

#script -c ./fuzz.sh -t out.log
# { IFS=:; ls -H $PATH; }
for i in `cat output/listbinaries`
do
echo $i
	timeout -s 9 2 strings $i | grep "^-" | sort -u  > output/arg_local.list

	printf "\n${RED} `date '+%H:%M:%S'` ${GREEN}[*] Fuzzing: $i ${RED} NoArgs\n"
	printf "${RED} `date '+%H:%M:%S'` ${YELLOW}[!] Running: $i AAAA..${NC}\n\n" 
	timeout -s 9 2 bash -c "$i `python2 -c 'print "A"*9000'`"
	base_name=`basename $i`	
	if [ $? -eq 139 ]; then
#                        zenity --info --text="Found: Segfault: $i AAAA.."
			echo "Found segfaul: $base_name " >> output/$base_name.crash
#			$ropper --file $i --chain execve > output/$base_name.ropperchain
#			$ropgadget --binary $i --ropchain  > output/$base_name.ropgadgetchain
        fi
	for args in `cat output/arg_local.list`;
	do
		printf "\n${GREEN} [*] Fuzzing: $i ${RED} Arguments: $args\n"
		printf "${YELLOW} [!] Running: $i $args AAAA..${NC}\n\n" 
		timeout -s 9 2 bash -c "$i $args `python2 -c 'print "A"*9000'`"
		if [ $? -eq 139 ]; then
# 			zenity --info --text="Found: Segfault: $i $args AAAA.."
			echo "Found segfaul: $base_name " >> output/$base_name.crash
#                        $ropper --file $i --chain execve > output/$base_name.ropperchain
#			$ropgadget --binary $i --ropchain  > output/$base_name.ropgadgetchain
		fi
	done;

done