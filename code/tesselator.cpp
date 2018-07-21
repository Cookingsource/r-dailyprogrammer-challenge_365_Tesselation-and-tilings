#include <stdio.h>

#define ArraySize( array ) sizeof(array) / sizeof(array[0])

static char rotations[][4] = 
{
    {'|', '-', '|', '-'},
    {'-', '|', '-', '|'}
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

int main(int argc, char const *argv[])
{
    printf("Regular rotation Tesselate given square ascii \n");
    printf("Rotation(multiples of 90):");

    // NOTE(rafa): No input validation
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
    printf("Write base tile lines\n");
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

    // all strings are in place
    // TODO: extend one in each direction
    // TODO: rotate de matrix
    // TODO: rotate the symbols

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
    int repeats = 2;
    int rotationIdx = (rotation % 360 ) / 90;

    for ( int verticalRepeats = 0; verticalRepeats < repeats; ++verticalRepeats)
    { 
        for(int i = 0; i < lineCount; ++i)
        {
            for( int horizontalRepeats = 0; horizontalRepeats < repeats; ++horizontalRepeats)
            {
                int mahnhattanDistance = (horizontalRepeats + verticalRepeats ) % 4;

                for( int charIdx = 0; charIdx < side; ++charIdx)
                {
                    int row = i;
                    int column = charIdx;
                    int row90 = side -1  - column;
                    int column90 = row;
                    int row180 = side -1 - column90;
                    int column180 = row90;
                    int row270 = side -1 - column180;
                    int column270 = row180;

                    if(mahnhattanDistance == 0)
                    {
                        char c = *(lines + lineBegins[row] + column);
                        printf("%c", getRotated(c, 0));
                    }
                    else if ( mahnhattanDistance == 1)
                    {
                        char c = *(lines + lineBegins[row90] + column90);
                        printf("%c",  getRotated(c, 1));
                    }
                    else if( mahnhattanDistance == 2)
                    {
                        char c = *(lines + lineBegins[row180] + column180);
                        printf("%c",  getRotated(c, 2));
                    }
                    else if ( mahnhattanDistance == 3)
                    {
                        char c = *(lines + lineBegins[row270] + column270);
                        printf("%c", getRotated(c, 3));
                    }

                    //// Test out not rotating
                    //printf("%c", *(lines + lineBegins[i]+ charIdx) );
                }
            }
            printf("\n");
        }
    }

    return 0;
}
