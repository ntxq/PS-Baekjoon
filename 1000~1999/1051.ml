let check x y nums len =
  let target = nums.(x).(y) in
  nums.(x + len).(y) = target
  && nums.(x).(y + len) = target
  && nums.(x + len).(y + len) = target

let maxLen x y n m nums =
  let check = check x y nums in
  let rec loop x y len acc =
    if x + len >= n || y + len >= m then acc
    else loop x y (len + 1) (if check len then len + 1 else acc)
  in
  loop x y 0 0

let solve n m nums =
  let rec loop idx acc =
    if idx >= n * m then acc
    else
      let x = idx / m and y = idx mod m in
      loop (idx + 1) (max acc (maxLen x y n m nums))
  in
  loop 0 0

let () =
  let n, m = Scanf.scanf "%d %d\n" (fun n m -> (n, m)) in
  Array.init n (fun _ ->
      Scanf.scanf "%s\n" (fun s ->
          String.to_seq s |> Seq.map int_of_char |> Array.of_seq))
  |> solve n m
  |> (fun len -> len * len)
  |> string_of_int |> print_endline
