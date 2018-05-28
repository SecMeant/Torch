import struct

def addObject(mapfile, objectID, x, y):
  f.write(struct.pack("Iff", objectID, x, y))

f = open("test.map","wb")
f.write(b'TM') # signature
f.write(struct.pack("II",30,40)) # map size

# object list
for i in range(0,21):
  addObject(f, 0, i, 0)

for j in range(0,20):
  addObject(f, 0, 0, j)
  addObject(f, 0, 20, j)

for i in range(0,21):
  addObject(f, 0, i, 20)

f.close()
