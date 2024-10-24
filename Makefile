INC= /home/galacticpast/Documents/raylib/src
LIB= /home/galacticpast/Documents/raylib/src
Basic3dRenderer:
		gcc src/ObjFileParser.c -g -o build/Basic3dRenderer
		gcc src/Basic3dRenderer.c -L$(LIB) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -I$(INC) -g -o build/Basic3dRenderer

