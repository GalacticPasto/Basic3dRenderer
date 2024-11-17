
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WINDOWS
//#undef WINDOWS
//#define LINUX

int main()
{

    FILE *readPtr;
    FILE *writePtr;

#ifdef WINDOWS
    // readPtr = fopen("Objs/Cone.obj", "r");
    // readPtr = fopen("Objs/Cube.obj", "r");
    // readPtr = fopen("Objs/Cylinder.obj", "r");
    //  readPtr = fopen("Objs/Mountains.obj","r");
    //  readPtr = fopen("Objs/Sphere.obj", "r");
    // readPtr = fopen("Objs/Spoon.obj", "r");
    // readPtr = fopen("Objs/Teacup.obj", "r");
    // readPtr = fopen("Objs/Teapot.obj", "r");
    // readPtr = fopen("Objs/Torus.obj", "r");
    // readPtr = fopen("Objs/VideoShip.obj", "r");
    // writePtr = fopen("src/meshData.h", "w");

    fopen_s(&readPtr, "..\\Objs\\VideoShip.obj", "r");
    fopen_s(&writePtr, "..\\src\\meshData.h", "w");

    char buffer[512] = {};
    if (readPtr != NULL)
    {
        int pointColInd = 0;
        int vertexDataInd = 0;

        while (fgets(buffer, sizeof(buffer), readPtr))
        {
            if (buffer[0] == 'o')
            {
                char *token;
                char *nextToken;
                strtok_s(buffer, " ", &nextToken);
                token = strtok_s(NULL, " ", &nextToken);
                fprintf(writePtr, "//%s\n", token);
            }
            else if (buffer[0] == 'v' && buffer[1] == ' ')
            {
                pointColInd++;
            }
            else if (buffer[0] == 'f')
            {
                vertexDataInd++;
            }
        }

        fprintf(writePtr, "#define POINTCOLIND %d\n", pointColInd);
        fprintf(writePtr, "#define VERTEXCOLIND %d\n", vertexDataInd);
        fprintf(writePtr, "float meshPoints[POINTCOLIND][4] = { \n");

        rewind(readPtr);

        while (fgets(buffer, sizeof(buffer), readPtr))
        {
            if (buffer[0] == 'v' && buffer[1] == ' ')
            {
                char *token;
                char *nextToken;
                strtok_s(buffer, " ", &nextToken);
                token = strtok_s(NULL, " ", &nextToken);
                fprintf(writePtr, "{");
                while (token != NULL)
                {
                    for (int i = 0; i < sizeof(token); i++)
                    {
                        fprintf(writePtr, "%c", token[i]);
                        if (i == sizeof(token) - 1)
                        {
                            fprintf(writePtr, ",");
                        }
                    }
                    token = strtok_s(NULL, " ", &nextToken);
                    if (token == NULL)
                    {
                        fprintf(writePtr, "\n");
                    }
                }
                fprintf(writePtr, "},");
            }
        }
        fprintf(writePtr, "}; \n");
        rewind(readPtr);
        fprintf(writePtr, "int meshVertexPoints[VERTEXCOLIND][4] = { \n");

        while (fgets(buffer, sizeof(buffer), readPtr))
        {
            if (buffer[0] == 'f')
            {
                char *token;
                char *nextToken;
                strtok_s(buffer, " ", &nextToken);
                token = strtok_s(NULL, " ", &nextToken);

                fprintf(writePtr, "{");
                while (token != NULL)
                {
                    for (int i = 0; i < sizeof(token); i++)
                    {
                        if (token[i] == '/')
                        {
                            fprintf(writePtr, ",");
                            break;
                        }
                        fprintf(writePtr, "%c", token[i]);
                    }
                    token = strtok_s(NULL, " ", &nextToken);
                    if (token == NULL)
                    {
                        fprintf(writePtr, "\n");
                    }
                }
                fprintf(writePtr, "},");
            }
        }

        fprintf(writePtr, "};\n");

        fclose(readPtr);
        fclose(writePtr);
    }
    else
    {
        printf("Cant find obj file :( ");
    }
#endif

#ifdef LINUX
    // readPtr = fopen("Objs/Cone.obj", "r");
    // readPtr = fopen("Objs/Cube.obj", "r");
    // readPtr = fopen("Objs/Cylinder.obj", "r");
    //   readPtr = fopen("Objs/Mountains.obj","r");
    //   readPtr = fopen("Objs/Sphere.obj", "r");
    //  readPtr = fopen("Objs/Spoon.obj", "r");
    //  readPtr = fopen("Objs/Teacup.obj", "r");
    // readPtr = fopen("Objs/Teapot.obj", "r");
    // readPtr = fopen("Objs/Torus.obj", "r");
    readPtr = fopen("Objs/VideoShip.obj", "r");
    writePtr = fopen("src/meshData.h", "w");

    char buffer[512] = {};
    if (readPtr != NULL)
    {
        int pointColInd = 0;
        int vertexDataInd = 0;

        while (fgets(buffer, sizeof(buffer), readPtr))
        {
            if (buffer[0] == 'o')
            {
                char *token = strtok(buffer, " ");
                token = strtok(NULL, " ");
                fprintf(writePtr, "//%s\n", token);
            }
            else if (buffer[0] == 'v' && buffer[1] == ' ')
            {
                pointColInd++;
            }
            else if (buffer[0] == 'f')
            {
                vertexDataInd++;
            }
        }

        fprintf(writePtr, "#define POINTCOLIND %d\n", pointColInd);
        fprintf(writePtr, "#define VERTEXCOLIND %d\n", vertexDataInd);
        fprintf(writePtr, "float meshPoints[POINTCOLIND][4] = { \n");

        rewind(readPtr);

        while (fgets(buffer, sizeof(buffer), readPtr))
        {
            if (buffer[0] == 'v' && buffer[1] == ' ')
            {
                char *token = strtok(buffer, " ");

                token = strtok(NULL, " ");
                fprintf(writePtr, "{");
                while (token != NULL)
                {
                    for (int i = 0; i < sizeof(token); i++)
                    {
                        fprintf(writePtr, "%c", token[i]);
                        if (i == sizeof(token) - 1)
                        {
                            fprintf(writePtr, ",");
                        }
                    }
                    token = strtok(NULL, " ");
                    if (token == NULL)
                    {
                        fprintf(writePtr, "\n");
                    }
                }
                fprintf(writePtr, "},");
            }
        }
        fprintf(writePtr, "}; \n");
        rewind(readPtr);
        fprintf(writePtr, "int meshVertexPoints[VERTEXCOLIND][4] = { \n");

        while (fgets(buffer, sizeof(buffer), readPtr))
        {
            if (buffer[0] == 'f')
            {
                char *token = strtok(buffer, " ");
                token = strtok(NULL, " ");

                fprintf(writePtr, "{");
                while (token != NULL)
                {
                    for (int i = 0; i < sizeof(token); i++)
                    {
                        if (token[i] == '/')
                        {
                            fprintf(writePtr, ",");
                            break;
                        }
                        fprintf(writePtr, "%c", token[i]);
                    }
                    token = strtok(NULL, " ");
                    if (token == NULL)
                    {
                        fprintf(writePtr, "\n");
                    }
                }
                fprintf(writePtr, "},");
            }
        }

        fprintf(writePtr, "};\n");

        fclose(readPtr);
        fclose(writePtr);
    }
    else
    {
        return 1;
    }
#endif
}
