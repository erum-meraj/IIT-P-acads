from scapy.all import *
import time
import sys

def ping(destination_ip, count=4, ttl=64, packet_size=64, timeout=1):
    # Ensure valid input
    if not isinstance(count, int) or count <= 0:
        raise ValueError("Count must be a positive integer")
    if not isinstance(ttl, int) or ttl <= 0:
        raise ValueError("TTL must be a positive integer")
    if not isinstance(packet_size, int) or packet_size <= 0:
        raise ValueError("Packet size must be a positive integer")
    if not isinstance(timeout, (int, float)) or timeout <= 0:
        raise ValueError("Timeout must be a positive number")
    

    sent_packets = 0
    received_packets = 0
    rtt_times = []

    # Perform ping
    print(f"Pinging {destination_ip} with {packet_size} bytes of data:")
    for i in range(count):
        try:
            # Send packet
            packet = IP(dst=destination_ip, ttl=ttl)/ICMP()/Raw(load=b'X'*packet_size)
            start_time = time.time()
            response = sr1(packet, timeout=timeout, verbose=False)
            end_time = time.time()
            
            # Check response
            if response:
                rtt = (end_time - start_time) * 1000  # Convert to milliseconds
                rtt_times.append(rtt)
                print(f"Reply from {destination_ip}: bytes={packet_size} time={rtt:.2f}ms TTL={response[IP].ttl}")
                received_packets += 1
            else:
                print(f"Request timed out.")
            
            sent_packets += 1
            time.sleep(1)  # Wait a second between pings

        except Exception as e:
            print(f"Error: {e}")
            continue

    # Summary
    packet_loss = ((sent_packets - received_packets) / sent_packets) * 100 if sent_packets else 100
    avg_rtt = sum(rtt_times) / len(rtt_times) if rtt_times else float('inf')
    min_rtt = min(rtt_times) if rtt_times else float('inf')
    max_rtt = max(rtt_times) if rtt_times else float('inf')
    
    print("\n--- Ping Statistics ---")
    print(f"Packets sent: {sent_packets}")
    print(f"Packets received: {received_packets}")
    print(f"Packet loss: {packet_loss:.2f}%")
    print(f"Average RTT: {avg_rtt:.2f}ms")
    print(f"Minimum RTT: {min_rtt:.2f}ms")
    print(f"Maximum RTT: {max_rtt:.2f}ms")

if __name__ == "__main__":
    try:
        # Sample usage: python ping_utility.py <destination_ip> <count> <ttl> <packet_size> <timeout>
        if len(sys.argv) < 2:
            raise ValueError("Destination IP is required")

        dest_ip = sys.argv[1]
        pkt_count = int(sys.argv[2]) if len(sys.argv) > 2 else 4
        ttl_value = int(sys.argv[3]) if len(sys.argv) > 3 else 64
        size_value = int(sys.argv[4]) if len(sys.argv) > 4 else 64
        timeout_value = float(sys.argv[5]) if len(sys.argv) > 5 else 1.0

        ping(dest_ip, pkt_count, ttl_value, size_value, timeout_value)

    except ValueError as e:
        print(f"Input error: {e}")
    except Exception as e:
        print(f"Unexpected error: {e}")
