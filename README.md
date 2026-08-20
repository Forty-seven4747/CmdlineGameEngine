# Commmand-line Game Engine (CGE)

This project can let you make your own game.

You can easily realize your own story if you have **learned about C++**.

You can also use Dev-C++ to edit.

## Code files of the project
- `game.cpp`
- `globals.cpp`
- `globals.h`
- `creation.cpp`
- `creation.h`
- `rooms.cpp`

## Defined variables and array
**Constants:**
|type|name|init. number|
|-----|-----|--|
|short|msize|64|
|short|froomax|256|
|short|dialmax|160|
|short|doormax|100|
|short|cremax|500|

**Structures:**

|type|name|
|---------------------------------------------------------|-----------------|
|Fdialogue{int room; bool trig;}                          |forcedia[froomax]|
|dials{char pose; short x,y; string words; double speed;} |dial[dialmax]|
|doors{short x,y; int gt; short tox,toy;}                 |d[doormax]|

**Other Variables**

|type|name|init. number|
|------------------|----|----|
|unsigned long long|tick||
|short|lim|10|
|char|gra[msize][msize]||
|char|prech|46('.')|
|char|bgch|46('.')|
|short|key||
|short|room|0|
|short|x|5|
|short|y|5|
|short|prex|-1|
|short|prey|-1|
|int|hp||
|string|wordpool||
|string|dialpool||


## Available Functions
- `getConsoleRows()` & `getConsoleLength()`: Get the size of the command prompt.
- `doorset(short ch, short x, short y, int gt, short tox, short toy)`:
  Plot a door(character 'O') at the current room, position(`x`,`y`).
  If player('@') touches the door, it will take player to room #`gt` and position(`tox`,`toy`).
- `dialword(string word)`: Triggle a dialogue and context with `word`.
- `randomint(int min,int max)`: Generates a number from `min` to `max`.

to be continued
