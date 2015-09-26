from sklearn import *
from scipy.sparse import *
from scipy import *
import numpy
x = [[0.,0.],[1.,0.],[0.,1.],[1.,1.]]
y = [0,0,0,1]
clf = svm.SVC(kernel='linear',C=2)
clf.fit(X=x,y=y)
print clf.dual_coef_