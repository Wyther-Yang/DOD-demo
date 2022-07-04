#include "vector2D.h"
#include <stdio.h>

int main()
{
        Vector2D xdirective{3.0f, 0.0f};
        Vector2D ydirective{0.0f, 4.0f};

        printf("Test of Vecotr2D unit result is: ");

        if (Distance(xdirective, ydirective) == 5.0f)
                printf("[fine]\n");
        else
                printf("[error]\n");
        
}