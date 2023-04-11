open! StdLabels
open! MoreLabels

let sieve =
  let isPrime = Array.make 1000001 true in

  let rec filter i j =
    if j < 1000001 then (
      isPrime.(j) <- false;
      filter i (i + j))
  in

  isPrime.(0) <- false;
  isPrime.(1) <- false;
  for i = 2 to 1000000 do
    if isPrime.(i) then filter i (i * i)
  done;

  isPrime

let countPartition x =
  let rec loop i acc =
    if i > x / 2 then acc
    else if sieve.(i) && sieve.(x - i) then loop (i + 1) (acc + 1)
    else loop (i + 1) acc
  in
  loop 2 0

let () =
  let testcases = input_line stdin |> int_of_string in
  for _ = 1 to testcases do
    input_line stdin |> int_of_string |> countPartition |> string_of_int
    |> fun s -> output_string stdout (s ^ "\n")
  done
