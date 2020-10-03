import random as r
import numpy as  np 
import math as m 

teta1 = r.uniform(-3.14, 3.14)
teta2 = r.uniform(-3.14, 3.14)
teta3 = r.uniform(-3.14, 3.14)

print(teta1, teta2, teta3)

L1 = 3
L2 = 2
L3 = 1

c1 = m.cos(teta1)
c2 = m.cos(teta2)
c3 = m.cos(teta3)
s1 = m.sin(teta1)
s2 = m.sin(teta2)
s3 = m.sin(teta3)

c12 = m.cos(teta1 + teta2)
c123 = m.cos(teta1 + teta2 + teta3)

s12 = m.sin(teta1 + teta2)
s123 = m.sin(teta1 + teta2 + teta3)

x = L1*c1 + L2*c12 + L3*c123
y = L1*s1 + L2*s12 + L3*s123
alf = teta1 + teta2 + teta3

x1 = x - L3 * c123
y1 = y - L3 * s123

cq2 = (x1**2 + y1**2 - L1**2 - L2**2) / (2*L1*L2)

q2 = m.acos(cq2)
#print("q2:", teta2, q2)

q2_01 = q2
q2_02 = -q2
#q2 


c2 = m.cos(q2_01)
s2 = m.sin(q2_02)

K = L1 + L2*c2


Dc1 = (y1 * L2 * s2)**2 - (L2**2 * s2**2 + K**2) * (y1**2 - K**2)
cq1_1 = ((y1 * L2 * s2) + m.sqrt(Dc1)) / (L2**2 * s2**2 + K**2)
cq1_2 = ((y1 * L2 * s2) - m.sqrt(Dc1)) / (L2**2 * s2**2 + K**2)
#print("c1:", c1, cq1_1, cq1_2, -cq1_1, -cq1_2)



q1_11 = m.acos(cq1_1)
q1_12 = -q1_11

q1_21 = m.acos(cq1_2)
q1_22 = -q1_21

q1_31 = m.acos(-cq1_1)
q1_32 = -q1_31

q1_41 = m.acos(-cq1_2)
q1_42 = -q1_41

q = [q1_11, q1_12, q1_21, q1_22, q1_31, q1_32, q1_41, q1_42]


q2 = q2_01

#print('q1:', teta1, q)

for q1 in q:
	q1 = q1
	q3 = alf - q1 - q2
	yn = L1*m.sin(q1) + L2*m.sin(q1 + q2) + L3*m.sin(q1 + q2 + q3)
	

	if round(yn, 2) == round(y, 2):
		Q1 = [q1, q2, q3]
		break

print(Q1)


q2 = q2_02

#print('q1:', teta1, q)

for q1 in q:
	q1 = q1
	q3 = alf - q1 - q2
	yn = L1*m.sin(q1) + L2*m.sin(q1 + q2) + L3*m.sin(q1 + q2 + q3)
	

	if round(yn, 2) == round(y, 2):
		Q2 = [q1, q2, q3]
		break

print(Q2)
