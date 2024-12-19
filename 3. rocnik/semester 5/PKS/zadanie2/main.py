import os
import socket
import struct
import zlib
import random

TYPE_SYN = 1
TYPE_SYN_ACK = 2
TYPE_ACK = 3
TYPE_TXT_MSG = 4
TYPE_FILE = 5
TYPE_FILE_END = 6
TYPE_KEEP_ALIVE = 7
TYPE_CHANGE_FRAG_SIZE = 8
TYPE_MESSAGE_END = 9
TYPE_SWITCH = 10
TYPE_FRAGS_AND_SIZE = 11

msg_id = 1
MAX_FRAGMENT_SIZE = 1500
HEADER_FORMAT = '>BHHI'


class Header:
    def __init__(self, type_id, msg_id, frag_id, checksum):
        self.type_id = type_id
        self.msg_id = msg_id
        self.frag_id = frag_id
        self.checksum = checksum

    def pack(self):
        return struct.pack(HEADER_FORMAT, self.type_id, self.msg_id, self.frag_id, self.checksum)

    @staticmethod
    def unpack(data):
        return Header(*struct.unpack(HEADER_FORMAT, data))


class Sender:
    def __init__(self, server_ip, port):
        self.server_ip = server_ip
        self.port = port
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    def initiate_handshake(self):
        global msg_id
        frag_id = 0
        checksum = 1
        syn_header = Header(TYPE_SYN, msg_id, frag_id, checksum)
        self.sock.sendto(syn_header.pack(), (self.server_ip, self.port))
        print("SYN sent")

        data, addr = self.sock.recvfrom(1024)
        received_header = Header.unpack(data)
        if received_header.type_id == TYPE_SYN_ACK:
            print("SYN-ACK received")
            ack_header = Header(TYPE_ACK, msg_id, frag_id, checksum)
            self.sock.sendto(ack_header.pack(), (self.server_ip, self.port))
            print("Handshake completed")
            return True
        else:
            print("Handshake failed")
            return False

    def wait_for_ack(self, expected_msg_id, expected_frag_id):
        try:
            self.sock.settimeout(2.0)
            while True:
                data, _ = self.sock.recvfrom(1024)
                received_header = Header.unpack(data)
                if (received_header.type_id == TYPE_ACK and
                        received_header.msg_id == expected_msg_id and
                        received_header.frag_id == expected_frag_id):
                    print(f"ACK received for message id {expected_msg_id}, fragment id {expected_frag_id}")
                    return True
        except socket.timeout:
            print("ACK not received, resending the packet")
            return False

    def send_message(self):
        while True:
            error = input("Do you want to simulate an error? yes/no: ")
            if error == "yes":
                num_of_errors = int(input("How many error packages?: "))
            else:
                num_of_errors = 0
            count = 0
            message = input("Enter message to send: ")
            global msg_id, MAX_FRAGMENT_SIZE
            msg_id += 1
            frag_id = 0
            data = message.encode('utf-8')
            total_fragments = len(data) // MAX_FRAGMENT_SIZE + (len(data) % MAX_FRAGMENT_SIZE > 0)
            print(f"Total fragments: {total_fragments}\nSize of message: {len(data)}")
            """
            frag_data = (str(total_fragments) + "|" + str(len(data))).encode('utf-8')
            checksum = compute_crc(frag_data)
            total_fragments_frag_data = len(frag_data) // MAX_FRAGMENT_SIZE + (len(frag_data) % MAX_FRAGMENT_SIZE > 0)
            for i in range(total_fragments_frag_data):
                frag_id += 1
                start_idx = (frag_id - 1) * MAX_FRAGMENT_SIZE
                end_idx = start_idx + MAX_FRAGMENT_SIZE
                fragment = frag_data[start_idx:end_idx]
                checksum = compute_crc(fragment)
                header = Header(TYPE_TXT_MSG, msg_id, frag_id, checksum)
                self.sock.sendto(header.pack() + fragment, (self.server_ip, self.port))
            

            frag_data_header = Header(TYPE_FRAGS_AND_SIZE, msg_id, frag_id, checksum)
            self.sock.sendto(frag_data_header.pack(), (self.server_ip, self.port))
            while not self.wait_for_ack(msg_id, frag_id):
                self.sock.sendto(frag_data_header.pack(), (self.server_ip, self.port))
            """
            for i in range(total_fragments):
                frag_id += 1
                start_idx = (frag_id - 1) * MAX_FRAGMENT_SIZE
                end_idx = start_idx + MAX_FRAGMENT_SIZE
                fragment = data[start_idx:end_idx]
                if str(error).lower() == "yes" and count < num_of_errors:
                    if random.random() < 0.5:
                        checksum = compute_crc(fragment) + 1
                        count += 1
                        header = Header(TYPE_TXT_MSG, msg_id, frag_id, checksum)
                        self.sock.sendto(header.pack() + fragment, (self.server_ip, self.port))
                        if not self.wait_for_ack(msg_id, frag_id):
                            self.sock.sendto(header.pack() + fragment, (self.server_ip, self.port))

                checksum = compute_crc(fragment)
                header = Header(TYPE_TXT_MSG, msg_id, frag_id, checksum)
                self.sock.sendto(header.pack() + fragment, (self.server_ip, self.port))
                while not self.wait_for_ack(msg_id, frag_id):
                    self.sock.sendto(header.pack() + fragment, (self.server_ip, self.port))
            frag_id = 0
            data = "e".encode('utf-8')
            checksum = compute_crc(data)
            header = Header(TYPE_MESSAGE_END, msg_id, frag_id, checksum)
            self.sock.sendto(header.pack() + data, (self.server_ip, self.port))
            if message.lower() == 'exit':
                break

    def send_file(self):
        error = input("Do you want to simulate an error? yes/no: ")
        if error == "yes":
            num_of_errors = int(input("How many error packages?: "))
        else:
            num_of_errors = 0
        count = 0
        path = input("Where is the exact path to the file you want to send:\n")
        file_name = os.path.basename(path)
        if os.path.exists(path):
            with open(path, 'rb') as file:
                global msg_id
                msg_id += 1
                frag_id = 0
                data = file_name.encode('utf-8')
                total_fragments = len(data) // MAX_FRAGMENT_SIZE + (len(data) % MAX_FRAGMENT_SIZE > 0)
                file_size = os.path.getsize(path)
                total_fragments_file = file_size // MAX_FRAGMENT_SIZE + (file_size % MAX_FRAGMENT_SIZE > 0)
                if total_fragments_file >= 65535:
                    print(f"Too many fragments({total_fragments_file}), try a different fragment size")
                    return
                print(f"Total fragments: {total_fragments_file + total_fragments}\nSize of message: {len(data)}")

                for i in range(total_fragments):
                    frag_id += 1
                    start_idx = (frag_id - 1) * MAX_FRAGMENT_SIZE
                    end_idx = start_idx + MAX_FRAGMENT_SIZE
                    fragment = data[start_idx:end_idx]
                    checksum = compute_crc(fragment)
                    header = Header(TYPE_TXT_MSG, msg_id, frag_id, checksum)
                    self.sock.sendto(header.pack() + fragment, (self.server_ip, self.port))
                    while not self.wait_for_ack(msg_id, frag_id):
                        self.sock.sendto(header.pack() + fragment, (self.server_ip, self.port))
                frag_id = 1
                data = "f".encode('utf-8')
                checksum = compute_crc(data)
                header = Header(TYPE_FILE, msg_id, frag_id, checksum)
                self.sock.sendto(header.pack() + data, (self.server_ip, self.port))

                while not self.wait_for_ack(msg_id, frag_id):
                    self.sock.sendto(header.pack() + data, (self.server_ip, self.port))

                while True:
                    data = file.read(MAX_FRAGMENT_SIZE)
                    if not data:
                        break
                    if str(error).lower() == "yes" and count < num_of_errors:
                        if random.random() < 0.5:
                            checksum = compute_crc(fragment) + 1
                            count += 1
                            header = Header(TYPE_TXT_MSG, msg_id, frag_id, checksum)
                            self.sock.sendto(header.pack() + fragment, (self.server_ip, self.port))
                            if not self.wait_for_ack(msg_id, frag_id):
                                self.sock.sendto(header.pack() + fragment, (self.server_ip, self.port))

                    checksum = compute_crc(data)
                    header = Header(TYPE_FILE, msg_id, frag_id, checksum)
                    self.sock.sendto(header.pack() + data, (self.server_ip, self.port))
                    while not self.wait_for_ack(msg_id, frag_id):
                        self.sock.sendto(header.pack() + data, (self.server_ip, self.port))

                    frag_id += 1
                data = "EOF".encode('utf-8')
                checksum = compute_crc(data)
                end_header = Header(TYPE_FILE_END, msg_id, frag_id, checksum)
                self.sock.sendto(end_header.pack() + data, (self.server_ip, self.port))
                while not self.wait_for_ack(msg_id, frag_id):
                    self.sock.sendto(header.pack() + data, (self.server_ip, self.port))

            print("File sent successfully.")
            try:
                self.sock.settimeout(5.0)
                while True:
                    data, _ = self.sock.recvfrom(1024)
                    received_header = Header.unpack(data)
                    if received_header.type_id == TYPE_SWITCH:
                        self.switch()
                        exit(0)
                    else:
                        break
            except socket.timeout:
                print("Something went wrong")
        else:
            print("File not found.")

    def change_fragment_size(self):
        global MAX_FRAGMENT_SIZE
        global msg_id
        new_frag_size = input("What should be the new fragment size?(in Bytes): ")
        while int(new_frag_size) >= 65507 - struct.calcsize(HEADER_FORMAT) or int(new_frag_size) <= 0:
            print(f"New fragment size should be less than {65507 - struct.calcsize(HEADER_FORMAT)} or greater than 0")
            new_frag_size = input("Try again: ")
        msg_id += 1
        frag_id = 0
        data = new_frag_size.encode('utf-8')
        total_fragments = len(data) // MAX_FRAGMENT_SIZE + (len(data) % MAX_FRAGMENT_SIZE > 0)
        print(f"Total fragments: {total_fragments}\nSize of message: {len(data)}")
        for i in range(total_fragments):
            frag_id += 1
            start_idx = (frag_id - 1) * MAX_FRAGMENT_SIZE
            end_idx = start_idx + MAX_FRAGMENT_SIZE
            fragment = data[start_idx:end_idx]
            checksum = compute_crc(fragment)
            header = Header(TYPE_TXT_MSG, msg_id, frag_id, checksum)
            self.sock.sendto(header.pack() + fragment, (self.server_ip, self.port))
            while not self.wait_for_ack(msg_id, frag_id):
                self.sock.sendto(header.pack() + fragment, (self.server_ip, self.port))
        data = "e".encode('utf-8')
        checksum = compute_crc(data)
        change_fragment_header = Header(TYPE_CHANGE_FRAG_SIZE, msg_id, frag_id, checksum)
        self.sock.sendto(change_fragment_header.pack() + data, (self.server_ip, self.port))
        while not self.wait_for_ack(msg_id, frag_id):
            self.sock.sendto(change_fragment_header.pack() + data, (self.server_ip, self.port))
        MAX_FRAGMENT_SIZE = int(new_frag_size)

    def switch(self):
        global msg_id
        msg_id += 1
        frag_id = 0
        data = "s".encode('utf-8')
        checksum = compute_crc(data)
        switch_header = Header(TYPE_SWITCH, msg_id, frag_id, checksum)
        self.sock.sendto(switch_header.pack() + data, (self.server_ip, self.port))
        print("Switch request sent")
        while not self.wait_for_ack(msg_id, frag_id):
            self.sock.sendto(switch_header.pack() + data, (self.server_ip, self.port))
        self.sock.close()
        start_receiver(self.server_ip, self.port)
        exit(0)


class Receiver:
    def __init__(self, server_ip, port):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind(('', port))
        self.port = port
        self.server_ip = server_ip
        self.file_save_path = input("Enter the FULL path where you want to save the received files:\n")

    def handle_handshake(self):
        data, addr = self.sock.recvfrom(1024)
        header = Header.unpack(data)

        if header.type_id == TYPE_SYN:
            print("SYN received")
            msg_id = header.msg_id
            frag_id = 0
            checksum = 0
            syn_ack_header = Header(TYPE_SYN_ACK, msg_id, frag_id, checksum)
            self.sock.sendto(syn_ack_header.pack(), addr)
            print("SYN-ACK sent")

            data, _ = self.sock.recvfrom(1024)
            received_header = Header.unpack(data)
            if received_header.type_id == TYPE_ACK:
                print("Handshake completed")
                return True
        return False

    def send_ack(self, msg_id, frag_id, addr):
        ack_header = Header(TYPE_ACK, msg_id, frag_id, 0)
        self.sock.sendto(ack_header.pack(), addr)

    def receive_message(self):
        global MAX_FRAGMENT_SIZE
        receiving_file = False
        file_name = None
        file_stream = None
        first_packet = True
        msg_contents = ""

        while True:
            buffer_size = MAX_FRAGMENT_SIZE + struct.calcsize(HEADER_FORMAT)
            data, addr = self.sock.recvfrom(buffer_size)
            header_size = struct.calcsize(HEADER_FORMAT)
            header = Header.unpack(data[:header_size])
            payload = data[header_size:]

            if header.checksum == compute_crc(payload):
                self.send_ack(header.msg_id, header.frag_id, addr)

                if header.type_id == TYPE_TXT_MSG:
                    msg_contents += payload.decode('utf-8')

                elif header.type_id == TYPE_FRAGS_AND_SIZE:
                    frags_and_size = msg_contents.split("|")
                    print(f"Total fragments: {frags_and_size[0]}, Size: {frags_and_size[1]}")

                elif header.type_id == TYPE_MESSAGE_END:
                    print(f"Message received: {msg_contents}")
                    if msg_contents.lower() == "exit":
                        break
                    msg_contents = ""

                elif header.type_id == TYPE_FILE:
                    if first_packet:
                        file_name = msg_contents
                        full_path = os.path.join(self.file_save_path, file_name)
                        file_stream = open(full_path, 'wb')
                        first_packet = False
                        receiving_file = True
                        print(f"Receiving file: {file_name}")
                        print(f"Saving it into: {full_path}")
                        msg_contents = ""
                    else:
                        file_stream.write(payload)

                elif header.type_id == TYPE_FILE_END:
                    if receiving_file and file_stream:
                        file_stream.close()
                        print(f"End of file transmission for file {file_name}")
                        receiving_file = False
                        file_stream = None
                        first_packet = True
                        switch = input("Do you want to switch? yes/no: ")
                        if switch == "yes":
                            switch_request_header = Header(TYPE_SWITCH, header.msg_id, 1, 1)
                            self.sock.sendto(switch_request_header.pack(), addr)
                        else:
                            random_header = Header(TYPE_TXT_MSG, header.msg_id, 1, 1)
                            self.sock.sendto(random_header.pack(), addr)

                elif header.type_id == TYPE_CHANGE_FRAG_SIZE:
                    MAX_FRAGMENT_SIZE = int(msg_contents)
                    print(f"Succesfully changed max fragment size. New fragment size is: {MAX_FRAGMENT_SIZE}")
                    msg_contents = ""

                elif header.type_id == TYPE_SWITCH:
                    print("Switch request received. Switching roles to Sender.")
                    self.sock.close()
                    start_sender(self.server_ip, self.port)
                    exit(0)

            else:
                print(f"Packet with msg_ID: {header.msg_id} and frag_ID: {header.frag_id} was corrupted")
                print("Waiting for resend")


def compute_crc(data):
    return zlib.crc32(data) & 0xffffffff


def start_sender(server_ip, port):
    if not server_ip and not port:
        server_ip = input("Type the receiver IP: ")
        port = int(input("Type the port: "))
        start = input("Try to establish connection? 1 - Yes, 2 - No\n")
        if start == "1":
            sender = Sender(server_ip, port)
            sender.initiate_handshake()
            while True:
                choice = input("f - file, t - text, c - change fragment, s - switch\nexit to exit\n")
                if choice.lower() == "t":
                    sender.send_message()
                elif choice.lower() == "f":
                    sender.send_file()
                elif choice.lower() == "c":
                    sender.change_fragment_size()
                elif choice.lower() == "s":
                    sender.switch()
                elif choice.lower() == "exit":
                    break
    else:
        sender = Sender(server_ip, port)
        while True:
            choice = input("f - file, t - text, c - change fragment, s - switch\nexit to exit\n")
            if choice.lower() == "t":
                sender.send_message()
            elif choice.lower() == "f":
                sender.send_file()
            elif choice.lower() == "c":
                sender.change_fragment_size()
            elif choice.lower() == "s":
                sender.switch()
            elif choice.lower() == "exit":
                break


def start_receiver(server_ip, port):
    if not server_ip and not port:
        server_ip = input("Enter your own IP: ")
        port = int(input("Enter the port to listen on: "))
        receiver = Receiver(server_ip, port)
        if receiver.handle_handshake():
            receiver.receive_message()
    else:
        receiver = Receiver(server_ip, port)
        receiver.receive_message()


def main_menu():
    while True:
        choice = input("Choose role: Sender (S) / Receiver (R) / Exit: \n").lower()
        if choice == 's':
            start_sender(None, None)
        elif choice == 'r':
            start_receiver(None, None)
        elif choice == 'exit':
            print("Exiting program.")
            break
        else:
            print("Invalid choice. Please choose S, R, or E.")


if __name__ == "__main__":
    main_menu()
