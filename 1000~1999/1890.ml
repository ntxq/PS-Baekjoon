open StdLabels
(* open MoreLabels *)

let countJumps (board : int array array) : int64 =
  let dp =
    Array.make_matrix ~dimx:(Array.length board)
      ~dimy:(Array.length board.(0))
      0L
  in
  dp.(0).(0) <- 1L;
  Array.iteri board ~f:(fun i row ->
      Array.iteri row ~f:(fun j dist ->
          if i + dist < Array.length board && dist > 0 then
            dp.(i + dist).(j) <- Int64.add dp.(i + dist).(j) dp.(i).(j);
          if j + dist < Array.length board && dist > 0 then
            dp.(i).(j + dist) <- Int64.add dp.(i).(j + dist) dp.(i).(j)));
  dp.(Array.length board - 1).(Array.length board.(0) - 1)

let () =
  let n = read_int () in
  let board =
    Array.init n ~f:(fun _ ->
        read_line ()
        |> String.split_on_char ~sep:' '
        |> List.map ~f:int_of_string |> Array.of_list)
  in
  countJumps board |> Int64.to_string |> print_endline
