#!/bin/sh
dte(){
	echo $(date +"%a %d %b")
}
tme(){
	echo $(date +"%H:%M")
}
upg(){
	UPGRADE=$(apt list --upgradeable | wc -l)
	echo " $((UPGRADE-1))"
}
int(){
	ETH=$(cat /sys/class/net/enp0s3/operstate)
	WIFI=$(cat /sys/class/net/wlo1/operstate)

	if [ "$ETH" = "up" ]; then
		echo ""
	elif [ "$WIFI" = "up" ]; then
		echo ""
	elif [ "$ETH" = "down" ] && [ "$WIFI" = "down"]; then
		echo ""
	fi
}
aud(){
	AUDIO=$(amixer get Master | tail -n1 | sed -r "s/.*\[(.*)%\].*/\1/")
	MUTE=$(pacmd list-sinks | awk '/muted/ {print $2 }')

	if [ "$MUTE" = "yes" ]; then
		echo " X"
	elif [ "$AUDIO" -ge 50 ]; then
		echo " $AUDIO"
	elif [ "$AUDIO" -lt 50 ] && [ "CHARGE" -ge 0 ]; then
		echo " $AUDIO"
	elif [ "$AUDIO" == 0 ]; then
		echo " $AUDIO"
	fi
}
bat(){
	CHARGE=$(cat /sys/class/power_supply/BAT0/capacity)
	STATUS=$(cat /sys/class/power_supply/BAT0/status)

	if [ "$STATUS" = "Charging" ]; then
		echo " $CHARGE%"
	elif [ "$CHARGE" -ge 90 ]; then
		echo " $CHARGE%"
	elif [ "$CHARGE" -lt 90 ] && [ "$CHARGE" -ge 65 ]; then
		echo " $CHARGE%"
	elif [ "$CHARGE" -lt 65 ] && [ "$CHARGE" -ge 45 ]; then
		echo " $CHARGE%"
	elif [ "$CHARGE" -lt 45 ] && [ "$CHARGE" -ge 15 ]; then
		echo " $CHARGE%"
	elif [ "$CHARGE" -lt 15 ]; then
		echo " $CHARGE%"
	fi
}

while true; do
	xsetroot -name "  $(dte) | $(upg) | $(aud) | $(bat) | $(tme) | $(int) "
	sleep 15s
done

