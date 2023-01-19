import random
from threading import Thread,Semaphore
import time
NP = 10000  # Numero de producciones (por cada productor)
PRO = 4  # Numero de productores
CON = 3  # Numero de consumidores
NZON = 6 # Numero de zonas criticas
buffers = [ ] #zona criticas
semaforo_productor = Semaphore(NZON + 1)
semaforo_consumidor = Semaphore(NZON + 1)

class parametros:
    id = 0,
    bnum = 0,
    
class hILO(Thread):
    def _init(self, numero_hilo, semaforo_productor):
        Thread.init__(self)
        self.semaforo=semaforo_productor
        self.numero_hilo = numero_hilo

    def run(self):
        semaforo_productor.acquire()
        #funcion
        semaforo_productor.release()

        
open("1s.txt", "w")
open("2s.txt", "w")
open("3s.txt", "w")
open("4s.txt", "w")


