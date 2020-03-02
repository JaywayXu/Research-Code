import cv2

# 读取图像
img = cv2.imread('a.jpg')
cv2.imshow('img', img)
# cv2.imwrite('x.jpg',img)

# 转换为灰度图
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
cv2.imshow('gray_img', gray)

# Canny算子求边界
caimg = cv2.Canny(gray, 200, 300)
cv2.imshow('Canny', caimg)

# 旋转图像
(h, w) = caimg.shape[:2]
center = (w // 2, h // 2)
M = cv2.getRotationMatrix2D(center, -20.5, 1)
rotated_ca = cv2.warpAffine(caimg, M, (w, h))
cv2.imshow('rotate_Canny', rotated_ca)
(h, w) = img.shape[:2]
center = (w // 2, h // 2)
M = cv2.getRotationMatrix2D(center, -20.5, 1)
rotated_img = cv2.warpAffine(img, M, (w, h))
cv2.imshow('rotate', rotated_img)

cv2.waitKey()
