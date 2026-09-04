import cv2
import mediapipe as mp
import serial
import time

# Intenta conectar al ESP32 
USAR_SERIAL = True
try:
    ser = serial.Serial('COM3', 115200, timeout=1)
    time.sleep(2)
    print("¡ESP32 conectado correctamente por el puerto COM!")
except Exception as e:
    USAR_SERIAL = False
    print("Modo prueba activado (Sin ESP32 conectado).")

# Inicializar cámara
cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)
if not cap.isOpened():
    cap = cv2.VideoCapture(1, cv2.CAP_DSHOW)

# Módulos de MediaPipe
mp_hands = mp.solutions.hands
hands = mp_hands.Hands(
    static_image_mode=False,
    max_num_hands=2,
    min_detection_confidence=0.7,
    min_tracking_confidence=0.5
)
mp_draw = mp.solutions.drawing_utils

tip_ids = [4, 8, 12, 16, 20]
ultimo_conteo = -1

while cap.isOpened():
    success, img = cap.read()
    if not success or img is None:
        continue

    img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    results = hands.process(img_rgb)

    dedos_arriba = 0

    if results.multi_hand_landmarks:
        # Requisito: Solo toma la primera mano detectada
        hand_landmarks = results.multi_hand_landmarks[0]
        mp_draw.draw_landmarks(img, hand_landmarks, mp_hands.HAND_CONNECTIONS)
        
        lm_list = []
        for id, lm in enumerate(hand_landmarks.landmark):
            h, w, c = img.shape
            cx, cy = int(lm.x * w), int(lm.y * h)
            lm_list.append([id, cx, cy])

        if len(lm_list) != 0:
            # Pulgar
            if lm_list[tip_ids[0]][1] > lm_list[tip_ids[0] - 1][1]:
                dedos_arriba += 1
            # Otros 4 dedos
            for id in range(1, 5):
                if lm_list[tip_ids[id]][2] < lm_list[tip_ids[id] - 2][2]:
                    dedos_arriba += 1

        if dedos_arriba != ultimo_conteo:
            ultimo_conteo = dedos_arriba
            print(f"Dedos detectados: {dedos_arriba}")
            
            # Si el ESP32 está conectado, le envía el dato por el cable
            if USAR_SERIAL:
                ser.write(f"{dedos_arriba}\n".encode())

    cv2.putText(img, f"Dedos: {dedos_arriba}", (20, 50), 
                cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

    cv2.imshow("MediaPipe Hand Tracking", img)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
if USAR_SERIAL:
    ser.close()
