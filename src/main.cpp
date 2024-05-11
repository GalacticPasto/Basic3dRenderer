#include "raylib.h"
#include <iostream>
#include <vector>
#include <math.h>

static const int cubePlane = 8;
static const int cubeVertex = 3;
static const int screenWidth =  1500;
static const int screenHeight =  900;
static const int offsetX =  screenWidth/2;
static const int offsetY =  screenHeight/2;

Vector3 matMultiply(std::vector<std::vector<float>>& mat2 ,Vector3& vertices)
{
    Vector3 ans = {0,0,0}; 
    
    ans.x = vertices.x * mat2[0][0] + vertices.y * mat2[0][1] + vertices.z * mat2[0][2];
    ans.y = vertices.x * mat2[1][0] + vertices.y * mat2[1][1] + vertices.z * mat2[1][2];
    ans.z = vertices.x * mat2[2][0] + vertices.y * mat2[2][1] + vertices.z * mat2[2][2];

    return ans;
}

void scaleMat(Vector3& mat, float scale)
{
    mat.x = mat.x * scale + offsetX;
    mat.y = mat.y * scale + offsetY;
    //mat.z = mat.z * scale;
}

void printMat(std::vector<std::vector<float>>& mat2, int row)
{
    for(int i = 0 ; i < row; i++)
    {
        for(int j = 0 ; j < cubeVertex ; j++)
        {
            printf("%f ",mat2[i][j]);
        }
        printf("\n ");
    }
    printf("\n ");

}




int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    float angle = 0.01;

    InitWindow(screenWidth, screenHeight, "Cube");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second



    //printMat(rotationMatZ,3);


    std::vector<Vector3>cube = 
    {
        {-0.5,-0.5,-0.5},
        {0.5,-0.5,-0.5},
        {0.5,0.5,-0.5},
        {-0.5,0.5,-0.5},
        {-0.5,-0.5,0.5},
        {0.5,-0.5,0.5},
        {0.5,0.5,0.5},
        {-0.5,0.5,0.5}
    };
    

    //
    //printMat(cube);

    int scale = 200;


    //std::vector<Vector3> cube = {
    //    {0,0,0},
    //    {1,0,0},
    //    {1,0,1},
    //    {0,0,1},
    //    {0,1,0},
    //    {1,1,0},
    //    {1,1,1},
    //    {0,1,1}
    //};

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        std::vector<Vector3> projected(cubePlane);
        std::vector<std::vector<float>> rotationMatZ = 
        {
            {(float)cos(angle),-(float)sin(angle),0},
            {(float)sin(angle),(float)cos(angle),0},
            {0,0,1}
        };

        std::vector<std::vector<float>> rotationMatX = 
        {
            {1,0,0},
            {0,(float)cos(angle),-(float)sin(angle)},
            {0,(float)sin(angle),(float)cos(angle)}
        };

        std::vector<std::vector<float>> rotationMatY = 
        {
            {(float)cos(angle),0,(float)sin(angle)},
            {0,1,0},
            {-(float)sin(angle),0,(float)cos(angle)}
        };

        //printf("rotationMatZ\n");
        //printMat(rotationMatZ,cubeVertex); 
        //printf("rotationMatX\n");
        //printMat(rotationMatX,cubeVertex); 
        //printf("rotationMatY\n");
        //printMat(rotationMatY,cubeVertex); 

        //matMultiply(scaled,rotationMatY,cubeVertex);    
        //matMultiply(scaled,rotationMatX,cubeVertex);    
        //matMultiply(scaled,projectionMat2d,cubeVertex);

        BeginDrawing();
        ClearBackground(BLACK);

        for(int i = 0 ; i < cube.size() ; i++)
        {
            Vector3 rotated = cube[i];
            //rotated = matMultiply(rotationMatY,rotated);    
            //rotated = matMultiply(rotationMatX,rotated);    
            //rotated = matMultiply(rotationMatZ,rotated);    

            float distance = 2;
            printf("%f\n",rotated.z);
            float z = 1 / ( distance - rotated.z);

            std::vector<std::vector<float>>projectionMat2d = 
            {
                {z,0,0},
                {0,z,0},
                {0,0,1},
            };

            rotated = matMultiply(projectionMat2d,rotated);
            scaleMat(rotated,scale);
            projected[i] = rotated;
        }

        for(int i = 0 ; i < cube.size() ; i++)
        {
            DrawCircle(projected[i].x,projected[i].y,5, WHITE);
        }

        DrawLine(projected[0].x,projected[0].y,projected[1].x,projected[1].y,WHITE); 
        DrawLine(projected[1].x,projected[1].y,projected[2].x,projected[2].y,WHITE); 
        DrawLine(projected[2].x,projected[2].y,projected[3].x,projected[3].y,WHITE); 
        DrawLine(projected[3].x,projected[3].y,projected[0].x,projected[0].y,WHITE); 

        DrawLine(projected[4].x,projected[4].y,projected[5].x,projected[5].y,WHITE); 
        DrawLine(projected[5].x,projected[5].y,projected[6].x,projected[6].y,WHITE); 
        DrawLine(projected[6].x,projected[6].y,projected[7].x,projected[7].y,WHITE); 
        DrawLine(projected[7].x,projected[7].y,projected[4].x,projected[4].y,WHITE); 

        DrawLine(projected[0].x,projected[0].y,projected[4].x,projected[4].y,WHITE); 
        DrawLine(projected[1].x,projected[1].y,projected[5].x,projected[5].y,WHITE); 
        DrawLine(projected[2].x,projected[2].y,projected[6].x,projected[6].y,WHITE); 
        DrawLine(projected[3].x,projected[3].y,projected[7].x,projected[7].y,WHITE); 



        angle += 0.01;
        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context
                          //--------------------------------------------------------------------------------------

    return 0;
}



