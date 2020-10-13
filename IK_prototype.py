import math as m
import matplotlib.pyplot as plt
import random as r


L0 = 43.36
L1 = 191.96
L2 = 117.63
L3 = 144.16
while 1:
    q1 = r.uniform(-3.14, 3.14)
    q2 = r.uniform(-3.14, 3.14)
    q3 = r.uniform(-3.14, 3.14)

    c1 = m.cos(q1)
    c12 = m.cos(q1 + q2)
    c123 = m.cos(q1 + q2 + q3)

    s1 = m.sin(q1)
    s12 = m.sin(q1 + q2)
    s123 = m.sin(q1 + q2 + q3)

    if ((L1 * c1) > 0) and ((L1 * c1 + L2 * c12) > 0) and ((L1 * c1 + L2 * c12 + L3 * c123) > 0):
        print(m.degrees(q1), m.degrees(q2), m.degrees(q3))
        x = L0 + L1 * c1 + L2 * c12 + L3 * c123
        y = L1 * s1 + L2 * s12 + L3 * s123
        alf = q1 + q2 + q3
        print(x, y, m.degrees(alf))
        print(1111)
        break

y = 75
x = 279
alf = m.radians(48)
print(x, y, m.degrees(alf))




def IK_solution(x, y, alf):
    calf = m.cos(alf)
    salf = m.sin(alf)

    x1 = x - L3 * calf - L0
    y1 = y - L3 * salf

    cq2 = (x1 ** 2 + y1 ** 2 - L1 ** 2 - L2 ** 2) / (2 * L1 * L2)



    q2 = m.acos(cq2)


    q2_01 = q2
    q2_02 = -q2

    c2 = m.cos(q2_01)
    s2 = m.sin(q2_01)

    K = L1 + L2 * c2

    Dc1 = (y1 * L2 * s2) ** 2 - (L2 ** 2 * s2 ** 2 + K ** 2) * (y1 ** 2 - K ** 2)
    cq1_1 = ((y1 * L2 * s2) + m.sqrt(Dc1)) / (L2 ** 2 * s2 ** 2 + K ** 2)
    cq1_2 = ((y1 * L2 * s2) - m.sqrt(Dc1)) / (L2 ** 2 * s2 ** 2 + K ** 2)

    q1_11 = m.acos(cq1_1)
    q1_12 = -q1_11

    q1_21 = m.acos(cq1_2)
    q1_22 = -q1_21

    q1_31 = m.acos(-cq1_1)
    q1_32 = -q1_31

    q1_41 = m.acos(-cq1_2)
    q1_42 = -q1_41


    q = [q1_11, q1_12, q1_21, q1_22, q1_31, q1_32, q1_41, q1_42]
    print(calf, salf, x1, y1)
    print(cq2, q2, K, Dc1, cq1_1, cq1_2)
    print(q)

    q2 = q2_01

    # print('q1:', teta1, q)

    for q1 in q:
        q1 = q1
        q3 = alf - q1 - q2
        yn = L1 * m.sin(q1) + L2 * m.sin(q1 + q2) + L3 * m.sin(q1 + q2 + q3)
        xn = L0 + L1 * m.cos(q1) + L2 * m.cos(q1 + q2) + L3 * m.cos(q1 + q2 + q3)

        if round(yn, 3) == round(y, 3) and round(xn, 3) == round(x, 3):
            Q1 = [q1, q2, q3]
            break

    #print(Q1)

    q2 = q2_02

    # print('q1:', teta1, q)

    for q1 in q:
        q1 = q1
        q3 = alf - q1 - q2
        yn = L1 * m.sin(q1) + L2 * m.sin(q1 + q2) + L3 * m.sin(q1 + q2 + q3)
        xn = L0 + L1 * m.cos(q1) + L2 * m.cos(q1 + q2) + L3 * m.cos(q1 + q2 + q3)

        if round(yn, 3) == round(y, 3) and round(xn, 3) == round(x, 3):
            Q2 = [q1, q2, q3]
            break

    #print(Q2)

    return Q1, Q2

def plot_man_ik(Q1, Q2):

    c1 = m.cos(Q1[0])
    c12 = m.cos(Q1[0] + Q1[1])
    c123 = m.cos(Q1[0] + Q1[1] + Q1[2])

    s1 =   m.sin(Q1[0])
    s12 =  m.sin(Q1[0] + Q1[1])
    s123 = m.sin(Q1[0] + Q1[1] + Q1[2])

    y_Q1 = [0, 0,  L1 * s1, L1 * s1 + L2 * s12, L1 * s1 + L2 * s12 + L3 * s123]
    x_Q1 = [0, L0, L0 + L1 * c1, L0 + L1 * c1 + L2 * c12, L0 + L1 * c1 + L2 * c12 + L3 * c123]

    if (L1 * c1) < L0:
        pass
    else:
        plt.plot(y_Q1, x_Q1, '--', marker='o')

    c1   = m.cos(Q2[0])
    c12 =  m.cos(Q2[0] + Q2[1])
    c123 = m.cos(Q2[0] + Q2[1] + Q2[2])

    s1 =   m.sin(Q2[0])
    s12 =  m.sin(Q2[0] + Q2[1])
    s123 = m.sin(Q2[0] + Q2[1] + Q2[2])

    y_Q2 = [0, 0, L1 * s1, L1 * s1 + L2 * s12, L1 * s1 + L2 * s12 + L3 * s123]
    x_Q2 = [0, L0, L0 + L1 * c1, L0 + L1 * c1 + L2 * c12, L0 + L1 * c1 + L2 * c12 + L3 * c123]



    if (L1 * c1) < L0:
        pass

    else:

        plt.plot(y_Q2, x_Q2, '--', marker='o')

Q1, Q2 = IK_solution(x, y, alf)



'''

y_random_position = [0, 0,  L1 * s1, L1 * s1 + L2 * s12, L1 * s1 + L2 * s12 + L3 * s123]
x_random_position = [0, L0, L0 + L1 * c1, L0 + L1 * c1 + L2 * c12, L0 + L1 * c1 + L2 * c12 + L3 * c123]

plt.plot(y_random_position, x_random_position, marker='o')
'''
#plt.grid()

#y_current = [L1 * s1 + L2 * s12 + L3 * s123, L1 * s1 + L2 * s12 + 170 * s123]
#x_current = [L0 + L1 * c1 + L2 * c12 + L3 * c123, L0 + L1 * c1 + L2 * c12 + 170 * c123]



#plt.plot(y_current, x_current)
plt.arrow(L1 * s1 + L2 * s12 + L3 * s123, L0 + L1 * c1 + L2 * c12 + L3 * c123,
          -(L1 * s1 + L2 * s12 + L3 * s123) + (L1 * s1 + L2 * s12 + 200 * s123),
          -(L0 + L1 * c1 + L2 * c12 + L3 * c123) + (L0 + L1 * c1 + L2 * c12 + 200 * c123),
         width = 5,
         head_length = 20)

print(Q1)
print(Q2)

plot_man_ik(Q1, Q2)



plt.xlim(-453.75, 453.75)
plt.ylim(0, 497.11)

plt.show()

