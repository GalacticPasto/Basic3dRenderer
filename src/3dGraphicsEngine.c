#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SCREENWIDTH 1200
#define SCREENHEIGHT 720 

void rotateMat(float mat[3][3],float res[4],float vec[4]);
void perspectiveApply(float mat[4][4],float res[4],float vec[4]);

int main(void) 
{

    InitWindow(SCREENWIDTH,SCREENHEIGHT,"3dGraphicsEngine");

    //world space

    FILE *fptr; 

    //int success = fopen_s(&fptr,"D:\\Code\\3dGraphicsEngine\\Objs\\Cube.obj","r");
    //int success = fopen_s(&fptr,"D:\\Code\\3dGraphicsEngine\\Objs\\Sphere.obj","r");
    //int success = fopen_s(&fptr,"D:\\Code\\3dGraphicsEngine\\Objs\\Cylinder.obj","r");
    //int success = fopen_s(&fptr,"D:\\Code\\3dGraphicsEngine\\Objs\\Cone.obj","r");
    //int success = fopen_s(&fptr,"D:\\Code\\3dGraphicsEngine\\Objs\\Torus.obj","r");
    //int success = fopen_s(&fptr,"D:\\Code\\3dGraphicsEngine\\Objs\\Teapot.obj","r");
    //int success = fopen_s(&fptr,"D:\\Code\\3dGraphicsEngine\\Objs\\Teapot.obj","r");
    //int success = fopen_s(&fptr,"D:\\Code\\3dGraphicsEngine\\Objs\\Mountains.obj","r");
    int success = fopen_s(&fptr,"D:\\Code\\3dGraphicsEngine\\Objs\\VideoShip.obj","r");

    char buffer[8192] = {};
    float meshPoints[8192][4] = {};
    int meshVertexData[8192][3] = {};

    if(success == 0)
    {
        int pointColInd = 0;
        int vertexColInd = 0;

        while(fgets(buffer,sizeof(buffer),fptr))
        {
            if(buffer[0] == 'v' && buffer[1] == ' ')
            {
                int pointRowInd = 0;
                char data[64] = {};
                char* nextToken = NULL;        
                char* token = strtok_s(buffer," ",&nextToken);        

                token = strtok_s(NULL," ",&nextToken);        

                while(token != NULL)
                {
                    for(int i = 0 ; i < sizeof(token) ; i++)
                    {
                        if(token[i] == ' ')break;
                        data[i] = token[i];
                    } 
                    float num = atof(data);
                    meshPoints[pointColInd][pointRowInd++] = num;
                    token = strtok_s(NULL," ",&nextToken);
                }
                pointColInd++;
            } 
            else if(buffer[0] == 'f')
            {
                int vertexRowInd= 0;

                char* nextToken = NULL;        
                char* token = strtok_s(buffer," ",&nextToken);        

                token = strtok_s(NULL," ",&nextToken);        

                char data[64] = {}; 
                while(token != NULL)
                {
                    for(int i = 0 ; i < sizeof(token) ; i++)
                    {
                        if(token[i] == ' ')break;
                        data[i] = token[i];
                    } 
                    int num = atoi(data);
                    meshVertexData[vertexColInd][vertexRowInd++] = num - 1;
                    token = strtok_s(NULL," ",&nextToken);
                }
                vertexColInd++;
            }
        }
        fclose(fptr);
    }
    else
    {
        printf("cant read obj file!! :( ");
    }



    float zNear = 0.1; 
    float zFar= 1000.0; 
    float zDiff = zFar - zNear;
    float aspectRatio = (float)SCREENWIDTH/(float)SCREENHEIGHT;  
    float fovX = 90;
    float fovY = 60;
    float fovRadX = 1.0 / tanf(fovX * 0.5/ 180.0f * PI);
    float fovRadY = 1.0 / tanf(fovY * 0.5/ 180.0f * PI);


    SetTargetFPS(60);

    float projectionMat[4][4] = 
    {
        {aspectRatio * fovRadX,0,0,0},
        {0,fovRadY,0,0},
        {0,zFar/zDiff, -((zFar * zNear)/zDiff),0},
        {0,0,1,0}
    };


    float angle = 1;
    while(!WindowShouldClose())
    {

        float rotationMatX[3][3] = 
        {
            {1,0,0},
            {0,(float)cosf(angle * DEG2RAD),-(float)sinf(angle*DEG2RAD)},
            {0,(float)sinf(angle * DEG2RAD),(float)cosf(angle*DEG2RAD)},
        };

        float rotationMatY[3][3] = 
        {
            {(float)cosf(angle * DEG2RAD),0,(float)sinf(angle*DEG2RAD)},
            {0,1,0},
            {-(float)sinf(angle * DEG2RAD),0,(float)cosf(angle*DEG2RAD)}
        };

        float rotationMatZ[3][3] = 
        {
            {(float)cosf(angle * DEG2RAD),-(float)sinf(angle*DEG2RAD),0},
            {(float)sinf(angle * DEG2RAD),(float)cosf(angle*DEG2RAD),0},
            {0,0,1},
        };

        float rotatedX[8192][4] = {};

        for(int i = 0 ; i < 8192 ; i++)
        {
            rotateMat(rotationMatY,rotatedX[i],meshPoints[i]);
        }

        float rotatedXY[8192][4] = {};
        for(int i = 0 ; i < 8192 ; i++)
        {
            rotateMat(rotationMatY,rotatedXY[i],rotatedX[i]);
        }

        float rotatedXYZ[8192][4] = {};
        for(int i = 0 ; i < 8192 ; i++)
        {
            rotateMat(rotationMatZ,rotatedXYZ[i],rotatedXY[i]);
        }


        float translated[8192][4] = {};
        for(int i = 0 ; i < 8192 ; i++)
        {
            for(int j = 0 ; j < 3 ; j++)
            {
                translated[i][j] = -1 * rotatedXYZ[i][j];
                //translated[i][j] = -1 * rotatedX[i][j];
                //translated[i][j] = -1 * meshPoints[i][j];
            }
            //camera depth 
            translated[i][2] += 8;
        }


        float projected[8192][4] = {};
        for(int i = 0 ; i < 8192 ; i++)
        {
            perspectiveApply(projectionMat,projected[i],translated[i]); 

            projected[i][0] *= 100;
            projected[i][1] *= 100;

            projected[i][0] += 0.5 * (float)SCREENWIDTH;
            projected[i][1] += 0.5 * (float)SCREENHEIGHT;

        }


        BeginDrawing();
        DrawFPS(0,1); 
        ClearBackground(BLACK);

        for(int i = 0 ; i < 8192 ; i++)
        {
            Vector2 V1 =  {projected[meshVertexData[i][0]][0], projected[meshVertexData[i][0]][1]};
            Vector2 V2 =  {projected[meshVertexData[i][1]][0], projected[meshVertexData[i][1]][1]};
            Vector2 V3 =  {projected[meshVertexData[i][2]][0], projected[meshVertexData[i][2]][1]};

            DrawTriangleLines(V1,V2,V3,RED);
        }

        angle += 1;



        EndDrawing();
    }
}

void rotateMat(float mat[3][3],float res[4],float vec[4])
{
    res[0] = vec[0] * mat[0][0] + vec[1] * mat[0][1] + vec[2] * mat[0][2];
    res[1] = vec[0] * mat[1][0] + vec[1] * mat[1][1] + vec[2] * mat[1][2];
    res[2] = vec[0] * mat[2][0] + vec[1] * mat[2][1] + vec[2] * mat[2][2];    
}


void perspectiveApply(float mat[4][4],float res[4],float vec[4])
{
    res[0] = vec[0] * mat[0][0] + vec[1] * mat[0][1] + vec[2] * mat[0][2] + vec[3];
    res[1] = vec[0] * mat[1][0] + vec[1] * mat[1][1] + vec[2] * mat[1][2] + vec[3];
    res[2] = vec[0] * mat[2][0] + vec[1] * mat[2][1] + vec[2] * mat[2][2] + vec[3];    

    float w = vec[0] * mat[3][0] + vec[1] * mat[3][1] + vec[2] * mat[3][2] + mat[3][3];

    if(w != 0)
    {
        res[0] /= w;
        res[1] /= w;
        res[2] /= w;
    }

}

