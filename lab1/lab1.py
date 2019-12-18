# x = 3*a*t/(1 + t^3), y = 3*a*t^2/(1 + t^3), -1 < A <= t <= B

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
from math import cos, sin, pi
from sympy.solvers import solve
from sympy import Symbol

import sys

# Объявляем все глобальные переменные
global X_COORD
global Y_COORD
global ITERATIONS
global x_center
global y_center
global a
global A
global B

def drawgrid(SERIF_OFFSET, SERIF_DISTANCE):
    glBegin(GL_LINES)
    # Цвет осей (черный)
    glColor3f(0.0, 0.0, 0.0)

    # Ось X
    glVertex2f(0.0, Y_COORD / 2)
    glVertex2f(X_COORD, Y_COORD / 2)

    glVertex2f(X_COORD, Y_COORD / 2)
    glVertex2f(X_COORD * 0.95, 0.54 * Y_COORD)

    glVertex2f(X_COORD, Y_COORD / 2)
    glVertex2f(X_COORD * 0.95, 0.46 * Y_COORD)

    # Разметка оси X
    p = X_COORD / 2
    i = X_COORD / 2
    while i < X_COORD:
        glVertex2f(i, Y_COORD / 2)
        glVertex2f(i, Y_COORD / 2 + SERIF_OFFSET)

        glVertex2f(p, Y_COORD / 2)
        glVertex2f(p, Y_COORD / 2 + SERIF_OFFSET)
        i += SERIF_DISTANCE
        p -= SERIF_DISTANCE

    # Ось Y
    t = Y_COORD / 2
    glVertex2f(X_COORD / 2, Y_COORD)
    glVertex2f(X_COORD / 2, 0.0)

    glVertex2f(X_COORD / 2, Y_COORD)
    glVertex2f(X_COORD * 0.54, 0.95 * Y_COORD)

    glVertex2f(X_COORD / 2, Y_COORD)
    glVertex2f(X_COORD * 0.46, 0.95 * Y_COORD)

    # Разметака оси Y
    i = Y_COORD / 2
    while i < Y_COORD:
        glVertex2f(X_COORD / 2, i)
        glVertex2f(Y_COORD / 2 + SERIF_OFFSET, i)

        glVertex2f(X_COORD / 2, t)
        glVertex2f(Y_COORD / 2 + SERIF_OFFSET, t)
        i += SERIF_DISTANCE
        t -= SERIF_DISTANCE

    glEnd()

    glColor3f(1.0, 0.0, 0.0)

    # Нумерация оси X
    for current in range(int(round(-X_COORD/2 + 1)), int(round(X_COORD/2))):

        glPushMatrix()
        glTranslatef(current + X_COORD/2, 0.25 + Y_COORD/2, 0.5)
        glScalef(0.003, 0.003, 1)

        string = str(current)
        for char in string:
                glutStrokeCharacter(GLUT_STROKE_ROMAN, ord(char))

        glPopMatrix()

    # Нумерация оси Y
    for current in range(int(round(-Y_COORD/2 + 1)), int(round(Y_COORD/2))):

        glPushMatrix()
        glTranslatef(0.25 + X_COORD/2, current + Y_COORD/2, 0.5)
        glScalef(0.003, 0.003, 1)

        string = str(current)
        for char in string:
            glutStrokeCharacter(GLUT_STROKE_ROMAN, ord(char))

        glPopMatrix()

    glPushMatrix()

    glTranslatef(-1 + X_COORD / 2, Y_COORD - 1, 0.5)
    glScalef(0.004, 0.004, 1)

    glColor3f(1.0, 0.0, 0.0)
    glutStrokeCharacter(GLUT_STROKE_ROMAN, ord('Y'))
    glColor3f(0.0, 0.0, 0.0)

    glPopMatrix()

    glPushMatrix()

    glTranslatef(X_COORD - 1, Y_COORD / 2 - 1, 0.5)
    glScalef(0.004, 0.004, 1)

    glColor3f(1.0, 0.0, 0.0)
    glutStrokeCharacter(GLUT_STROKE_ROMAN, ord('X'))
    glColor3f(0.0, 0.0, 0.0)

    glPopMatrix()


def drawfunc():
    # Сам график
    # x = 3*a*t/(1 + t^3), y = 3*a*t^2/(1 + t^3), -1 < A <= t <= B
    glBegin(GL_POINTS)
    glColor3f(0.8, 0.0, 0.8)
    ITERATIONS = 0.0005
    t = A
    # Расчет точек
    x = 3 * a * t/(1 + t ** 3)
    y = 3 * a * (t ** 2)/ (1 + t ** 3)
    while t < B:
        # Постановка точки
        glVertex2f(x_center + x, y_center + y)
        t += t * ITERATIONS
        if t == 0:
            t += ITERATIONS
        # Перерасчет координат
        x = 3 * a * t / (1 + t ** 3)
        y = 3 * a * (t ** 2) / (1 + t ** 3)
    glEnd()


def display():
    glClear(GL_COLOR_BUFFER_BIT)

    # Параметры 1-й размер зачечки, второй частота засечки (шаг)
    drawgrid(0.45, 0.75)
    drawfunc()

    glutSwapBuffers()
    glFlush()


# Ввод параметров
print("Enter a: ")
a = int(input())
if a < 0:
    print("Wrong parameter a")
    sys.exit()

print("Enter A > -1: ")
A = int(input())
if A <= -1:
    print("Wrong parameter A")
    sys.exit()

print("Enter B > A: ")
B = int(input())
if B < A:
    print("Wrong parameter B")
    sys.exit()

X_COORD = max(2, 4 * int(a))
Y_COORD = max(2, 4 * int(a))
x_center = X_COORD / 2
y_center = Y_COORD / 2

# Использовать двойную буферизацию и цвета в формате RGB (Красный, Зеленый, Синий)
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB)
# Указываем начальный размер окна (ширина, высота)
glutInitWindowSize(800, 600)
# Указываем начальное положение (смещение) окна относительно левого верхнего угла экрана
glutInitWindowPosition(500, 200)
# Инициализация OpenGl
glutInit(sys.argv)
# Название окна
glutCreateWindow("Lab_1, Var_18")
# Цвет плоскости (Белый)
glClearColor(1.0, 1.0, 1.0, 1.0)
glMatrixMode(GL_PROJECTION)
glLoadIdentity()
# Пространство координат
glOrtho(0.0, X_COORD, 0.0, Y_COORD, -1.0, 1.0)
# Определяем процедуру, отвечающую за перерисовку
glutDisplayFunc(display)
# Запускаем основной цикл
glutMainLoop()
