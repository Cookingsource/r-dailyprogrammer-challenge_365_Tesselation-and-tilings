#include <stdio.h>

#define ArraySize( array ) sizeof(array) / sizeof(array[0])


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

    //  123  90  111  90  321  90  333
    //  123  ->  222  ->  321  ->  222
    //  123      333      321  90  111
    int repeats = 2;
    for ( int verticalRepeats = 0; verticalRepeats < repeats; ++verticalRepeats)
    { 
        for(int i = 0; i < lineCount; ++i)
        {
            for( int horizontalRepeats = 0; horizontalRepeats < repeats; ++horizontalRepeats)
            {
                int mahnhattanDistance = horizontalRepeats + verticalRepeats;

                for( int charIdx = 0; charIdx < side; ++charIdx)
                {
                    printf("%c", *(lines + lineBegins[i]+ charIdx) );
                }
            }
            printf("\n");
        }
    }

    return 0;
}
