# 42-FDF
Discover the basic of graphic programming

MiniLibX - Manipulating images

SYNOPSYS
       void *
       mlx_new_image ( void *mlx_ptr, int width, int height );

       char *
       mlx_get_data_addr  (  void  *img_ptr, int *bits_per_pixel, int *size_line, int
       *endian );

       int
       mlx_put_image_to_window ( void *mlx_ptr, void *win_ptr, void *img_ptr, int  x,
       int y );

       unsigned int
       mlx_get_color_value ( void *mlx_ptr, int color );

       void *
       mlx_xpm_to_image ( void *mlx_ptr, char **xpm_data, int *width, int *height );

       void *
       mlx_xpm_file_to_image ( void *mlx_ptr, char *filename, int *width, int *height
       );

       int
       mlx_destroy_image ( void *mlx_ptr, void *img_ptr );

DESCRIPTION
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

       mlx_get_data_addr returns a char * address that represents the begining of the
       memory   area  where  the  image  is  stored.  From  this  adress,  the  first
       bits_per_pixel bits represent the color of the first pixel in the  first  line
       of  the  image.  The  second group of bits_per_pixel bits represent the second
       pixel of the first line, and so on.  Add size_line to the adress  to  get  the
       begining of the second line. You can reach any pixels of the image that way.

       mlx_destroy_image destroys the given image ( img_ptr ).

Wiki "Endianness"

Endianness refers to the sequential order used to numerically interpret a range of bytes in computer memory as a larger, composed word value. It also describes the order of byte transmission over a digital link. Words may be represented in big-endian or little-endian format, with the term "end" denoting the front end or start of the word, a nomenclature potentially counterintuitive given the connotation of "finish" or "final portion" associated with "end" as a stand-alone term in everyday language. When storing a word in big-endian format the most significant byte, which is the byte containing the most significant bit, is stored first and the following bytes are stored in decreasing significance order with the least significant byte, which is the byte containing the least significant bit, thus being stored at last place. Little-endian format reverses the order of the sequence and stores the least significant byte at the first location with the most significant byte being stored last.[1] The order of bits within a byte can also have endianness (as discussed later); however, a byte is typically handled as a numerical value or character symbol and so bit sequence order is obviated.

https://upload.wikimedia.org/wikipedia/commons/thumb/5/54/Big-Endian.svg/280px-Big-Endian.svg.png
https://upload.wikimedia.org/wikipedia/commons/thumb/e/ed/Little-Endian.svg/280px-Little-Endian.svg.png

mlx_get_data_addr returns a char * address that represents the begining of the
memory   area  where  the  image  is  stored.  From  this  adress,  the  first
bits_per_pixel bits represent the color of the first pixel in the  first  line
of  the  image.  The  second group of bits_per_pixel bits represent the second
pixel of the first line, and so on.  Add size_line to the adress  to  get  the
begining of the second line. You can reach any pixels of the image that way.

STORING COLOR INSIDE IMAGES
       Depending  on  the display, the number of bits used to store a pixel color can
       change. The user usually represents a color in RGB mode, using  one  byte  for
       each  component (see mlx_pixel_put manual). This must be translated to fit the
       bits_per_pixel requirement of the image, and make the color understandable  to
       the graphical system.  That is the purpose of the mlx_get_color_value () func-
       tion. It takes a standard RGB color parameter, and  returns  an  unsigned  int
       value.   The bits_per_pixel least significant bits of this value can be stored
       in the image.

       Keep in mind that the least significant bits position  depends  on  the  local
       computer's  endian.  If  the endian of the image (in fact the endian of the X-
       Server's computer for remote X11 display) differs from the local endian,  then
       the value should be transformed before being used.
       
SET RGB COLORS

You indicate RGB color values in foregroundColor, backgroundColor and altBackgrndColor. An RGB value is a 4-byte Long Integer whose format (0x00RRGGBB) is described in the following table (bytes are numbered from 0 to 3, from right to left):

Byte	Description
3	Must be zero if absolute RGB color
2	Red component of the color (0..255)
1	Green component of the color (0..255)
0	Blue component of the color (0..255)


The following table shows some examples of RGB color values:

Value	Description
0x00000000	Black
0x00FF0000	Bright Red
0x0000FF00	Bright Green
0x000000FF	Bright Blue
0x007F7F7F	Gray
0x00FFFF00	Bright Yellow
0x00FF7F7F	Red Pastel
0x00FFFFFF	White

http://www.4d.com/docs/CMU/CMU00628.HTM
