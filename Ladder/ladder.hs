main = interact ladder
ladder p = show s
  where 
    s = ceiling $ f h / sin (f v * 0.0174532925)
    h:v:[] = map read $ words p
    f = fromIntegral