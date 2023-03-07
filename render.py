# you will need to install cv2
# Run "pip3 install opencv-python" in CLI
import cv2
import sys
# Kaleidoscope requires numpy. Uncomment this line and install it if you need to.
import numpy as np

# Store command line arguments in variables
#  change the next line to store the filename
filename = sys.argv[1]
manip = sys.argv[2]

# Open the image file
img = cv2.imread('../' + filename)
# Get the dimensions (in pixels) of the image
dimensions = img.shape
# Copy the original image into an image for manipulation
img_manip = cv2.resize(img, (dimensions[1], dimensions[0]))
img_flip = cv2.resize(img, (dimensions[1], dimensions[0]))
img_mirror = cv2.resize(img, (dimensions[1], dimensions[0]))
# Store white in a list, where each of the three parts is on a scale of [0, 255]
white = 255
for x in range(dimensions[0]):
    for y in range(dimensions[1]):
        if manip == 'flip':
            img_manip[x, y] = img[dimensions[0]-1-x, y]
        elif manip == 'mirror':
            # mirror the image and store in img_manip[x, y]
            img_manip[x, y] = img[x, dimensions[1]-1-y]
        elif manip == 'invert':
            # invert the image and store in img_manip[x, y]
            # Hint: img[x, y] returns the color of the pixel at that coordinate.
            # You can invert by subtracting that color from white.
            for i in range(0, 3):
                img_manip[x, y][i] = white - img[x, y][i]
        img_flip[x, y] = img[dimensions[0]-1-x, y]
        img_mirror[x, y] = img[x, dimensions[1]-1-y]

img_flip_mirrored = cv2.resize(img_flip, (dimensions[1], dimensions[0]))
for x in range(dimensions[0]):
    for y in range(dimensions[1]):
        img_flip_mirrored[x, y] = img_flip[x, dimensions[1]-1-y]

# Displays the original image in the top left corner of the screen.
image = 'Original image'
cv2.namedWindow(image)
cv2.moveWindow(image, 0, 0)
cv2.imshow(image, img)
# Display the manipulated image alongside the original image.
new_image = 'Manipulated image'
cv2.namedWindow(new_image)
cv2.moveWindow(new_image, dimensions[1], 0)
cv2.imshow(new_image, img_manip)

index = filename.find('.')
splitName = filename.split('.')
Kfilename = splitName[0] + "_kaleidoscope." + splitName[1]

# Create a kaleidoscope image, display it, and save it to a file.
# This line puts two images side-by-side in one window.
vertical_concat1 = np.concatenate((img, img_flip), axis=0)
vertical_concat2 = np.concatenate((img_mirror, img_flip_mirrored), axis=0)

horizontal_concat = np.concatenate((vertical_concat1, vertical_concat2), axis=1)
# Save the image using the imwrite method from cv2
cv2.imwrite("../" + Kfilename, horizontal_concat)
# Show the image
cv2.imshow('Horizontal Concatenation!', horizontal_concat)


# Infinite loop to keep the windows open until the escape key is pressed.
while True:
    k = cv2.waitKey(1)
    if k == 27:
        cv2.destroyAllWindows()
        exit()

