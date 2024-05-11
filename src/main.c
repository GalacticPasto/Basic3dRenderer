#include "raylib.h"
#include <stdio.h>
#include <math.h>

#define cubePlane 8
#define cubeVertex 3

#define screenWidth  1500
#define screenHeight  900
#define fps  60
#define tickRate 5
#define offsetX  screenWidth/2
#define offsetY  screenHeight/2
#define distance 2 

void matMultiply(float mat1[][cubeVertex], float mat2[][cubeVertex],int mat2Row)
{
    float copy[cubePlane][cubeVertex];

    memcpy(copy,mat1,sizeof(float)*cubePlane*cubeVertex);

    for(int i = 0 ; i < mat2Row ; i++)
    {
        for(int j = 0 ; j < cubePlane ; j++)
        {
            float num = 0;
            for(int k = 0 ; k < cubeVertex ; k++)
            {
                num += mat2[i][k] * copy[j][k];
            }
            mat1[j][i] = num;
        } 
    }

}
void applyProjection(float mat1[][cubeVertex])
{
    for(int i = 0 ; i < cubePlane ; i++)
    {
        mat1[i][0] /= distance - mat1[i][2];
        mat1[i][1] /= distance - mat1[i][2];
    }
}

void scaleMat(float mat[][cubeVertex] , int rows, float scale)
{
    for(int i = 0 ; i < rows ; i++)
    {
        for(int j = 0 ; j < cubeVertex ; j++)
        {
            mat[i][j] *= scale;
            if(j == 0)
            {
                mat[i][j] += offsetX;
            }
            else if(j == 1)
            {
                mat[i][j] += offsetY;
            }
        }
    } 
}

void printMat(float mat[][cubeVertex],int row)
{
    for(int i = 0 ; i < row; i++)
    {
        for(int j = 0 ; j < cubeVertex ; j++)
        {
            printf("%f ",mat[i][j]);
        }
        printf("\n ");
    }
    printf("\n ");

}




int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    double angle = 0.05;

    InitWindow(screenWidth, screenHeight, "Cube");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second



    //printMat(rotationMatZ,3);

    //float cube[cubePlane][cubeVertex] = 
    //{
    //    {0,0,0},
    //    {1,0,0},
    //    {1,0,1},
    //    {0,0,1},
    //    {0,1,0},
    //    {1,1,0},
    //    {1,1,1},
    //    {0,1,1},
    //};


    float cube[cubePlane][cubeVertex] = 
    {
        {-1,-1,-1},
        {1,-1,-1},
        {1,1,-1},
        {-1,1,-1},
        {-1,-1,1},
        {1,-1,1},
        {1,1,1},
        {-1,1,1}
    };
    

    //
    //printMat(cube);

    int scale = 100;


    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float rotationMatZ[cubeVertex][cubeVertex] = 
        {
            {cos(angle),sin(angle) * -1,0},
            {sin(angle),cos(angle),0},
            {0,0,1}
        };

        float rotationMatX[cubeVertex][cubeVertex] = 
        {
            {1,0,0},
            {0,cos(angle),sin(angle) * -1},
            {0,sin(angle),cos(angle)}
        };
        float rotationMatY[cubeVertex][cubeVertex] = 
        {
            {cos(angle),0,sin(angle)},
            {0,1,0},
            {-sin(angle),0,cos(angle)}
        };

        //printMat(scaled,cubePlane); 
        
        //matMultiply(scaled,rotationMatY,cubeVertex);    
        //matMultiply(scaled,rotationMatX,cubeVertex);    
        //matMultiply(scaled,projectionMat2d,cubeVertex);

        matMultiply(cube,rotationMatY,cubeVertex);    
        matMultiply(cube,rotationMatX,cubeVertex);    
        matMultiply(cube,rotationMatZ,cubeVertex);    

        float scaled[cubePlane][cubeVertex];
        memcpy(scaled,cube,sizeof(float)*cubePlane*cubeVertex);
        applyProjection(scaled);
        scaleMat(scaled,cubePlane,100);

        BeginDrawing();

        ClearBackground(BLACK);

        for(int i = 0 ; i < cubePlane ; i++)
        {
            float x = scaled[i][0];
            float y = scaled[i][1];

            DrawCircle(x,y,5,WHITE);
        }


        //for(int i = 0 ; i < cubePlane / 2; i++)
        //{
        //    DrawLine(scaled[i][0],scaled[i][1],scaled[(i+1) % 4][0],scaled[(i+1) % 4][1],WHITE);
        //    DrawLine(scaled[i][0],scaled[i][1],scaled[i+4][0],scaled[i+4][1],WHITE);
        //    DrawLine(scaled[i+4][0],scaled[i+4][1],scaled[((i+1) % 4) + 4][0],scaled[((i+4) % 4) + 4][1],WHITE);
        //}

        DrawLine(scaled[0][0],scaled[0][1],scaled[1][0],scaled[1][1],WHITE); 
        DrawLine(scaled[1][0],scaled[1][1],scaled[2][0],scaled[2][1],WHITE); 
        DrawLine(scaled[2][0],scaled[2][1],scaled[3][0],scaled[3][1],WHITE); 
        DrawLine(scaled[3][0],scaled[3][1],scaled[0][0],scaled[0][1],WHITE); 

        DrawLine(scaled[4][0],scaled[4][1],scaled[5][0],scaled[5][1],WHITE); 
        DrawLine(scaled[5][0],scaled[5][1],scaled[6][0],scaled[6][1],WHITE); 
        DrawLine(scaled[6][0],scaled[6][1],scaled[7][0],scaled[7][1],WHITE); 
        DrawLine(scaled[7][0],scaled[7][1],scaled[4][0],scaled[4][1],WHITE); 

        DrawLine(scaled[0][0],scaled[0][1],scaled[4][0],scaled[4][1],WHITE); 
        DrawLine(scaled[1][0],scaled[1][1],scaled[5][0],scaled[5][1],WHITE); 
        DrawLine(scaled[2][0],scaled[2][1],scaled[6][0],scaled[6][1],WHITE); 
        DrawLine(scaled[3][0],scaled[3][1],scaled[7][0],scaled[7][1],WHITE); 
        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context
                          //--------------------------------------------------------------------------------------

    return 0;
}



