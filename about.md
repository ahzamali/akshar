# About Akshar 1.1

## Development Team

**A program by:**
- Ahzam Ali
- Anwar Parvez
- Neeraj Grover

**Developed at:**
Computer Sciences Lab  
Department of Electronics and Communication  
Faculty of Engineering and Technology, Jamia Millia Islamia  
New Delhi - 110025

**Completion Date:** May 16, 1999  
**Copyright:** © Ahzam Ali 1999

The program is freeware - you are free to modify and improve the program in your way.

## Preface

In an attempt to do something new we thought of designing a Hindi text editor. Since DOS based Hindi editors were not available, Hindi editors were available but for Windows based systems that required additional Hindi fonts to be loaded. We are successful in designing it. This is not an ultimate, it requires lot of improvements yet it accomplishes the requirements. We will appreciate your contribution in improving this software.

The program is designed by three of us:
- **Anwar Parvez** - Font design
- **Neeraj Grover** - Character display module  
- **Ahzam Ali** - Rest of the modules and integration

## Technical Overview

### The Font System

Letters in Hindi are not uniform, which posed a lot of difficulty in displaying these characters. Character overlapping is ubiquitous in Hindi script, which compels the design to be complicated, requiring very prudent controls.

Because of the disparate size of characters, they are stored in different formats:
- **Main characters** (ka, kha, etc.) - stored in 8 × 13 pixels format
- **Matras** - stored in 8 × 8 pixels format  
- **Larger matras** (ee ki matras and aa ki matras) - stored in 10 × 19 pixels format

The font files:
- `HSC.HIN` - contains the main characters
- `HSCM.HIN` - contains the matras

At program startup, main characters are loaded into the `hin_main_char` array and matras into the `hin_matra` array from these files.

### Character Display

Two main functions handle character display:
- `hnd_prn()` - for main characters
- `hnd_prn_matra()` - for matras

The `identkey()` function identifies the key pressed and passes parameters to the appropriate display function. Some characters require special treatment and have their displaying routine within the `identkey()` function itself.

### Character Deletion

Characters are deleted in different ways:
- **8 × 13 pixel characters** - deleted by superimposing the image next to the character
- **Matras** - deleted by overwriting them in background color
- **Special matras** (ee ki matras) - deleted along with the letter they're attached to

The `pointer()` function draws the character before the cursor and at the cursor on the status bar to help users understand which character will be deleted.

### Cursor Movement

Cursor movement between characters is not uniform due to the varying character widths. Movement is calculated based on the number of pixels the cursor moved after displaying each character.

## File Management

### Document Storage
Documents are saved as binary files with:
- Header: "Hindi editor"
- File extension: `.hif` (Hindi file)
- Content: English letters corresponding to Hindi characters typed

The document buffer (`*char_str`) temporarily stores content before saving via the `savefile()` function. The `openfile()` function reads files by checking the header and loading the character string into the buffer.

### Key Functions
- `getfilename()` - prompts user for filename
- `new_file()` - clears buffer and reinitializes screen
- `print_massage()` - displays messages on status bar
- `print_hin_str()` - prints Hindi strings on screen

## Screen Management

### Display System
- **Graphics Mode:** 640 × 480 pixels, 16 colors
- **Screen Initialization:** `initscreen()` displays function key assignments
- **Cursor Management:** `cursor()` makes cursor blink until key press
- **Movement Functions:** `moveptrlt()`, `moveptrrt()`, `moveptrup()`, `moveptrdn()`

### Main Program Loop
The program enters a main loop that:
1. Calls `pointer()` to show character context
2. Calls `cursor()` to display blinking cursor
3. Processes key input through switch-case statements
4. Handles function keys and general character input
5. Returns to beginning of loop

## Printing System

The most significant feature is printing Hindi text. The system:
1. Reads the display screen
2. Creates an image in memory
3. Prints in graphics mode

**Printer Support:** Epson-100 dot matrix printer (line printer)
- Image is read in 8-pixel vertical segments from top
- Complete rows of 8 pixels are sent at a time
- Graphics mode commands are used for printer control

## Historical Context

This project represents a pioneering effort in DOS-based Hindi computing, addressing the lack of native Hindi text editing tools available in 1999. The custom font rendering and character mapping system demonstrates innovative approaches to multilingual computing in resource-constrained environments.

---

*We hope this information helps you understand the program. It would be our pleasure to receive your comments and queries on this program.*
