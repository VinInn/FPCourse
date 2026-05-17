import math
import numpy as np
x = float.fromhex("0x1.e64002p-2")
z=x*x


def p(x) :
  print(x.hex(),float(np.float32(x)).hex())




p(x)
p(math.sin(x))
p( x*(1-z/6) )
p( x*(1-z/6*(1-z/20)) )
p( x*(1-z/6*(1-z/20*(1-z/42))) )
p( x*(1-z/6*(1-z/20*(1-z/42*(1-z/72)))) )
p( x*(1-z/6*(1-z/20*(1-z/42*(1-z/72*(1-z/110))))) )
p( x*(1-z/6*(1-z/20*(1-z/42*(1-z/72*(1-z/110*(1-z/(12*13))))))) )
p( x*(1-z/6*(1-z/20*(1-z/42*(1-z/72*(1-z/110*(1-z/(12*13)*(1-z/(14*15)) )))))) )

