# Akshar - Hindi (Devanagari) Text Editor

A DOS-based Hindi text editor written in C, designed to provide native Hindi text editing capabilities without requiring additional font installations.

## Overview

Akshar is a pioneering Hindi text editor developed in 1999 for DOS systems. At a time when Hindi text editors were primarily available for Windows and required additional font installations, Akshar provided a standalone solution for Hindi text editing in DOS environments.

## Features

- Native Hindi (Devanagari) text input and display
- DOS-based interface with graphics support
- Custom font rendering system
- File save/load functionality with `.hif` extension
- Keyboard mapping for Hindi character input
- Built-in cursor management and text navigation

## Technical Details

- **Language**: C
- **Platform**: DOS
- **Graphics**: Uses Borland Graphics Interface (BGI)
- **File Format**: Custom `.hif` format for Hindi text files
- **Dependencies**: Borland C++ compiler with graphics libraries

## Authors

- **Ahzam Ali** - Main development and integration
- **Anwar Parvez** - Font design
- **Neeraj Grover** - Character display module

Developed at the Computer Sciences Lab, Department of Electronics and Communication, Faculty of Engineering and Technology, Jamia Millia Islamia, New Delhi.

**Completion Date**: May 16, 1999

## Historical Significance

This project represents an early effort to bring Hindi computing to DOS systems, addressing the lack of native Hindi text editing tools available at the time. The custom font rendering and character mapping system demonstrates innovative approaches to multilingual computing in resource-constrained environments.

## Building and Running

This software was designed for DOS systems with Borland C++ compiler. To compile:

```bash
# Using Borland C++ (historical)
bcc akshar.c -lbgi
```

**Note**: This is legacy software designed for DOS systems. Modern compilation may require compatibility layers or DOS emulators.

## File Structure

- `akshar.c` - Main source code
- `MakingOfAkshar-text.txt` - Original documentation and development notes

## License

This software is released as freeware under the MIT License. You are free to modify and improve the program.

## Contributing

While this is a historical project, contributions for documentation, modernization, or educational purposes are welcome. The original authors encourage improvements and modifications to the software.

## Acknowledgments

Special thanks to the Computer Sciences Lab at Jamia Millia Islamia for providing the development environment and support for this pioneering Hindi computing project.

---

*"In an attempt to do something new we thought of designing a Hindi text editor."* - Original documentation, 1999
