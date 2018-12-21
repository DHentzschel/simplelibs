![Simple Libs](https://i.imgur.com/924RJUe.png)

## SimpleLibs

### A project to simplify developing in C++ STL
If you want to, I would be very thankful if you support my project. ♥

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/7795db8d362f487291406195815840e7)](https://app.codacy.com/app/DHentzschel/simplelibs?utm_source=github.com&utm_medium=referral&utm_content=DHentzschel/simplelibs&utm_campaign=Badge_Grade_Dashboard)
[![Buy me a coffee](https://i.imgur.com/Z1FmtML.png)](https://www.buymeacoffee.com/GRZ9x0mKe)

##### What SimpleLibs is
SimpleLibs is considered to be kind of a framework assisting software developers by providing multiple core classes and functions for developing in C++ (and STL). It can be only used on Windows 10.0.17134.0 or later. 

##### What SimpleLibs NOT is
SimpleLibs is NOT a project for reinventing the wheel. It would not fit in with the author's plans about the whole project.
Also there are _currently_ no plans for porting the source code to Linux. Dear contributors, you're welcome. 

## Projects
### Content
The whole project is rather a project collection containing the following sub projects:
  - SimpleCore and SimpleCore.Test 
  - SimpleGraphics and SimpleGraphics.Test
  - SimpleGui and SimpleGui.Test
  - SimpleMySql and SimpleMySql.Test
  - SimpleNetwork and SimpleNetwork.Test 
  
| Project name | Functionality |
| ------------ | ------------- |
| SimpleCore | Consists of core classes, functions and STL extensions, such as AString, AVector, AList (advanced string/vector/list), file and directory classes, file parsing classes and hash functions. |
| SimpleGraphics | Consists of classes and functions based on GLEW and GLFW. It is considered to get used in 2D graphics development. Classes such as Window, Texture, Audio and Input things are planned. |
| SimpleGui | Consists of classes and functions based on Microsoft's WINAPI for creating windows forms application projects.Classes such as Form, diverse UI elements (Button, TextBox, ...) are planned. |
| SimpleMySql | Consists of classes and functions based on Oracle's MYSQL C Connector such as SqlDatabase and SqlQuery. |
| SimpleNetwork | Consists of classes and functions based on Microsoft's WINAPI to create socket projects using TCP/IP. It contains classes such as (Local)TcpSocket and (Local)TcpServer. |

### Test projects
At the moment, test projects do not contain any tests. Since I wanted to write new tests and switched over to GitHub from GitLab, I ignored the existing test projects in order to create new ones. Also here: Dear contributors, you're welcome.

## Information

### I found bugs! What now?

Well, I'm not surprised, it's a young project. Just pass me a bug report or, if possible, fix the bug and do a pull request.

### License
Copyright © 2018, [Daniel Hentzschel](AUTHOR.md).

Since I do not know how to continue (except further development on these projects), I do NOT grant a commercial use. Use it for private/open source and free projects, you may publish parts or the whole source code but without removing a license and copyright notice.

There may be a licensing model in the future for commercial projects but until then, please follow the license above.

### Installation

SimpleLibs require Windows 10.0.17134.0 or above to compile. I use [Microsoft Visual Studio 2017](https://visualstudio.microsoft.com/) which works fine.
The required language standard is c++17. All versions before are deprecated and not usable.
Also it is required to download and install [MySQL server](https://dev.mysql.com/downloads/windows/installer/8.0.html). It is recommended to use the tested MySQL server version 8.0 or above.

**Important notes:** Both projects SimpleGraphics and SimpleMySql contain x64 binaries (dll and lib).  
If you like to compile for x86, replace them by the files in the directories: _MySQLConnectorC\\lib\\x86\\_, _OpenGL\\glfw-3.2.1\\lib\\x86\\_ and _OpenGL\\glew-2.1.0\\lib\\x86\\_.

### Contributors

As already mentioned you're free and particularly welcome to contribute.  
If you have ideas to implement a feature or fix a bug, please contact me or try it on your own and pass me a pull request.

### Todo

 - _Write Tests_
 - _Continue working on SimpleGraphics_
 - _Maybe implement UDP protocol in for SimpleNetwork_
 - _Continue working on SimpleGui_
 - Add extern LICENSE file
