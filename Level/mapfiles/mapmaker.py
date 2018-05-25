import struct

def addObject(mapfile, objectID, x, y):
  f.write(struct.pack("Iff", objectID, x, y))

f = open("test.map","wb")
f.write(b'TM') # signature
f.write(struct.pack("II",30,40)) # map size

# object list
addObject(f, 0, 3, 3)
addObject(f, 0, 4, 5)

f.close()
