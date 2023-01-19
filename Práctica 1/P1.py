import cv2
from threading import Thread

class imagen:
    name = ""
    color = ""
    
formatos = [".jpg", ".jpeg", ".png"]

def color(a):
    image = cv2.imread(a.name)
    image2 = cv2.imread(a.name)
    image3 = cv2.imread(a.name)
    widht, heigth, croma = image.shape
    imageSize = [widht, heigth]
    
    # Nuevo formato de imagen
    for i in range(len(formatos)):
        newName = a.name.replace(formatos[i], "")

    if a.color == "red":
        for i in range(0, imageSize[0]):
            for j in range(0, imageSize[1]):
                image.itemset((i, j, 2), 255)
        cv2.imwrite(newName + '_Red.png',image)

    if a.color == "blue":
        for i in range(0, imageSize[0]):
            for j in range(0, imageSize[1]):
                image2.itemset((i, j, 0), 255)
        cv2.imwrite(newName + '_Blue.png',image2)

    for i in range(0, imageSize[0]):
            for j in range(0, imageSize[1]):
                image3.itemset((i, j, 1), 255)
    cv2.imwrite(newName + '_Green.png',image3)
    
n = int(input("Número de imágenes: "))
imagenes = []
hilos = []

# Registra nombres de imagenes
for i in range(n):
    imagenes.append(input("Nombre de la imagen {0}: ".format(i + 1)))

# Crea hilos para rojo
for i in range(n):
    props = imagen()
    props.name = imagenes[i]
    props.color = "red"
    hilos.append(Thread(target=color, args=(props, )))

# Crea hilos para azul
for i in range(n):
    props = imagen()
    props.name = imagenes[i]
    props.color = "blue"
    hilos.append(Thread(target=color, args=(props, )))

# Ejecuta los hilos
for i in range(2*n):
    hilos[i].start()