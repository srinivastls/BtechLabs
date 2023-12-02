import cv2
import numpy as np
import tkinter as tk
from PIL import Image, ImageTk
from tkinter import filedialog

def apply_bokeh_effect():
    image_path = input_entry.get()
    image_frame.pack(side='top')
    # Read the image
    img = cv2.imread(image_path)
    copy_of_img = img.copy()
    background_img = img.copy()
    mask = np.zeros(img.shape[:2], np.uint8)

    bgd_model = np.zeros((1, 65), np.float64)
    fgd_model = np.zeros((1, 65), np.float64)

    x, y, w, h = cv2.selectROI("Select the Region of Interest", img)
    start = (x, y)
    end = (x + w, y + h)
    rect = (x, y, w, h)

    cv2.rectangle(copy_of_img, start, end, (0, 0, 255), 3)

    # Implementing GrabCut Algorithm for removing background

    cv2.grabCut(img, mask, rect, bgd_model, fgd_model, 100, cv2.GC_INIT_WITH_RECT)
    mask2 = np.where((mask == 2) | (mask == 0), 0, 1).astype('uint8')
    no_bg_image = img * mask2[:, :, np.newaxis]

    # Adding new Background

    blurImg = cv2.blur(background_img, (10, 10))

    blurImg[mask2 != 0] = [0, 0, 0]



    bokeh = no_bg_image + blurImg
    bokeh = cv2.cvtColor(bokeh, cv2.COLOR_BGR2RGB)
    # Save the resulting image
    blurred_img = Image.fromarray(bokeh)
    
    photo = ImageTk.PhotoImage(blurred_img)
    image_label.config(image=photo)
    image_label.image = photo


def open_file_dialog():
    file_path = filedialog.askopenfilename(filetypes=[("Image files", "*.jpg *.jpeg *.png *.bmp *.gif")])
    input_entry.delete(0, tk.END)
    input_entry.insert(0, file_path)



# Create the main tkinter window
root = tk.Tk()
root.title("Bokeh Effect Application")
image_frame = tk.Frame(root)
image_frame.pack_forget()

image_label = tk.Label(image_frame)
image_label.pack()
# Create and place GUI elements
input_label = tk.Label(root, text="Input Image:")
input_label.pack()
input_entry = tk.Entry(root, width=50)
input_entry.pack()
browse_button = tk.Button(root, text="Browse", command=open_file_dialog)
browse_button.pack()

apply_button = tk.Button(root, text="Apply Bokeh Effect", command=apply_bokeh_effect)
apply_button.pack()

status_label = tk.Label(root, text="")
status_label.pack()

root.mainloop()
