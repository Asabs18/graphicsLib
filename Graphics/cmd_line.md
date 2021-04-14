# ACL Command Line Parser:

## command line design:

- the command line will accept a "/" or a "-"
- and / or a - preceding a question mark will print the following:

### Key:  
[/P Row, Col] - a point on the console [/P2] & [/P3] can be used if more than one point is need  
[/C char] - any character input  
[/U] - draws a char with underline  
[/B] - draws the char(s) bold  
[/FG | /BG predefined color] - takes a predefined color for foreground or background  
[/FGrgb | /BGrgb rgb color]- takes a rgb color for foreground or background  
[/S str] - passes in a string  
[/R corner1,corner2,corner3,corner4,horLine,vertLine] - defines the corners of a fancy rect  
[/I] - if used, a concentric shape will have a space every other shape  
[/T time] - inputs time in milliseconds to wait between each repetition in a function  

```c
/DRAWCHAR [/P Row Col] [/C char] - Draws a char at a specified spot  
          [/U] [/B] [/FG Blue|Red|...] [/BGrgb r g b]      
    
/DRAWSTRING [/P Row Col] [/S str] - draws a string at a specified spot  
            [/U] [/B] [/FG Blue|Red|...] [/BGrgb r g b] 

/DRAWLINE [/P Row Col] [/P2 Row Col] - draws a line from point 1 to point 2  
          [/C char] [/U] [/B] [/FG Blue|Red|...] [/BGrgb r g b] 

/DRAWRECT  [/P Row Col] [/P2 Row Col] - draws a normal rect using only 1 character *P = up left P2 = up Right*  
           [/C char] [/U] [/B] 
           [/FG Blue|Red|...] [/BGrgb r g b]

/FILLRECT [/P Row Col] [/P2 Row Col] - fills a rectangle *P = up left P2 = up Right* fills a rect by setting foreground color to background color and drawing colored boxes inside the specified area   
          [/U] [/B] [/FG Blue|Red|...]  
          [/BGrgb r g b] [/C char]

/DRAWRECTFANCY [/P Row Col] [/P2 Row Col] - draws a Rect including extended ascii characters *P = up left P2 = up Right*  
              [/U] [/B] [/FG Blue|Red|...] [/BGrgb r g b] 
              [/R vertLine horLine upLeft upRight downLeft downRight]

/DRAWCONCENTRICRECT [/I] [/P Row Col] - draws a concentric rectangle *P = up left P2 = up Right*  
                    [/P2 Row Col] [/U] [/B] [/FG Blue|Red|...] [/BGrgb r g b]  
                    [/C char]

/DRAWTRIANGLE [/P Row Col] [/P2 Row Col] - draws a triangle *all 3 points = triangle points, function connects them, no order needed*  
              [/P3 Row Col] [/U] [/B] [/FG Blue|Red|...] [/BGrgb r g b] 
              [/C char]

/DRAWCONCENTRICTRIANGLE [/I] [/P Row Col] - draws a concentric triangle *all 3 points = triangle points, function connects them, no order needed*  
                        [/P2 Row Col] [/P3 Row Col]  
                        [/U] [/B] [/FG Blue|Red|...] [/BGrgb r g b]  [/C char]

/FILLTRIANGLE [/P Row Col] [/P2 Row Col] - fills a triangle *all 3 points = triangle points, function connects them, no order needed*  
              [/P3 Row Col] [/U] [/B] [/FG Blue|Red|...] [/BGrgb r g b]   
              [/C char]

/DRAWSMALLCUBE [/P Row Col] [/U] [/B] [/FG Blue|Red|...] [/BGrgb r g b]  - draws a small cube *2 spaces*  

/RAINBOW [/U] [/B] [/FG Blue|Red|...] [/BGrgb r g b]  - draws a rainbow pattern on the whole screen  

/SPIRAL [/U] [/B] [/FG Blue|Red|...] [/BGrgb r g b]  [/C char] - draws a spiral on the whole screen  

/DRUNKWALK [/U] [/B] [/FG Blue|Red|...] [/BGrgb r g b]  [/C char] - has a character walk randomly around the screen  
           [/T time]

/MOVINGLINEV [/U] [/B] [/FG Blue|Red|...] [/BGrgb r g b]  [/C char] - draws a moving line across the screen vertical  
             [/T time]

/MOVINGLINEH [/U] [/B] [/FG Blue|Red|...] [/BGrgb r g b]  [/C char] - draws a moving line across the screen horizontal  
             [/T time]

/GRID [/U] [/B] [/FG Blue|Red|...] [/BGrgb r g b]  [/C char] - draws a grid pattern on the screen   
```

-The conSize will be preset but if you want to change it /initConsole [conSize=Row,Col] [fontSize=Row,Col]

-If a user enters a function i.e drawChar then /? or /help the console will print a single instruction line like below

DRAWCHAR [Point Row Col] [/C char] [/U] [/B] [/FG Blue|Red|...] [/BGrgb r g b] - Draws a char at a specified spot

-If a function is entered missing any parameters then the preset defaults for that parameter will be filled in.

-If a function is entered with an invalid call a short error message will be printed

-When a valid function is entered Graphics Demo will run that function resulting in a short demo of the function

### Console_t:
- initConsole
- drawString
- drawChar
- drawLine
- drawSmallCube
- drawRect
- drawFancyRect
- fillRect
- freeConsole
- getConsoleSize
- VdrawLine
- HdrawLine
- drawDiagonalLine
### Special Effects/Demo:
- Spiral
- Rainbow
- MovingLine(v/h)
- grid
- drunkWalk
- drawConcentricRect
- drawConcentricTriangle

### App:
- drawTriangle
- fillTriangle

### Defaults:
- point_s = 10,10
- underline = false
- bold = false
- Frgb = blue
- Brgb = blue
- char = "/0"
- conSize = 100, 50

### Colors:
*These all work for foreground and background*
- black  
- red  
- green  
- yellow  
- blue  
- magenta  
- cyan  
- white  

### Short Hands for Ascii characters:
- LIGHT_SHADE = LS
- MEDIUM_SHADE = MS
- DARK_SHADE = DS
- DOUBLE_LINE_DOWNLEFT_CORNER = DLDC
- DOUBLE_LINE_HOR = DLH
- DOUBLE_LINE_VERT = DLV
- DOUBLE_LINE_UPRIGHT_CORNER = DLURC
- DOUBLE_LINE_UPLEFT_CORNER = DLULC
- DOUBLE_LINE_DOWNRIGHT_CORNER = DLDRC
- DOUBLE_LINE_DOWN_HOR = DLDH
- DOUBLE_LINE_FOUR_PRONG = DLFP
- DOUBLE_LINE_RIGHT_VERT = DLRV
- DOUBLE_LINE_LEFT_VERT = DLLV
- DOUBLE_LINE_UP_HOR = DLUH
- LINE_VERT = LV
- LINE_VERT_LEFT_PRONG = LVLP
- LINE_UP_RIGHT_CORNER = LURC
- LINE_DOWN_LEFT_CORNER = LDLC
- LINE_DOWN_RIGHT_CORNER = LDRC
- LINE_UP_LEFT_CORNER = LULC
- LINE_HOR_UP_PRONG = LHUP
- LINE_HOR_DOWN_PRONG = LHDP
- LINE_VERT_RIGHT_PRONG = LVRP
- LINE_HOR = LH
- LINE_FOUR_PRONG = LFP
- FULL_BLOCK = FB
- LOWER_HALF_BLOCK = LOHB
- LEFT_HALF_BLOCK = LEHB
- RIGHT_HALF_BLOCK = RHB
- UPPER_HALF_BLOCK = UHB
- SMALL_BLOCK = SB


/DRAWRECTFANCY /P 1 1 /P2 10 10 /FG blue /BG blue /R LV LH LULC LURC LDLC LDRC 
/DRAWCONCENTRICRECT /I /P 1 1 /P2 10 10 /FG Red /BG Red /C "\0"
/DRUNKWALK /FG Green /BG Green /C 0 /T 100

```c

///HELPER FUNCTIONS///

pointCheck(){
    if(strcmp("/P", argv[arg]) == 0 || strcmp("/P2", argv[arg]) == 0 || strcmp("/P3", argv[arg]) == 0){
        if(arg + 2 < argc){
            row = arg + 1;
            col = arg + 2;
            arg+=2
        }
        else{
            error();
        }
    }
}
charCheck(){
    if(strcmp("/C", argv[arg]) == 0){
        if(arg + 1 < argc){
           char = arg + 1;
           arg++;
        }
        else{
            error();
        }
    }
}
underlineCheck(){
    if(strcmp("/U", argv[arg]) == 0){
        if(arg + 1 < argc){
            underline = true;
            arg++;
        }
        else{
            error();
        }
    }
}

boldCheck(){
    if(strcmp("/B", argv[arg]) == 0){
        if(arg + 1 < argc){
            bold = true;
            arg++;
        }
        else{
            error();
        }
    }
}

predefColorCheck(){
    if(strcmp("/FG", argv[arg]) == 0){
        if(arg + 1 < argc){
            if(isValidColor){
                foreground = arg + 1;
                arg++;
            }
            else{
                error();
            }
        }
        else{
            error();
        }
    }
    else if("/BG", argv[arg]) == 0){
        if(arg + 1 < argc){
            if(isValidColor){
                foreground = arg + 1;
                arg++;
            }
            else{
                error();
            }
        }
        else{
            error();
        }
    }
}

rgbColorCheck(){
    if(strcmp("/FGrgb", argv[arg]) == 0){
        if(arg + 3 < argc){
            if(isValidRgb){
                fR = arg + 1;
                fG = arg + 2;
                fB = arg + 3;
                arg+=3;
            }
            else{
                error();
            }
        }
        else{
            error();
        }
    }
    if(strcmp("/BGrgb", argv[arg]) == 0){
        if(arg + 3 < argc){
            if(isValidRgb){
                bR = arg + 1;
                bG = arg + 2;
                bB = arg + 3;
                arg+=3;
            }
            else{
                error();
            }
        }
        else{
            error();
        }
    }
}

strCheck(){
    if(strcmp("/S", argv[arg]) == 0){
        if(arg + 1 < argc){
            str = arg + 1;
            arg++;
        }
        else{
            error();
        }
    }
}

rectCheck(){
    if(strcmp("/R", argv[arg]) == 0){
        if(arg + 6 < argc){
            for(int i = 1; i < 6 i++){
                if(strlen(argv[arg + 1]) != 1){
                    error();
                }
            }
            vertLine = arg + 1;
            horLine = arg + 2;
            upLeft = arg + 3;
            upRight = arg + 4;
            downLeft = arg + 5;
            downRight = arg + 6;
            arg + 6;
        }
        else{
            error();
        }
    }
}

spacesCheck(){
    if(strcmp("/I", argv[arg]) == 0){
        if(arg + 1 < argc){
            isSpaces = true;
            arg++;
        }
        else{
            error();
        }
    }
}

timeCheck(){
    if(strcmp("/T", argv[arg]) == 0){
        if(arg + 1 < argc){
            if(isDigit(arg + 1)){
                time = arg + 1;
            }
            arg++;
        }
        else{
            error();
        }
    }
}

switch(char* switch, int argAdditions){
    if(strcmp(switch, argv[arg] + argAdditions) == 0){
        return true;
    }
    return false;
}

///PARSER///
for(int arg = 1; arg < argc; arg++){
    if(switch("/", 0) || switch("-", 0)){
        if(switch("drawchar", 1){
            while(arg + 1 < argc){
                arg++;
                pointCheck();
                charCheck();
                underlineCheck();
                boldCheck();
                predefColorCheck();
                rgbColorCheck();
            }
        }
        else if(switch("drawstring", 1){
            while(arg + 1 < argc){
                arg++;
                pointCheck();
                strCheck();
                underlineCheck();
                boldCheck();
                predefColorCheck();
                rgbColorCheck();
            }
        }
        else if(switch("drawline", 1){
            while(arg + 1 < argc){
                arg++;
                pointCheck();
                charCheck();
                underlineCheck();
                boldCheck();
                predefColorCheck();
                rgbColorCheck();
            }
        }
        else if(switch("drawrect", 1){
            while(arg + 1 < argc){
                arg++;
                pointCheck();
                charCheck();
                underlineCheck();
                boldCheck();
                predefColorCheck();
                rgbColorCheck();
            }
        }
        else if(switch("drawrectfancy", 1){
            while(arg + 1 < argc){
                arg++;
                pointCheck();
                underlineCheck();
                boldCheck();
                predefColorCheck();
                rgbColorCheck();
                rectCheck();
            }
        }
        else if(switch("drawconcentricrect", 1){
            while(arg + 1 < argc){
                arg++;
                pointCheck();
                charCheck();
                spacesCheck();
                underlineCheck();
                boldCheck();
                predefColorCheck();
                rgbColorCheck();
            }
        }
        else if(switch("drawtriangle", 1){
            while(arg + 1 < argc){
                arg++;
                pointCheck();
                charCheck();
                underlineCheck();
                boldCheck();
                predefColorCheck();
                rgbColorCheck();
            }
        }
        else if(switch("drawconcentrictriangle", 1){
            while(arg + 1 < argc){
                arg++;
                pointCheck();
                charCheck();
                spacesCheck();
                underlineCheck();
                boldCheck();
                predefColorCheck();
                rgbColorCheck();
            }
        }
        else if(switch("drawsmallcube", 1){
            while(arg + 1 < argc){
                arg++;
                pointCheck();
                underlineCheck();
                boldCheck();
                predefColorCheck();
                rgbColorCheck();
            }
        }
        else if(switch("fillrect", 1){
            while(arg + 1 < argc){
                arg++;
                pointCheck();
                charCheck();
                underlineCheck();
                boldCheck();
                predefColorCheck();
                rgbColorCheck();
            }
        }
        else if(switch("filltriangle", 1){
            while(arg + 1 < argc){
                arg++;
                pointCheck();
                charCheck();
                underlineCheck();
                boldCheck();
                predefColorCheck();
                rgbColorCheck();
            }
        }
        else if(switch("rainbow", 1){
            while(arg + 1 < argc){
                arg++;
                underlineCheck();
                boldCheck();
                predefColorCheck();
                rgbColorCheck();
            }
        }
        else if(switch("spiral", 1){
            while(arg + 1 < argc){
                arg++;
                underlineCheck();
                charCheck();
                boldCheck();
                predefColorCheck();
                rgbColorCheck();
            }
        }
        else if(switch("drunkwalk", 1){
            while(arg + 1 < argc){
                arg++;
                charCheck();
                underlineCheck();
                boldCheck();
                predefColorCheck();
                rgbColorCheck();
                timeCheck();
            }
        }
        else if(switch("movinglinev", 1){
            while(arg + 1 < argc){
                arg++;
                underlineCheck();
                boldCheck();
                predefColorCheck();
                rgbColorCheck();
                timeCheck();
            }
        }
        else if(switch("movinglineh", 1){
            while(arg + 1 < argc){
                arg++;
                underlineCheck();
                boldCheck();
                predefColorCheck();
                rgbColorCheck();
                timeCheck();
            }
        }
        else if(switch("grid", 1){
            while(arg + 1 < argc){
                arg++;
                charCheck();
                underlineCheck();
                boldCheck();
                predefColorCheck();
                rgbColorCheck();
            }
        }
    }
}
```

### Helper Functions(need to write):
- isValidColor
- isValidRgb
- error