import socket
import time
import sys

UDP_IP = "127.0.0.1"
UDP_PORT = 5005
buf = 200
file_name = './Cliente1/A1.txt'


sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Datos
datos = []
carpeta = input('Nombre de la carpeta: ')
while True:
    if len(datos) == 0:
        data = input('Usuario: ').encode()
    else:
        data = input(f'Archivo {len(datos)}: ').encode()
    if data == b'':
        sock.sendto(b'Ok', (UDP_IP, UDP_PORT))
        break
    datos.append(data.decode('UTF-8'))
    sock.sendto(data, (UDP_IP, UDP_PORT))

for i in range(1, len(datos)):
    f = open(f'./{carpeta}/{datos[i]}', "rb")
    data = f.read(buf)
    while(data):
        print(data)
        if sock.sendto(data, (UDP_IP, UDP_PORT)):
            data = f.read(buf)
            time.sleep(0.02) # Give receiver a bit time to save
    sock.sendto(b'Ok', (UDP_IP, UDP_PORT))
    f.close()

sock.close()
