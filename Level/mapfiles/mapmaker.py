import struct

def addObject(mapfile, objid, x, y):
  mapfile.write(struct.pack("Iff", objid, x, y))

def mttomap(mt, mapfile):
  x = 0
  y = 0
  for line in mt:
    x = 0
    for obj in line:
      if chr(obj) == 'X':
       addObject(mapfile,0,x,y)
      elif chr(obj) == 'B':
       addObject(mapfile,1,x,y)
      elif chr(obj) == 'L':
       addObject(mapfile,2,x,y)
      elif chr(obj) == 'O':
       x+=1
       continue
      else:
       addObject(mapfile,1337,x,y);
      x+=1
    y+=1

f = open("test.map","wb")
f.write(b'TM') # signature
f.write(struct.pack("II",30,40)) # map size

mtInst = open("map.mt","rb")
mttomap(mtInst, f)

f.close()
