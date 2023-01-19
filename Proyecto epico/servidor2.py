import os
import socket
import struct
from threading import Thread


def receive_file_size(sck: socket.socket):
    fmt = "<Q"
    expected_bytes = struct.calcsize(fmt)
    received_bytes = 0
    stream = bytes()
    while received_bytes < expected_bytes:
        chunk = sck.recv(expected_bytes - received_bytes)
        stream += chunk
        received_bytes += len(chunk)
    filesize = struct.unpack(fmt, stream)[0]
    return filesize


def receive_file(sck: socket.socket, filename):
    # bytes que se recibirán del archivo.
    filesize = receive_file_size(sck)
    # Abrir un nuevo archivo en donde guardar
    with open(filename, "wb") as f:
        received_bytes = 0
        # Recibir los datos del archivo en bloques de 200 bytes
        while received_bytes < filesize:
            chunk = sck.recv(200)
            if chunk:
                f.write(chunk)
                received_bytes += len(chunk)
        f.close()

    # Enviar archivo a Linux 1 y 3


def send_file(sck: socket.socket):
    # file = sck.recv(1024).decode('utf-8')
    filesize = os.path.getsize(f'./servidor2/A2.pdf')
    # Cantidad de
    totalBytes = int(sck.recv(1024).decode('utf-8'))
    sck.sendall(str(filesize).encode())
    sck.recv(1024)
    sck.sendall(struct.pack("<Q", int(filesize / 3)))
    # Enviar el archivo en bloques de 200 bytes.
    with open('./servidor2/A2.pdf', "rb") as f:
        f.seek(totalBytes, 1)
        bytesF = totalBytes
        while read_bytes := f.read(int(filesize / 3)):
            print(read_bytes, int(filesize / 3))
            sck.sendall(read_bytes)
            bytesF += len(read_bytes)
            if bytesF == int(filesize / 3) * 2:
                break
        f.close()


class Client(Thread):
    def __init__(self, conn, address):
        Thread.__init__(self)

        self.conn = conn
        self.address = address

    def run(self):
        while True:
            data = self.conn.recv(1024)
            if data:
                print(data)
                self.conn.sendall(b'Ok')
                while True:
                    if data == b'upload':
                        os.makedirs(f'servidor2', exist_ok=True)
                        print("Recibiendo archivo...")
                        receive_file(self.conn, f"./servidor2/A2.pdf")
                        print("Archivo recibido.")
                        self.conn.sendall(b'Fin')
                        cliente('192.168.2.222', 6002)
                        cliente('192.168.2.222', 6004)
                        break
                    elif data == b'download':
                        print('Devolviendo archivo')
                        # self.conn.sendall(b'Ok')
                        send_file(self.conn)
                        print('Enviado')
                        break


def servidor2():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server:
        server.bind(('192.168.2.222', 6003))
        server.listen(2)
        print("Esperando al cliente...")
        flag = 0
        while True:
            conn, address = server.accept()
            print(f"{address[0]}:{address[1]} conectado.")
            c = Client(conn, address)
            c.start()


def cliente(ip, puerto):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as cliente:
        cliente.connect((ip, puerto))
        print("Conectado al servidor2.")

        # Enviar archivo
        file = './servidor2/A2.pdf'
        filesize = os.path.getsize(file)
        cliente.sendall(b'upload')
        cliente.recv(1024)
        cliente.sendall(struct.pack("<Q", filesize))
        # Enviar el archivo en bloques de 200 bytes.
        with open(file, "rb") as f:
            while read_bytes := f.read(200):
                cliente.sendall(read_bytes)
            f.close()

        # Acaba
        cliente.close()  # Cierra cliente


servidor2()

print("Conexión cerrada.")
