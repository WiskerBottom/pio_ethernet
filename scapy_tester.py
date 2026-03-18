from scapy.all import *
import time

# Set interface
iface = "eth0"

# Define MAC addresses
src_mac = "00:11:22:33:44:55"  # Your MAC (use 'ifconfig eth0' to check)
dst_mac = "ff:ff:ff:ff:ff:ff"  # Broadcast
eth_type = 0x0800  # IPv4

# Create a valid Ethernet frame (minimum 64 bytes)
# Ethernet header = 14 bytes
# IP header = 20 bytes (minimum)
# UDP header = 8 bytes
# Payload = 22 bytes (to reach 64 total)

frame = Ether(src=src_mac, dst=dst_mac, type=eth_type) / \
        IP(dst="192.168.1.1") / \
        UDP(dport=1234) / \
        "X" * 22  # Pad to 64 bytes total

# Check size
print(f"Frame size: {len(frame)} bytes")

# Send
while (1==1):
	sendp(frame, iface=iface, verbose=0)
	print("Sent 10 Mbps-compatible Ethernet frame")
	time.sleep(1)
