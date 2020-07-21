import cv2
import numpy as np
import matplotlib.pyplot as plt

# Read image
img = cv2.imread("ncc_main.png").astype(np.float32)
H, W, C = img.shape

# Read templete image
temp = cv2.imread("ncc_template.png").astype(np.float32)
Ht, Wt, Ct = temp.shape


# Templete matching
i, j = -1, -1
v = -1

temp_mean = np.mean(temp)
for y in range(H-Ht):
    for x in range(W-Wt):
        img_mean = np.mean(img[y:y+Ht, x:x+Wt])
        _v = np.sum((img[y:y+Ht, x:x+Wt] - img_mean) * (temp - temp_mean))
        _v /= np.sqrt(np.sum((img[y:y+Ht, x:x+Wt] - img_mean)**2)
                      * np.sum((temp - temp_mean)**2))
        if _v > v:
            v = _v
            i, j = x, y

out = img.copy()
cv2.rectangle(out, pt1=(i, j), pt2=(i+Wt, j+Ht),
              color=(0, 0, 255), thickness=1)
out = out.astype(np.uint8)

# Save result
cv2.imwrite("ncc_out.jpg", out)
cv2.imshow("result", out)
cv2.waitKey(0)
cv2.destroyAllWindows()
