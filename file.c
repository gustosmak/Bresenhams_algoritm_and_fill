#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

typedef struct{
    int x, y;
}point;

void drow_segment(int **m, point *start, point *end);
void DDA(int **m, point *start, point *end);
void drow_geometric(int **m, point* vertices, int n);
int flood_fill_4(int **m, int x, int y);
int flood_fill_8(int **m, int x, int y);
void print(int **m);
int printPNG(const char *filename, int **m, int scale);
int scanline(int **m);
int test(int **m);


int main(){
    int **m;
    if(!(m = (int**)malloc(21*sizeof(int*)))){
        printf("\nmemory allocation failed");
        return 1;
    }
    int i, j;
    for (i=0; i<21; i++){
        if (!(m[i]=(int*)calloc(41, sizeof(int)))){
            printf("memory allocation failed");
            return 1;
        }
    }
    int count_choice = -1;
    while(count_choice!=0){
        printf("\n ==general menu== \n if you want:\n drow segmet with Bresenham: enter 1\n drow segment with DDA: enter 2\n drow geometric figure: enter 3\n flood fill(4): enter 4\n flood fill(8): enter 5\n scanline: enter 6\n test: enter 7\n clean: enter 8\n print PNG: enter 9\n exit: enter 0\n");
        scanf("%d", &count_choice);
        switch (count_choice)
        {
        case 1:{
            point start, end;
            start.x=-1; start.y=-1; end.x=-1; end.x=-1;
            while(start.x<1||start.x>40||start.y<1||start.y>20){
                printf("\nenter start x and start y:");
                scanf("%d %d", &start.x, &start.y);
                if (start.x<1||start.x>40){
                    printf("x must be in [1;40]");
                }
                if (start.y<1||start.y>20){
                    printf("y must be in [1;20]");
                }
            }
            while(end.x<1||end.x>40||end.y<1||end.y>20){
                printf("\nenter end x and end y:");
                scanf("%d %d", &end.x, &end.y);
                if (end.x<1||end.x>40){
                    printf("x must be in [1;40]");
                }
                if (end.y<1||end.y>20){
                    printf("y must be in [1;20]");
                }
            }
            drow_segment(m, &start, &end);
            print(m);
            break;
        }
        case 2:{
            point start, end;
            start.x=-1; start.y=-1; end.x=-1; end.x=-1;
            while(start.x<1||start.x>40||start.y<1||start.y>20){
                printf("\nenter start x and start y:");
                scanf("%d %d", &start.x, &start.y);
                if (start.x<1||start.x>40){
                    printf("x must be in [1;40]");
                }
                if (start.y<1||start.y>20){
                    printf("y must be in [1;20]");
                }
            }
            while(end.x<1||end.x>40||end.y<1||end.y>20){
                printf("\nenter end x and end y:");
                scanf("%d %d", &end.x, &end.y);
                if (end.x<1||end.x>40){
                    printf("x must be in [1;40]");
                }
                if (end.y<1||end.y>20){
                    printf("y must be in [1;20]");
                }
            }
            DDA(m, &start, &end);
            print(m);
            break;
        }
        case 3:{
            int n=1;
            while(n<3){
                printf("\nenter the number of vertices:");
                scanf("%d", &n);
                if (n<3){
                    printf("number of vertices must be >2");
                }
            }
            point *vertices;
            if(!(vertices = (point*)malloc(n*sizeof(point)))){
                printf("\nmemory allocation failed");
                return 1;
            }
            int i;
            for (i=0; i<n; i++){
                while (vertices[i].x<1||vertices[i].x>40||vertices[i].y<1||vertices[i].y>20){
                    printf("\nenter start x and start y of %d vertices:", i+1);
                    scanf("%d %d", &vertices[i].x, &vertices[i].y);
                    if (vertices[i].x<1||vertices[i].x>40){
                        printf("x must be in [1;40]");
                    }
                    if (vertices[i].y<1||vertices[i].y>20){
                        printf("y must be in [1;20]");
                    }
                }
            }
            drow_geometric(m, vertices, n);
            free(vertices);
            print(m);
            break;
        }
        case 4:{
            point point4;
            point4.x=-1; point4.y=-1;
            while(point4.x<1||point4.x>40||point4.y<1||point4.y>20){
                printf("\nenter the fill start point(x and y):");
                scanf("%d %d", &point4.x, &point4.y);
                if (point4.x<1||point4.x>40){
                    printf("x must be in [1;40]");
                }
                if (point4.y<1||point4.y>20){
                    printf("y must be in [1;20]");
                }
            }
            flood_fill_4(m, point4.x, point4.y);
            print(m);
            break;
        }
        case 5:{
            point point8;
            point8.x=-1; point8.y=-1;
            while(point8.x<1||point8.x>40||point8.y<1||point8.y>20){
                printf("\nenter the fill start point(x and y):");
                scanf("%d %d", &point8.x, &point8.y);
                if (point8.x<1||point8.x>40){
                    printf("x must be in [1;40]");
                }
                if (point8.y<1||point8.y>20){
                    printf("y must be in [1;20]");
                }
            }
            flood_fill_8(m, point8.x, point8.y);
            print(m);
            break;
        }
        case 6:{
            scanline(m);
            print(m);
            break;
        }
        case 7:
            test(m);
            print(m);
            break;
        case 8:
            for(i=1; i<41; i++){
                for (j=1; j<21; j++)
                    m[j][i]=0;
            }
            break;
        case 9: {
            char fname[256];
            printf("Enter output PNG file name: ");
            scanf("%255s", fname);
            int scale = 10;
            if (printPNG(fname, m, scale) == 0)
                printf("Saved to %s\n", fname);
            break;
        }
        default:
            break;
        };
    }
    for (i=0; i<21; i++){
        free(m[i]);
    }
    free(m);
    return 0;
}

void print(int **m){
    int i, j;
    for(i=0; i<21; i++){
        for(j=0; j<=40; j++){
            if (j==0){
                printf("%2d", i);
                continue;}
            if (i==0){
                printf("%2d", j);
                continue;}
            if (m[i][j]==0){
                printf(" |");
                continue;}
            if (m[i][j]==1){
                printf("**");
                continue;}
            else
                printf("  ");
        }
        printf("\n");
    }
}

int error(int dx, int dy, int Di_1){
    if (Di_1<0)
        return Di_1+2*dy;
    else
        return Di_1+2*dy-2*dx;
}

void swap(int *a, int *b){
    int t=*a;
    *a=*b;
    *b=t;
}

void drow_segment(int **m, point *start, point *end) {
    int Di, i, count_x, count_y, k=0;

    int dx = abs(start->x - end->x);
    int dy = abs(start->y - end->y);

    int startX = start->x+1;
    int startY = start->y;
    int endX = end->x+1;
    int endY = end->y;

    if (dx >= dy) {
        if (startX > endX) {
            swap(&startX, &endX);
            swap(&startY, &endY);
        }

        Di = 2 * dy - dx;
        count_y = startY;

        for (i = -1; i < dx; i++) {
            m[count_y][startX + i] = 1;
            k++;
            if (Di < 0) {
                Di = error(dx, dy, Di);
            } else {
                if (startY < endY){
                    //m[count_y][startX + i+1] = 1; //для кореектной работы flood_fill_8
                    count_y++;
                    }
                else{
                    //m[count_y-1][startX + i+1] = 1; //для кореектной работы flood_fill_8
                    count_y--;
                    }
                Di = error(dx, dy, Di);
            }
        }
    } else {
        if (startY > endY) {
            swap(&startX, &endX);
            swap(&startY, &endY);
        }

        Di = 2 * dx - dy;
        count_x = startX-1;

        for (i = 0; i <= dy; i++) {
            m[startY + i][count_x] = 1;
            k++;
            if (Di < 0) {
                Di = error(dy, dx, Di);
            } else {
                if (startX < endX){
                    //m[startY + i+1][count_x] = 1; //для кореектной работы flood_fill_8
                    count_x++;
                }
                else{
                    //m[startY + i+1][count_x] = 1; //для кореектной работы flood_fill_8
                    count_x--;
                }
                Di = error(dy, dx, Di);
            }
        }
    }
    printf("calls: %d\n", k);
}

void DDA(int **m, point *start, point *end){
    int startX = start->x;
    int startY = start->y;
    int endX = end->x;
    int endY = end->y;
    int L = (abs(endX - startX) > abs(endY - startY))?(abs(endX - startX) + 1):(abs(endY - startY) + 1);

    float dx = (float)(endX - startX) / (L - 1);
    float dy = (float)(endY - startY) / (L - 1);

    int i;
    int k=0;
    float x = startX;
    float y = startY;
    for (i = 0; i < L; i++) {
        m[(int)roundf(y)][(int)roundf(x)] = 1;
        x += dx;
        y += dy;
        k++;
    }
    printf("calls: %d\n", k);
}

void drow_geometric(int **m, point* vertices, int n){
    int i;
    for (i=0; i<n-1; i++){
        drow_segment(m, &vertices[i], &vertices[i+1]);
    }
    drow_segment(m, &vertices[n-1], &vertices[0]);
}

int flood_fill_4(int **m, int x, int y){
    if (m[y][x]==1||m[y][x]==2)
        return 0;
    m[y][x]=2;
    if (y-1>0)
        flood_fill_4(m, x, y-1);
    if (y+1<21)
        flood_fill_4(m, x, y+1);
    if (x-1>=0)
        flood_fill_4(m, x-1, y);
    if (x+1<41)
        flood_fill_4(m, x+1, y);
    return 0;
}

int flood_fill_8(int **m, int x, int y){
    if (m[y][x]==1||m[y][x]==2)
        return 0;
    m[y][x]=2;
    if (y-1>0){
        flood_fill_8(m, x, y-1);
        if (x-1>=0)
            flood_fill_8(m, x-1, y-1);
        if (x+1<41)
            flood_fill_8(m, x+1, y-1);
        }
    if (y+1<21){
        flood_fill_8(m, x, y+1);
        if (x-1>=0)
            flood_fill_8(m, x-1, y+1);
        if (x+1<41)
            flood_fill_8(m, x+1, y+1);
        }
    if (x-1>=0)
        flood_fill_8(m, x-1, y);
    if (x+1<41)
        flood_fill_8(m, x+1, y);
    return 0;
}

int test(int **m){
    point *vertices;
    if(!(vertices = (point*)malloc(4*sizeof(point)))){
                printf("\nmemory allocation failed");
                return 1;
            }
    vertices[0].x=8; vertices[0].y=3;
    vertices[1].x=8; vertices[1].y=10;
    vertices[2].x=29; vertices[2].y=18;
    vertices[3].x=24; vertices[3].y=3;
    drow_geometric(m, vertices, 4);
    flood_fill_8(m, 19, 7);
    return 0;
}

int printPNG(const char *filename, int **m, int scale) {
    const int img_w = 40 * scale;
    const int img_h = 20 * scale;

    // Выделяем буфер для пикселей: 3 канала (RGB) на пиксель
    unsigned char *pixels;
    if (!(pixels = (unsigned char*)malloc((size_t)img_w * img_h * 3))) {
        printf("memory allocation failed\n");
        return 1;
    }

    // Цвета для значений: 0 — пусто, 1 — стена, 2 — заливка
    const unsigned char colors[3][3] = {
        {255, 255, 255}, // 0: белый
        {0,   0,   0  }, // 1: чёрный
        {255, 0,   0  }  // 2: красный
    };
    int y, x;
    for (y = 0; y < 20; y++) {
        for (x = 0; x < 40; x++) {
            int val = m[y][x];
            unsigned char r = colors[val][0];
            unsigned char g = colors[val][1];
            unsigned char b = colors[val][2];
            for (int dy = 0; dy < scale; dy++) {
                for (int dx = 0; dx < scale; dx++) {
                    int px = x * scale + dx;
                    int py = y * scale + dy;
                    size_t idx = ((size_t)py * img_w + px) * 3;
                    pixels[idx + 0] = r;
                    pixels[idx + 1] = g;
                    pixels[idx + 2] = b;
                }
            }
        }
    }
    int ok = stbi_write_png(filename, img_w, img_h, 3, pixels, img_w * 3);
    free(pixels);

    if (!ok) {
        fprintf(stderr, "write_map_png: failed to write %s\n", filename);
        return 1;
    }
    return 0;
}


int scanline(int **m){
    int row, column;
    int leftBorder, rightBorder;
    int foundLeft, foundRight;

    for(row=1; row<=20; row++){
        foundLeft = 0;
        foundRight = 0;
        leftBorder = 0;
        rightBorder = 0;

        for(column=1; column<=40; column++){
            if (m[row][column]==1){
                leftBorder = column;
                foundLeft = 1;
                break;
            }
        }
        for(column=40; column>=1; column--){
            if (m[row][column]==1){
                rightBorder = column;
                foundRight = 1;
                break;
            }
        }

        if (!foundLeft||!foundRight)
            continue;
        if (rightBorder-leftBorder<2)
            continue;

        for(column=leftBorder+1; column<rightBorder; column++){
            if (m[row][column]==0)
                m[row][column]=2;
        }
    }
    return 0;
}