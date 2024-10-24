#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

    FILE *readPtr;
    FILE *writePtr;

    // readPtr =   fopen("../Objs/Cube.obj","r");
    //  readPtr = fopen("../Objs/Sphere.obj","r");
    // readPtr = fopen("../Objs/Cylinder.obj", "r");
    //  readPtr = fopen("../Objs/Cone.obj","r");
    readPtr = fopen("../Objs/Torus.obj", "r");
    // readPtr = fopen("../Objs/Teapot.obj", "r");
    // readPtr = fopen("../Objs/Mountains.obj","r");
    // readPtr = fopen("../Objs/Cube.obj", "r");
    writePtr = fopen("../src/meshData.h", "w");

    char buffer[512] = {};

    if (readPtr != NULL)
    {
        int pointColInd = 0;
        int vertexDataInd = 0;

        while (fgets(buffer, sizeof(buffer), readPtr))
        {
            if (buffer[0] == 'v' && buffer[1] == ' ')
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
        fprintf(writePtr, "float meshPoints[POINTCOLIND][3] = { \n");

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
        fprintf(writePtr, "int meshVertexPoints[VERTEXCOLIND][3] = { \n");

        while (fgets(buffer, sizeof(buffer), readPtr))
        {
            if (buffer[0] == 'f')
            {
                char *token = strtok(buffer, " ");
                token = strtok(NULL, " ");

                char data[64] = {};
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
        printf("cant read obj file!! :( ");
    }
}
