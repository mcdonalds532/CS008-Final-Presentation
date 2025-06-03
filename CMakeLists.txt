cmake_minimum_required(VERSION 3.14)
project(CS008_Final_Presentation)

include(FetchContent)
FetchContent_Declare(
        malena
        GIT_REPOSITORY https://github.com/daversmith/Malena.git
        GIT_TAG v0.2.5
)
FetchContent_MakeAvailable(malena)

add_executable(CS008_Final_Presentation main.cpp
        ApplicationSelector.cpp
        ApplicationSelector.h
        FiniteStateMachine.cpp
        FiniteStateMachine.h
        Applications/Autocorrect/AutocorrectApp.cpp
        Applications/Autocorrect/AutocorrectApp.h
        Applications/Autocorrect/FileReader.cpp
        Applications/Autocorrect/FileReader.h
        Applications/Autocorrect/CompareWords.h
        Applications/Autocorrect/Heap.cpp
        Applications/Autocorrect/Heap.h
        Applications/Autocorrect/Word.cpp
        Applications/Autocorrect/Word.h
        Applications/Autocorrect/WordSort.cpp
        Applications/Autocorrect/WordSort.h
        Applications/Minesweeper/MinesweeperModel.cpp
        Applications/Minesweeper/MinesweeperModel.h
        Applications/Minesweeper/MinesweeperNode.cpp
        Applications/Minesweeper/MinesweeperNode.h
        Applications/Minesweeper/MinesweeperApp.cpp
        Applications/Minesweeper/MinesweeperApp.h
        Applications/Minesweeper/Backtracking.cpp
        Applications/Minesweeper/Backtracking.h
        "Applications/Sliding Puzzle/Node.h"
        "Applications/Sliding Puzzle/CompareNodes.h"
        "Applications/Sliding Puzzle/SubGoal.h"
        "Applications/Sliding Puzzle/Model.cpp"
        "Applications/Sliding Puzzle/Model.h"
        "Applications/Sliding Puzzle/SlidingPuzzleApp.cpp"
        "Applications/Sliding Puzzle/SlidingPuzzleApp.h"
        "Applications/Sliding Puzzle/SlidingPuzzleSolver.cpp"
        "Applications/Sliding Puzzle/SlidingPuzzleSolver.h"
)

target_link_libraries(CS008_Final_Presentation PRIVATE Malena::Malena)