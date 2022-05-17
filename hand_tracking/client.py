import socketio

# standard Python
sio = socketio.Client()

@sio.event
def connect():
    print("Conectado!")
    sio.emit('data', "Hello World")

@sio.event
def connect_error():
    print("A conexao falhou!")

@sio.on('info')
def on_message(data):
    print('Info:', data)


sio.connect('http://localhost:5000')