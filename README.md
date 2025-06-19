# PraktikumAUTOSAR
This is the repository for a practical exercise to create an Indicator-Lights-System using AUTOSAR.

# Pictures of the architecture in dSPACE SystemDesk
General Architecture:  
![RootComposition](https://github.com/user-attachments/assets/bf357a6a-6e1a-4ad2-b0d7-52ce0a2e9ffa)


Archtitecture of central ECU:
![ZSE_Composition](https://github.com/user-attachments/assets/9ca3b0e4-3738-4657-86f9-066aa25271ad)

# Integration into Tresos Template
- Copy Code into corresponding runnable
- Delete the status return, because runnables have return void
- Change name of the Read/Write functions to the actual RTE function names

# Build and Run
- make clean
- make all : build the project
- make test : build and run all tests

./program to run the main program (currently only one iteration)
./run_tests to run all tests 