import os
import cv2
import numpy as np
from flask import Flask, render_template, request, redirect, url_for, send_from_directory
from PIL import Image

app = Flask(__name__)

UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = {'png', 'jpg', 'jpeg', 'gif'}

app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER
app.config['MAX_CONTENT_LENGTH'] = 16 * 1024 * 1024  # Limit file size to 16MB

def allowed_file(filename):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

def apply_bokeh_effect(image_path):
    img = cv2.imread(image_path)
    
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

    bokeh_path = 'bokeh_image.jpg'
    cv2.imwrite(bokeh_path, bokeh)
    return bokeh_path

@app.route('/', methods=['GET', 'POST'])
def index():
    image_url = None
    bokeh_applied = False
    download_url = None

    if request.method == 'POST':
        if 'image' not in request.files:
            return redirect(request.url)

        image = request.files['image']

        if image.filename == '':
            return redirect(request.url)

        if image and allowed_file(image.filename):
            image_path = os.path.join(app.config['UPLOAD_FOLDER'], image.filename)
            image.save(image_path)
            
            bokeh_path = apply_bokeh_effect(image_path)
            image_url = os.path.join('uploads', image.filename)
            bokeh_applied = True
            download_url = bokeh_path

    return render_template('index.html', image_url=image_url, bokeh_applied=bokeh_applied, download_url=download_url)

@app.route('/uploads/<filename>')
def uploaded_file(filename):
    return send_from_directory(app.config['UPLOAD_FOLDER'], filename)

if __name__ == '__main__':
    app.run(debug=True)
