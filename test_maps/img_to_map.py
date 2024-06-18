from PIL import Image

def image_to_pixel_data(image_path):
    # Open the image
    with Image.open(image_path) as img:
        # Convert the image to RGB format
        img = img.convert('RGB')
        width, height = img.size
        pixels = img.load()

        # Initialize an empty list to store pixel information
        pixel_data = []

        # Iterate through each pixel in the image
        for y in range(height):
            for x in range(width):
                r, g, b = pixels[x, y]
                hex_color = f'{r:02x}{g:02x}{b:02x}'
                pixel_data.append(f'0,0x{hex_color}')
            pixel_data.append('\n')  # Add newline at the end of each row

        # Join the pixel data with spaces
        pixel_data_string = ' '.join(pixel_data).strip()

        return pixel_data_string

# Path to your image file
image_path = input("Image path >> ")

# Get the pixel data as a formatted string
pixel_data_string = image_to_pixel_data(image_path)

# Print or save the pixel data string
res_path = image_path.replace(".jpg", ".fdf")

# Optionally, save the output to a text file
with open(res_path, 'w') as file:
    file.write(pixel_data_string)
