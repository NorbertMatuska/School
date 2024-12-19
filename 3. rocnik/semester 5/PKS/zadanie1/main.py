from scapy.all import rdpcap
from binascii import hexlify
import ruamel.yaml
from ruamel.yaml.scalarstring import LiteralScalarString


# get full path of the testing file
def testing_file():
    file_path = "vzorky_pcap_na_analyzu/"
    file_name = "trace-26.pcap"
    full_file_path = file_path + file_name

    return full_file_path


# ----------------------------------------------------------
# Functions for getting protocols and ports
# ----------------------------------------------------------
def get_ether_type(packet):
    ether_types = []
    with open("protocols/ethertype.txt", "r") as file:
        for line in file:
            # split by whitespace and append a tuple
            hex_value, name = line.strip().split()

            ether_types.append((hex_value, name))

    for i in range(len(ether_types)):
        if ether_types[i][0] == hexlify(packet[12:14]).decode().upper():
            ether_type = ether_types[i][1]
            return ether_type


def get_pid_type(packet):
    pid_types = []
    with open("protocols/pid.txt", "r") as file:
        for line in file:
            hex_value, name = line.strip().split()

            pid_types.append((hex_value, name))

    for x in range(len(pid_types)):
        if pid_types[x][0] == hexlify(packet[20:22]).decode().upper():
            pid_type = pid_types[x][1]
            return pid_type


def get_sap_type(packet):
    sap_types = []
    with open("protocols/sap.txt", "r") as file:
        for line in file:
            hex_value, name = line.strip().split()

            sap_types.append((hex_value, name))

    for i in range(len(sap_types)):
        if sap_types[i][0] == hexlify(packet[14:15]).decode().upper():
            sap_type = sap_types[i][1]
            return sap_type


def get_ipv4_protocol(packet):
    ipv4_protocols = []
    with open("protocols/ipv4_protocol.txt", "r") as file:
        for line in file:
            hex_value, name = line.strip().split()

            ipv4_protocols.append((hex_value, name))

    for i in range(len(ipv4_protocols)):
        if ipv4_protocols[i][0] == hexlify(packet[23:24]).decode().upper():
            ipv4_protocol = ipv4_protocols[i][1]
            return ipv4_protocol


def get_udp_protocol(packet):
    udp_protocols = []
    header_length = check_ipv4_length(packet)

    with open("protocols/udp_protocol.txt", "r") as file:
        for line in file:
            hex_value, name = line.strip().split()

            udp_protocols.append((hex_value, name))
    for i in range(len(udp_protocols)):
        if udp_protocols[i][0] == str(int(hexlify(packet[14 + header_length:16 + header_length]).decode().upper(), 16)):
            udp_protocol = udp_protocols[i][1]
            return udp_protocol
        elif udp_protocols[i][0] == str(
                int(hexlify(packet[16 + header_length:18 + header_length]).decode().upper(), 16)):
            udp_protocol = udp_protocols[i][1]
            return udp_protocol


def get_tcp_protocol(packet):
    tcp_protocols = []
    header_length = check_ipv4_length(packet)

    with open("protocols/tcp_protocol.txt", "r") as file:
        for line in file:
            hex_value, name = line.strip().split()

            tcp_protocols.append((hex_value, name))
    for i in range(len(tcp_protocols)):
        if tcp_protocols[i][0] == str(int(hexlify(packet[14 + header_length:16 + header_length]).decode().upper(), 16)):
            tcp_protocol = tcp_protocols[i][1]
            return tcp_protocol
        elif tcp_protocols[i][0] == str(
                int(hexlify(packet[16 + header_length:18 + header_length]).decode().upper(), 16)):
            tcp_protocol = tcp_protocols[i][1]
            return tcp_protocol


# checks IHL
def check_ipv4_length(packet):
    ihl = hexlify(packet[14:15]).decode().upper()
    ihl = ihl[1:]
    header_length = int(ihl, 16) * 4
    return header_length


# reads the file and returns it in byte form
def read_file():
    full_file_path = testing_file()
    packets = rdpcap(full_file_path)

    packet_bytes = []
    for packet in packets:
        packet_bytes.append(bytes(packet))

    return packet_bytes


# class for counting IP addresses for statistic purposes
class IP_Address_Counter:
    def __init__(self):
        self.ip_count_list = []

    def add_ip(self, src_ip):
        # if the ip address is already in the list, increment the counter
        for item in self.ip_count_list:
            if item[0] == src_ip:
                item[1] += 1
                return
        # otherwise append the new ip address into the list
        self.ip_count_list.append([src_ip, 1])

    def print_all(self):
        return self.ip_count_list

    def get_most_common_ip(self):
        if not self.ip_count_list:
            return None

        most_common_ips = []
        most_common_count = 0

        # returns the ip that has occured the most
        for item in self.ip_count_list:
            if item[1] > most_common_count:
                most_common_ips = [item[0]]
                most_common_count = item[1]
            elif item[1] == most_common_count:
                most_common_ips.append(item[0])

        return most_common_ips

    # appends statistics to output file
    def print_to_yaml(self):
        ipv4_stats = []
        yaml = ruamel.yaml.YAML()

        for item in self.ip_count_list:
            data = {
                "node": item[0],
                "number_of_sent_packets": item[1],
            }
            ipv4_stats.append(data)

        with open("hexdump.yaml", "a") as file:
            file.write("\n")
            yaml.dump({"ipv4_senders": ipv4_stats}, file)
            most_common_ips = self.get_most_common_ip()
            file.write("\nmax_send_packets_by:\n")
            for i in range(len(most_common_ips)):
                file.write("  - " + most_common_ips[i])
                if i != (len(most_common_ips) - 1):
                    file.write("\n")


# converts hexadecimal ip into decimal ip with formatting
def hex_to_ip(ip):
    formatted_ip = ""
    tmp = []
    for x in range(0, len(ip), 2):
        pair = ip[x:x + 2]
        tmp.append(pair)
    for i in range(len(tmp)):
        formatted_ip += str(int(tmp[i], 16))
        if i != (len(tmp) - 1):
            formatted_ip += "."
    return formatted_ip


# formats the hexa frame with added whitespace every 1 byte
# and a newline every 16 bytes
def format_hexa_frame(hexa_frame):
    formatted_hexa_frame = ""
    for i in range(len(hexa_frame)):
        formatted_hexa_frame += hexa_frame[i]
        if (i + 1) % 32 == 0:
            formatted_hexa_frame += "\n"
        elif (i + 1) % 2 == 0:
            if (i + 1) != len(hexa_frame):
                formatted_hexa_frame += " "

    if not len(hexa_frame) % 32 == 0:
        formatted_hexa_frame += "\n"
    return formatted_hexa_frame


def uloha1():
    packet_bytes = read_file()
    yaml = ruamel.yaml.YAML()

    full_file_path = testing_file()
    file_parts = full_file_path.split("/")
    file_name = file_parts[-1]
    print("Testing file: " + file_name)

    packets_array = []

    # initialize an instance of the ip counter class
    ip_counter = IP_Address_Counter()

    for i in range(len(packet_bytes)):
        packet = packet_bytes[i]

        frame_len = len(packet)
        if (len(packet) + 4) < 64:
            frame_len_medium = 64
        else:
            frame_len_medium = len(packet) + 4
        src_mac = hexlify(packet[6:12]).decode().upper()
        dst_mac = hexlify(packet[0:6]).decode().upper()
        hexa_frame = hexlify(packet).decode().upper()

        formatted_hex_frame = format_hexa_frame(hexa_frame)
        # 0 - starting index, 12 - ending index, 2 - step
        src_mac = ":".join([src_mac[i:i + 2] for i in range(0, 12, 2)])
        dst_mac = ":".join([dst_mac[i:i + 2] for i in range(0, 12, 2)])

        # initialize variables that are not in every frame
        ether_type = None
        sap_type = None
        pid_type = None

        src_ip = None
        dst_ip = None
        ipv4_protocol = None
        app_protocol = None

        src_port = None
        dst_port = None

        arp_opcode = None

        # num_dec = int(str(hexlify(packet[12:14]))[2: -1], 16)
        # ether_type size
        num_dec = int(hexlify(packet[12:14]).decode(), 16)
        if num_dec > 1500:
            frame_type = "ETHERNET II"
            ether_type = get_ether_type(packet)

            if ether_type == "IPv4":
                # get ips and count them
                src_ip = hex_to_ip(hexlify(packet[26:30]).decode().upper())
                ip_counter.add_ip(src_ip)
                dst_ip = hex_to_ip(hexlify(packet[30:34]).decode().upper())

                ipv4_protocol = get_ipv4_protocol(packet)
                if ipv4_protocol == "UDP":
                    app_protocol = get_udp_protocol(packet)
                    # as we are inside ipv4 protocol, we need to check for IHL
                    header_length = check_ipv4_length(packet)
                    src_port = int(hexlify(packet[14 + header_length:16 + header_length]), 16)
                    dst_port = int(hexlify(packet[16 + header_length:18 + header_length]), 16)
                elif ipv4_protocol == "TCP":
                    app_protocol = get_tcp_protocol(packet)

                    header_length = check_ipv4_length(packet)
                    src_port = int(hexlify(packet[14 + header_length:16 + header_length]), 16)
                    dst_port = int(hexlify(packet[16 + header_length:18 + header_length]), 16)
            elif ether_type == "ARP":
                tmp_opcode = int(hexlify(packet[20:22]), 16)
                if tmp_opcode == 1:
                    arp_opcode = "REQUEST"
                elif tmp_opcode == 2:
                    arp_opcode = "REPLY"
                src_ip = hex_to_ip(hexlify(packet[28:32]).decode().upper())
                dst_ip = hex_to_ip(hexlify(packet[38:42]).decode().upper())

        else:
            if hexlify(packet[14:16]).decode() == "aaaa":
                frame_type = "IEEE 802.3 LLC & SNAP"
                pid_type = get_pid_type(packet)
            elif hexlify(packet[14:16]).decode() == "ffff":
                frame_type = "IEEE 802.3 RAW"
            else:
                frame_type = "IEEE 802.3 LLC"
                sap_type = get_sap_type(packet)
        # store data of each packet inside a dictionary
        data = {
            "frame_number": i + 1,
            "len_frame_pcap": frame_len,
            "len_frame_medium": frame_len_medium,
            "frame_type": frame_type,
            "src_mac": src_mac,
            "dst_mac": dst_mac,
            # only if its not None will it store inside a dictionary
            **({"ether_type": ether_type} if ether_type is not None else {}),
            **({"arp_opcode": arp_opcode} if arp_opcode is not None else {}),
            **({"src_ip": src_ip} if src_ip is not None else {}),
            **({"dst_ip": dst_ip} if dst_ip is not None else {}),
            **({"protocol": ipv4_protocol} if ipv4_protocol is not None else {}),
            **({"src_port": src_port} if src_port is not None else {}),
            **({"dst_port": dst_port} if dst_port is not None else {}),
            **({"app_protocol": app_protocol} if app_protocol is not None else {}),
            **({"sap": sap_type} if sap_type is not None else {}),
            **({"pid": pid_type} if pid_type is not None else {}),
            "hexa_frame": LiteralScalarString(formatted_hex_frame),
        }
        # append packet data in a list
        packets_array.append(data)

    start_data = {
        "name": "PKS2023/24",
        "pcap_name": file_name,
    }

    with open("hexdump.yaml", "w") as file1:
        yaml.dump(start_data, file1)

    with open("hexdump.yaml", "a") as yaml_file:
        yaml.default_flow_style = False
        yaml.explicit_start = False
        yaml.dump({"packets": packets_array}, yaml_file)

    ip_counter.print_to_yaml()

    return packets_array


def uloha_4_arp(packet_array):
    arp_array = []
    # get all arp packets
    for i in range(len(packet_array)):
        if packet_array[i]["frame_type"] == "ETHERNET II":
            if "ether_type" in packet_array[i]:
                if packet_array[i]["ether_type"] == "ARP":
                    arp_array.append(packet_array[i])

    completed_comm = []
    completed_comm_pairs = []
    for i in range(len(arp_array)):
        if arp_array[i]["arp_opcode"] == "REQUEST":
            x = i + 1  # start searching for replies from the next element

            while x < len(arp_array):
                # if a pair is found append it to the list
                if arp_array[x]["arp_opcode"] == "REPLY" and arp_array[x]["src_ip"] == arp_array[i]["dst_ip"] and \
                        arp_array[i]["src_ip"] == arp_array[x]["dst_ip"]:
                    completed_comm_pairs.append(arp_array[i])
                    completed_comm_pairs.append(arp_array[x])
                    break
                x += 1
    for packet in completed_comm_pairs:
        src_ip = packet["src_ip"]
        dst_ip = packet["dst_ip"]

        group_found = False
        # group the pairs based on ips in one communication
        for group in completed_comm:
            # check if there is an existing group with the same src_ip and dst_ip
            if src_ip == group[0]["src_ip"] and dst_ip == group[0]["dst_ip"] \
                    or src_ip == group[0]["dst_ip"] and dst_ip == group[0]["src_ip"]:
                group.append(packet)
                group_found = True
                break
        if not group_found:
            # if not, create new communication
            completed_comm.append([packet])
    partial_comms_unsorted = []
    # get the rest of packets without a pair
    for packet in arp_array:
        if packet not in completed_comm_pairs:
            partial_comms_unsorted.append(packet)
    partial_comms = []
    for i in range(len(partial_comms_unsorted)):
        src_ip = partial_comms_unsorted[i]["src_ip"]
        dst_ip = partial_comms_unsorted[i]["dst_ip"]

        # check if there is an existing group with the same src_ip and dst_ip
        group_index = None
        for j in range(len(partial_comms)):
            if partial_comms[j][0]["src_ip"] == src_ip and partial_comms[j][0]["dst_ip"] == dst_ip:
                group_index = j
                break

        if group_index is not None:
            # append the communication to the existing group
            partial_comms[group_index].append(partial_comms_unsorted[i])
        else:
            # create a new group for this communication
            partial_comms.append([partial_comms_unsorted[i]])

    full_file_path = testing_file()
    file_parts = full_file_path.split("/")
    file_name = file_parts[-1]
    yaml = ruamel.yaml.YAML()

    start_data = {
        "name": "PKS2023/24",
        "pcap_name": file_name,
        "filter_name": "ARP",
    }
    with open("hexdump_arp.yaml", "w") as file:
        yaml.dump(start_data, file)
    if len(completed_comm) > 0:
        with open("hexdump_arp.yaml", "a") as file:
            comm_counter = 1

            file.write("complete_comms:\n")
            for group in completed_comm:
                file.write("  - number_comm: " + str(comm_counter) + "\n")
                file.write("    packets:\n")
                for communication in group:
                    file.write("      - frame_number: " + str(communication["frame_number"]) + "\n")
                    file.write("        len_frame_pcap: " + str(communication["len_frame_pcap"]) + "\n")
                    file.write("        len_frame_medium: " + str(communication["len_frame_medium"]) + "\n")
                    file.write("        frame_type: " + str(communication["frame_type"]) + "\n")
                    file.write("        src_mac: " + str(communication["src_mac"]) + "\n")
                    file.write("        dst_mac: " + str(communication["dst_mac"]) + "\n")
                    file.write("        ether_type: " + str(communication["ether_type"]) + "\n")
                    file.write("        arp_opcode: " + str(communication["arp_opcode"]) + "\n")
                    file.write("        src_ip: " + str(communication["src_ip"]) + "\n")
                    file.write("        dst_ip: " + str(communication["dst_ip"]) + "\n")
                    file.write("        hexa_frame: |\n")
                    frame_list = communication["hexa_frame"].split("\n")
                    for i in range(len(frame_list)):
                        if i < (len(frame_list) - 1):
                            file.write("          " + frame_list[i] + "\n")
                    file.write("\n")
                comm_counter += 1

    if len(partial_comms) > 0:
        with open("hexdump_arp.yaml", "a") as file:
            comm_counter = 1

            file.write("partial_comms:\n")
            for group in partial_comms:
                file.write("  - number_comm: " + str(comm_counter) + "\n")
                file.write("    packets:\n")
                for communication in group:
                    file.write("      - frame_number: " + str(communication["frame_number"]) + "\n")
                    file.write("        len_frame_pcap: " + str(communication["len_frame_pcap"]) + "\n")
                    file.write("        len_frame_medium: " + str(communication["len_frame_medium"]) + "\n")
                    file.write("        frame_type: " + str(communication["frame_type"]) + "\n")
                    file.write("        src_mac: " + str(communication["src_mac"]) + "\n")
                    file.write("        dst_mac: " + str(communication["dst_mac"]) + "\n")
                    file.write("        ether_type: " + str(communication["ether_type"]) + "\n")
                    file.write("        arp_opcode: " + str(communication["arp_opcode"]) + "\n")
                    file.write("        src_ip: " + str(communication["src_ip"]) + "\n")
                    file.write("        dst_ip: " + str(communication["dst_ip"]) + "\n")
                    file.write("        hexa_frame: |\n")
                    frame_list = communication["hexa_frame"].split("\n")
                    for i in range(len(frame_list)):
                        if i < (len(frame_list) - 1):
                            file.write("          " + frame_list[i] + "\n")
                    file.write("\n")
                comm_counter += 1


def get_icmp_types(icmp_type):
    icmp_types = []
    with open("protocols/icmp_types.txt", "r") as file:
        for line in file:
            # split by ":"
            parts = line.strip().split(":")
            icmp_types.append(parts)

    # check for a match
    for i in range(len(icmp_types)):
        if str(icmp_type) == str(icmp_types[i][0]):
            icmp_type = icmp_types[i][1]
            return icmp_type
    # if there was not a match, return None (that means the packet is probably fragmented)
    return None


def uloha_4_icmp(packet_array):
    packet_bytes = read_file()
    # initialize two arrays: one for analyzed packet and one for the same packet but in a raw form
    icmp_array = []
    icmp_bytes = []
    # get all icmp packets
    for i in range(len(packet_array)):
        if packet_array[i]["frame_type"] == "ETHERNET II":
            if "ether_type" in packet_array[i]:
                if packet_array[i]["ether_type"] == "IPv4":
                    if "protocol" in packet_array[i]:
                        if packet_array[i]["protocol"] == "ICMP":
                            icmp_array.append(packet_array[i])
                            icmp_bytes.append(packet_bytes[i])

    i = 0
    # iterate through raw packets and get type, id and seqn
    for packet in icmp_bytes:
        header_length = check_ipv4_length(packet)

        icmp_type = int(hexlify(packet[14+header_length:15+header_length]), 16)
        icmp_id = int(hexlify(packet[18+header_length:20+header_length]), 16)
        icmp_seq = int(hexlify(packet[20+header_length:22+header_length]), 16)

        icmp_type = get_icmp_types(icmp_type)

        if icmp_type is not None:
            icmp_array[i]["icmp_type"] = icmp_type
            icmp_array[i]["icmp_id"] = icmp_id
            icmp_array[i]["icmp_seq"] = icmp_seq
        i += 1
    complete_comms_pairs = []
    complete_comms = []
    # find pairs for completed communication
    for i in range(len(icmp_array)):
        j = i + 1
        if "icmp_type" in icmp_array[i]:
            if icmp_array[i]["icmp_type"] == "ECHO REQUEST":
                while j < len(icmp_array):
                    if "icmp_id" in icmp_array[j]:
                        # echo reply has the same id and seqn
                        if icmp_array[i]["icmp_id"] == icmp_array[j]["icmp_id"]:
                            if icmp_array[i]["icmp_seq"] == icmp_array[j]["icmp_seq"]:
                                complete_comms_pairs.append(icmp_array[i])
                                complete_comms_pairs.append(icmp_array[j])
                                break
                        # completed comm can also be even if time exceeded
                        elif icmp_array[i]["icmp_type"] == "TIME EXCEEDED":
                            if icmp_array[i]["src_ip"] == icmp_array[j]["dst_ip"]:
                                if icmp_array[i]["dst_ip"] == icmp_array[j]["src_ip"]:
                                    complete_comms_pairs.append(icmp_array[i])
                                    complete_comms_pairs.append(icmp_array[j])
                                    break
                    j += 1

    for packet in complete_comms_pairs:
        src_ip = packet["src_ip"]
        dst_ip = packet["dst_ip"]

        group_found = False
        # group pairs of completed comms based on ips
        for group in complete_comms:
            if src_ip == group[0]["src_ip"] and dst_ip == group[0]["dst_ip"] \
                    or src_ip == group[0]["dst_ip"] and dst_ip == group[0]["src_ip"]:

                group.append(packet)
                group_found = True
                break
        if not group_found:
            complete_comms.append([packet])

    partial_comms_unsorted = []
    partial_comms = []
    # get the rest of unpaired packets
    for packet in icmp_array:
        if "icmp_type" in packet:
            if packet not in complete_comms_pairs:
                partial_comms_unsorted.append(packet)

    for packet in partial_comms_unsorted:
        src_ip = packet["src_ip"]
        dst_ip = packet["dst_ip"]

        group_found = False
        # group partial comms based on ips
        for group in partial_comms:
            if src_ip == group[0]["src_ip"] and dst_ip == group[0]["dst_ip"] \
                    or src_ip == group[0]["dst_ip"] and dst_ip == group[0]["src_ip"]:

                group.append(packet)
                group_found = True
                break
        if not group_found:
            partial_comms.append([packet])

    full_file_path = testing_file()
    file_parts = full_file_path.split("/")
    file_name = file_parts[-1]
    with open("hexdump_icmp.yaml", "w") as file:
        file.write("name: PKS2023/24\n")
        file.write("pcap_name: " + str(file_name) + "\n")
        file.write("filter_name: ICMP\n")

    if len(complete_comms) > 0:
        with open("hexdump_icmp.yaml", "a") as file:
            comm_counter = 1

            file.write("complete_comms:\n")
            for group in complete_comms:
                file.write("  - number_comm: " + str(comm_counter) + "\n")
                file.write("    src_comm: " + str(group[0]["src_ip"]) + "\n")
                file.write("    dst_comm: " + str(group[0]["dst_ip"]) + "\n")
                file.write("    packets:\n")
                for communication in group:
                    file.write("      - frame_number: " + str(communication["frame_number"]) + "\n")
                    file.write("        len_frame_pcap: " + str(communication["len_frame_pcap"]) + "\n")
                    file.write("        len_frame_medium: " + str(communication["len_frame_medium"]) + "\n")
                    file.write("        frame_type: " + str(communication["frame_type"]) + "\n")
                    file.write("        src_mac: " + str(communication["src_mac"]) + "\n")
                    file.write("        dst_mac: " + str(communication["dst_mac"]) + "\n")
                    file.write("        ether_type: " + str(communication["ether_type"]) + "\n")
                    file.write("        src_ip: " + str(communication["src_ip"]) + "\n")
                    file.write("        dst_ip: " + str(communication["dst_ip"]) + "\n")
                    file.write("        protocol: " + str(communication["protocol"]) + "\n")
                    file.write("        icmp_type: " + str(communication["icmp_type"]) + "\n")
                    file.write("        icmp_id: " + str(communication["icmp_id"]) + "\n")
                    file.write("        icmp_seq: " + str(communication["icmp_seq"]) + "\n")
                    file.write("        hexa_frame: |\n")
                    frame_list = communication["hexa_frame"].split("\n")
                    for i in range(len(frame_list)):
                        if i < (len(frame_list) - 1):
                            file.write("          " + frame_list[i] + "\n")
                    file.write("\n")
                comm_counter += 1

    if len(partial_comms) > 0:
        with open("hexdump_icmp.yaml", "a") as file:
            comm_counter = 1

            file.write("partial_comms:\n")
            for group in partial_comms:
                file.write("  - number_comm: " + str(comm_counter) + "\n")
                file.write("    packets:\n")
                for communication in group:
                    file.write("      - frame_number: " + str(communication["frame_number"]) + "\n")
                    file.write("        len_frame_pcap: " + str(communication["len_frame_pcap"]) + "\n")
                    file.write("        len_frame_medium: " + str(communication["len_frame_medium"]) + "\n")
                    file.write("        frame_type: " + str(communication["frame_type"]) + "\n")
                    file.write("        src_mac: " + str(communication["src_mac"]) + "\n")
                    file.write("        dst_mac: " + str(communication["dst_mac"]) + "\n")
                    file.write("        ether_type: " + str(communication["ether_type"]) + "\n")
                    file.write("        src_ip: " + str(communication["src_ip"]) + "\n")
                    file.write("        dst_ip: " + str(communication["dst_ip"]) + "\n")
                    file.write("        protocol: " + str(communication["protocol"]) + "\n")
                    file.write("        icmp_type: " + str(communication["icmp_type"]) + "\n")
                    # file.write("        icmp_id: " + str(communication["icmp_id"]) + "\n")
                    # file.write("        icmp_seq: " + str(communication["icmp_seq"]) + "\n")
                    file.write("        hexa_frame: |\n")
                    frame_list = communication["hexa_frame"].split("\n")
                    for i in range(len(frame_list)):
                        if i < (len(frame_list) - 1):
                            file.write("          " + frame_list[i] + "\n")
                    file.write("\n")
                comm_counter += 1


def uloha_4_tftp(packet_array):
    packet_bytes = read_file()

    tftp_array = []
    tftp_bytes = []
    # get all udp protocols
    for i in range(len(packet_array)):
        if packet_array[i]["frame_type"] == "ETHERNET II":
            if "ether_type" in packet_array[i]:
                if packet_array[i]["ether_type"] == "IPv4":
                    if "protocol" in packet_array[i]:
                        if packet_array[i]["protocol"] == "UDP":
                            tftp_array.append(packet_array[i])
                            tftp_bytes.append(packet_bytes[i])
    complete_comms = []
    partial_comms = []
    # iterate through the whole list of tftp
    for i, packet in enumerate(tftp_array):
        header_length = check_ipv4_length(tftp_bytes[i])
        packet["tftp_opcode"] = int(hexlify(tftp_bytes[i][22+header_length:24+header_length]).decode(), 16)
        if packet["tftp_opcode"] == 1:  # Read Request
            current_communication = [packet]
            src_port = packet["src_port"]
            next_comm = i + 1
            last_data_packet_size = 0
            # iterate through the whole list after the packet with read request
            while next_comm < len(tftp_array):
                next_packet = tftp_array[next_comm]
                header_length = check_ipv4_length(tftp_bytes[next_comm])
                next_packet["tftp_opcode"] = int(
                    hexlify(tftp_bytes[next_comm][22+header_length:24+header_length]).decode(), 16)
                next_packet["block"] = int(
                    hexlify(tftp_bytes[next_comm][24+header_length:26+header_length]).decode(), 16)
                # find data packet with the same ports
                if src_port == next_packet["dst_port"] or src_port == next_packet["src_port"]:
                    if next_packet["tftp_opcode"] == 3:  # Data
                        data_packet_size = next_packet["len_frame_pcap"]

                        ack_packet_num = next_comm + 1
                        # iterate through the whole list after the data packet
                        if ack_packet_num < len(tftp_array):
                            ack_packet = tftp_array[ack_packet_num]
                            header_length = check_ipv4_length(tftp_bytes[ack_packet_num])
                            ack_packet["tftp_opcode"] = int(
                                hexlify(tftp_bytes[ack_packet_num][22+header_length:24+header_length]).decode(), 16)
                            ack_packet["block"] = int(
                                hexlify(tftp_bytes[ack_packet_num][24+header_length:26+header_length]).decode(), 16)
                            # find ack packet with same block number
                            if (
                                    ack_packet["tftp_opcode"] == 4
                                    and ack_packet["block"] == next_packet["block"]
                            ):
                                current_communication.append(next_packet)  # add data packet to the communication
                                current_communication.append(ack_packet)  # add ack packet
                                if data_packet_size < last_data_packet_size:
                                    complete_comms.append(current_communication)
                                    break
                                last_data_packet_size = data_packet_size
                            elif ack_packet["tftp_opcode"] == 5:  # Error
                                # Communication ends if there's an error packet
                                current_communication.append(next_packet)
                                current_communication.append(ack_packet)
                                complete_comms.append(current_communication)
                                break
                            else:
                                # ACK missing
                                partial_comms.append(current_communication)
                                break
                        else:
                            # EOF no ack no error
                            partial_comms.append(current_communication)
                            break

                    elif next_packet["tftp_opcode"] == 5:  # Error
                        # Communication ends if there's an error packet
                        current_communication.append(next_packet)
                        complete_comms.append(current_communication)
                        break
                    next_comm += 1

                else:
                    # Communication ends if the source or destination port changes
                    partial_comms.append(current_communication)
                    break

        # same logic as Read Request
        elif packet["tftp_opcode"] == 2:  # Write Request
            current_communication = [packet]
            src_port = packet["src_port"]
            next_comm = i + 1
            last_data_packet_size = 0
            block_num = 0
            while next_comm < len(tftp_array):
                next_packet = tftp_array[next_comm]
                header_length = check_ipv4_length(tftp_bytes[next_comm])
                next_packet["tftp_opcode"] = int(
                    hexlify(tftp_bytes[next_comm][22+header_length:24+header_length]).decode(), 16)
                next_packet["block"] = int(
                    hexlify(tftp_bytes[next_comm][24+header_length:26+header_length]).decode(), 16)

                if src_port == next_packet["dst_port"] or src_port == next_packet["src_port"]:
                    if next_packet["tftp_opcode"] == 4:  # ack
                        if next_packet["block"] == block_num:  # first ACK for write request
                            current_communication.append(next_packet)
                    elif next_packet["tftp_opcode"] == 3:  # data
                        data_packet_size = next_packet["len_frame_pcap"]

                        # Check for the ACK packet with the same block number
                        ack_packet_num = next_comm + 1
                        if ack_packet_num < len(tftp_array):
                            ack_packet = tftp_array[ack_packet_num]
                            header_length = check_ipv4_length(tftp_bytes[ack_packet_num])
                            ack_packet["tftp_opcode"] = int(
                                hexlify(tftp_bytes[ack_packet_num][22 + header_length:24 + header_length]).decode(), 16)
                            ack_packet["block"] = int(
                                hexlify(tftp_bytes[ack_packet_num][24 + header_length:26 + header_length]).decode(), 16)
                            if (
                                    ack_packet["tftp_opcode"] == 4
                                    and ack_packet["block"] == next_packet["block"]
                            ):
                                current_communication.append(next_packet)  # add data packet to the communication
                                current_communication.append(ack_packet)  # add ack packet
                                if data_packet_size < last_data_packet_size:
                                    complete_comms.append(current_communication)
                                    break
                                last_data_packet_size = data_packet_size
                            elif ack_packet["tftp_opcode"] == 5:  # Error
                                # Communication ends if there's an error packet
                                current_communication.append(next_packet)
                                current_communication.append(ack_packet)
                                complete_comms.append(current_communication)
                                break
                            else:
                                # ACK not found
                                partial_comms.append(current_communication)
                                break
                        else:
                            # EOF no ack no error
                            partial_comms.append(current_communication)
                            break

                    elif next_packet["tftp_opcode"] == 5:  # Error
                        # Communication ends if there's an error packet
                        current_communication.append(next_packet)
                        complete_comms.append(current_communication)
                        break
                    next_comm += 1
                    if (next_comm + 1) == len(tftp_array):
                        partial_comms.append(current_communication)
                        break

                else:
                    # Communication ends if the source or destination port changes
                    partial_comms.append(current_communication)
                    break

    full_file_path = testing_file()
    file_parts = full_file_path.split("/")
    file_name = file_parts[-1]

    with open("hexdump_tftp.yaml", "w") as file:
        file.write("name: PKS2023/24\n")
        file.write("pcap_name: " + file_name + "\n")
        file.write("filter_name: TFTP\n")
    with open("hexdump_tftp.yaml", "a") as file:
        comm_counter = 1
        file.write("complete_comms:\n")
        for group in complete_comms:
            file.write("  - number_comm: " + str(comm_counter) + "\n")
            file.write("    src_comm: " + str(group[0]["src_ip"]) + "\n")
            file.write("    dst_comm: " + str(group[0]["dst_ip"]) + "\n")
            file.write("    packets:\n")
            for communication in group:
                file.write("      - frame_number: " + str(communication["frame_number"]) + "\n")
                file.write("        len_frame_pcap: " + str(communication["len_frame_pcap"]) + "\n")
                file.write("        len_frame_medium: " + str(communication["len_frame_medium"]) + "\n")
                file.write("        frame_type: " + str(communication["frame_type"]) + "\n")
                file.write("        src_mac: " + str(communication["src_mac"]) + "\n")
                file.write("        dst_mac: " + str(communication["dst_mac"]) + "\n")
                file.write("        ether_type: " + str(communication["ether_type"]) + "\n")
                file.write("        src_ip: " + str(communication["src_ip"]) + "\n")
                file.write("        dst_ip: " + str(communication["dst_ip"]) + "\n")
                file.write("        protocol: " + str(communication["protocol"]) + "\n")
                file.write("        src_port: " + str(communication["src_port"]) + "\n")
                file.write("        dst_port: " + str(communication["dst_port"]) + "\n")
                file.write("        app_protocol: TFTP\n")
#                file.write("        tftp_opcode: " + str(communication["tftp_opcode"]) + "\n")
#                if "block" in communication:
#                    file.write("        block: " + str(communication["block"]) + "\n")
                file.write("        hexa_frame: |\n")
                frame_list = communication["hexa_frame"].split("\n")
                for i in range(len(frame_list)):
                    if i < (len(frame_list) - 1):
                        file.write("          " + frame_list[i] + "\n")
                file.write("\n")
            comm_counter += 1
    with open("hexdump_tftp.yaml", "a") as file:
        comm_counter = 1
        file.write("partial_comms:\n")
        for group in partial_comms:
            file.write("  - number_comm: " + str(comm_counter) + "\n")
            file.write("    packets:\n")
            for communication in group:
                file.write("      - frame_number: " + str(communication["frame_number"]) + "\n")
                file.write("        len_frame_pcap: " + str(communication["len_frame_pcap"]) + "\n")
                file.write("        len_frame_medium: " + str(communication["len_frame_medium"]) + "\n")
                file.write("        frame_type: " + str(communication["frame_type"]) + "\n")
                file.write("        src_mac: " + str(communication["src_mac"]) + "\n")
                file.write("        dst_mac: " + str(communication["dst_mac"]) + "\n")
                file.write("        ether_type: " + str(communication["ether_type"]) + "\n")
                file.write("        src_ip: " + str(communication["src_ip"]) + "\n")
                file.write("        dst_ip: " + str(communication["dst_ip"]) + "\n")
                file.write("        protocol: " + str(communication["protocol"]) + "\n")
                file.write("        src_port: " + str(communication["src_port"]) + "\n")
                file.write("        dst_port: " + str(communication["dst_port"]) + "\n")
                file.write("        app_protocol: TFTP\n")
#                file.write("        tftp_opcode: " + str(communication["tftp_opcode"]) + "\n")
#                if "block" in communication:
#                    file.write("        block: " + str(communication["block"]) + "\n")
                file.write("        hexa_frame: |\n")
                frame_list = communication["hexa_frame"].split("\n")
                for i in range(len(frame_list)):
                    if i < (len(frame_list) - 1):
                        file.write("          " + frame_list[i] + "\n")
                file.write("\n")
            comm_counter += 1


def uloha_4_frag(packet_array):
    packet_bytes = read_file()

    icmp_array = []
    icmp_bytes = []
    for i in range(len(packet_array)):
        if packet_array[i]["frame_type"] == "ETHERNET II":
            if "ether_type" in packet_array[i]:
                if packet_array[i]["ether_type"] == "IPv4":
                    if "protocol" in packet_array[i]:
                        if packet_array[i]["protocol"] == "ICMP":
                            icmp_array.append(packet_array[i])
                            icmp_bytes.append(packet_bytes[i])

    i = 0
    # same as in icmp function except for pairing the fragmented packets
    for packet in icmp_bytes:
        header_length = check_ipv4_length(packet)

        ip_id = int(hexlify(packet[18:20]), 16)
        icmp_array[i]["id"] = ip_id

        flag_and_offset = hexlify(packet[20:22]).decode().upper()
        flag = flag_and_offset[0]
        frag_offset = int(flag_and_offset[1:], 16) * 8
        if int(flag) == 2:
            icmp_array[i]["flags_mf"] = "true"
            icmp_array[i]["frag_offset"] = frag_offset
        else:
            icmp_array[i]["flags_mf"] = "false"
            icmp_array[i]["frag_offset"] = frag_offset
        icmp_type = int(hexlify(packet[14 + header_length:15 + header_length]), 16)
        icmp_id = int(hexlify(packet[18 + header_length:20 + header_length]), 16)
        icmp_seq = int(hexlify(packet[20 + header_length:22 + header_length]), 16)

        icmp_type = get_icmp_types(icmp_type)

        if icmp_type is not None:
            icmp_array[i]["icmp_type"] = icmp_type
            icmp_array[i]["icmp_id"] = icmp_id
            icmp_array[i]["icmp_seq"] = icmp_seq

        i += 1

    complete_comms_pairs = []
    complete_comms = []
    for i in range(len(icmp_array)):
        j = i + 1
        if "icmp_type" in icmp_array[i]:
            if icmp_array[i]["icmp_type"] == "ECHO REQUEST":
                while j < len(icmp_array):
                    if "icmp_id" in icmp_array[j]:
                        if icmp_array[i]["icmp_id"] == icmp_array[j]["icmp_id"]:
                            if icmp_array[i]["icmp_seq"] == icmp_array[j]["icmp_seq"]:
                                complete_comms_pairs.append(icmp_array[i])
                                complete_comms_pairs.append(icmp_array[j])
                                break
                        elif icmp_array[i]["icmp_type"] == "TIME EXCEEDED":
                            if icmp_array[i]["src_ip"] == icmp_array[j]["dst_ip"]:
                                if icmp_array[i]["dst_ip"] == icmp_array[j]["src_ip"]:
                                    complete_comms_pairs.append(icmp_array[i])
                                    complete_comms_pairs.append(icmp_array[j])
                                    break
                    j += 1

    for packet in complete_comms_pairs:
        src_ip = packet["src_ip"]
        dst_ip = packet["dst_ip"]

        group_found = False
        for group in complete_comms:
            if src_ip == group[0]["src_ip"] and dst_ip == group[0]["dst_ip"] \
                    or src_ip == group[0]["dst_ip"] and dst_ip == group[0]["src_ip"]:
                group.append(packet)
                group_found = True
                break
        if not group_found:
            complete_comms.append([packet])

    partial_comms_unsorted = []
    partial_comms = []
    for packet in icmp_array:
        if "icmp_type" in packet:
            if packet not in complete_comms_pairs:
                partial_comms_unsorted.append(packet)

    for packet in partial_comms_unsorted:
        src_ip = packet["src_ip"]
        dst_ip = packet["dst_ip"]

        group_found = False
        for group in partial_comms:
            if src_ip == group[0]["src_ip"] and dst_ip == group[0]["dst_ip"] \
                    or src_ip == group[0]["dst_ip"] and dst_ip == group[0]["src_ip"]:
                group.append(packet)
                group_found = True
                break
        if not group_found:
            partial_comms.append([packet])

    whole_comm = complete_comms_pairs
    whole_comm.extend(partial_comms_unsorted)
    fragmented_comms = []
    # get the remaining packets in icmp array
    for packet in icmp_array:
        if packet not in whole_comm:
            fragmented_comms.append(packet)

    for packet in fragmented_comms:
        packet_found = False
        # group them based on id and ips
        for group in complete_comms:
            for comm in group:
                if comm["id"] == packet["id"] and comm["src_ip"] == packet["src_ip"] \
                        and comm["dst_ip"] == packet["dst_ip"]:
                    group.append(packet)
                    packet_found = True
                    break
            if packet_found:
                break
        for group in partial_comms:
            for comm in group:
                if comm["id"] == packet["id"] and comm["src_ip"] == packet["src_ip"] \
                        and comm["dst_ip"] == packet["dst_ip"]:
                    group.append(packet)
                    packet_found = True
                    break
            if packet_found:
                break
    for i in range(len(complete_comms)):
        complete_comms[i] = sorted(complete_comms[i], key=lambda x: x["frame_number"])

    full_file_path = testing_file()
    file_parts = full_file_path.split("/")
    file_name = file_parts[-1]
    with open("hexdump_icmp.yaml", "w") as file:
        file.write("name: PKS2023/24\n")
        file.write("pcap_name: " + str(file_name) + "\n")
        file.write("filter_name: ICMP\n")

    if len(complete_comms) > 0:
        with open("hexdump_icmp.yaml", "a") as file:
            comm_counter = 1

            file.write("complete_comms:\n")
            for group in complete_comms:
                file.write("  - number_comm: " + str(comm_counter) + "\n")
                file.write("    src_comm: " + str(group[0]["src_ip"]) + "\n")
                file.write("    dst_comm: " + str(group[0]["dst_ip"]) + "\n")
                file.write("    packets:\n")
                for communication in group:
                    file.write("      - frame_number: " + str(communication["frame_number"]) + "\n")
                    file.write("        len_frame_pcap: " + str(communication["len_frame_pcap"]) + "\n")
                    file.write("        len_frame_medium: " + str(communication["len_frame_medium"]) + "\n")
                    file.write("        frame_type: " + str(communication["frame_type"]) + "\n")
                    file.write("        src_mac: " + str(communication["src_mac"]) + "\n")
                    file.write("        dst_mac: " + str(communication["dst_mac"]) + "\n")
                    file.write("        ether_type: " + str(communication["ether_type"]) + "\n")
                    file.write("        src_ip: " + str(communication["src_ip"]) + "\n")
                    file.write("        dst_ip: " + str(communication["dst_ip"]) + "\n")
                    file.write("        protocol: " + str(communication["protocol"]) + "\n")
                    if "id" in communication:
                        file.write("        id: " + str(communication["id"]) + "\n")
                    if "flags_mf" in communication and "frag_offset" in communication:
                        file.write("        flags_mf: " + str(communication["flags_mf"]) + "\n")
                        file.write("        frag_offset: " + str(communication["frag_offset"]) + "\n")
                    if "icmp_type" in communication and "icmp_id" in communication and "icmp_seq" in communication:
                        file.write("        icmp_type: " + str(communication["icmp_type"]) + "\n")
                        file.write("        icmp_id: " + str(communication["icmp_id"]) + "\n")
                        file.write("        icmp_seq: " + str(communication["icmp_seq"]) + "\n")
                    file.write("        hexa_frame: |\n")
                    frame_list = communication["hexa_frame"].split("\n")
                    for i in range(len(frame_list)):
                        if i < (len(frame_list) - 1):
                            file.write("          " + frame_list[i] + "\n")
                    file.write("\n")
                comm_counter += 1

    if len(partial_comms) > 0:
        with open("hexdump_icmp.yaml", "a") as file:
            comm_counter = 1

            file.write("partial_comms:\n")
            for group in partial_comms:
                file.write("  - number_comm: " + str(comm_counter) + "\n")
                file.write("    packets:\n")
                for communication in group:
                    file.write("      - frame_number: " + str(communication["frame_number"]) + "\n")
                    file.write("        len_frame_pcap: " + str(communication["len_frame_pcap"]) + "\n")
                    file.write("        len_frame_medium: " + str(communication["len_frame_medium"]) + "\n")
                    file.write("        frame_type: " + str(communication["frame_type"]) + "\n")
                    file.write("        src_mac: " + str(communication["src_mac"]) + "\n")
                    file.write("        dst_mac: " + str(communication["dst_mac"]) + "\n")
                    file.write("        ether_type: " + str(communication["ether_type"]) + "\n")
                    file.write("        src_ip: " + str(communication["src_ip"]) + "\n")
                    file.write("        dst_ip: " + str(communication["dst_ip"]) + "\n")
                    file.write("        protocol: " + str(communication["protocol"]) + "\n")
                    if "id" in communication:
                        file.write("        id: " + str(communication["id"]) + "\n")
                    if "flags_mf" in communication and "frag_offset" in communication:
                        file.write("        flags_mf: " + str(communication["flags_mf"]) + "\n")
                        file.write("        frag_offset: " + str(communication["frag_offset"]) + "\n")
                    if "icmp_type" in communication and "icmp_id" in communication and "icmp_seq" in communication:
                        file.write("        icmp_type: " + str(communication["icmp_type"]) + "\n")
#                        file.write("        icmp_id: " + str(communication["icmp_id"]) + "\n")
#                        file.write("        icmp_seq: " + str(communication["icmp_seq"]) + "\n")
                    file.write("        hexa_frame: |\n")
                    frame_list = communication["hexa_frame"].split("\n")
                    for i in range(len(frame_list)):
                        if i < (len(frame_list) - 1):
                            file.write("          " + frame_list[i] + "\n")
                    file.write("\n")
                comm_counter += 1


def handle_default(tmp):
    print("unknown input")


if __name__ == "__main__":

    packet_arr = uloha1()
    # "switch" function
    menu = {
        "ARP": uloha_4_arp,
        "ICMP": uloha_4_icmp,
        "TFTP": uloha_4_tftp,
        "FRAG": uloha_4_frag,
    }
    print("MENU\nType one of the following:\n")
    print("ARP\nICMP\nTFTP\nFRAG\n")
    user_input = input("input: ").strip().upper()

    try:
        action = menu.get(user_input, handle_default)
        action(packet_arr)
    except Exception as e:
        print("An error occured: ", str(e))
