"""

This is where the keycode can be decoded
https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h

Kernel documentation about input events
https://www.kernel.org/doc/Documentation/input/input.txt

A blog post about handling input events with python.
https://thehackerdiary.wordpress.com/2017/04/21/exploring-devinput-1/

"""

import struct

f = open('/dev/input/event5', 'rb')

while 1:
    data = f.read(24)
    d = struct.unpack('4IHHI', data)

    if d[4] == 1:
        print(d)


