import cv2 as cv
import numpy as np

image = cv.imread('cv/image1.png')
gray_image = cv.cvtColor(image, cv.COLOR_BGR2GRAY)
blurred = cv.GaussianBlur(gray_image, (5, 5), 0)

edges = cv.Canny(blurred, threshold1=30, threshold2=100)

c = 0.05

sharpened = np.uint8(gray_image + c*edges)

cv.imshow('Original Image', gray_image)
cv.imshow('Canny Edges', edges)
cv.imshow('Sharpening', sharpened)


cv.waitKey(0)
cv.destroyAllWindows()
