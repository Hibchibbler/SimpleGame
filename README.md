SimpleGame Architecture Basics  
==============================
TankGame  
--------
TankGame is the parent node in a data structure, that contains the entire state of a game. Particularly, the game has a Tank oriented theme.  
TankGame is composed of image data for the dash board, font(s), and player state/image data. The notion of player 1 and player 2 are throughout the code base.  
Each player has a dedicated class Player for tracking aformentioned things.  
  
TankGame is designed to be used in a simple game loop that fits nicely in main().  
If you look at main.cpp, it should be self evident how TankGame is used.
  
Comm  
----
Comm implements all the server and client code.  
it is built upon SFML 2.0 and TCP  
  
Comm is simple to setup and use.  
1. Instantiate a Comm object.  
2. Use either StartServer() or StartClient() to initiate Communications.  
3. Use Receive() to poll the Comm object for events that are either data payloads, or special notifications.  
  
Once you start a Comm object up, you will want to use Recieve() to poll for events.  
There are different types of events, which means the payload formats can differ.  
  
**Get a packet:**  
        sg::CommPacket packet;  
        while (tankGame.comm.Receive(packet)){  
            tankGame.onRemoteEvent(packet);  
        }  

**Get the packet type:**  
        sf::Uint32 packetType;  
        packet.packet >> packetType;  

**The differences:**  
 * sg::CommPacket::Acceptance  
 * sg::CommPacket::Disconnect  
 * sg::CommPacket::Data  
 * sg::CommPacket::Error  
  
  
You need to use the sg::CommPacket::Acceptance and sg::CommPacket::Disconnect events to keep track of who is connecting, and who is disconnecting.  
Acceptance means that either we successfully made an outgoing connection(if you chose StartClient()),  
or an incoming connection request was accepted(if you chose StartServer())  
  
In this game, we (attempt) to base the start of most game play when the sg::CommPacket::Acceptance occurs.  
And also, in this game, if a Disconnect occurs, communication is halted, but everything else continues as normal.  
TRIVIA: The reason you can't hurt the other tank when there is no one connected, is because it is the responsibility of a connected  
client to reduce its own health when it detects it has been hit. So, without a connected client, there is no one to determine if the other tank is being hit!  
  
The primary packet type that is transmitted back and forth is sg::CommPacket::Data.  
The players constantly use sg::CommPacket::Data packets to transmit their position and orientation values, and the position for every in-flight projectile.  
  
The sg::CommPacket::Error packet type indicates an error occurred in the Comm object.  
It is likely a failed outgoing connection, or the listener didn't like something you gave it.


  
Player  
------
Player contains all state that is specific to a player. Player also contains the image data used drawing  
the tank to the display. TankGame is composed of two instances of this class, among other things.  
  
