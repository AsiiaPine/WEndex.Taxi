# WEndex.Taxi

This project is a backend for the taxi ordering application

To use it:

- download all files
- compile in your lovely programm
- Run main function
___
To use the system you can also change .txt files and put here yours data.

Map.txt contains coordinates of buildings in Innopolis City, their address( St. Build. City Area), and keys.
Keys are used for simplicity searching the buildings. But this feature is not working yet.

Passengers.txt contains all info about users and is used for LogIn method. 
Drivers.txt-same as Passengers.txt

Orders.txt contains all the orders, which was make for all the time

CurrentOrders.txt contains orders, which are not closed, after what they are overwritten to Order.txt

______
When any app is connecting to the system, it is working with data throughout PassengerGateway or DriverGateway. 

###  
PassengerGateway contains methods:
- LogIn (user write username and password in the app and the app send it to the method, which is searching the Passenger in the memory. Success: the Gateway accept the pointer of the passenger and starnts working with the data connected to it. Wrong password/username: the system writes "Wrong user name or password")
- SignIn (user writes username, email and password. New  passenger created and writes to data)
- LogOut
- OrderTheRide (system catch current time and gets two addresses)
- SeeOrderHistory(writes all orders of the user)
