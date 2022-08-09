// server
const PORT = process.env.PORT || 4000

const io = require('socket.io')(PORT, {
    cors: {
        origin: '*'
    }
});

let lastData = {}

io.on("connection", socket => {
    console.log("USUARIO: " + socket.id);

    socket.on('data', data => {
        if (JSON.stringify(data) !== JSON.stringify(lastData)) {
            lastData = data;
            io.emit('info', data);
        }
    })

    socket.on("disconnect", () => {
        console.log("USUARIO DESCONECTADO: " + socket.id);
    });
});