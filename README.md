# 42-FDF
Discover the basic of graphic programming

MiniLibX - Manipulating images

mlx_new_image () creates a new image in memory. It returns a void * identifier
needed  to manipulate this image later. It only needs the size of the image to
be created, using the width and height parameters, and the mlx_ptr  connection
identifier (see the mlx manual).

The  user can draw inside the image (see below), and can dump the image inside
a specified window at any time to display it on the screen. This is done using
mlx_put_image_to_window (). Three identifiers are needed here, for the connec-
tion to the display, the window to use, and the image (respectively mlx_ptr  ,
win_ptr and img_ptr ). The ( x , y ) coordinates define where the image should
be placed in the window.

mlx_get_data_addr () returns information about the created image,  allowing  a
user to modify it later. The img_ptr parameter specifies the image to use. The
three next parameters should be the addresses of three different  valid  inte-
gers.   bits_per_pixel will be filled with the number of bits needed to repre-
sent a pixel color (also called the depth of the  image).   size_line  is  the
number  of bytes used to store one line of the image in memory.  This informa-
tion is needed to move from one line to another in the  image.   endian  tells
you  wether the pixel color in the image needs to be stored in little endian (
endian == 0), or big endian ( endian == 1).

Wiki "Endianness"
https://upload.wikimedia.org/wikipedia/commons/thumb/5/54/Big-Endian.svg/280px-Big-Endian.svg.png
https://upload.wikimedia.org/wikipedia/commons/thumb/e/ed/Little-Endian.svg/280px-Little-Endian.svg.png

mlx_get_data_addr returns a char * address that represents the begining of the
memory   area  where  the  image  is  stored.  From  this  adress,  the  first
bits_per_pixel bits represent the color of the first pixel in the  first  line
of  the  image.  The  second group of bits_per_pixel bits represent the second
pixel of the first line, and so on.  Add size_line to the adress  to  get  the
begining of the second line. You can reach any pixels of the image that way.
