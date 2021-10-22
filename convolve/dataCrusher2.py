#     ***************************************************************************
#     Trapezoid & Simpson's Rule based convolution routine.
#
#     NOTE: This algorithm should not be used to evaluate functions that are NOT
#     positive valued!!! (func >= 0 everywhere)
#
#     Ryan Clement
#     February 4, 2011
#     ***************************************************************************

#     import modules
import math
import sys

#     ***** BEGIN Functions *****

#     Legendre Interpolation Polynomial
def lip(x,xa,xm,xb,fa,fm,fb):
      f1 = fa*(x-xm)*(x-xb)/((xa-xm)*(xa-xb))
      f2 = fm*(x-xa)*(x-xb)/((xm-xa)*(xm-xb))
      f3 = fb*(x-xa)*(x-xm)/((xb-xa)*(xb-xm))
      ans = f1 + f2 + f3
      return ans
#     ***

#     Simpsons Rule
def simp(xa,xb,fa,fm,fb):
      ans = (xb-xa)*(fa + (4.0*fm) + fb)/6.0
      return ans
#     ***

#     Trapezoid Rule
def trap(xa,xb,fa,fb):
      ans = (xb-xa)*(fa+fb)/2.0
      return ans
#     ***

#     Normalized Gaussian Function for Convolution
def   gauss(x,mu,sig):
      p = math.pi
      sig2 = math.pow(sig,2)
      c1 = 2.0*p*sig2
      c2 = math.sqrt(c1)
      c3 = math.pow((x-mu),2)/(-2.0*sig2)
      g = math.exp(c3)/c2
      return g
#     ***

#     Square Function for Convolution
def   square(x,w):
      hw = w/2.0
      y = math.fabs(x)
      if (y <= hw):
            ans = 1.0/w
      else:
            ans = 0.0
      return ans
#     ***
      

#     ***** END Functions *****

#     ***** BEGIN Main Program *****

#     give user some info
print 'Begin Trapezoid & Modified Simpson Rule Convolutionator'
print 'I will be back!\n'

#     open i/o files
#     get data file names
#     input data
f1 = sys.argv[1]
print 'Opening data file: ',f1
inf1 = open(f1,'r')
#     output data
#     for Simpsons Rule
f2 = sys.argv[2]
print 'Opening data file: ',f2
outf2 = open(f2,'w')
#     for Trapezoid Rule
f3 = sys.argv[3]
print 'Opening data file: ',f3
outf3 = open(f3,'w')

#     read data
data = inf1.readlines()

#     begin integration routine
n = len(data)
nints = (n-1)/2
print 'File length: ',n
print 'Number of integration regions: ',nints
print 'Total number of integration steps: ',nints*n,'\n'

sint = 0.0
tint = 0.0
outseq = range(n)
seq = range(nints)
#     for <*** following line ***> problems that are monotonic decreasing use the reverse (otherwise comment out)
#     seq.reverse()
#
#     centroid and width for Gaussian convolution function
sig = 4.0
mu = 1.0
wid = 1.0e4
print "The width of the pulse is: ",wid
w2 = wid/2.0
ratthresh = 1
#     outer loop
for k in outseq:
#     convolution function abscissa
      c = data[k]
      c = c.split()
      t = float(c[0])
#     use right-side dx check to compare dx and wid
      if (k == (n-1)):
            cb = data[k-1] # don't want to fall off the end of the array
      else:
            cb = data[k+1]
      cb = cb.split()
      tb = float(cb[0])
      tdx = math.fabs(tb - t)
      rat = w2/tdx
      if (rat < 1.0):
            fm = float(c[1])
            if ( ( k != 0 ) and ( k != (n-1) ) ):
                  xm = t
                  a = data[k-1]
                  a = a.split()
                  xa = float(a[0])
                  fa = float(a[1])
                  b = data[k+1]
                  b = b.split()
                  xb = float(b[0])
                  fb = float(b[1])
      #           two new function endpoints
                  xan = xm - w2
                  xbn = xm + w2
                  fan = lip(xan,xa,xm,xb,fa,fm,fb)
                  fbn = lip(xbn,xa,xm,xb,fa,fm,fb)
                  s1 = square(0,wid)
      #           convolution
                  if ( ( fan >= 0 ) and ( fbn >= 0 ) ):
                        f1 = fan*s1
                        f2 = fm*s1
                        f3 = fbn*s1
                        tint = trap(xan,xm,f1,f2) + trap(xm,xbn,f2,f3)
                        sint = simp(xan,xbn,f1,f2,f3)
                  else:
      #                 quadratic approximation to data failed!
                        print "Trouble ... Trouble ... Trouble!!!"
                        sint = fm
                        tint = fm
            else:
#                 punt!
                  sint = fm
                  tint = fm
            
      else:
      #     inner loop
            for i in seq:
      #     prepare input data
                  j = 2*i
      #           a is left endpoint for this integration region
                  a = data[j]
                  a = a.split()
                  xa = float(a[0])
                  fa = float(a[1])
      #            fca = gauss(t,xa+mu,sig)
                  fca = square(t-xa,wid)
      #           b is right endpoint for this integration region
                  b = data[j+2]
                  b = b.split()
                  xb = float(b[0])
                  fb = float(b[1])
      #            fcb = gauss(t,xb+mu,sig)
                  fcb = square(t-xb,wid)
      #           m is middle point for this integration region
                  m = data[j+1]
                  m = m.split()
                  xm = float(m[0])
                  fm = float(m[1])
      
      #           find midpoint value (rem: possible non-uniform data)
#                 Note: should also add check for uniform interval here to prevent
#                       duplicate work and numerical errors.
                  xc = (xb+xa)/2.0
      #           new midpoint function value based on quadratic approximation to data
                  test = 0
                  fc = lip(xc,xa,xm,xb,fa,fm,fb)
                  if ( (fc < 0) or (fa==0) or (fb==0) or (fm==0) ):
                        test = 1
      #            fcm = gauss(t,xc+mu,sig)
                  fcm = square(t-xc,wid)
      #           convoluted function values
                  f1 = fa*fca
                  f2 = fc*fcm
                  f3 = fb*fcb
                  f4 = fm*fcm
      #           add result for this region
                  sumtrap = trap(xa,xm,f1,f4) + trap(xm,xb,f4,f3)
                  if ( ( test > 0 ) or ( rat < ratthresh ) ):
#                       quadratic approximation to data failed!
#                        print "Issue?"
#                        print "The ratio is: ",rat,ratthresh
#                        print "Test = ",test
                        sint += sumtrap
                  else:
                        sint += simp(xa,xb,f1,f2,f3)
                  tint += sumtrap

#     write convolved data point to file
      outf2.write(str(t)+'     '+str(sint)+'\n') 
      outf3.write(str(t)+'     '+str(tint)+'\n') 
      sint = 0.0
      tint = 0.0

#     close input file
inf1.close()
#     close output file
outf2.close()
#     close output file
outf3.close()

#     ***** END Main Program *****
print 'END of program ...'


