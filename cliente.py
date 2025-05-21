import socket
import time

HOST = '127.0.0.1'
PORT = 8080

mensajes = [
    "Hola servidor!",
    "¿Cómo estás?",
    "Esto es una prueba.",
    "Probando 1 2 3",
    "exit"
]

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    for msg in mensajes:
        print("Enviando:", msg)
        s.sendall(msg.encode())
        data = s.recv(1024)
        print("Recibido:", data.decode())
        time.sleep(0.5)  # Espera 1 segundo entre mensajes
