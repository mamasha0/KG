#include "graphics.h"
#include "Piramid.h"
#include <stdlib.h>
#include <iostream>
#include <algorithm>

void hud(vector<Piramid>& piramids) {
    vector<Triangle> triangles;
    for (int i = 0; i < piramids.size(); i++) {
        piramids[i].projection();
        vector<Triangle> curTriangles = piramids[i].getTriandles();
        for (int j = 0; j < curTriangles.size(); j++)
            triangles.push_back(curTriangles[j]);
    }
    for (int i = 1; i < triangles.size(); i++) {
        for (int j = 0; j < triangles.size() - i; j++)
            if (triangles[j].getMidZ() < triangles[j + 1].getMidZ())
                swap(triangles[j], triangles[j + 1]);
    }

    for (int i = 0; i < triangles.size(); i++) {
        triangles[i].print();
        triangles[i].painting();
    }
}
//тень
void shadow(vector<Piramid>& piramids, Point3D l) {
    for (int i = 0; i < piramids.size(); i++)
        piramids[i].parintShadow(l);
}
//Границы по осям X и Y
void setMax(vector<Piramid>& piramids, int maxX, int maxY) {
    for (int i = 0; i < piramids.size(); i++)
        piramids[i].setMax(maxX, maxY);
}

void drowTask(vector<Piramid>& piramids, Point3D& l) {
    cleardevice();
    hud(piramids);
    shadow(piramids, l);
}
//Функция перемещения
void transfer(vector<Piramid>& piramids, int number, double dx, double dy, double dz) {
    for (int i = 0; i < piramids.size(); i++)
        if (number == 0 || i == number - 1)
            piramids[i].transfer(dx, dy, dz);
}
//Функция масштабирования
void scale(vector<Piramid>& piramids, int number, double sx, double sy, double sz) {
    for (int i = 0; i < piramids.size(); i++)
        if (number == 0 || i == number - 1)
            piramids[i].scale(sx, sy, sz);
}
//Функция вращения
void rotation(vector<Piramid>& piramids, int number, double angle, Axises axis) {
    for (int i = 0; i < piramids.size(); i++)
        if (number == 0 || i == number - 1)
            piramids[i].rotation(angle, axis);
}

vector<Piramid> createTask() {
    Piramid piramid1(Point3D(400, 400, 0), Point3D(350, 250, 100), Point3D(300, 300, 0), Point3D(270, 270, 200), BLUE, GREEN, RED, YELLOW);
    Piramid piramid2(Point3D(350, 350, 100), Point3D(400, 300, 0), Point3D(250, 250, 100), Point3D(350, 350, 100), CYAN, MAGENTA, BROWN, LIGHTRED);
    vector<Piramid> piramids;
    piramids.push_back(piramid1);
    piramids.push_back(piramid2);
    return piramids;
}

int main() {

    //инициализация графического окна
    int gm, gd = DETECT;
    char a[2] = " ";
    initgraph(&gd, &gm, a); 
    const int maxX = getmaxx() - 10, maxY = getmaxy() - 10;
    vector<Piramid> piramids = createTask();
    setMax(piramids, maxX, maxY);
    double range = 10, rel = 1.1, angle = 10; //коэффициенты
    Point3D l(0, 0, 0);  //источник света
    drowTask(piramids, l);
    bool isExit = false;
    int number = 0; //
    int choice;
    while (!isExit)
    {
        //обработка нажатий
        choice = getch();
        switch (choice)
        {
        case 48: //0
            number = 0;
            break;
        case 49: //1 пирамида
            number = 1;
            break;
        case 50: //2 пирамида
            number = 2;
            break;
        case -27: //t - перемещение по оси Z
            transfer(piramids, number, 0, 0, range);
            drowTask(piramids, l);
            break;
        case -17: //g - перемещение по оси Z
            transfer(piramids, number, 0, 0, -range);
            drowTask(piramids, l);
            break;
        case -10: //w
            transfer(piramids, number, 0, -range, 0);
            drowTask(piramids, l);
            break;
        case -5: //s
            transfer(piramids, number, 0, range, 0);
            drowTask(piramids, l);
            break;
        case -12: //a 
            transfer(piramids, number, -range, 0, 0);
            drowTask(piramids, l);
            break;
        case -30: //d 
            transfer(piramids, number, range, 0, 0);
            drowTask(piramids, l);
            break;
        case -32: //уменьшение - f 
            scale(piramids, number, 1.0 / rel, 1.0 / rel, 1.0 / rel);
            drowTask(piramids, l);
            break;
        case -22: //увеличение - r 
            scale(piramids, number, rel, rel, rel);
            drowTask(piramids, l);
            break;
        case -23: //q - вращение по оси z 
            rotation(piramids, number, -angle, Axises::Z);
            drowTask(piramids, l);
            break;
        case -13: //e - вращение по оси z
            rotation(piramids, number, angle, Axises::Z);
            drowTask(piramids, l);
            break;
        case 72: //Up - вращение по оси x     
            rotation(piramids, number, -angle, Axises::X);
            drowTask(piramids, l);
            break;
        case 80: //Down - вращение по оси x  
            rotation(piramids, number, angle, Axises::X);
            drowTask(piramids, l);
            break;
        case 75: //Left - вращение по оси y  
            rotation(piramids, number, angle, Axises::Y);
            drowTask(piramids, l);
            break;
        case 77: //Right - вращение по оси y
            rotation(piramids, number, -angle, Axises::Y);
            drowTask(piramids, l);
            break;
        case 27:
            isExit = true;
            break;
        }
    }
    //закрытие графического окна
    closegraph();
}
