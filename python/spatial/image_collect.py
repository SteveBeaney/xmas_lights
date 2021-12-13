import time
import requests
import cv2
from matplotlib import pyplot as plt

STRING_LIGHTS = 500
N_LIGHTS = 100
PASS = 'right'

if __name__ == '__main__':
    url = 'http://192.168.1.197/led/'
    lights = [(None, None, None)] * 500
    for k in range( 1 ):
        for i in range(100):
            for j in range(500):
                lights[j] = (0, 0, 0)
            lights[i] = (255, 255, 255)
            a = ''
            for rgb in lights:
                a += str.format('{:02X}{:02X}{:02X}', rgb[0], rgb[1], rgb[2])
            x = requests.post(url, data=a)
            video_capture = cv2.VideoCapture(2)
            if not video_capture.isOpened():
                raise Exception("Could not open video device")
            ret, frame = video_capture.read()
            image = frame[:,:,::-1] # BGR => RGB
            cv2.imwrite(f'img/a_{PASS}_{i}.jpg', image)
            video_capture.release()
            plt.imshow(image)
            print(i)
            # time.sleep(1)
