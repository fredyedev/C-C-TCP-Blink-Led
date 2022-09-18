# C-C-TCP-Blink-Led
A simple TCP Blink-Led (ON/OFF) using GPIO Raspberry Pi.


Use Instructions:

The File ServerTCP_Turn<on,off>.c compile and execute on rbp with the next commands
gcc -o Serverled ServerTCP_Turn<on,off>.c
./Serverled port
port = TCP Port in the interval 7000-8000

The File ClientTCP_Turno<on,off>.c compile and execute on your computer in the same network that rbp with the next commands
gcc -o Clientled ClietTCP_Turno<on,off>.c
Execute:
./Clientled port ip

port = same that the rbp choice
ip = ip address of the rbp- DHCP ip address
For the led use gpio  9 and 11. 
First we execute ejecute TCP Server on rbp
Second we execute the client on the computer(computers)  
Actions Messeges from the client: 
on turn on the led
off turn off the led
exit close the server
adios close the client
