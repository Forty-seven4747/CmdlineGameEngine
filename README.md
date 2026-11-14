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

|file|what it holds|
|----|-------------|
|`game.cpp`|console helpers, dialogue, drawing, the frame loop and `main()`|
|`globals.h`|includes, constants, structures, `extern` declarations, function prototypes|
|`globals.cpp`|the one and only definition of every global variable and array|
|`creation.h`|the `creation` structure and `crerase()`|
|`creation.cpp`|`cre[]`, `crerase()`, `creationset()`, `creationupdate()`|
|`rooms.cpp`|`roomchg()`, one `case` per room — this is where a story is written|

## Defined variables and array

**Constants:**

|type|name|init. number|
|-----|-----|--|
|short|msize|64|
|short|froomax|256|
|short|dialmax|160|
|short|doormax|100|
|short|cremax|500|

`msize` is the real size of `gra[][]`. `lim` says how much of it is drawn and played. Constants are shared through `globals.h`; the arrays are defined once in `globals.cpp` / `creation.cpp`.

**Structures:**

|type|name|
|---------------------------------------------------------|-----------------|
|Fdialogue{int room; bool trig;}                          |forcedia[froomax]|
|dials{char pose; short x,y; string words; double speed;} |dial[dialmax]|
|doors{short x,y; int gt; short tox,toy;}                 |d[doormax]|
|creation{see creation fields below}                      |cre[cremax]|

**creation fields:**

|type|name|what it is for|
|----|----|--------------|
|int|freq|ticks to wait between two moves|
|char|pose|character drawn on the map; the null character means an empty slot|
|string|words|what is said when the player touches it|
|short|x,y|current position|
|bool|trig|already initialised in this room|
|unsigned long long|tick|tick of the last move|
|short|nex,ney|reserved, not used for now|
|`vector<short>`|deltax,deltay|step tables, one pair from each per move|
|int|mdpoint|cursor into the step tables|
|short|dx,dy|constant speed on each axis|
|int|roomat|which room it belongs to|

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
|short|fdcur||
|short|creacur||

`gra[x][y]` is indexed `[row][column]`: `x` is vertical (up/down), `y` is horizontal (left/right). `prex/prey` is the cell the player came from, `-1` before the first move. `prech` keeps the background character that `@` covered, so it can be restored. `hp`, `wordpool` and `dialpool` are scratch space; `wordpool` and `dialpool` hold the letters already printed by a dialogue. `fdcur` and `creacur` are the next free slot of `forcedia[]` and `cre[]`.

## Available Functions

- `getConsoleRows()` & `getConsoleLength()`: Get the size of the command prompt.
- `doorset(short ch, short x, short y, int gt, short tox, short toy)`:
Plot a door(character 'O') at the current room, position(`x`,`y`).
If player('@') touches the door, it will take player to room #`gt` and position(`tox`,`toy`).
- `dialword(string word)`: Triggle a dialogue and context with `word`.
- `randomint(int min,int max)`: Generates a number from `min` to `max`.

The four above are only the beginning. `d[]` and `dial[]` are wiped at the start of every frame, so all of the calls below belong **inside `roomchg()`**, which runs once per frame.

### Console and dialogue

- `hidecursor()` & `showcursor()`: hide or show the blinking console caret.
- `gotoxy(int x,int y)`: move the console cursor. Dialogues are printed at row `lim+3`.
- `dialword(string word)`: prints `word` one letter at a time with a short pause, then throws away any key pressed while reading. A direct, one-shot line of text.
- `dialogue(short ch=0)`: speaks `dial[ch].words` letter by letter. A bigger `dial[ch].speed` holds each letter longer. It also marks the forced dialogue of this room as played.
- `findfroom(int r=room)`: returns the index of this room's forced-dialogue entry, or `-1`. The argument is unused — the search always reads the global `room`.
- `dialset(short ch,char pose,short x,short y,string words,double sp=1.0,bool force=false)`:
  Places a talkative object that looks like `pose` at (`x`,`y`). Stepping on it pushes the player back and calls `dialogue(ch)`. `sp` is the speed of speaking.
  With `force=true` the first five arguments are ignored: the line goes into `dial[dialmax-1]` **off the map** and plays by itself as soon as the room is entered, once per room. `forcedia[]` and `fdcur` remember which rooms already played it.

### Drawing the background

- `bgchar(short col,string a)`: writes a string into column `col` of `gra[][]`, one character per row. Longer than `lim` is ignored.
- `bgrect(char f,short xs,short ys,short xe,short ye)`: fills a rectangle with character `f`. `s=start, e=end`. Out-of-range rectangles are ignored.
- `randomint(int min,int max=-47)`: with both numbers it returns a value in `[min,max)`; if `min>max` the range is reversed. `max==-47` is the sign for "from 0 to `min`".

### Creations

- `creationset(char pose,short initx,short inity,string words,int freq=50,short nextx=0,short nexty=0,const vector<short>& movedeltax=vector<short>(),const vector<short>& movedeltay=vector<short>(),short xdelta=0,short ydelta=0)`:
  Places a creation. **No slot number is needed** — one call takes the next free slot through `creacur`, and `roomat` clears it automatically when the room changes. `freq` is the number of ticks between two moves. There are three mutually exclusive movement modes, picked in this order:
  1. `xdelta` or `ydelta` is not zero → moves constantly by that vector, turning around at the edge of the map.
  2. Both step tables are non-empty → takes one `(deltax[k],deltay[k])` pair per move and wraps around at the end of the table. The two tables are used in pairs, so the shorter one decides the length. Walls, the player and other creations block a step.
  3. Both tables are empty → random walk, up to eight tries per move to find a free cell.

  Because the tables are `vector<short>`, C++11 brace lists work directly:

```cpp
creationset('a',7,7,"Don't run!",20,0,0,{1,0,-1,0},{0,1,0,-1},0,0);//a square path
creationset('a',8,8,"SO WHAT!",20,0,0,{-1,0,1,0},{0,-1,0,1},0,0);
creationset('b',6,1,"You touched me!",9,0,0,vector<short>(),vector<short>(),0,1);//constant speed
```

- `crerase(int n)`: empties one `cre[]` slot. `roomchg()` calls it for the unused tail slots, so it is rarely needed in a room.
- `creationupdate()`: moves every live creation. Called by `graph()` before anything is drawn, so what is printed is this frame's position.

### Engine internals

These are called by the frame loop. They are listed here because changing them changes how a room behaves.

- `roomchg(short r)`: the room table. Add a `case` here to add a room; unknown numbers fall into `default`, which prints a "room does not exist" message. It also resets `creacur` and clears the tail of `cre[]`.
- `checkDoor()`: returns true when the player stands on a door. It only changes `room`, `x`, `y`, `prex`, `prey` — it never touches `gra` or `d[]`.
- `gracre()`: draws doors as `O`, `dial[]` poses and `cre[]` poses into `gra[][]`, in that order.
- `updMChara()`: clamps the player into `[0,lim)`, pushes back from walls and talkative objects, resolves creation collisions, writes `@` and restores the previous cell's background.
- `sthhere(int x,int y)`: returns true when a cell is a wall or outside the map. Used by the collision fallback.
- `graph()`: one whole frame, see below.
- `main()`: hides the cursor, seeds `srand(time(0))`, then loops on keyboard input, calling `graph()` and incrementing `tick` each time.

## How one frame runs

```
graph()
  gotoxy(0,0)
  pass 0..1:
      memset(d,-1) / memset(gra,bgch) / clear every dial[] slot
      roomchg(room)            lay background, doors, dials and creations
      checkDoor()              if the room changed, continue and lay it again
  creationupdate()             move creations first
  gracre()                     draw doors, dials and creations — same stage as the background
  updMChara()                  the player, collisions, '@'
  print gra
  forced dialogue              an overlay, printed after the complete picture
```

`checkDoor()` must come **after** `roomchg(room)`: the door array is empty before the room is laid. When a door is taken, `continue` lays the new room once more, and the drawing happens only on the last pass. That is why doors and creations appear together with the background on the very frame the room changes.

## Controls

|key|action|
|---|------|
|Arrow up / down|`x--` / `x++`|
|Arrow left / right|`y--` / `y++`|
|Esc|quit, clear the screen and print `bye!`|

Arrow keys arrive as two reads: `0xe0` first, then `0x48`, `0x50`, `0x4b` or `0x4d`. Reading a dialogue throws away buffered keys, so a key pressed during a long line is lost.

## Make your own room

Add a `case` to `roomchg()` in `rooms.cpp`. Nothing has to be registered anywhere else:

```cpp
case 4:{
    bgrect('#',0,0,0,9);
    bgchar(3,"A new room");
    dialset(0,'&',4,4,"Hello there.");
    creationset('c',2,2,"...",47);
    doorset(0,9,9,0,5,5);
    break;
}
```

`doorset` takes the player to room `gt` and drops them at `(tox,toy)`. Every room needs its own `doorset` call, because `d[]` is cleared each frame. A forced dialogue is one `dialset(...,true)` per room.

## Build

- Written for **Dev-C++ 5.11** with TDM-GCC 4.9.2 (MinGW64). `windows.h` and `conio.h` mean Windows only.
- **C++11 is required.** `Makefile.win` and `cmdEngine.dev` both carry `-std=c++11`; the brace lists in `rooms.cpp` need it. In Dev-C++ pick `Project → Project Options → Compiler → Code Generation → ISO C++11`.
- Build with **F12 (Rebuild All)** after changing any `.h`. `Makefile.win` only compares timestamps of `.cpp` against `.o` and does not track header dependencies; a plain build can link objects built against an older structure layout without any linker error.
- Switching between the Debug and Release compiler sets also needs a full rebuild: `-g3` is baked into the `.o` files, so relinking alone keeps the debug sections and a large exe.

## Notes

- `lim` is 10 while `msize` is 64. Only the `lim x lim` corner of `gra[][]` is drawn and checked; a bigger map needs `lim` changed and a console tall enough for it.
- `tick` only advances once per loop in `main()`. There is no `Sleep` in the main loop, so `freq` is measured in frames and the game runs as fast as the machine allows.
- `hp`, `nex` and `ney` are declared but unused. `findfroom(int r)` ignores `r`.
- `getConsoleRows()` and `getConsoleLength()` return `-1` when there is no real console (for example under a pipe or a pseudo terminal). `dialword()` multiplies the length by 10 to wipe a line, so running the engine outside a console needs care.
- `updMChara()` writes `@` over whatever is already in that cell, so a creation under the player is hidden for that frame.
