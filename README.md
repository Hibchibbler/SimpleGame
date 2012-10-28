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

**The different types:**  
 * sg::CommPacket::Acceptance  
 * sg::CommPacket::Disconnect  
 * sg::CommPacket::Data  
 * sg::CommPacket::Error  
  
  
You need to use the sg::CommPacket::Acceptance and sg::CommPacket::Disconnect events to keep track of who is connecting, and who is disconnecting.  
Acceptance means that either we successfully made an outgoing connection(if you chose StartClient()),  
or an incoming connection request was accepted(if you chose StartServer())  
  
The primary packet type that is transmitted back and forth is sg::CommPacket::Data.  
The players constantly use sg::CommPacket::Data packets to transmit their position and orientation values, and the position for every in-flight projectile.  
  
The sg::CommPacket::Error packet type indicates an error occurred in the Comm object.  
It is likely a failed outgoing connection, or the listener didn't bind to the port that you specified.
  



Player  
------
Player contains all state that is specific to a player. Player also contains the image data used drawing  
the tank to the display. TankGame is composed of two instances of this class, among other things.

HUD
---
This contains all the player stats, and dashboard imagery.


Floor
-----
This contains the crude map loading code, and gets all the right tiles in the right spot in a big vector.
Each render pass, the vector is iterated through, and the individual tiles are plastered to the display.


Map Maker
=========
The map maker is a simple app written with C#.
I placed the C# project into the SimpleGame directory because i'm lazy, and i wanted to track it.
the Directory containing the map maker visual studio solution file is SimpleGame\TankMapMaker

The size of the map it produces is hard coded. so..

  
  
Important links  
===============  
http://www.dafont.com/digital-7.font  <- where i found the currently used font. they want money.
http://daringfireball.net/projects/markdown/dingus  <- "markdown" is what is used to create this README.md file

