# Projet 2ARC - Firewall

## Avant de compiler le firewall

Installer *libnfnetlink*:
https://netfilter.org/projects/libnfnetlink/downloads.html

Installer *libnetfilter_queue*:
https://netfilter.org/projects/libnetfilter_queue/downloads.html

Après décompression:
```
./configure

make

sudo make install
```

## Avant d'exécuter le firewall

Configurer Iptables :
```
sudo iptables -A OUTPUT -p tcp -j NFQUEUE –queue-num 0

sudo sh -c "iptables-save > /etc/iptables.rules"

sudo nano /etc/network/interfaces
	add line: pre-up iptables-restore < /etc/iptables.rules
```
