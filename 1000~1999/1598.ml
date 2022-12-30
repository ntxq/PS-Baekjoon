let dist u v =
  let xDiff = abs (u / 4 - v / 4) in
  let yDiff = abs ((u mod 4) - (v mod 4)) in
  xDiff + yDiff

let () =
    let u, v = Scanf.scanf "%d %d" (fun u v -> u, v) in
    print_endline (string_of_int (dist (u - 1) (v - 1)))