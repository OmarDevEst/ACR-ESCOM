import os
import socket
import struct


def send_file(sck: socket.socket, filename):
    # Obtener el tamaño del archivo a enviar.
    filesize = os.path.getsize(filename)
    # Cantidad de
    sck.sendall(struct.pack("<Q", filesize))
    # Enviar el archivo en bloques de 200 bytes.
    with open(filename, "rb") as f:
        while read_bytes := f.read(200):
            sck.sendall(read_bytes)
        f.close()


with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as conn:
    conn.connect(("10.10.5.1", 6192))
    print("Conectado al servidor.")

    datos = []
    carpeta = input('Carpeta: ')
    while True:
        if len(datos) == 0:
            output_data = input("Usuario: ").encode()
        else:
            output_data = input(f"Archivo {len(datos)}: ").encode()
        if output_data == b'':
            output_data = b'Enviar'

        if output_data:
            try:
                conn.send(output_data)
            except TypeError:
                conn.send(bytes(output_data, "utf-8"))
            # Recibir respuesta.
            input_data = conn.recv(1024)
            if input_data:
                # print(input_data.decode("utf-8") if
                #       isinstance(input_data, bytes) else input_data)
                if input_data == b'Enviar':
                    break
                datos.append(input_data.decode('utf-8'))

    for i in range(1, len(datos)):
        print("Enviando archivo...")
        send_file(conn, f"./{carpeta}/{datos[i]}")
        print("Enviado.")

        data = conn.recv(4096)
        # print('Servidor: {!r}'.format(data))

print("Conexión cerrada.")
