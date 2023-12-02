# Importing Libraries
import cv2
import numpy as np
def main():
    

    my_img = cv2.imread('my.jpg')
    # Resizing the my image
    scale = 0.7
    width = int(my_img.shape[1]*scale)
    height = int(my_img.shape[0]*scale)
    dsize = (width, height)
    my_img = cv2.resize(my_img, dsize)



    # Selecting the Region of Interest of the image
    copy_of_my = my_img.copy()
    mask = np.zeros(my_img.shape[:2], np.uint8)

    background_model = np.zeros((1, 65), np.float64)
    fgd_model = np.zeros((1, 65), np.float64)

    x, y, w, h = cv2.selectROI("Select the Region of Interest", my_img)
    start = (x, y)
    end = (x+w, y+h)
    rect = (x, y, w, h)

    cv2.rectangle(copy_of_my, start, end, (0, 0, 255), 3)

    # Implementing GrabCut Algorithm for removing background

    cv2.grabCut(my_img, mask, rect, background_model, fgd_model, 100, cv2.GC_INIT_WITH_RECT)
    mask2 = np.where((mask == 2) | (mask == 0), 0, 1).astype('uint8')
    no_bg_my = my_img * mask2[:, :, np.newaxis]

    # Adding new Background
    background_img = cv2.imread('historic.jpeg')
    background_img = cv2.resize(background_img, dsize)
    background_img[mask2 != 0] = [0, 0, 0]

    final_img = no_bg_my + background_img
    cv2.imshow("Final Image", final_img)
    cv2.imwrite('final_image.jpeg', final_img)


    cv2.waitKey(0)
    cv2.destroyAllWindows()
    
    
if __name__ == "__main__":
    main()