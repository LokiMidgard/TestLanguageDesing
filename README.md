# TestLanguageDesing

**This is berfore early prototyping.** Better Move on ;)
Scripting languge

Usecase:
 - old SNES jrpg like games with primitvs for drawing tilemaps text and sprites
 - hard to use incorrectly
 - target includes yung people without prior programming experience.

Features:
- [ ] Stack based Byte code interpreter
- [ ] Static typed language with union and intersection types
- [ ] Non nullable references (unless type explicit includes null)
- [ ] Objects should not be usable between threads without explicit opt in
      - can every type cratede as a shared objec? (I think no?)
      - Every Property of a shared object is automaticly implemented with an async read/write lock
      - what about methods?
      - can parameter be non shareable objects? (When? Always?)
      - ...
- [ ] Async await support
- [ ] No garbage collector, explicity new and delete
      - Metadata of an reference nows if the type was delted,
        should be impossible to access reused memory over an stale reference
      - Owner of Pointer is explicity set and can be transfererd.
      - Static analyzis should be able to detect if a reference that owns a pointer
        leaves the scope without being deleted


# How to

## find out if an object was deleted

The Memory of the Program is devided in 4 parts Stack, Heap, Instructions, Lookup.

References to Objects do not point directly in the Heap but in the Lookup, an an entry in the Lookup has a pointer to the heap.
Besides a pointer in the lookup, a reference has also an id. If a new Object is alocated a new Metadata object is alocated in the
Lookup and enough memory is alocated on the heap. The Metadata sets values like Type etc and sets the id to 1. The Reference also sets the ID to `1`.
If an object gets deleted the Id in the Metadata is negated. `1` will be `-1`. When accessing a reference the ID of the reference and the ID of the Metadata
can be compared, only if both values are identicle the object is still valid.

Instead of allocating a new metadatadata object an already freed object can be reused by negating the negative id again and increasing it. `-1` will be `2`.
Since all Metadataobjects have the same size independent of the objects referenced there should e no fragmentation in the lookup memory.


Every Object has some Metadata like type size etc. 
