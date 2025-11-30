from scapy.all import *
import time
import socket
import sys

def tracert(destination, max_ttl=30, packet_size=60, timeout=2, src_ip=None, pings_per_hop=3, delay=1, output_file=None):

    if output_file:
        try:
            f = open(output_file, 'w')
        except IOError:
            print(f"Error: Unable to open file {output_file} for writing.")
            return

    # Display and write the header
    header = "Hop\tIP Address\tRTT (ms)\tPacket Loss (%)"
    print(header)
    if output_file:
        f.write(header + "\n")

    for ttl in range(1, max_ttl + 1):
        rtt_list = []
        packet_loss = 0

        for _ in range(pings_per_hop):
            # Create the ICMP packet with specified TTL
            packet = IP(dst=destination, ttl=ttl) / ICMP()
            if src_ip:
                packet.src = src_ip

            # Record the start time
            start_time = time.time()
            # Send the packet and receive a reply
            reply = sr1(packet, verbose=0, timeout=timeout)
            # Record the end time
            end_time = time.time()

            if reply is None:
                rtt_list.append(None)
                packet_loss += 1
            else:
                rtt = (end_time - start_time) * 1000  # Convert to milliseconds
                rtt_list.append(rtt)

            time.sleep(delay)

        # Calculate average RTT and packet loss for this hop
        valid_rtts = [rtt for rtt in rtt_list if rtt is not None]
        avg_rtt = sum(valid_rtts) / len(valid_rtts) if valid_rtts else None
        packet_loss_percentage = (packet_loss / pings_per_hop) * 100

        # Prepare hop information for display
        hop_info = f"{ttl}\t"
        if valid_rtts:
            hop_info += f"{reply.src}\t{avg_rtt:.2f}\t{packet_loss_percentage:.1f}%"
        else:
            hop_info += "\t\t100%"

        print(hop_info)
        if output_file:
            f.write(hop_info + "\n")

        # Stop if the destination has been reached
        if reply and reply.src == destination:
            break

    if output_file:
        f.close()

def validate_input(destination, max_ttl, packet_size, timeout, src_ip):
    
    try:
        socket.gethostbyname(destination)
    except socket.error:
        raise ValueError("Invalid destination IP address")

    # Validate max TTL
    if not (1 <= max_ttl <= 255):
        raise ValueError("Max TTL must be between 1 and 255")

    # Validate packet size
    if packet_size < 28:  # Minimum size for IP/ICMP header
        raise ValueError("Packet size must be at least 28 bytes")

    # Validate timeout
    if timeout <= 0:
        raise ValueError("Timeout must be greater than 0")

    # Validate source IP
    if src_ip:
        try:
            socket.gethostbyname(src_ip)
        except socket.error:
            raise ValueError("Invalid source IP address")


try:
    # Collect user inputs
    destination_ip = input("Enter destination IP or hostname: ")
    max_ttl = int(input("Enter maximum TTL (default 30): ") or 30)
    packet_size = int(input("Enter packet size (default 60 bytes): ") or 60)
    timeout = float(input("Enter timeout in seconds (default 2): ") or 2)
    src_ip = input("Enter source IP (leave blank for default): ") or None
    pings_per_hop = int(input("Enter number of pings per hop (default 3): ") or 3)
    delay = float(input("Enter delay between pings in seconds (default 1): ") or 1)
    output_file = input("Enter output file name (leave blank for no file): ") or None

    # Validate inputs
    validate_input(destination_ip, max_ttl, packet_size, timeout, src_ip)

    # Perform traceroute
    tracert(destination_ip, max_ttl, packet_size, timeout, src_ip, pings_per_hop, delay, output_file)

except ValueError as ve:
    print(f"Input Error: {ve}")
except Exception as e:
    print(f"An unexpected error occurred: {e}")
