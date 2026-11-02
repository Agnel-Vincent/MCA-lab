import numpy as np
r = int(input("Enter number of rows: "))
c = int(input("Enter number of columns: "))
pixels = []
print("Enter pixel values:")
for i in range(r * c):
    value = int(input("Pixel: "))
    pixels.append(value)
image = np.array(pixels).reshape(r, c)
print("\nOriginal Image:\n", image)
print("\nSliced Region:\n", image[0:2, 0:2])
b = int(input("\nEnter brightness value: "))
bright = np.clip(image + b, 0, 255)
print("\nBrightness Adjusted Image:\n", bright)
matrix = np.eye(c, dtype=int)
result = np.matmul(image, matrix)
print("\nTransformed Image:\n", result)