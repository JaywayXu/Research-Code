from imutils.object_detection import non_max_suppression
import numpy as np
import imutils
import cv2
import time


def Draw_body(img_name):
    # convert the image into gray
    gray = cv2.cvtColor(img_name, cv2.COLOR_BGR2GRAY)
    # initialize the detector
    hog = cv2.HOGDescriptor()
    hog.setSVMDetector(cv2.HOGDescriptor_getDefaultPeopleDetector())

    # detect people in img
    peoples, weights = hog.detectMultiScale(
        gray, winStride=(1, 1), padding=(8, 8), scale=1.05)

    # apply non-max suppresion to the bounding boxes
    peoples = np.array([[x, y, x+w, y+h] for (x, y, w, h) in peoples])
    pick = non_max_suppression(peoples, probs=None, overlapThresh=0.65)

    # draw the final bounding boxes

    for (xa, ya, xb, yb) in pick:
        cv2.rectangle(img_name, (xa, ya), (xb, yb), (180, 255, 45), 3)


def Faces_Detect(img):
    # convert image
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces_cascade = cv2.CascadeClassifier(
        'haarcascade_frontalface_default.xml')
    # detect faces
    faces = faces_cascade.detectMultiScale(img, 1.3, 5)
    result = []
    for (x, y, width, height) in faces:
        result.append((x, y, x + width, y + height))

    return result

# Draw faces


def Draw_Faces(img):
    faces = Faces_Detect(img)
    if faces:
        for (x1, y1, x2, y2) in faces:
            cv2.rectangle(img, (x1, y1), (x2, y2), (255, 255, 0), 2)


# Test
if __name__ == '__main__':
    t_start = time.time()

    # 创建读取视频实例
    cap = cv2.VideoCapture("Running.mp4")
    # 获取视频编码格式，帧率FPS，Size
    fourcc = cv2.VideoWriter_fourcc(*'mp4v')
    fps = int(round(cap.get(cv2.CAP_PROP_FPS)))
    width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    out = cv2.VideoWriter(
        'out.mp4', fourcc, fps, (width, height))

    while cap.isOpened():
        # 读取每一帧
        ret, frame = cap.read()
        if ret == True:
            Draw_body(frame)  # 检测行人
            # Draw_Faces(frame)  # 检测人脸
            out.write(frame)  # 写入
        else:
            break

    cap.release()

    t_end = time.time()
    print("%f s" % (t_end - t_start))
