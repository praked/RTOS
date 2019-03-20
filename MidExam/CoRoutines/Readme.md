# Co-Routines 

Coroutines are generalization of subroutines. They are used for cooperative multitasking where a process voluntarily yield (give away) control periodically or when idle in order to enable multiple applications to be run simultaneously. The difference between coroutine and subroutine is :

-Unlike subroutines, coroutines have many entry points for suspending and resuming execution. Coroutine can suspend its execution and transfer control to other coroutine and can resume again execution from the point it left off.

-Unlike subroutines, there is no main function to call coroutines in particular order and coordinate the results. Coroutines are cooperative that means they link together to form a pipeline. One coroutine may consume input data and send it to other which process it. Finally there may be a coroutine to display result.

# Co-Routines in Python 
# Implementation

The co-routine is implemented using Mutex locks, which make sure that only one portion of program is being executed. Provided this guarantee, there is no need to consider race conditions between these portions of code. Hence simple global variables can be used for data transfer.

# Simple co-routine test
The output of the simple co-routine test is expected as follows,
```
print_mesg co-routine #0 recieved message A
print_digit co-routine #4 recieved message 1
print_mesg co-routine #1 recieved message B
print_digit co-routine #3 recieved message 2
print_mesg co-routine #2 recieved message C
print_mesg co-routine #1 recieved message X
print_digit co-routine #3 recieved message 3
print_mesg co-routine #2 recieved message Z
```

# Snake and ladder game
Following output was obtained for snake and ladder game
```
Player 0 at 0 playing a turn
        --Rolled a 1
        --New location is 1
Player 1 at 0 playing a turn
        --Rolled a 3
        --New location is 3
Player 2 at 0 playing a turn
        --Rolled a 4
        --New location is 4
Player 3 at 0 playing a turn
        --Rolled a 5
        --Climbed a ladder_s
        --New location is 20
Player 0 at 1 playing a turn
        --Rolled a 1
        --New location is 2
Player 1 at 3 playing a turn
        --Rolled a 1
        --New location is 4
Player 2 at 4 playing a turn
        --Rolled a 3
        --New location is 7
Player 3 at 20 playing a turn
        --Rolled a 3
        --New location is 23
Player 0 at 2 playing a turn
        --Rolled a 3
        --Climbed a ladder_s
        --New location is 20
Player 1 at 4 playing a turn
        --Rolled a 2
        --Climbed a ladder_s
        --New location is 14
Player 2 at 7 playing a turn
        --Rolled a 5
        --New location is 12
Player 3 at 23 playing a turn
        --Rolled a 5
        --New location is 28
Player 0 at 20 playing a turn
        --Rolled a 6
        --Met a snake
        --New location is 10
Player 1 at 14 playing a turn
        --Rolled a 1
        --Climbed a ladder_s
        --Climbed a ladder_s
        --Met a snake
        --Climbed a ladder_s
        --New location is 14
Player 2 at 12 playing a turn
        --Rolled a 5
        --Climbed a ladder_s
        --New location is 76
Player 3 at 28 playing a turn
        --Rolled a 4
        --New location is 32
Player 0 at 10 playing a turn
        --Rolled a 6
        --New location is 16
Player 1 at 14 playing a turn
        --Rolled a 1
        --Climbed a ladder_s
        --Climbed a ladder_s
        --Met a snake
        --Climbed a ladder_s
        --New location is 14
Player 2 at 76 playing a turn
        --Rolled a 3
        --New location is 79
Player 3 at 32 playing a turn
        --Rolled a 4
        --Climbed a ladder_s
        --Met a snake
        --Climbed a ladder_s
        --New location is 14
Player 0 at 16 playing a turn
        --Rolled a 2
        --Met a snake
        --New location is 1
Player 1 at 14 playing a turn
        --Rolled a 5
        --New location is 19
Player 2 at 79 playing a turn
        --Rolled a 3
        --New location is 82
Player 3 at 14 playing a turn
        --Rolled a 4
        --Met a snake
        --New location is 1
Player 0 at 1 playing a turn
        --Rolled a 2
        --New location is 3
Player 1 at 19 playing a turn
        --Rolled a 3
        --New location is 22
Player 2 at 82 playing a turn
        --Rolled a 4
        --New location is 86
Player 3 at 1 playing a turn
        --Rolled a 5
        --Climbed a ladder_s
        --New location is 14
Player 0 at 3 playing a turn
        --Rolled a 1
        --New location is 4
Player 1 at 22 playing a turn
        --Rolled a 6
        --New location is 28
Player 2 at 86 playing a turn
        --Rolled a 2
        --New location is 88
Player 3 at 14 playing a turn
        --Rolled a 1
        --Climbed a ladder_s
        --Climbed a ladder_s
        --Met a snake
        --Climbed a ladder_s
        --New location is 14
Player 0 at 4 playing a turn
        --Rolled a 6
        --New location is 10
Player 1 at 28 playing a turn
        --Rolled a 6
        --New location is 34
Player 2 at 88 playing a turn
        --Rolled a 4
        --New location is 92
Player 3 at 14 playing a turn
        --Rolled a 6
        --New location is 20
Player 0 at 10 playing a turn
        --Rolled a 6
        --New location is 16
Player 1 at 34 playing a turn
        --Rolled a 4
        --New location is 38
Player 2 at 92 playing a turn
        --Rolled a 2
        --New location is 94
Player 3 at 20 playing a turn
        --Rolled a 2
        --New location is 22
Player 0 at 16 playing a turn
        --Rolled a 5
        --New location is 21
Player 1 at 38 playing a turn
        --Rolled a 4
        --New location is 42
Player 2 at 94 playing a turn
        --Rolled a 4
        --New location is 98
Player 3 at 22 playing a turn
        --Rolled a 2
        --Climbed a ladder_s
        --New location is 77
Player 0 at 21 playing a turn
        --Rolled a 5
        --Met a snake
        --New location is 10
Player 1 at 42 playing a turn
        --Rolled a 1
        --New location is 43
Player 2 at 98 playing a turn
        --Rolled a 6
        --New location is 104
Player 2 Wins!
Player 3 at 77 playing a turn
        --Rolled a 4
        --New location is 81
Player 0 at 10 playing a turn
        --Rolled a 1
        --Climbed a ladder_s
        --New location is 23
Player 1 at 43 playing a turn
        --Rolled a 6
        --New location is 49
Player 3 at 81 playing a turn
        --Rolled a 5
        --New location is 86
Player 0 at 23 playing a turn
        --Rolled a 1
        --Climbed a ladder_s
        --New location is 77
Player 1 at 49 playing a turn
        --Rolled a 4
        --New location is 53
Player 3 at 86 playing a turn
        --Rolled a 1
        --New location is 87
Player 0 at 77 playing a turn
        --Rolled a 2
        --New location is 79
Player 1 at 53 playing a turn
        --Rolled a 3
        --New location is 56
Player 3 at 87 playing a turn
        --Rolled a 1
        --New location is 88
Player 0 at 79 playing a turn
        --Rolled a 4
        --New location is 83
Player 1 at 56 playing a turn
        --Rolled a 5
        --New location is 61
Player 3 at 88 playing a turn
        --Rolled a 5
        --New location is 93
Player 0 at 83 playing a turn
        --Rolled a 3
        --New location is 86
Player 1 at 61 playing a turn
        --Rolled a 1
        --New location is 62
Player 3 at 93 playing a turn
        --Rolled a 6
        --Met a snake
        --New location is 9
Player 0 at 86 playing a turn
        --Rolled a 2
        --New location is 88
Player 1 at 62 playing a turn
        --Rolled a 4
        --New location is 66
Player 3 at 9 playing a turn
        --Rolled a 1
        --New location is 10
Player 0 at 88 playing a turn
        --Rolled a 1
        --New location is 89
Player 1 at 66 playing a turn
        --Rolled a 3
        --New location is 69
Player 3 at 10 playing a turn
        --Rolled a 4
        --New location is 14
Player 0 at 89 playing a turn
        --Rolled a 6
        --New location is 95
Player 1 at 69 playing a turn
        --Rolled a 2
        --New location is 71
Player 3 at 14 playing a turn
        --Rolled a 1
        --Climbed a ladder_s
        --Climbed a ladder_s
        --Met a snake
        --Climbed a ladder_s
        --New location is 14
Player 0 at 95 playing a turn
        --Rolled a 4
        --Met a snake
        --New location is 9
Player 1 at 71 playing a turn
        --Rolled a 3
        --New location is 74
Player 3 at 14 playing a turn
        --Rolled a 2
        --New location is 16
Player 0 at 9 playing a turn
        --Rolled a 6
        --Climbed a ladder_s
        --Climbed a ladder_s
        --Met a snake
        --Climbed a ladder_s
        --New location is 14
Player 1 at 74 playing a turn
        --Rolled a 3
        --New location is 77
Player 3 at 16 playing a turn
        --Rolled a 5
        --New location is 21
Player 0 at 14 playing a turn
        --Rolled a 3
        --Climbed a ladder_s
        --New location is 76
Player 1 at 77 playing a turn
        --Rolled a 2
        --New location is 79
Player 3 at 21 playing a turn
        --Rolled a 2
        --New location is 23
Player 0 at 76 playing a turn
        --Rolled a 5
        --New location is 81
Player 1 at 79 playing a turn
        --Rolled a 6
        --Met a snake
        --Met a snake
        --New location is 20
Player 3 at 23 playing a turn
        --Rolled a 6
        --New location is 29
Player 0 at 81 playing a turn
        --Rolled a 3
        --New location is 84
Player 1 at 20 playing a turn
        --Rolled a 5
        --New location is 25
Player 3 at 29 playing a turn
        --Rolled a 6
        --New location is 35
Player 0 at 84 playing a turn
        --Rolled a 3
        --New location is 87
Player 1 at 25 playing a turn
        --Rolled a 2
        --New location is 27
Player 3 at 35 playing a turn
        --Rolled a 3
        --New location is 38
Player 0 at 87 playing a turn
        --Rolled a 1
        --New location is 88
Player 1 at 27 playing a turn
        --Rolled a 4
        --New location is 31
Player 3 at 38 playing a turn
        --Rolled a 3
        --Climbed a ladder_s
        --New location is 62
Player 0 at 88 playing a turn
        --Rolled a 4
        --New location is 92
Player 1 at 31 playing a turn
        --Rolled a 3
        --New location is 34
Player 3 at 62 playing a turn
        --Rolled a 4
        --New location is 66
Player 0 at 92 playing a turn
        --Rolled a 4
        --New location is 96
Player 1 at 34 playing a turn
        --Rolled a 3
        --New location is 37
Player 3 at 66 playing a turn
        --Rolled a 6
        --New location is 72
Player 0 at 96 playing a turn
        --Rolled a 6
        --New location is 102
Player 0 Wins!
Player 1 at 37 playing a turn
        --Rolled a 1
        --New location is 38
Player 3 at 72 playing a turn
        --Rolled a 5
        --New location is 77
Player 1 at 38 playing a turn
        --Rolled a 4
        --New location is 42
Player 3 at 77 playing a turn
        --Rolled a 2
        --New location is 79
Player 1 at 42 playing a turn
        --Rolled a 5
        --New location is 47
Player 3 at 79 playing a turn
        --Rolled a 3
        --New location is 82
Player 1 at 47 playing a turn
        --Rolled a 1
        --New location is 48
Player 3 at 82 playing a turn
        --Rolled a 6
        --New location is 88
Player 1 at 48 playing a turn
        --Rolled a 2
        --Climbed a ladder_s
        --New location is 72
Player 3 at 88 playing a turn
        --Rolled a 1
        --New location is 89
Player 1 at 72 playing a turn
        --Rolled a 1
        --New location is 73
Player 3 at 89 playing a turn
        --Rolled a 3
        --New location is 92
Player 1 at 73 playing a turn
        --Rolled a 5
        --Met a snake
        --New location is 30
Player 3 at 92 playing a turn
        --Rolled a 4
        --New location is 96
Player 1 at 30 playing a turn
        --Rolled a 6
        --Climbed a ladder_s
        --Met a snake
        --Climbed a ladder_s
        --New location is 14
Player 3 at 96 playing a turn
        --Rolled a 1
        --New location is 97
Player 1 at 14 playing a turn
        --Rolled a 2
        --New location is 16
Player 3 at 97 playing a turn
        --Rolled a 4
        --New location is 101
Player 3 Wins!
Player 1 at 16 playing a turn
        --Rolled a 1
        --Climbed a ladder_s
        --New location is 76
Player 1 at 76 playing a turn
        --Rolled a 4
        --Climbed a ladder_s
        --New location is 97
Player 1 at 97 playing a turn
        --Rolled a 6
        --New location is 103
Player 1 Wins!
Winners
 1st place : 2
 2nd place : 0
 3rd place : 3
 4th place : 1
Total turnaround time: 31981
```
# Performance

The snake and ladder game was run several times to get the running time with following results:

| # Run | Time taken (uS)
|-----------|---------|
| 1         |  38242  |
| 2         |  31981  |
| 3         |  13939  |
| 4         |  41962  |
| 5         |  30889  |
