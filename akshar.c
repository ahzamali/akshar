/*
 * Akshar Hindi (devnagri) editor designed by
 * Ahzam Ali
 * Anwar Parvez
 * Neeraj Grover
 * Completed on May 16, 1999
 *
 * Feel free to modify and use the program in your way
 */

#include<stdio.h>
#include<bios.h>
#include<string.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<dos.h>

#define maxxc 510
#define maxyc 450
#define EXT ".hif"
#define BXCOL 01
#define BFCOL 11
#define FGCOL 00
#define BKCOL 15
#define CRCOL 12
#define BRCOL 01
#define OFCOL 10
#define xcinc 8
#define ycinc 27
#define incx 8
#define incy 38

void bar(int left, int top, int right, int bottom);

/*
 * Function Declaration
 */

void getchar (void);
void putchar (void);
void bkspace (void);
void cursor (int x, int y);
void Exit (void);
void getfilename (void);
void getline (void);
void hin_prn (int astat, int maxa, int maxb);
void hin_prn_matra (int astat, int maxa, int maxb);
void identkey (char c);
void initscreen (void);
void moveptrlt (void);
void moveptrrt (void);
void moveptrdn (void);
void moveptrup (void);
void new_file (void);
void openfile (void);
void print_massage (char *mes);
void print_hin_str (char *str, int rp, int lc);
void pointer (void);
void print_file (void);
void putline (void);
void refresh (void);
void scrollup (void);
void scrolldn (void);
void savefile (void);

void *image1, *image2;

//init of char
//character number reffered */
char hin_main_char[800][13], hin_matra[20][19], cur_char = 0, del,
currentlineNo = 0;

int total_line = 0, a, b, backgr_color = 15, print_color, xcpos = incx;
int ycpos = incy, tempxcp, total_char = 0;

static char c = 0, *char_str, *trn, print_flag, save_flag = 1, name_flag = 0;

char filename[20] = "csuke";

FILE *fp;

/*
 * Main Function
 */

void main (void)
{
    int i, j, driver, mode;
    driver = VGA;
    mode = VGAHI;
    // Initiate graphics mode 640 X 480 X 16

    initgraph (&driver, &mode, "\\tc\\bgi");

    char_str = (char *) malloc (6400);
    for (i = 0; i < 6400; i++)
        char_str[i] = '\0';

    // Read the font from the data files

    FILE *f;
    f = fopen ("hscm.hin", "rb");
    if (f == NULL)
    {
        closegraph ();
        printf ("FILE hscm.hin NOT FOUND");
        exit (1);
    }
    fread (hin_matra, sizeof (hin_matra), 1, f);
    fclose (f);
    f = fopen ("hsc.hin", "rb");
    if (f == NULL)
    {
        closegraph ();
        printf ("FILE hsc.hin NOT FOUND");
        exit (1);
    }

    fread (hin_main_char, sizeof (hin_main_char), 1, f);

    fclose (f);
    initscreen ();

    // Main program loop
begin:

    // Points to the character
    pointer ();

    // Blinks the cursor
    cursor (xcpos, ycpos);
    print_flag = 1;
    print_color = 0;

    c = getch ();
    switch (c)
    {
        // Do nothing when Escape and tab is pressed
        case 27:
        case 9:
            goto begin;

        // Process backspace
        case 8:
            if (cur_char > 0 && char_str[cur_char - 1])
            {
                bkspace ();
                if (char_str[cur_char - 1] == 'f')
                    bkspace ();
            }
            goto begin;
        case 0:
            // If the key pressed is function key
            switch (getch ())
            {
                //up arrow
                case 72:
                    if (ycpos > incy + 22 && currentlineNo > 0)
                    {
                        putchar ();
                        moveptrup ();
                        getchar ();
                        currentlineNo--;
                    }
                    goto begin;
                //down arrow
                case 80:
                    if (ycpos < (15 * ycinc) && currentlineNo < total_line)
                    {
                        putchar ();
                        moveptrdn ();
                        getchar ();
                        currentlineNo++;
                    }
                    goto begin;
                //left arrow
                case 75:
                    if ((cur_char > 0) && (char_str[cur_char - 1] != 0))
                    {
                        putchar ();
                        moveptrlt ();
                        getchar ();
                    }
                    goto begin;
                //right arrow
                case 77:
                    if (char_str[cur_char] != 10 && char_str[cur_char] != 0 && 
                        total_char > cur_char)
                    {
                        putchar ();
                        moveptrrt ();
                        getchar ();
                    }
                    goto begin;
                // Function 1
                case 59:
                    savefile ();
                    goto begin;
                // Function 2
                case 60:
                    getfilename ();
                    goto begin;
                // Function 3
                case 61:
                    openfile ();
                    goto begin;
                // Function 4
                case 62:
                    refresh ();
                    goto begin;
                // Function 5
                case 63:
                    print_file ();
                    goto begin;
                // Function 6
                case 64:
                    new_file ();
                    goto begin;
                // Function 10
                case 68:
                    Exit ();
                // Delete
                case 83:
                    if (total_char > cur_char && char_str[cur_char] != '\n')
                    {
                        tempxcp = xcpos;
                        print_flag = 0;
                        identkey (char_str[cur_char]);
                        getline ();
                        xcpos = tempxcp;
                        putline ();
                        memmove (char_str + cur_char, char_str + cur_char + 1,
                                total_char - cur_char);
                        getchar ();
                    }
                    goto begin;
                default:
                    goto begin;
            }

        default:
            if (c == 9)
                goto begin;
            if (c == 13 && currentlineNo == 14)
            {
                print_massage ("vkSj ykbu ufga gSa MkdgesV ns[ksa");
                goto begin;
            }
            if (total_char > cur_char)
                memmove (char_str + cur_char + 1, char_str + cur_char,
                        total_char - cur_char);
            identkey (c);

            if (c == 13)
                char_str[cur_char] = '\n';
            else
                char_str[cur_char] = c;
            char_str[total_char + 1] = '\0';

            total_char++;
            cur_char++;
            save_flag = 0;

            break;
    }
    if (xcpos >= maxxc && ycpos <= (16 * ycinc))
    {
        xcpos = incx;
        ycpos += ycinc;
        char_str[cur_char] = '\n';
        cur_char++;
        total_char++;
        currentlineNo++;
        total_line++;
    }
    goto begin;
}

// Clears the buffer and resets the values to initial values
void new_file (void)
{
    cur_char = 0;
    total_char = 0;
    xcpos = incx;
    ycpos = incy;
    save_flag = 1;
    initscreen ();
    return;
}

// Prints the file
void print_file (void)
{
    register int i, j, x, y, ln;
    int temp[8], templ = 0, l = 128;
    char printch[500][3];

    // Check if the printer is busy
    if (biosprint (2, 0, 0) != 0x90)
    {
        print_massage ("fizaVj o;Lr gS 7 ugha gS");
        return;
    }

    // Display a massage and print the image on white area of screen
    void *image3;
    image3 = malloc (imagesize (12, 435, 450, 457));
    getimage (12, 435, 450, 457, image3);
    setfillstyle (1, BXCOL);
    bar (12, 435, 450, 457);
    print_color = BFCOL;
    print_hin_str ("d`I;k izrh{k djs-", 2, 16);
    for (ln = 0; ln < 16; ln++)
    {
        for (y = 0; y < 3; y++)
            for (x = 5; x < 505; x++)
            {
                for (j = 0; j < 8; j++)
                {
                    if (getpixel (x, j + 30 + y * 8 + ln * 27) == 0)
                        temp[j] = 1;
                    else
                        temp[j] = 0;
                    templ += (temp[j] * l);
                    l /= 2;
                }
                l = 128;
                printch[x - 5][y] = templ;
                templ = 0;
            }

        biosprint (0, 0x1b, 0);
        biosprint (0, 0x33, 0);
        biosprint (0, 0x18, 0);
        for (j = 0; j < 3; j++)
        {
            biosprint (0, 0x1b, 0);
            biosprint (0, 0x2a, 0);
            biosprint (0, 0x00, 0);
            biosprint (0, 500 % 256, 0);
            biosprint (0, 500 / 256, 0);
            for (i = 0; i < 500; i++)
                biosprint (0, printch[i][j], 0);
            biosprint (0, '\r', 0);
            biosprint (0, '\n', 0);
        }
    }
    putimage (12, 435, image3, 0);
    free (image3);
    print_color = FGCOL;
    return;
}

// Exit the program after displaying the massage and save file if the
// file is not saved
void Exit (void)
{
    putchar ();
    if (save_flag == 0)
        savefile ();
    cleardevice ();
    print_color = OFCOL;
    print_hin_str ("vikj d=", 34, 6);
    print_hin_str ("vgtte] vuoj vkSj uhjt", 28, 7);
    print_hin_str ("dh izirgrh", 33, 8);
    setcolor (1);
    outtextxy (250, 254, "(c)");
    print_hin_str ("vgtte vyh] 1999", 33, 9);
    print_hin_str ("v£d tkudkjh dsfy, MkdgesV ns[ksa", 26, 10);
    getch ();
    closegraph ();
    exit (0);
}

// Move the cursor up when up arrow is pressed
void moveptrup (void)
{
    register int j;
    for (j = 0; j < 2;)
    {
        cur_char--;
        if (char_str[cur_char] == 10)
            j++;
        if (cur_char == 0)
            break;
    }
    if (cur_char != 0)
        cur_char++;
    xcpos = incx;
    ycpos -= ycinc;
    return;
}

// Move the cursor left
void moveptrlt (void)
{
    print_flag = 0;
    print_color = BKCOL;
    identkey (char_str[cur_char - 1]);
    cur_char--;
    return;
}

// Move the cursor right
void moveptrrt (void)
{
    print_flag = 0;
    print_color = FGCOL;
    identkey (char_str[cur_char]);
    cur_char++;
    return;
}

// Move the cursor down
void moveptrdn (void)
{
    while (char_str[cur_char] != '\n')
        cur_char++;
    cur_char++;
    xcpos = incx;
    ycpos += ycinc;
    return;
}
// Initialises the screen display
void initscreen (void)
{
    int i;
    setfillstyle (1, BKCOL);
    bar (0, 0, 640, 480);
    setfillstyle (1, BRCOL);
    bar (0, 0, 640, 30);
    bar (0, 435, 640, 480);
    outtextxy (2, 10, "F1");
    outtextxy (70, 10, "F2");
    outtextxy (150, 10, "F3");
    outtextxy (260, 10, "F4");
    outtextxy (340, 10, "F5");
    outtextxy (410, 10, "F6");
    outtextxy (490, 10, "F10");
    print_color = BFCOL;
    print_hin_str ("lso", 2, 0);
    print_hin_str ("Yuekad.k", 11, 0);
    print_hin_str ("[kksyus dsfty;s", 21, 0);
    print_hin_str ("igquoz £}", 35, 0);
    print_hin_str ("eqn.kZ", 45, 0);
    print_hin_str ("upk", 54, 0);
    print_hin_str ("fudkl", 65, 0);
    for (i = 0; i < 8; i++)
    {
        if (filename[i] == '.')
            break;
    }
    filename[i] = '\0';
    print_hin_str (filename, 35, 16);
    print_color = FGCOL;
    getchar ();
}

// Print a string in hindi
void print_hin_str (char *str, int r, int c)
{
    int xct, yct;
    print_flag = 1;
    xct = xcpos;
    yct = ycpos;
    xcpos = r * xcinc + incx;
    ycpos = c * ycinc + 8;
    while (*str != '\0')
    {
        identkey (*str);
        str++;
    }
    xcpos = xct;
    ycpos = yct;
    return;
}

// Manages backspace function
void bkspace ()
{
    getline ();
    print_color = backgr_color;
    cur_char--;
    total_char--;
    identkey (char_str[cur_char]);
    memmove (char_str + cur_char, char_str + cur_char + 1, total_char - 
            cur_char + 1);
    putline ();
    return;
}

// Prints character
void hin_prn (int astat, int maxa, int maxb)
{
    register int a, A;
    if (print_flag == 0)
        for (a = 0; a < 8; a++)
            for (b = 0; b < 3; b++)
                if (getpixel (xcpos + a, ycpos + b) == CRCOL)
                    putpixel (xcpos + a, ycpos + b, backgr_color);
    if (print_color == backgr_color)
        xcpos -= maxa;

    for (a = astat, A = 0; a < astat + maxa && A < maxa; a++, A++)
    {
        for (b = 0; b < maxb; b++)
            if (hin_main_char[a][b] != 0)
                putpixel (xcpos + A, ycpos + b, print_color);
    }

    if (print_flag == 0 && print_color == backgr_color)
        xcpos -= maxa;

    if (print_color != backgr_color)
        xcpos += maxa;

    return;
}

// Prints Matra
void hin_prn_matra (int astat, int maxa, int maxb)
{
    int A;
    for (a = 0; a < 8; a++)
        for (b = 0; b < 3; b++)
            if (getpixel (xcpos + a, ycpos + b) == CRCOL)
                putpixel (xcpos + a, ycpos + b, backgr_color);
    if (print_flag != 0)
        for (a = astat, A = 0; a < astat + maxa && A < maxa; a++, A++)
            for (b = 0; b < maxb; b++)
                if (hin_matra[a][b] != 0)
                    putpixel (xcpos + A, ycpos + b, print_color);
    return;
}

// Makes the cursor blink and reports to main when a key is pressed
void cursor (int x, int y)
{
    while (!kbhit ())
    {
        setfillstyle (1, CRCOL);
        bar (x, y, x + 1, y + 1);
        delay (7);
        setfillstyle (1, backgr_color);
        bar (x, y, x + 1, y + 1);
        delay (7);
    }
    return;
}

// Displays the character that will be deleted on pressing backspace and
// delete respectively
void pointer (void)
{
    int xc, yc;
    print_flag = 1;
    backgr_color = BXCOL;
    setfillstyle (1, BXCOL);
    bar (30, 435, 120, 460);
    xc = xcpos;
    yc = ycpos;
    xcpos = 42;
    ycpos = 445;
    print_color = BFCOL;
    identkey (char_str[cur_char - 1]);
    xcpos = 80;
    ycpos = 445;
    print_color = CRCOL;
    identkey (char_str[cur_char]);
    xcpos = xc;
    ycpos = yc;
    backgr_color = BKCOL;
    return;
}

// Saves the image on which the cursor is displayed
void getchar (void)
{
    image1 = malloc (imagesize (0, 0, 8, 2));
    getimage (xcpos, ycpos, xcpos + 8, ycpos + 1, image1);
    return;
}

// Puts the image when the cursor is moved from a place
void putchar (void)
{
    putimage (xcpos, ycpos, image1, 0);
    free (image1);
    return;
}
// Identifies the characters and decides how to print that
//hindi numerics
//hindi special characters
void identkey (char c)
{
    switch (c)
    {
        case '`':
            if (print_color == backgr_color)
                xcpos += 8;
            xcpos -= 8;
            ycpos += 13;
            hin_prn (0, 8, 4);
            if (print_color == backgr_color)
                xcpos += 8;
            ycpos -= 13;
            break;
        case '~':
            if (print_color == backgr_color)
                xcpos += 4;
            xcpos -= 4;
            ycpos += 13;
            hin_prn (8, 4, 4);
            if (print_color == backgr_color)
                xcpos += 4;
            ycpos -= 13;
            break;
        case '1':
            hin_prn (12, 8, 13);
            break;
        case '!':
            hin_prn (20, 4, 13);
            break;
        case '2':
            hin_prn (24, 8, 13);
            break;
        case '@':
            hin_prn (32, 8, 13);
            break;
        case '3':
            hin_prn (40, 8, 13);
            break;
        case '#':
            hin_prn (48, 8, 13);
            break;
        case '4':
            hin_prn (56, 8, 13);
            break;
        case '$':
            hin_prn (64, 8, 13);
            break;
        case '%':
            hin_prn (72, 8, 13);
            break;
        case '5':
            hin_prn (80, 4, 13);
            break;
        case '6':
            hin_prn (84, 8, 13);
            break;
        case '^':
            hin_prn (92, 4, 6);
            break;
        case '&':
            hin_prn (96, 8, 13);
            break;
        case '7':
            hin_prn (104, 8, 13);
            break;
        case '8':
            hin_prn (112, 8, 13);
            break;
        case '*':
            hin_prn (120, 4, 6);
            break;
        case '9':
            hin_prn (124, 8, 13);
            break;
        case '(':
            if (print_color == backgr_color)
                xcpos -= 2;
            hin_prn (132, 4, 13);
            if (print_color != backgr_color)
                xcpos += 2;
            break;
        case '0':
            hin_prn (136, 8, 13);
            break;
        case ')':
            hin_prn (144, 8, 13);
            break;
        case '-':
            if (print_color == backgr_color)
                xcpos -= 2;

            fflush (stdin);
            fflush (stdout);
            if (print_flag != 0)
            {
                for (a = 0; a < 8; a++)
                    for (b = 0; b < 13; b++)
                        if (getpixel (xcpos + a, ycpos + b) == CRCOL)
                            putpixel (xcpos + a, ycpos + b, FGCOL);

                putpixel (xcpos + 2, ycpos + 13, print_color);
            }

            if (print_color != backgr_color)
                xcpos += 2;
            break;
        case '_':
            hin_prn (152, 8, 13);
            break;
        case '=':
            hin_prn (160, 6, 13);
            break;
        case '+':
            if (print_flag != 0)
                putpixel (xcpos - 4, ycpos + 14, print_color);
            else
                putpixel (xcpos - 4, ycpos + 14, backgr_color);
            break;
        case '\\':
            hin_prn (166, 8, 13);
            break;
        case '|':
            hin_prn (174, 8, 13);
            break;

        // first line over

        //hindi characters
        case 'q':
            if (print_color == backgr_color)
                xcpos += 6;
            xcpos -= 6;
            ycpos += 13;
            hin_prn (182, 6, 5);
            if (print_color == backgr_color)
                xcpos += 6;
            ycpos -= 13;
            break;
        case 'Q':
            hin_prn (188, 8, 13);
            break;
        case 'w':
            if (print_color == backgr_color)
                xcpos += 6;
            xcpos -= 4;
            ycpos += 13;
            hin_prn (196, 6, 5);
            if (print_color == backgr_color)
                xcpos += 6;
            xcpos -= 2;
            ycpos -= 13;
            break;
        case 'W':
            if (print_color == backgr_color)
                xcpos += 8;
            xcpos -= 4;
            ycpos -= 8;
            hin_prn (202, 8, 8);
            if (print_color == backgr_color)
                xcpos += 8;
            ycpos += 8;
            xcpos -= 4;
            break;
        case 'e':
            hin_prn (210, 8, 13);
            break;
        case 'E':
            hin_prn (210, 6, 13);
            break;
        case 'r':
            hin_prn (218, 8, 13);
            break;
        case 'R':
            hin_prn (218, 6, 13);
            break;
        case 't':
            hin_prn (226, 8, 13);
            break;
        case 'T':
            hin_prn (226, 6, 13);
            break;
        case 'y':
            hin_prn (234, 8, 13);
            break;
        case 'Y':
            hin_prn (234, 6, 13);
            break;
        case 'u':
            hin_prn (242, 8, 13);
            break;
        case 'U':
            hin_prn (242, 6, 13);
            break;
        case 'i':
            hin_prn (250, 8, 13);
            break;
        case 'I':
            hin_prn (250, 6, 13);
            break;
        case 'o':
            hin_prn (258, 8, 13);
            break;
        case 'O':
            hin_prn (266, 6, 13);
            break;
        case 'p':
            hin_prn (272, 8, 13);
            break;
        case 'P':
            hin_prn (272, 6, 13);
            break;
        case '[':
            hin_prn (280, 6, 13);
            break;
        case '{':
            hin_prn (286, 6, 13);
            break;
        case ']':
            if (print_color == backgr_color)
                xcpos -= 2;
            xcpos += 1;
            ycpos += 11;
            hin_prn (292, 4, 6);

            if (print_color != backgr_color)
                xcpos += 1;

            if (print_color == backgr_color)
                xcpos += 1;

            ycpos -= 11;
            break;
        case '}':
            hin_prn (296, 8, 13);
            break;

        // 2nd row over
        case 'a':
            if (print_flag != 0)
                putpixel (xcpos, ycpos - 5, print_color);
            if (print_color == backgr_color)
                putpixel (xcpos, ycpos - 5, backgr_color);
            break;
        case 'A':
            if (print_color == backgr_color)
                xcpos += 4;
            hin_prn (304, 3, 13);
            if (print_color != backgr_color)
                xcpos += 4;
            break;
        case 's':
            if (print_color == backgr_color)
                xcpos += 8;
            xcpos -= 8;
            ycpos -= 8;
            hin_prn (307, 8, 8);
            if (print_color == backgr_color)
                xcpos += 8;
            ycpos += 8;
            break;
        case 'S':
            if (print_color == backgr_color)
                xcpos += 8;
            xcpos -= 8;
            ycpos -= 8;
            hin_prn (315, 8, 8);
            if (print_color == backgr_color)
                xcpos += 8;
            ycpos += 8;
            break;
        case 'd':
            hin_prn (323, 8, 13);
            break;
        case 'D':
            hin_prn (331, 6, 13);
            break;
        case 'f':
            if (print_color == backgr_color)
                xcpos += 2;
            ycpos -= 6;
            hin_prn_matra (0, 10, 19);
            ycpos += 6;
            if (print_color != backgr_color)
                xcpos += 2;
            break;
        case 'F':
            hin_prn (337, 6, 13);
            break;
        case 'g':
            hin_prn (343, 8, 13);
            break;
        case 'G':
            hin_prn (351, 8, 13);
            break;
        case 'h':
            if (print_color != backgr_color)
                xcpos -= 4;
            ycpos -= 6;
            if (print_color == backgr_color)
                xcpos -= 10;
            hin_prn_matra (10, 10, 19);
            if (print_color != backgr_color)
                xcpos += 10;
            if (print_color == backgr_color)
                xcpos += 4;
            ycpos += 6;
            break;
        case 'H':
            hin_prn (359, 6, 13);
            break;
        case 'j':
            hin_prn (365, 8, 13);
            break;
        case 'J':
            hin_prn (373, 8, 13);
            break;
        case 'K':
            hin_prn (381, 8, 13);
            break;
        case 'k':
            hin_prn (389, 3, 13);
            break;
        case 'l':
            hin_prn (392, 8, 13);
            break;
        case 'L':
            hin_prn (392, 6, 13);
            break;
        case ';':
            hin_prn (400, 8, 13);
            break;
        case ':':
            hin_prn (408, 8, 13);
            break;
        case '\'':
            hin_prn (416, 6, 13);
            break;
        case '"':
            hin_prn (422, 6, 13);
            break;

        //single quote
        //3rd line over
        case 'Z':
            if (print_color == backgr_color)
                xcpos += 8;
            xcpos -= 4;
            ycpos -= 8;
            hin_prn (428, 8, 8);
            if (print_color == backgr_color)
                xcpos += 8;
            xcpos -= 4;
            ycpos += 8;
            break;
        case 'z':
            xcpos -= 6;
            ycpos += 7;
            if (print_color == backgr_color)
                xcpos += 4;
            hin_prn (436, 4, 4);
            if (print_color == backgr_color)
                xcpos += 4;
            ycpos -= 7;
            xcpos += 2;
            break;
        case 'x': //pura ga
            hin_prn (440, 8, 13);
            break;
        case 'X': //aadha ga
            hin_prn (440, 6, 13);
            break;
        case 'c':
            hin_prn (448, 8, 13);
            break;
        case 'C':
            hin_prn (448, 6, 13);
            break;
        case 'v':
            hin_prn (456, 8, 13);
            break;
        case 'V':
            hin_prn (464, 8, 13);
            break;
        case 'b':
            hin_prn (472, 8, 13);
            break;
        case 'B':
            hin_prn (480, 8, 13);
            break;
        case 'n':
            hin_prn (488, 8, 13);
            break;
        case 'N':
            hin_prn (496, 8, 13);
            break;
        case 'm':
            hin_prn (504, 8, 13);
            break;
        case 'M':
            hin_prn (512, 8, 13);
            break;
        case ',':
            hin_prn (520, 8, 13);
            break;
        case '<':
            hin_prn (528, 8, 13);
            break;
        case '.':
            hin_prn (536, 6, 13);
            break;
        case '>':
            hin_prn (542, 8, 13);
            break;
        case '?':
            hin_prn (550, 6, 13);
            break;
        case '/':
            hin_prn (556, 6, 13);
            break;
        case 30:
            hin_prn (562, 8, 13);
            break;
        case 31:
            hin_prn (570, 8, 13);
            break;
        case 28:
            hin_prn (578, 8, 13);
            break;
        case 1:
            hin_prn (586, 8, 13);
            break;
        case 15:
            hin_prn (594, 8, 13);
            break;
        case 5:
            hin_prn (602, 8, 13);
            break;
        case 18:
            hin_prn (610, 8, 13);
            break;
        case 17:
            hin_prn (618, 8, 13);
            break;
        case 23:
            hin_prn (626, 8, 13);
            break;
        case 4:
            hin_prn (634, 8, 13);
            break;
        case 6:
            hin_prn (642, 8, 13);
            break;
        case 24:
            hin_prn (650, 8, 13);
            break;
        case 11:
            hin_prn (658, 8, 13);
            break;
        case 12:
            hin_prn (666, 8, 13);
            break;
        case 2:
            hin_prn (674, 8, 13);
            break;
        case 14:
            hin_prn (682, 8, 13);
            break;
        case 13: //RETURN KEY
        case 10:
            if (print_flag != 0)
            {
                if (ycpos < (ycinc * 15))
                {
                    currentlineNo++;
                    total_line++;
                    xcpos = incx;
                    ycpos += ycinc;
                }
            }
            break;
        case 32: //SPACE BAR
            if (xcpos < 620)
                if (print_color == backgr_color)
                    xcpos -= xcinc;
                else if (print_color != backgr_color)
                    xcpos += xcinc;
            break;
        default:
            break;
    } // end of switch
    return;
}
// Moves the line back when a character is deleted
void getline (void)
{
    image2 = malloc (imagesize (xcpos, ycpos - 8, maxxc, ycpos + 17));
    getimage (xcpos, ycpos - 8, maxxc, ycpos + 17, image2);
    return;
}

void putline (void)
{
    putimage (xcpos, ycpos - 8, image2, 0);
    free (image2);
    return;
}

// Refreshes the display
void refresh (void)
{
    register int i;
    total_line = 0;
    initscreen ();
    xcpos = incx;
    ycpos = incy;
    for(i = 0; i < total_char; i++)
        identkey (char_str[i]);
    cur_char = 0;
    i = 0;
    xcpos = incx;
    ycpos = incy;
    getchar ();
    return;
}

// Function to save the buffer content on disk
void savefile (void)
{
    int i;
    FILE * f;
    char_str[total_char] = '\0';
    if (name_flag == 0)
        getfilename ();
    strcat (filename, EXT);
    f = fopen (filename, "wb");
    fwrite ("Hindi editor", sizeof ("Hindi editor"), 1, f);
    fwrite (&total_char, 2, 1, f);
    fwrite (char_str, total_char, 1, f);
    fclose (f);
    save_flag = 1;
    return;
}

// Read a file from the disk
void openfile (void)
{
    FILE * fo;
    int i;
    char tp[600];
    getfilename ();

    if (filename[0] == '\0')
        return;

    strcat (filename, EXT);

    fo = fopen (filename, "rb");
    if (fo != NULL)
    {
        fread (tp, 12, 1, fo);
        tp[12] = 0;

        if (strcmp (tp, "Hindi editor") != 0)
        {
            print_massage ("Qkby ekU; ugha gS");
            return;
        }

        fread (tp, 2, 1, fo);
        cur_char = tp[0] * 256 + tp[1];
        fseek (fo, 14, SEEK_SET);
        fread (char_str, cur_char, 1, fo);
        fclose (fo);

        initscreen ();
        xcpos = incx;
        ycpos = incy;
        total_char = 0;
        name_flag = 1;
        for (i = 0; i <= cur_char; i++)
        {
            identkey (char_str[i]);
            total_char++;
        }
        cur_char++;
        getchar ();
        return;
    }
    else
    {
        print_massage ("Qkby ugh feyk");
        return;
    }
}

// Displays a massage on the status bar
void print_massage (char *mes)
{
    void *image3;
    image3 = malloc (imagesize (12, 435, 450, 457));
    getimage (12, 435, 450, 457, image3);
    setfillstyle (1, BXCOL);
    bar (12, 435, 450, 457);
    print_color = BFCOL;
    print_hin_str (mes, 2, 16);
    getch ();
    putimage (12, 435, image3, 0);
    free (image3);
    print_color = FGCOL;
    return;
}

// Gets the file name from the user
void getfilename (void)
{
    void *image3, *image4;
    int xc, yc, i;
    xc = xcpos;
    yc = ycpos;
    print_flag = 1;
    xcpos = 300;
    ycpos = 225;
    image3 = malloc (imagesize (200, 206, 400, 240));
    getimage (200, 210, 400, 250, image3);
    setfillstyle (1, BXCOL);
    bar (200, 210, 400, 250);
    setfillstyle (1, 7);
    bar (290, 215, 370, 242);
    print_hin_str ("Qkby dk uke", 25, 8);
    for (i = 0; i < 8; i++)
    {
        print_color = BFCOL;
        backgr_color = 7;
        cursor (xcpos, ycpos);
        c = getch ();
        if (c == 13)
            break;
        if (c == 27)
            goto ret;
        if (c == 8 && i > 0)
        {
            print_color = backgr_color;
            i--;
            image4 = malloc (imagesize (xcpos, ycpos - 8, 400, ycpos + 17));
            getimage (xcpos, ycpos - 8, 370, ycpos + 17, image4);
            identkey (filename[i]);
            putimage (xcpos, ycpos - 8, image4, 0);
            free (image4);
            print_color = BFCOL;
            filename[i] = '\0';
            i--;
            continue;
        }
        if (c != 8 && c != 83)
        {
            filename[i] = c;
            filename[i + 1] = '\0';
            identkey (c);
        }
    }
    save_flag = 1;
    
ret:
    putimage (200, 210, image3, 0);
    free (image3);
    bar (250, 435, 360, 460);
    for (i = 0; i < 8; i++)
    {
        if (filename[i] == '.')
            break;
    }
    filename[i] = '\0';
    print_hin_str (filename, 35, 16);
    print_color = 0;
    xcpos = xc;
    ycpos = yc;
    return;
}
