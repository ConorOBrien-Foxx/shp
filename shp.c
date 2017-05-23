#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEFAULT_MEMORY_SIZE 1000

char* readFile(char* name){
    FILE* file;
    file = fopen(name, "r");
    
    if(fseeko(file, 0, SEEK_END) != 0){
        fprintf(stderr, "error occured when reading file '%s'\n", name);
        exit(-1);
    }
    off_t fileSize = ftello(file);
    if(fseeko(file, SEEK_SET, 0) != 0){
        fprintf(stderr, "error occured when reading file '%s'\n", name);
        exit(-1);
    }
    
    char* res = malloc((fileSize + 1) * sizeof(char));
    fread(res, fileSize, 1, file);
    fclose(file);
    
    res[fileSize] = '\0';
    
    return res;
}

/*
+    add accumulators together into the current accumulator
;    increase accumulator by the delta value
:    increase pointer by delta value
-    negate the delta value
#    mod 127 the accumulator, output ascii char, and reset accumulator
<    read cell from memory into accumulator
>    save accumulator into memory
~    swap accumulator with secondary accumulator
.    go to the (accumulator)th position in memory
*    read character of input into accumulator
(    if the accumulator is zero, skip to the next matching `)`
)    if the accumulator is not zero, rewind to the previous matching `(`
p    print the numeric value of the accumulator
`    show debug information
!    set accumulator to 1 if zero; otherwise, 0
@    exit with exit code equal to the accumulator
*/

int main(int argc, char** argv){
    int A = 0;
    int B = 0;
    int deltaValue = 1;
    int* memory = malloc(sizeof(int) * DEFAULT_MEMORY_SIZE);
    int memPtr = 0;
    int maxPtr = -1;
    
    char* file = readFile(argv[1]);
    int i;
    off_t len = strlen(file);
    for(i = 0; i < len; i++){
        char cur = file[i];
        if(cur == ';')
            A += deltaValue;
        else if(cur == ':'){
            memPtr += deltaValue;
            if(memPtr > maxPtr)
                maxPtr = memPtr;
        }
        else if(cur == '+')
            A += B * deltaValue;
        else if(cur == '-')
            deltaValue = -deltaValue;
        else if(cur == '#'){
            putchar(A % 127);
            A = 0;
        }
        else if(cur == 'p')
            printf("%i", A);
        else if(cur == '<'){
            A = memory[memPtr];
            if(memPtr > maxPtr)
                maxPtr = memPtr;
        }
        else if(cur == '>'){
            memory[memPtr] = A;
            if(memPtr > maxPtr)
                maxPtr = memPtr;
        }
        else if(cur == '~'){
            A ^= B;
            B ^= A;
            A ^= B;
        }
        else if(cur == '.'){
            memPtr = A;
            if(memPtr > maxPtr)
                maxPtr = memPtr;
        }
        else if(cur == '*')
            A = getchar();
        else if(cur == '('){
            if(A == 0){
                int depth = 1;
                while(i < len && depth){
                    i++;
                    if(file[i] == '('){
                        depth++;
                    }
                    else if(file[i] == ')'){
                        depth--;
                    }
                }
            }
        }
        else if(cur == ')'){
            if(A != 0){
                int depth = 1;
                while(i < len && depth){
                    --i;
                    if(file[i] == '('){
                        depth--;
                    }
                    else if(file[i] == ')'){
                        depth++;
                    }
                }
            }
        }
        else if(cur == '`'){
            printf("(%i, %i, %c)@%i", A, B, deltaValue == 1 ? '+' : '-', memPtr);
            // print memory
            printf(" { ");
            for(int t = 0; t <= maxPtr; t++){
                printf("(%i|%c)", memory[t], memory[t]);
                if(t != maxPtr)
                    printf(" , ");
            }
            printf(" }\n");
        }
        else if(cur == '!'){
            A = A == 0 ? 1 : 0;
        }
        else if(cur == '@'){
            exit(A);
        }
    }
    
    free(memory);
    free(file);
}