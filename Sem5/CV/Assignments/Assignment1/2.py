import cv2
import numpy as np


def MarrHildrethEdgeDetection(image_path, sigma, threshold):
    image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
    
    blurred = cv2.GaussianBlur(image, (5, 5), sigma)

    laplacian = cv2.Laplacian(blurred, cv2.CV_64F)
    rows, cols = laplacian.shape
    zero_crossings = np.zeros_like(laplacian)
    
    for i in range(1, rows - 1):
        for j in range(1, cols - 1):
            neighbors = [
                laplacian[i - 1, j],
                laplacian[i + 1, j],
                laplacian[i, j - 1],
                laplacian[i, j + 1],
                laplacian[i - 1, j - 1],
                laplacian[i - 1, j + 1],
                laplacian[i + 1, j - 1],
                laplacian[i + 1, j + 1]
            ]
            if (laplacian[i, j] < 0 and any(n > 0 for n in neighbors)) or (laplacian[i, j] > 0 and any(n < 0 for n in neighbors)):
                zero_crossings[i, j] = 255
    
    return zero_crossings


input_image_path = 'cv/image1.png'
sigma = 1.4 
threshold = 10 
edges = MarrHildrethEdgeDetection(input_image_path, sigma, threshold)

image = cv2.imread(input_image_path, cv2.IMREAD_GRAYSCALE)

c = 0.05

sharpened = np.uint8(image + c*edges)
cv2.imshow('image',image)
cv2.imshow('MarrHildrethEdge',edges)
cv2.imshow('Sharpened',sharpened)


cv2.waitKey(0)
cv2.destroyAllWindows()