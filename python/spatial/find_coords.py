
import skimage.io
import skimage.color
import skimage.filters
import cv2
import json
import io

STRING_LIGHTS = 500
N_LIGHTS = 100
PASS = ('front','right')

def find_led(mask):
    x_sum = 0
    y_sum = 0
    n = 0
    for y, a in enumerate(mask):
        for x, b in enumerate(a):
            if b:
                n += 1
                x_sum += x
                y_sum += y
    if n > 0:
        x_sum = x_sum / n
        y_sum = y_sum / n
    return (n, x_sum, y_sum, mask[int(y_sum)][int(x_sum)])


def binary_prep(image_file, t):
    rgb = cv2.imread(image_file)
    gray = cv2.cvtColor(rgb, cv2.COLOR_RGB2GRAY)
    blurred = skimage.filters.gaussian(gray, sigma=1.5)
    binary_mask = blurred > t
    return binary_mask

def process_string( orth_view ):
    lights = []
    for i in range(99):
        t = 0.99
        while t > 0.3:
            mask = binary_prep(f'./img/a_{orth_view}_{i}.jpg', t)
            n, x, y, state = find_led(mask)
            if n > 5 and state:
                break
            t -= 0.01
        if state:
            lights.append((x, y))
        else:
            lights.append((-1, -1))
    with io.open(f'./{orth_view}_raw_location.json', 'w', encoding='utf-8') as f:
        f.write(json.dumps(lights, indent=4, ensure_ascii=False))

for orth_view in PASS:
    print( orth_view )
    process_string( orth_view )