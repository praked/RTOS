### Pranav Kedia
### CC by 4.0

### How To Run:

1. First execute the server and than any other client.

### Performance Data

Number of Clients running | Time (in microseconds) | Time Range (in microseconds)
------------ | ------------- | -------------
1 | 47 | 43 - 69
2 | 67 | 41 - 89
3 | 83 | 45 - 353
4 | 117 | 42 - 349
5 | 222 | 66 - 476

The range mentioned above is the one occuring the most. And the value picked is the one which is occuring nearly the most. But sometimes the value reached in near 45000 microsecond.

#### How was data measured?

1. All programs were running parallely and each program was sending a command in an infinite loop.
2. One by one each program was stopped to decrease the number of parallel processes.
3. The recorded time of the stopped client were recorded.

The code uploaded does not do the same. It ask the user to give some input that should be sent to the server.
