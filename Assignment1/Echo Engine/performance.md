#Pranav Kedia
#CC by 4.0

### Performance Data

Number of Clients running | Time (in microseconds) | Time Range (in microseconds)
------------ | ------------- | -------------
1 | 8 | 8 - 10
2 | 11 | 9 - 15
3 | 13 | 7 - 23
4 | 12 | 9 - 19
5 | 16 | 12 - 24

The range mentioned above is the one occuring the most. And the value picked is the one which is occuring nearly the most. But 
sometimes the value reached in near 100 to 300 microsecond.

### How To Run:

1. First execute the server and than any other client, becuase server is creating the message queue.

#### How was data measured?

1. All programs were running parallely and each program was sending a charecter in an infinite loop.
2. One by one each program was stopped to decrease the number of parallel processes.
3. The recorder clock cycles of the stopped client was observed and the a number was picked in from the range in which most clock cycles appeared.
