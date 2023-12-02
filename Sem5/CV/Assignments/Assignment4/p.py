import tkinter as tk
from tkinter import filedialog
from PIL import Image, ImageTk
import cv2
import numpy as np

window = tk.Tk()
window.title('Bokeh Effect')
window.geometry('400x400')

image_frame = tk.Frame(window)
image_frame.pack_forget()

image_label = tk.Label(image_frame)
image_label.pack()

def save():
    global image_name
    image_name = text_box.get()
    cv2.imwrite(image_name, bokeh)
    text_frame.pack_forget()


text_frame = tk.Frame(window)
text_frame.pack_forget()

text_label = tk.Label(text_frame)
text_label.config(text='Enter the Image Name: ')
text_label.pack(side='left')
text_box = tk.Entry(text_frame, width=20)
text_box.pack(side='right')
ok_btn = tk.Button(text_frame, text='Save', command=save)
ok_btn.pack_forget()


def insert_img():
    image_frame.pack(side='top')
    global img
    file_path = filedialog.askopenfilename(title="Select an Image",
                                           filetypes=[("Image files", "*.jpg *.png *.gif *.jpeg")])
    if file_path:
        image = Image.open(file_path)
        photo = ImageTk.PhotoImage(image)
        image_label.config(image=photo)
        image_label.image = photo
        img = cv2.imread(file_path)
        bokeh_btn.pack(side='right')


def bokeh_effect():
    global bokeh
    bokeh_btn.pack_forget()

    # Selecting the Region of Interest of the image
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
    blurred_img = Image.fromarray(bokeh)
    
    photo = ImageTk.PhotoImage(blurred_img)
    image_label.config(image=photo)
    image_label.image = photo
    save_btn.pack(side='right')

def save_img():
    save_btn.pack_forget()
    text_frame.pack(side='top')
    ok_btn.pack(side='bottom')


buttons_frame = tk.Frame(window)
buttons_frame.pack(side='bottom')
insert_btn = tk.Button(buttons_frame, text="Insert", command=insert_img)
insert_btn.pack(side='left')
bokeh_btn = tk.Button(buttons_frame, text="Bokeh", command=bokeh_effect)
bokeh_btn.pack_forget()
save_btn = tk.Button(buttons_frame, text='Save Image', command=save_img)
save_btn.pack_forget()


window.mainloop()