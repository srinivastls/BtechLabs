import cv2
import numpy as np
import tkinter as tk
from PIL import Image, ImageTk
from tkinter import filedialog

def apply_bokeh_effect(image_path):
    image_frame.pack(side='top')
    # Read the image
    my_img = cv2.imread(image_path)
    background_img = my_img.copy()
    # Initialize the mask with zeros
    mask = np.zeros(my_img.shape[:2], np.uint8)

    
   
    # Create a mask condition based on the color range
    mask_condition = ((my_img[:, :, 0] >= 0) & (my_img[:, :, 0] <=255) &
                      (my_img[:, :, 1] >= 10) & (my_img[:, :, 1] <= 250)&
                     (my_img[:, :, 2] >= 0) & (my_img[:, :, 2] <= 255))

    # Set the mask condition to mark the foreground pixels
    mask[mask_condition] = cv2.GC_PR_FGD

    background_model = np.zeros((1, 65), np.float64)
    foreground_model = np.zeros((1, 65), np.float64)
    

    cv2.grabCut(my_img, mask,None, background_model, foreground_model, 100, cv2.GC_INIT_WITH_MASK)
    mask2 = np.where((mask == 2) | (mask == 0), 0, 1).astype('uint8')
    no_bg_my = my_img * mask2[:, :, np.newaxis]


    # Adding new Background

    blurImg = cv2.blur(background_img, (10, 10))

    blurImg[mask2 != 0] = [0, 0, 0]



    bokeh = no_bg_my + blurImg
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

def apply_bokeh():
    input_image_path = input_entry.get()
    
    apply_bokeh_effect(input_image_path)

# Create the main tkinter window
window = tk.Tk()
window.title("Bokeh Effect Application")
image_frame = tk.Frame(window)
image_frame.pack_forget()

image_label = tk.Label(image_frame)
image_label.pack()
# Create and place GUI elements
input_label = tk.Label(window, text="Input Image:")
input_label.pack()
input_entry = tk.Entry(window, width=50)
input_entry.pack()
browse_button = tk.Button(window, text="Browse", command=open_file_dialog)
browse_button.pack()

apply_button = tk.Button(window, text="Apply Bokeh Effect", command=apply_bokeh)
apply_button.pack()

status_label = tk.Label(window, text="")
status_label.pack()

window.mainloop()
