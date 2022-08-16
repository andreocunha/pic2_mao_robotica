import cv2
import mediapipe as mp
import socketio
from google.protobuf.json_format import MessageToDict

sio = socketio.Client()

frameWidth = 640
frameHeight = 480
cap = cv2.VideoCapture(0)
cap.set(3, frameWidth)
cap.set(4, frameHeight)

mpHands=mp.solutions.hands
hands=mpHands.Hands(
    max_num_hands=1,
    model_complexity=0,
    min_detection_confidence=0.5,
    min_tracking_confidence=0.5
)
mpDraw = mp.solutions.drawing_utils
mp_drawing_styles = mp.solutions.drawing_styles

pTime = 0
cTime = 0

tipIds = [4, 8, 12, 16, 20]

conectedToServer = False

# funcoes do SocketIO
@sio.event
def connect():
    print("Conectado!")
    # sio.emit('data', "Leitura da mão iniciada")

@sio.event
def connect_error():
    print("A conexao falhou!")

@sio.on('info')
def on_message(data):
    print('Info:', data)

# conecta ao socketio
try:
    sio.connect('http://localhost:4000')
    # sio.connect('https://server-robotic-hand.herokuapp.com')
    conectedToServer = True
except:
    print("Erro ao conectar ao socketio")

def escala(valor):
    if valor <= 0.4:
        return 0
    elif valor > 0.4 and valor <= 0.8:
        return 25
    elif valor > 0.8 and valor <= 1.2:
        return 50
    elif valor > 1.2 and valor <= 1.8:
        return 75
    elif valor > 1.8:
        return 100

while True:
    success, img = cap.read()
    img= cv2.flip(img,1)
    imgRGB = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    results = hands.process(imgRGB)


    if results.multi_hand_landmarks:

        for i in results.multi_handedness:
            label = MessageToDict(i)['classification'][0]['label']
            
            if(label == 'Right'):
                for handLms in results.multi_hand_landmarks: 

                    #handLMs sao 21 pontos da mão.
                    lmList = []
                    for id, lm in enumerate(handLms.landmark):
                        # print(id, lm)
                        #lm = x,y cordinate of each landmark in float numbers. lm.x, lm.y methods
                        #So, need to covert in integer
                        h, w, c =img.shape
                        cx, cy = int(lm.x * w), int(lm.y * h)
                        # print(id, cx, cy)
                        lmList.append([id, cx, cy])
                        # if id == 4: #(To draw 4th point)
                        cv2.circle(img, (cx, cy), 5, (255, 0, 255), cv2.FILLED)
                    # print(lmList)

                    if len(lmList) != 0:
                        fingers = {}

                        distRef = ((lmList[0][1] - lmList[1][1]) ** 2 + (lmList[0][2] - lmList[1][2]) ** 2) ** 0.5

                        # Dedao
                        if lmList[tipIds[0]][1] < lmList[5][1] and lmList[5][1] < lmList[9][1]:
                            fingers['dedo1'] = 100
                        else:
                            if lmList[tipIds[0]][1] > lmList[5][1] and lmList[5][1] > lmList[9][1]:
                                fingers['dedo1'] = 100
                            else:
                                fingers['dedo1'] = 0


                        # Para os outros 4 dedos
                        for id in range(1,5):
                            result = ((lmList[tipIds[id]][1] - lmList[tipIds[id]-3][1]) ** 2 + (lmList[tipIds[id]][2] - lmList[tipIds[id]-3][2]) ** 2) ** 0.5
                            if id == 4:
                                result = result*1.2
                            result = escala(result/distRef)
                            if lmList[tipIds[id]][2] < lmList[tipIds[id]-3][2]:
                                fingers['dedo'+str(id+1)] = result
                            else:
                                fingers['dedo'+str(id+1)] = 0

                        if conectedToServer:
                            sio.emit('data', fingers)

                    #drawing points and lines(=handconections)
                    mpDraw.draw_landmarks(img, handLms, mpHands.HAND_CONNECTIONS, mp_drawing_styles.get_default_hand_landmarks_style(),mp_drawing_styles.get_default_hand_connections_style())
            
    
    cv2.imshow('image', img)
    if cv2.waitKey(1)==27:
        break