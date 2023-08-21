open! StdLabels
open! MoreLabels

module Deque : sig
  type t

  val empty : t
  val push_front : t -> int -> t
  val push_back : t -> int -> t
  val pop_front : t -> t * int option
  val pop_back : t -> t * int option
  val length : t -> int
  val is_empty : t -> bool
  val front : t -> t * int option
  val back : t -> t * int option
end = struct
  type t =
    { front : int list
    ; back : int list
    ; length : int
    }

  let empty = { front = []; back = []; length = 0 }

  let normalize t =
    let split xs len =
      let xs, ys, _ =
        List.fold_right xs ~init:([], [], 0) ~f:(fun x (xs, ys, i) ->
          if i < len / 2 then xs, x :: ys, i + 1 else x :: xs, ys, i + 1)
      in
      xs, List.rev ys
    in
    match t.front, t.back with
    | [], [] -> t
    | [], xs ->
      let back, front = split xs t.length in
      { front; back; length = t.length }
    | xs, [] ->
      let front, back = split xs t.length in
      { front; back; length = t.length }
    | _, _ -> t
  ;;

  let push_front t x = { t with front = x :: t.front; length = t.length + 1 }
  let push_back t x = { t with back = x :: t.back; length = t.length + 1 }

  let pop_front t =
    let t = normalize t in
    match t.front, t.back with
    | [], [] -> t, None
    | [], [ x ] -> { front = []; back = []; length = t.length - 1 }, Some x
    | x :: xs, ys -> { front = xs; back = ys; length = t.length - 1 }, Some x
    | [], _ -> assert false
  ;;

  let pop_back t =
    let t = normalize t in
    match t.front, t.back with
    | [], [] -> t, None
    | [ x ], [] -> { front = []; back = []; length = t.length - 1 }, Some x
    | xs, y :: ys -> { front = xs; back = ys; length = t.length - 1 }, Some y
    | _, [] -> assert false
  ;;

  let length t = t.length
  let is_empty t = t.length = 0

  let front t =
    let t = normalize t in
    match t.front, t.back with
    | [], [] -> t, None
    | [], [ x ] -> t, Some x
    | x :: _, _ -> t, Some x
    | [], _ -> assert false
  ;;

  let back t =
    let t = normalize t in
    match t.front, t.back with
    | [], [] -> t, None
    | [ x ], [] -> t, Some x
    | _, y :: _ -> t, Some y
    | _, [] -> assert false
  ;;
end

let rec process n t =
  if n > 0
  then
    (match
       input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
     with
     | [ 1; x ] -> Deque.push_front t x
     | [ 2; x ] -> Deque.push_back t x
     | [ 3 ] ->
       (match Deque.pop_front t with
        | t, Some x ->
          string_of_int x ^ "\n" |> output_string stdout;
          t
        | t, None ->
          output_string stdout "-1\n";
          t)
     | [ 4 ] ->
       (match Deque.pop_back t with
        | t, Some x ->
          string_of_int x ^ "\n" |> output_string stdout;
          t
        | t, None ->
          output_string stdout "-1\n";
          t)
     | [ 5 ] ->
       string_of_int (Deque.length t) ^ "\n" |> output_string stdout;
       t
     | [ 6 ] ->
       string_of_int (Deque.is_empty t |> Bool.to_int) ^ "\n" |> output_string stdout;
       t
     | [ 7 ] ->
       (match Deque.front t with
        | t, Some x ->
          string_of_int x ^ "\n" |> output_string stdout;
          t
        | t, None ->
          output_string stdout "-1\n";
          t)
     | [ 8 ] ->
       (match Deque.back t with
        | t, Some x ->
          string_of_int x ^ "\n" |> output_string stdout;
          t
        | t, None ->
          output_string stdout "-1\n";
          t)
     | _ -> assert false)
    |> process (n - 1)
;;

let () =
  let n = input_line stdin |> int_of_string in
  process n Deque.empty
;;
