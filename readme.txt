GameObject:
Purposefully not given any transform component by default. Since not everything has a position. Multiples of components were allowed but poorly supported, I wanted to resrict as little as possible here even though maybe that would have been easier.
GO's were also given a Startup() function which is only excuted on their first update, I've found this to be reoccuring in my code and thought it'd be handy to have.
They were also given tags, which were useful in some cases to help figure out what kind of GO was being dealt with. Though I think there is likely a better system to do this, since it's easy to start giving tags to everything and have GO's be a big mess of them.

Component:
All components were given empty implementations of all their functions, so subclasses didn't need to needlessly define functions they weren't ever gonna use.

Input:
I had a grand vision of unified access by having all keys be the same. This caused a lot of hassle, looking back I'd likely delegate to the managers for this. I'd also like to have added simple functions to see if something was pressed without the use of commands, since they were often a burden to have to deal with/go trough. I'll definitely look more into this topic to see how to do it in a nice way, maybe rewrite this part of the engine.

Events:
I prefered the use of the event system over observer/subject since with the Event system I made it was easy to send and receive events and less cumborsume in my opinion. The Events also allowed for easy data transfer

https://github.com/HuygheHenri-Thibault/Boopigin