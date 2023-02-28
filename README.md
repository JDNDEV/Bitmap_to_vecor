# Bitmap_to_vector
Simple code developed to convert little imagens into vector to be used in arduino whit LCD ILI9341.

Its consist basically in a loop to count the number of repetitions of the same color in an array of bitmaps. 

Then it is reduced to a number of repetitions of a given color in the array of bitmaps.

For example, in this array:

FF FF FF FF FF FF FF 78 78 78 78 55 55 55 FF FF FF FF FF FF

Will be reduced to:

07 FF 04 78 03 55 06 FF

Thus reducing memory usage.


