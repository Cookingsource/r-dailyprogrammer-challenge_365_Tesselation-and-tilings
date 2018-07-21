#include <stdio.h>

#define ArraySize( array ) sizeof(array) / sizeof(array[0])

static char rotations[][4] = 
{
    {'|', '-', '|', '-'},
    {'-', '|', '-', '|'},
    {'/', '\\', '/', '\\'},
    {'\\', '/', '\\', '/'},
    {'{', '}', '{', '}'},
    {'}', '{', '}', '{'},
    //{'!', '!', '¡', '¡'},
    //{'¡', '¡', '!', '!'},
    //{'?', '?', '¿', '¿'},
    //{'¿', '¿', '?', '?'},
    {'{', '{', '}', '}'},
    {'}', '}', '{', '{'},
    {'(', '(', ')', ')'},
    {')', ')', '(', '('},
    {'<', '<', '>', '>'},
    {'>', '>', '<', '<'},
    {'[', '[', ']', ']'},
    {']', ']', '[', '['},
    //{'´', '´', '`', '`'},
    //{'`', '`', '´', '´'}
};

static char getRotated(char symbol, int rotationIdx)
{
    int indexOfChar = -1;
    for(int i = 0; i<ArraySize(rotations); ++i)
    {
        if(rotations[i][0]==symbol)
        {
            indexOfChar = i;
            break;
        }
    }

    if(indexOfChar == -1)
        return symbol;
    else
        return rotations[indexOfChar][rotationIdx];
}

static char Sample(const char* lines, int side, int row, int column)
{
    return *(lines + ((side + 1) * row) + column);
}

static char getSymbolFromRotatedMatrix(const char* lines, int side, int row, int column, int rotationIdx)
{
    char sampled = 0;
    if(rotationIdx == 0)
    {
        sampled = Sample(lines, side, row, column);
    }
    else if ( rotationIdx == 1)
    {
        int row90 = side -1  - column;
        int column90 = row;
        sampled = Sample(lines, side, row90, column90);
    }
    else if( rotationIdx == 2)
    {
        int row180 = side -1 - row;
        int column180 = side -1 - column;
        sampled = Sample(lines, side, row180, column180);
    }
    else if ( rotationIdx == 3)
    {
        int row270 = column;
        int column270 = side -1 - row;
        char sampled = Sample(lines, side, row270, column270);
    }

    return getRotated(sampled, rotationIdx);
}

static void tesselate(const char* lines, int side, int rotationDeg, int repeats)
{
    // (row, column)
    // (0,0)(0,1)(0,2)   90 (2,0)(1,0)(0,0) 
    // (1,0)(1,1)(1,2)   -> (2,1)(1,1)(0,1)
    // (2,0)(2,1)(2,2)      (2,2)(1,2)(0,2)
    // 
    // (r,c) => (R - c - 1, r )? 
    // (0,0) => (2,0)
    // (0,1) => (1,0)
    // (0,2) => (0,0)
    // (1,0) => (2,1)
    // (1,1) => (1,1)
    // (1,2) => (0,1)
    // (2,0) => (2,2)
    // (2,1) => (1,2)
    // (2,2) => (0,2)

    //  123  90  111  90  321  90  333
    //  123  ->  222  ->  321  ->  222
    //  123      333      321  90  111

    int rotationIdx = (rotationDeg % 360 ) / 90;

    printf("base rotation idx %d\n", rotationIdx);

    for ( int verticalRepeats = 0; verticalRepeats < repeats; ++verticalRepeats)
    { 
        for(int i = 0; i < side; ++i)
        {
            for( int horizontalRepeats = 0; horizontalRepeats < repeats; ++horizontalRepeats)
            {
                int mahnhattanDistance = horizontalRepeats + verticalRepeats;
                //printf("Manhattan distance %d\n", mahnhattanDistance);

                for( int charIdx = 0; charIdx < side; ++charIdx)
                {
                    int row = i;
                    int column = charIdx;
                    int adjustedRotationIdx = (mahnhattanDistance * rotationIdx) % 4;
                    //printf("Adjusted rotation idx %d \n", adjustedRotationIdx);

                    printf("%c", getSymbolFromRotatedMatrix(lines, side, row, column, adjustedRotationIdx));
                    

                    //// Test out not rotating
                    //printf("%c", *(lines + lineBegins[i]+ charIdx) );
                }
            }
            printf("\n");
        }
    }
}

static void runFromUserInput()
{
    printf("Regular rotation Tesselate given square ascii \n");
    printf("Rotation(multiples of 90):");

    int rotation = 0;
    scanf(" %d", &rotation);

    int side = 0;
    printf("Square side ( positive ): ");
    scanf( "%d", &side);

    printf("Input: {rotation: %d , side: %d} \n", rotation, side);

    // Get <side> lines
    char lines[512] = {};
    int lineBegins[256] = {}; 
    for( int i = 0; i< ArraySize(lineBegins); ++i)
        lineBegins[i] = -1; // -1 meaning no more string

    int lineCount = 0;

    int writeOffset = 0;
    //printf("Write base tile lines\n");
    for ( int i = 0; i<side; ++i)
    {
        // printf("Scan for line %d\n",i);

        scanf(" %[^\n]%*c", lines + writeOffset);
        lineCount+= 1;
        lineBegins[i] = writeOffset;
        // printf("%c%c%c<%d><%d><%d>\n", 
        //     lines[writeOffset], lines[writeOffset+1], lines[writeOffset+2], 
        //     lines[writeOffset+3], lines[writeOffset+4], lines[writeOffset+5]);
        
        for ( int idx = writeOffset; idx < ArraySize(lines); ++idx)
        {
            if( lines[idx] == '\0')
            {
                writeOffset = idx +1;
                break;
            }
        }
    }

    for ( int lineIdx; lineIdx<lineCount; ++lineIdx)
    {
        printf("[%d] \"%s\"\n", lineBegins[lineIdx],   lines + lineBegins[lineIdx]);
    }

    tesselate(lines, lineCount, rotation, 2);
}

static void runExamples()
{
    const char* lines = "--x\0--x\0--x\0";
    tesselate(lines, 3, 90, 2);
    lines = "####\0#--#\0#++#\0####\0";
    tesselate(lines, 4, 90, 2);
    lines = "/\\-/|-\0/\\/-\\/\0||\\\\-\\\0|\\|-|/\0|-\\|/|\0|\\-/-\\\0";
    tesselate(lines, 6, 90, 2);
    lines = "&`{!#;\0"
            "#*#@+#\0"
            "~/}}?|\0"
            "'|(==]\0"
            "\\^)~=*\0"
            "|?|*<%\0";
    tesselate(lines, 6, 180, 2);
}

int main(int argc, char const *argv[])
{
    if(argc == 1)
        runFromUserInput();
    else
        runExamples();


    return 0;
}
