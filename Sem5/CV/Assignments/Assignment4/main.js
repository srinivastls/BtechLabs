let inputImage;
let outputImage;
let isBokehApplied = false;

function setup() {
    outputImage = document.getElementById('outputImage');

    document.getElementById('imageInput').addEventListener('change', function (e) {
        const file = e.target.files[0];
        if (file) {
            const reader = new FileReader();
            reader.onload = function (event) {
                inputImage = new Image();
                inputImage.src = event.target.result;
                outputImage.src = event.target.result;
            };
            reader.readAsDataURL(file);
        }
    });

    document.getElementById('applyBokehButton').addEventListener('click', function () {
        if (inputImage) {
            applyBokehButton(inputImage);
        }
    });
}

function applyBokehButton(image) {
    // Create a canvas for image processing
    let processingCanvas = createCanvas(image.width, image.height);
    processingCanvas.hide(); // Hide the processing canvas
    image(image, 0, 0, image.width, image.height); // Draw the input image on the processing canvas

    // Apply a blur effect to the processing canvas
    processingCanvas.filter(BLUR, 100); // Adjust the blur strength as needed

    // Get the modified image from the processing canvas
    let modifiedImage = processingCanvas.elt.toDataURL("jpeg");
    
    // Update the src attribute of the output image
    outputImage.src = modifiedImage;

    // Remove the processing canvas
    processingCanvas.remove();
}
