from eventlet import monkey_patch
monkey_patch()
from flask import Flask, request
from flask_socketio import SocketIO

app = application = Flask(__name__)
socketio = SocketIO(app, logger=True, engineio_logger=True, async_handlers=True)

connected_users = {}

@socketio.on('connect')
def on_connect(**kwargs):
    print("Client connected %s" % request.sid)

@socketio.on('disconnect')
def on_disconnect(**kwargs):
    print("Client disconnected %s" % request.sid)

@socketio.on('ping_from_client')
def ping():
    socketio.emit('pong_from_server')

@socketio.on_error_default
def error_handler(e):
    print("socket error: %s, %s" % (e, str(request.event)))

if __name__ == '__main__':
    socketio.run(app, port=5000, debug=True)