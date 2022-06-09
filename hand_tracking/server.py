from eventlet import monkey_patch
monkey_patch()
from flask import Flask, request
from flask_socketio import SocketIO

app = application = Flask(__name__)
socketio = SocketIO(app, logger=True, engineio_logger=True, async_handlers=True)

connected_users = {}

@socketio.on('connect')
def on_connect(sid, data):
    print("Client connected %s" % sid)

@socketio.on('disconnect')
def on_disconnect(sid, data):
    print("Client disconnected %s" % sid)

@socketio.on('data')
def my_function(sid, data):
    print("Cliente %s enviou: %s" % (sid, data))
    socketio.emit('info', 'Hello World do servidor')

@socketio.on_error_default
def error_handler(e):
    print("socket error: %s, %s" % (e, str(request.event)))

if __name__ == '__main__':
    socketio.run(app, port=5000, debug=False)