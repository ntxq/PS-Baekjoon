open! StdLabels
open! MoreLabels

let binary_power base exp modular =
  let open Int64 in
  let rec aux base exp modular acc =
    if equal exp 0L then acc
    else if equal (logand exp 1L) 0L then
      aux (unsigned_rem (mul base base) modular) (shift_right exp 1) modular acc
    else
      aux
        (unsigned_rem (mul base base) modular)
        (shift_right exp 1) modular
        (unsigned_rem (mul acc base) modular)
  in

  aux (unsigned_rem base modular) exp modular 1L

let check_composite n a d s =
  let open Int64 in
  let rec aux x n s =
    if s = 0 then true
    else
      let x = unsigned_rem (mul x x) n in
      if equal x (pred n) then false else aux x n (s - 1)
  in

  let x = binary_power a d n in
  if equal x 1L || equal x (pred n) then false else aux x n s

let miller_rabin n =
  let open Int64 in
  let r = ref 0 in
  let d = ref (pred n) in
  while equal (logand !d 1L) 0L do
    d := shift_right !d 1;
    incr r
  done;

  List.for_all [ 2L; 3L; 5L; 7L; 11L ] ~f:(fun a ->
      a = n || not (check_composite n a !d !r))

let () =
  let n = input_line stdin |> int_of_string in
  List.init ~len:n ~f:(fun _ ->
      input_line stdin |> Int64.of_string
      |> (fun x -> Int64.(succ (mul 2L x)))
      |> miller_rabin)
  |> List.fold_left ~init:0 ~f:(fun acc x -> if x then acc + 1 else acc)
  |> string_of_int |> print_endline
