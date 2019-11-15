# Kerberos
These are programs that simulate the operation of Kerberos

## Operating principles of Kerberos
Once per user session:  
1.C → AS: IDC || IDtgs  
2.AS → C: E(KC, Tickettgs)

### Once per type of service:  
3.C → TGS: IDC || IDV || Tickettgs  
4.TGS → C: TicketV

### Once per service session:  
5.C → V: IDC || TicketV

### Where tickets are defined as:  
 Tickettgs = E(Ktgs,[IDC||ADC||IDtgs||TS1||Duration1])  
 TicketV = E(KV,[IDC||ADC||IDV||TS2||Duration2])  
#### and  
  C = client  
  AS = authentication server  
  V = server  
  IDc = identifier user on C  
  IDv = identifier of V  
  Pc = password of user on C  
  ADc  = network address of C  
  Kv = secret encryption key shared by AS and V  

## We have the following guidelines:
* The identifiers of the clients, servers and TGS (IDc, IDv, IDtgs) as well as their secret keys (Kc, Kv and Ktgs) are letters, digits or punctuation symbols (see the table below).  
* The address of the principals (ADc and ADv) is an IPv4 address represented as a string of characters (eg the string '10.34.251.3').  
* The authentication server (AS) and the ticket granting server (TGS) consult a table containing the secret key of each of the principals. This table must be in a text file called **cles.txt** and contain, on each line, the identifier of a principal and its secret key, separated by a space.  
* The timestamps (TS1 and TS2) contain the POSIX time of the corresponding ticket.  
* The durations (Duration1 and Duration2) are expressed in seconds relative to the timestamp of the ticket.  
* The concatenation (||) operation will simply be the insertion of the space character between two fields.  
### Hash function:
The encryption function E to be used is a special version of a shift cipher algorithm. Each possible input character is associated with a number between 0 and 71, as in the following table.  
![table](https://user-images.githubusercontent.com/57264479/68959529-7ec94b00-07ce-11ea-8b34-e972ed369254.png)  

## How to use it  
**>cd ./code**  
**>make**  
1. An authentication server that must be called from the command line as follows:  
  **./as**  
    **IDc ADc IDtgs**  
2. Client decrypt the encrypted message contains the Tickettgs:  
  **./client**
    **client_key message_encrypted**  
3. A ticket granting server that must be called from the command line as follows:  
  **./tgt**  
    **IDc ADc IDv Tickettgs**  
4. A server providing a service, which must be able to be called from the command line as follows:  
  **./serveur**  
    **IDc ADc TicketV**  

## Demo  
* The server (V) grants access when the procedure is followed with appropriate values:  
![1](https://user-images.githubusercontent.com/57264479/68960815-38292000-07d1-11ea-9b6d-5420697e7880.png)  

* The TGS refuses a ticket if the client's address is not the same as that provided to the AS:  
![2](https://user-images.githubusercontent.com/57264479/68960956-82aa9c80-07d1-11ea-8fce-fa5430bacf67.png)  

* The server (V) refuses a ticket for the same reasons:  
![3](https://user-images.githubusercontent.com/57264479/68961039-acfc5a00-07d1-11ea-9b61-699f432fb902.png)  

* Server (V) refuse a ticket after it expires:  
![4](https://user-images.githubusercontent.com/57264479/68961122-e1701600-07d1-11ea-9f0a-4a5f888bf7ff.png)  


