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


class Client(Thread):
    def __init__(self, conn, address):
        Thread.__init__(self)

        self.conn = conn
        self.address = address

    def run(self):
        datos = []
        while True:
            try:
                # Recibir datos del cliente.
                input_data = self.conn.recv(1024)
            except socket.error:
                print("[%s] Error de lectura." % self.name)
                break
            else:
                # Reenviar la información recibida.
                if input_data:
                    self.conn.send(input_data)
                    if input_data == b'Enviar':
                        break
                    datos.append(input_data.decode('utf-8'))

        os.makedirs(f'{datos[0]}_servidor', exist_ok=True)
        for i in range(1, len(datos)):
            print("Recibiendo archivo...")
            receive_file(self.conn, f"./{datos[0]}_servidor/{datos[i]}")
            print("Archivo recibido.")

            self.conn.sendall(b'Fin')


with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server:
    server.bind(("localhost", 6192))
    server.listen(2)
    print("Esperando al cliente...")
    flag = 0
    while True:
        conn, address = server.accept()
        print(f"{address[0]}:{address[1]} conectado.")
        c = Client(conn, address)
        c.start()

print("Conexión cerrada.")
