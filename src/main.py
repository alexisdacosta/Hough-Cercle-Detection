import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt

img = cv.imread('src/images/coins2.jpg',0)
laplacian = cv.Laplacian(img,cv.CV_64F)
sobelx = cv.Sobel(img,cv.CV_64F,1,0,ksize=5)
sobely = cv.Sobel(img,cv.CV_64F,0,1,ksize=5)
plt.subplot(2,3,1),plt.imshow(img,cmap = 'gray')
plt.title('Original'), plt.xticks([]), plt.yticks([])
plt.subplot(2,3,2),plt.imshow(laplacian,cmap = 'gray')
plt.title('Laplacian'), plt.xticks([]), plt.yticks([])
plt.subplot(2,3,3),plt.imshow(sobelx,cmap = 'gray')
plt.title('Sobel X'), plt.xticks([]), plt.yticks([])
plt.subplot(2,3,4),plt.imshow(sobely,cmap = 'gray')
plt.title('Sobel Y'), plt.xticks([]), plt.yticks([])


# Read image as gray-scale
img = cv.imread('src/images/coins2.jpg', cv.IMREAD_COLOR)
# Convert to gray-scale
gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
# Blur the image to reduce noise
img_blur = cv.medianBlur(gray, 5)

edges = cv.Canny(img_blur, 50, 200)
# Apply hough transform on the image
circles = cv.HoughCircles(img_blur, cv.HOUGH_GRADIENT, 1, img.shape[0]/64)
# Draw detected circles
if circles is not None:
    circles = np.uint16(np.around(circles))
    for i in circles[0, :]:
        cv.circle(img, (i[0], i[1]), i[2], (0, 255, 0), 2)
        # Draw inner circle
        cv.circle(img, (i[0], i[1]), 2, (0, 0, 255), 3)
        
plt.subplot(2,3,5),plt.imshow(edges,cmap = 'gray')
plt.title('Edge'), plt.xticks([]), plt.yticks([])
plt.subplot(2,3,6),plt.imshow(img,cmap = 'gray')
plt.title('Cercle Detection'), plt.xticks([]), plt.yticks([])
plt.show()