#context-free select Position of aleatory tail
#context-free show Table
#context-free chek Winner or Game Over
#context-free print Table structure
#proto MovingRightDown(_X_)
#proto MovingLeftUp(_X_)
#proto checkPointLeftUp(_X_)
#proto checkPointRightDown(_X_)
#proto checkMoveRightDown(_X_)
#proto checkMoveLeftUp(_X_)
#define KUP        5
#define KDOWN     24
#define KLEFT     19
#define KRIGHT     4
#define KESCAPE   27
#define MOVEHORZ   1
#define MOVEVERT   0 
#define equaltables(_X_,_Y_)   _I_=1,\
                               __LOOP_ROW__:,\
                                    _J_=1,\
                                    __LOOP_COL__:,\
                                        [_I_,_J_]get(_X_),get(_Y_),neq? do{{0},jmp(__OUT__LOOP__)},\
                                        ++_J_,{4,_J_}jle(__LOOP_COL__),\
                                    ++_I_,{4,_I_}jle(__LOOP_ROW__),\
                               {1},__OUT__LOOP__:,clear mark
#include <hopper.h>

main:
  .ctrl c
  contador de movimientos=0
  score=0
  table=0,{4,4}zeros array(table)  // create table
  oldTable=0, show Structure=1
 /* define initial positions */
  {""}tok sep
  select Position of aleatory tail
  select Position of aleatory tail
  home
  hide cursor
  show Table
  c=0, go=1,swFin=1

 /* game! */
  __PLAY_GAME__:
     
     if key pressed?
         lastkey(c)
         oldTable = table
         switch(c)
            case(KRIGHT) :: do{ _check Move Right Down(MOVEHORZ), exit }
            case(KDOWN)  :: do{ _check Move Right Down(MOVEVERT), exit }
            case(KLEFT)  :: do{ _check Move Left Up(MOVEHORZ),    exit }
            case(KUP)    :: do{ _check Move Left Up(MOVEVERT),    exit }
            case(KESCAPE):: do{ go=0,swFin=0 }
         end switch
         kbfree
         chek Winner or Game Over
         {go}do{
             if ( not( equal tables(oldTable, table) ) )
                select Position  of aleatory tail
                ++contador de movimientos
             end if
             show Table
         }
     end if
     {go},jt(__PLAY_GAME__)

     if ( {swFin} )
        {"          \LG","YOU WIN!!!\OFF"}
     else
        {"          \LR","GAME OVER\OFF"}
     end if
     println
     show cursor
exit(0)

.locals
Moving Right Down(tmpTab)
   {tmpTab} compact,ht=0,cpy(ht), length,{4}sub,sizet=0,mov(sizet)
   clear(tmpTab),{sizet}zerosarray(tmpTab)
   {ht,tmpTab}array(CONCAT)
   {tmpTab}
back
Moving Left Up(tmpTab)
   {tmpTab} compact,clear(tmpTab),cpy(tmpTab), length,{4}sub,sizet=0,mov(sizet)
   {sizet}zero?,not,do{ ht=0,{sizet}zerosarray(ht)
   {ht,tmpTab}array(CONCAT) }
   {tmpTab}
back
check Point Right Down(tmpTab)
  v1=0,v2=0,tScore=0,totScore=0
  for(k=4,{k}gthan(1),--k)
     [k]get(tmpTab),mov(v1)
     [{k}minus(1)]get(tmpTab),mov(v2)
     if( {v1} eqto (v2) )
         {v1,v2}add,cpy(tScore),[k]put(tmpTab),[{k}minus(1)]{0}put(tmpTab)
         {tScore}plus(totScore),mov(totScore)
     end if
  next
  {tmpTab,totScore}
back
check Move Right Down (_DIRECTION_)
  tmpTab=0
  for(i=1,{i}lethan(4),++i)
    if ( {_DIRECTION_} )    // rows or cols??
       [i,1:4]   // rows!
    else
       [1:4,i]   // cols!
    end if
    get(table), mov(tmpTab)
    
    if( {tmpTab}stats(SUMMATORY) )     // exist numbers in the row??
       clear mark
       _Moving Right Down(tmpTab),mov(tmpTab)    // move its!
       clear mark
       _check Point Right Down(tmpTab),plus(score),mov(score)  // check score...
       mov(tmpTab)
       _Moving Right Down(tmpTab),mov(tmpTab)   // move remanents!
       if( {_DIRECTION_} )
          [i,1:4]
       else
          [1:4,i]
       end if
       {tmpTab}, put(table)
    end if
  next
  clear mark.
back

check Point Left Up(tmpTab)
  v1=0,v2=0,tScore=0,totScore=0
  for(k=1,{k}lthan(4),++k)
     [k]get(tmpTab),mov(v1)
     [{k}plus(1)]get(tmpTab),mov(v2)
     if( {v1} eqto (v2) )
        {v1,v2}add,cpy(tScore),[k]put(tmpTab),[{k}plus(1)]{0}put(tmpTab)
        {tScore}plus(totScore),mov(totScore)
     end if
  next
  {tmpTab,totScore}
back

check Move Left Up(_DIRECTION_)
  tmpTab=0 
  for(i=1,{i}lethan(4),++i)
    if( {_DIRECTION_} )
       [i,1:4]
    else 
       [1:4,i]
    end if
    get(table),mov(tmpTab)
    if( {tmpTab}stats(SUMMATORY) )  // exist numbers in the row??
       clear mark
       _Moving Left Up(tmpTab),mov(tmpTab)  // move its!
       clear mark
       _check Point Left Up(tmpTab),plus(score),mov(score)  // check score...
       mov(tmpTab)
       _Moving Left Up(tmpTab),mov(tmpTab)  // move remanents!
       if( {_DIRECTION_} )
          [i,1:4]
       else
          [1:4,i]
       end if
       {tmpTab},put(table)
    end if
  next
  clear mark.
back

chek Winner or Game Over:
  {table}gthan(0),xtonum,stats(SUMMATORY),{16} eq? do{{0}mov(go),{0}mov(swFin),back}  // You loose!
  {0}reshape(table),{2048,table}array(SCAN){0} neq? do{{0}mov(go),back}   // you Win!
  {4,4}reshape(table)
back

select Position of aleatory tail:
  prec(-1)
  __NO_VALID_POS__:
     {10}rand, mulby(10),ceil,module(5),x=0,cpy(x),zero?,do{x=1}
     {10}rand, mulby(10),ceil,module(5),y=0,cpy(y),zero?,do{y=1}
     [x,y]get(table),jnz(__NO_VALID_POS__)
  newTail=2
  {1}rand,gthan(0.9), do{ newTail=4 }
  {newTail},put(table), clear mark.
  prec(0)
back

show Table:
  tmpTable=0
  {" ",6,table}xtostr,padcenter,mov(tmpTable)
 // prepare colours of tiles
  {"\BGLGR\BK      \OFF","  0   ",tmpTable}   transform, mov(tmpTable)
  {"\BGLGR\BK  2   \OFF","  2   ",tmpTable}   transform, mov(tmpTable)
  {"\BGLGR\B  4   \OFF","  4   ",tmpTable}    transform, mov(tmpTable)
  {"\BGLGR\B  8   \OFF","  8   ",tmpTable}    transform, mov(tmpTable)
  {"\BGR\W  16  \OFF","  16  ",tmpTable}      transform, mov(tmpTable)
  {"\BGY\BK  32  \OFF","  32  ",tmpTable}     transform, mov(tmpTable)
  {"\BGB\W  64  \OFF","  64  ",tmpTable}      transform, mov(tmpTable)
  {"\BGLM\BK 128  \OFF"," 128  ",tmpTable}    transform, mov(tmpTable)
  {"\BGG\W 256  \OFF"," 256  ",tmpTable}      transform, mov(tmpTable)
  {"\BGB\W 512  \OFF"," 512  ",tmpTable}      transform, mov(tmpTable)  
  {"\BGR\W 1024 \OFF"," 1024 ",tmpTable}      transform, mov(tmpTable)
  {"\BGBK\W\ENF 2048 \OFF"," 2048 ",tmpTable} transform, mov(tmpTable)

 // and PRINT!!
  {show Structure} do{ print Table structure,{0} mov(show Structure) }

  clear mark
  scrx=2
  for (i=1, {i}lethan(4),++i)
        {2,scrx}goxy,[1,i]get(tmpTable),print
        {4,scrx}goxy,[2,i]get(tmpTable),print
        {6,scrx}goxy,[3,i]get(tmpTable),print
        {8,scrx}goxy,[4,i]get(tmpTable),print
        clear mark
        scrx += 7
  next

  {"\BGB\W\ENF","\n\n\t   2 0 4 8   \OFF\n\n"}
  {"Movimiento # ",contador de movimientos,", \INVSCORE=",score,"\OFF\n"}//,tmpTable}
  println

back

print Table structure:
  {"┌──────┬──────┬──────┬──────┐\n"},strtoutf8,
  {"│ 2048 │ 2048 │ 2048 │ 2048 │\n"},strtoutf8,
  {"├──────┼──────┼──────┼──────┤\n"},strtoutf8,
  {"│ 2048 │ 2048 │ 2048 │ 2048 │\n"},strtoutf8,
  {"├──────┼──────┼──────┼──────┤\n"},strtoutf8,
  {"│ 2048 │ 2048 │ 2048 │ 2048 │\n"},strtoutf8,
  {"├──────┼──────┼──────┼──────┤\n"},strtoutf8,
  {"│ 2048 │ 2048 │ 2048 │ 2048 │\n"},strtoutf8,
  {"└──────┴──────┴──────┴──────┘"},strtoutf8,
  println
back
