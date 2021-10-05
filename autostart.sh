#!/bin/sh
dte(){
	echo $(date +"%A %d %B - %H:%M")
}
upg(){
	upgrades="$(aptitude search '~U' | wc -l)"
	echo " $upgrades"
}
bat(){
	battery="$(cat /sys/class/power_supply/BAT0/capacity)%"
	echo " $battery"
}

while true; do
	xsetroot -name " $(dte) | $(upg) | $(bat) "
	sleep 30s
done
