# Malloc

The aim of this project is to build a malloc implementation offering 3 buckets:
 - a first one for tiny memory blocks
 - second one for small memory blocks
 - third one for the other ones

## Implementation
 I choose to build on two different strategies: one for the tiny and small
 blocks, and one for the lage blocks.

### Small block strategy
I build a heap, starting with a heap header, containing informations about the
length of the current heap chunk and the address of the next free memory chunk.
