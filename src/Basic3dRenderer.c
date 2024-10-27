#include "meshData.h"
#include <math.h>
#include <raylib.h>

#define SCREENWIDTH 1200
#define SCREENHEIGHT 720

void rotateMat(float mat[3][3], float res[4], float vec[4]);
void perspectiveApply(float mat[4][4], float res[4], float vec[4]);

int main(void)
{

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Basic3dRenderer");

    bool showWireFrame = 0;

    float zNear       = 0.1;
    float zFar        = 1000.0;
    float zDiff       = zFar - zNear;
    float aspectRatio = (float)SCREENWIDTH / (float)SCREENHEIGHT;
    float fovX        = 90;
    float fovY        = 60;
    float fovRadX     = 1.0 / tanf(fovX * 0.5 / 180.0f * PI);
    float fovRadY     = 1.0 / tanf(fovY * 0.5 / 180.0f * PI);

    float cameraDepth = 3;
    float scale       = 100;

    SetTargetFPS(240);

    float projectionMat[4][4] = {
        {aspectRatio * fovRadX,            0,                         0, 0},
        {                    0,      fovRadY,                         0, 0},
        {                    0, zFar / zDiff, -((zFar * zNear) / zDiff), 0},
        {                    0,            0,                         1, 0}
    };

    float angle = 1;
    while (!WindowShouldClose())
    {
        float rotationMatX[3][3] = {
            {1,                            0,                             0},
            {0, (float)cosf(angle * DEG2RAD), -(float)sinf(angle * DEG2RAD)},
            {0, (float)sinf(angle * DEG2RAD),  (float)cosf(angle * DEG2RAD)},
        };

        float rotationMatY[3][3] = {
            { (float)cosf(angle * DEG2RAD), 0, (float)sinf(angle * DEG2RAD)},
            {                            0, 1,                            0},
            {-(float)sinf(angle * DEG2RAD), 0, (float)cosf(angle * DEG2RAD)}
        };

        float rotationMatZ[3][3] = {
            {(float)cosf(angle * DEG2RAD), -(float)sinf(angle * DEG2RAD), 0},
            {(float)sinf(angle * DEG2RAD),  (float)cosf(angle * DEG2RAD), 0},
            {                           0,                             0, 1},
        };

        float rotatedX[POINTCOLIND][4] = {};

        for (int i = 0; i < POINTCOLIND; i++)
        {
            rotateMat(rotationMatX, rotatedX[i], meshPoints[i]);
        }

        float rotatedXY[POINTCOLIND][4] = {};
        for (int i = 0; i < POINTCOLIND; i++)
        {
            rotateMat(rotationMatY, rotatedXY[i], rotatedX[i]);
        }

        float rotatedXYZ[POINTCOLIND][4] = {};
        for (int i = 0; i < POINTCOLIND; i++)
        {
            rotateMat(rotationMatZ, rotatedXYZ[i], rotatedXY[i]);
        }
        if (IsKeyPressed(KEY_I))
        {
            showWireFrame = 1;
        }
        else if (IsKeyPressed(KEY_O))
        {
            showWireFrame = 0;
        }

        if (IsKeyPressed(KEY_W))
        {
            scale += 100;
        }
        if (IsKeyPressed(KEY_S))
        {
            if (scale - 100 != 0)
            {
                scale -= 100;
            }
        }
        if (IsKeyPressed(KEY_D))
        {
            cameraDepth -= 1;
        }
        if (IsKeyPressed(KEY_A))
        {
            cameraDepth += 1;
        }

        float translated[POINTCOLIND][4] = {};
        for (int i = 0; i < POINTCOLIND; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                translated[i][j] = -1 * rotatedXYZ[i][j];
            }
            // camera depth
            translated[i][2] += cameraDepth;
        }

        float normals[VERTEXCOLIND][4] = {};

        for (int i = 0; i < VERTEXCOLIND; i++)
        {
            float aX = translated[meshVertexPoints[i][1] - 1][0] - translated[meshVertexPoints[i][0] - 1][0];
            float aY = translated[meshVertexPoints[i][1] - 1][1] - translated[meshVertexPoints[i][0] - 1][1];
            float aZ = translated[meshVertexPoints[i][1] - 1][2] - translated[meshVertexPoints[i][0] - 1][2];

            float bX = translated[meshVertexPoints[i][2] - 1][0] - translated[meshVertexPoints[i][0] - 1][0];
            float bY = translated[meshVertexPoints[i][2] - 1][1] - translated[meshVertexPoints[i][0] - 1][1];
            float bZ = translated[meshVertexPoints[i][2] - 1][2] - translated[meshVertexPoints[i][0] - 1][2];

            normals[i][0] = aY * bZ - aZ * bY;
            normals[i][1] = aZ * bX - aX * bZ;
            normals[i][2] = aX * bY - aY * bX;

            float normalMag = sqrtf(normals[i][0] * normals[i][0] + normals[i][1] * normals[i][1] + normals[i][2] * normals[i][2]);

            normals[i][0] /= normalMag;
            normals[i][1] /= normalMag;
            normals[i][2] /= normalMag;

            float dotProduct = normals[i][0] * translated[meshVertexPoints[i][0] - 1][0] + normals[i][1] * translated[meshVertexPoints[i][0] - 1][1] +
                               normals[i][2] * translated[meshVertexPoints[i][0] - 1][2];

            normals[i][3] = dotProduct;
        }

        float projected[POINTCOLIND][4] = {};
        for (int i = 0; i < POINTCOLIND; i++)
        {
            perspectiveApply(projectionMat, projected[i], translated[i]);

            projected[i][0] *= 1 + scale;
            projected[i][1] *= 2 + scale;

            projected[i][0] += 0.5 * (float)SCREENWIDTH;
            projected[i][1] += 0.5 * (float)SCREENHEIGHT;
        }

        BeginDrawing();
        DrawFPS(0, 1);
        ClearBackground(BLACK);

        for (int i = 0; i < VERTEXCOLIND; i++)
        {
            if (normals[i][3] > 0.0f)
            {
                float lightDirection[3] = {0.0f, 0.0f, 1.0f};
                float lightDirectionMag =
                    sqrtf(lightDirection[0] * lightDirection[0] + lightDirection[1] * lightDirection[1] + lightDirection[2] * lightDirection[2]);

                for (int j = 0; j < 3; j++)
                {
                    lightDirection[j] /= lightDirectionMag;
                }

                float lightDotProduct = 0;
                for (int j = 0; j < 3; j++)
                {
                    lightDotProduct += lightDirection[j] * normals[i][j];
                }

                Color color = {
                    .r = lightDotProduct * 225,
                    .g = lightDotProduct * 225,
                    .b = lightDotProduct * 225,
                    .a = 225,
                };

                Vector2 V1 = {projected[meshVertexPoints[i][0] - 1][0], projected[meshVertexPoints[i][0] - 1][1]};
                Vector2 V2 = {projected[meshVertexPoints[i][1] - 1][0], projected[meshVertexPoints[i][1] - 1][1]};
                Vector2 V3 = {projected[meshVertexPoints[i][2] - 1][0], projected[meshVertexPoints[i][2] - 1][1]};

                DrawTriangle(V1, V3, V2, color);
                if (showWireFrame)
                {
                    DrawTriangleLines(V1, V3, V2, BLACK);
                }
            }
        }

        if (angle > 360)
        {
            angle = 0;
        }
        angle += 0.1;
        EndDrawing();
    }
}

void rotateMat(float mat[3][3], float res[4], float vec[4])
{
    res[0] = vec[0] * mat[0][0] + vec[1] * mat[0][1] + vec[2] * mat[0][2];
    res[1] = vec[0] * mat[1][0] + vec[1] * mat[1][1] + vec[2] * mat[1][2];
    res[2] = vec[0] * mat[2][0] + vec[1] * mat[2][1] + vec[2] * mat[2][2];
}

void perspectiveApply(float mat[4][4], float res[4], float vec[4])
{
    res[0] = vec[0] * mat[0][0] + vec[1] * mat[0][1] + vec[2] * mat[0][2] + vec[3];
    res[1] = vec[0] * mat[1][0] + vec[1] * mat[1][1] + vec[2] * mat[1][2] + vec[3];
    res[2] = vec[0] * mat[2][0] + vec[1] * mat[2][1] + vec[2] * mat[2][2] + vec[3];

    float w = vec[0] * mat[3][0] + vec[1] * mat[3][1] + vec[2] * mat[3][2] + mat[3][3];

    if (w != 0)
    {
        res[0] /= w;
        res[1] /= w;
        res[2] /= w;
    }
}
