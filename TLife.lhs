> module Main where
>
> import Array
>
> data State = Alive | Dead
> data MicroAssertion = AliveCell (Int,Int) 
>                     | DeadCell (Int,Int)
>                     | DeadUpperPlane Int 
>                     | AliveUpperPlane Int 
>                     | DeadLowerPlane Int
>                     | AliveLowerPlane Int 
>                     | DeadLeftPlane Int 
>                     | AliveLeftPlane Int 
>                     | DeadRightPlane Int 
>                     | AliveRightPlane Int
>         deriving Show
>
> data Assertion = And [MicroAssertion]
>         deriving Show
> data Alternatives = Or [Assertion]
>
> neighbours :: (Int,Int) -> [(Int,Int)]
> neighbours (x,y) = [(x-1,y-1),(x,y-1),(x+1,y-1),
>                     (x-1,y),(x,y),(x+1,y),
>                     (x-1,y+1),(x,y+1),(x+1,y+1)]
>
> dropNthElement n xs = let (ys,zs) = splitAt n xs   in   ys ++ (tail zs)
> 
> nElementPartitions :: Int -> [a] -> [([a],[a])]
> nElementPartitions 1 (xs) = 
>   [ ([xs !! i],dropNthElement i xs) | i <- everyListPosition ]
>   where everyListPosition = [0 .. (length xs) - 1]
> nElementPartitions n (xs) =
>     [(d:xs,ys)
>          | (d,parts) <- oneElementPartitions , 
>            (xs,ys) <- nElementPartitions (n-1) parts 
>     ]
>   where oneElementPartitions = [(xs !! i,dropNthElement i xs) | i <- everyListPosition ]
>         everyListPosition = [0 .. (length xs) - 1]

>         


nAlive creates an assertion list to represent the concept of m cells in the
past and n cells in the future being alive.

> mnAlive :: (Int,Int) -> Int -> Int -> [(Assertion,Assertion)]
> mnAlive (x,y) m n = [(p,f) | p <- past, f <- future ]
>  where cells = neighbours (x,y)
>        past = [ And ((map AliveCell alives) ++ (map DeadCell deads))
>                     | (alives,deads) <- nElementPartitions m cells]
>        future = [ And ((map AliveCell alives) ++ (map DeadCell deads))
>                       | (alives,deads) <- nElementPartitions n cells]
>        

makeAssertions takes a cell assertion and creates the assertions which
would need to happen in the future or past to make that possible.


> main = putStr (show (mnAlive (1,1) 2 2))