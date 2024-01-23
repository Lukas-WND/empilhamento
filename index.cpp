#include "iostream"
#include <windows.h>

using namespace std;

typedef struct Coord {
    float x, y, z, a, b, c;
} Coord;

typedef struct Box {
    float length, width, height;
    Coord position;
} Box;

typedef struct Floor {
    int floorNumber, angle;
    Box *boxes;
} Floor;

typedef struct Stack
{
    Floor *floors;
} Stack;

Coord bases[3];

void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void initBases(){
    bases[0].x = 0;
    bases[0].y = 0;
    bases[0].z = 0;
    bases[0].a = 0;
    bases[0].b = 0;
    bases[0].c = 0;

    bases[1].x = -98;
    bases[1].y = 1335;
    bases[1].z = -705.466;
    bases[1].a = -1.101;
    bases[1].b = 0.448;
    bases[1].c = 1.883;

    bases[2].x = 1232;
    bases[2].y = -428;
    bases[2].z = -960;
    bases[2].a = 0;
    bases[2].b = 0;
    bases[2].c = 90;

    bases[3].x = -1232;
    bases[3].y = 428;
    bases[3].z = -960;
    bases[3].a = 0;
    bases[3].b = 0;
    bases[3].c = -90;
}

Coord initializeBoxPosition(float length, float width, float height, int side){
    Coord vertexA, vertexB, initialPosition;

    vertexA.x = 420;
    vertexA.y = -580;
    vertexA.z = -1000;
    vertexA.a = 0;
    vertexA.b = 0;
    vertexA.c = 0;

    vertexB.x = -370;
    vertexB.y = -535;
    vertexB.z = -1000;
    vertexB.a = 0;
    vertexB.b = 0;
    vertexB.c = 0;

    if(side == 1) {

        initialPosition.x = (bases[2].y * -1) + (vertexA.y + (width/2));
        initialPosition.y = bases[2].x - (vertexA.x + (length/2));
        initialPosition.z = (bases[2].z * -1) + vertexA.z + height;
        initialPosition.c = bases[2].c;
        initialPosition.a = 0;
        initialPosition.b = 0;

    } else if(side == 2) {

        initialPosition.x = bases[3].y - (vertexB.y + (width/2));
        initialPosition.y = (bases[3].x * -1) + (vertexB.x - (length/2));
        initialPosition.z = (bases[3].z * -1) + vertexB.z + height;
        initialPosition.c = bases[3].c;
        initialPosition.a = 0;
        initialPosition.b = 0;
    }

    return initialPosition;

}

int main(){
    int maxBoxes, boxesPerFloor;
    float length, width, height;

    initBases();

    gotoxy(3, 1);
    cout << "GERADOR DE SCRIPTS PARA O ROBO";

    gotoxy(1, 3);
    cout << "Quantidade de caixas: ";
    gotoxy(1, 4);
    cout << "Caixas por andar: ";
    gotoxy(1, 5);
    cout << "Comprimento das caixa: ";
    gotoxy(1, 6);
    cout << "Largura das caixas: ";
    gotoxy(1, 7);
    cout << "Altura das caixas: ";

    gotoxy(25, 3);
    cin >> maxBoxes;
    gotoxy(25, 4);
    cin >> boxesPerFloor;
    gotoxy(25, 5);
    cin >> length;
    gotoxy(25, 6);
    cin >> width;
    gotoxy(25, 7);
    cin >> height;

    Stack stacks[2];
    Floor floorsSide1[maxBoxes/boxesPerFloor], floorsSide2[maxBoxes/boxesPerFloor];
    Box boxesSide1[maxBoxes/boxesPerFloor][boxesPerFloor], boxesSide2[maxBoxes/boxesPerFloor][boxesPerFloor];

    for(int i = 0; i < (maxBoxes/boxesPerFloor); i++){
        for(int j = 0; j < boxesPerFloor; j++){
            boxesSide1[i][j].length = length;
            boxesSide1[i][j].width = width;
            boxesSide1[i][j].height = height;
            boxesSide1[i][j].position = initializeBoxPosition(length, width, height, 1);

            boxesSide2[i][j].length = length;
            boxesSide2[i][j].width = width;
            boxesSide2[i][j].height = height;
            boxesSide2[i][j].position = initializeBoxPosition(length, width, height, 2);
        }
    }

    for(int i = 0; i < (maxBoxes/boxesPerFloor); i++){
        floorsSide1[i].floorNumber = i;
        floorsSide2[i].floorNumber = i;

        floorsSide1[i].boxes = boxesSide1[i];
        floorsSide2[i].boxes = boxesSide2[i];

        if(i % 2 == 0){
            floorsSide1[i].angle = 0;
            floorsSide2[i].angle = 0;
        } else {
            floorsSide1[i].angle = 180;
            floorsSide2[i].angle = 180;
        }

    }

    stacks[0].floors = floorsSide1;
    stacks[1].floors = floorsSide2;
}
