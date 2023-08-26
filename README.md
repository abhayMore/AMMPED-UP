# AMMPED - UP
Clone of the classic Bomberman game, made in C++, SFML & TGUI.

v1.0 : https://youtu.be/dV3PnYL2-nw

v2.0 : https://youtu.be/P5EFfVkfIMc

If you want to open this in Visual Studio, follow these steps :
Note : The project is in 64 bit.
Libraries are needed to run the projects
SFML 
1. Download SFML for Visual Studio 2022 (64 Bit), SFML C++15 Visual Studio 2017 64 Bit : https://www.sfml-dev.org/files/SFML-2.5.1-windows-vc15-64-bit.zip.
2. Extract the zip file and rename the extracted folder as SFML.
3. Make a directory named "Dependencies" (Case sensitive) inside the AMMPED-UP directory where all other directories are present.
4. Copy the renamed SFML folder and paste it inside the Dependencies directory.
5. Copy the contents of bin folder inside SFML folder and paste it inside the AMMPED-UP directory where all other directories are present.(dynamic libraries(dlls)

Do the same step again for TGUI :
1. Download TGUI for Visual Studio 2022 (64 Bit), TGUI Visual Studio (2017-2022) 64 Bit : https://github.com/texus/TGUI/releases/download/v0.9.5/TGUI-0.9.5-VisualStudio-64bit-for-SFML-2.5.1.zip.
2. Extract the zip file and rename the extracted folder as TGUI.
3. Copy the renamed TGUI folder and paste it inside the Dependencies directory.(Made in previous step)
4. Copy the contents of bin folder inside TGUI folder and paste it inside the AMMPED-UP directory where all other directories are present.(dynamic libraries(dlls)

For the mongocxx setup follow this tutorial:
Tutorial website : https://www.mongodb.com/developer/products/mongodb/getting-started-mongodb-cpp/
1. After following the tutorial, generated folders(two), paste both the folders (mongo-c-driver & mongo-cxx-driver) inside the Dependencies folder.
2. Copy the contents of the bin folders inside both the folders(mongo-c-driver & mongo-cxx-driver) and paste it inside the AMMPED-UP directory where all other directories are present.(dynamic libraries(dlls)
3. You are done, open the solution file and run the Project.

This is how it should look inside the repo with the Dependencies Folder & all the DLLs from SFML, TGUI & Mongocxx.

![output](https://github.com/abhayMore/AMMPED-UP/blob/master/ReadMeFiles/OverallFolderView.png)

This is how it should look inside the Dependencies Folder.

![output](https://github.com/abhayMore/AMMPED-UP/blob/master/ReadMeFiles/FinalDependencies.png)
