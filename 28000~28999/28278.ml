open! StdLabels
open! MoreLabels

module Stack : sig
  type t

  val empty : t
  val push : t -> int -> t
  val pop : t -> t * int option
  val length : t -> int
  val is_empty : t -> bool
  val top : t -> int option
end = struct
  type t = int list * int

  let empty = [], 0
  let push (t, len) x = x :: t, len + 1

  let pop (t, len) =
    match t with
    | [] -> ([], 0), None
    | x :: xs -> (xs, len - 1), Some x
  ;;

  let length (_, len) = len
  let is_empty (_, len) = len = 0

  let top (t, _) =
    match t with
    | [] -> None
    | x :: _ -> Some x
  ;;
end

let rec process n t =
  if n > 0
  then
    (match
       input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
     with
     | [ 1; x ] -> Stack.push t x
     | [ 2 ] ->
       (match Stack.pop t with
        | t, None ->
          output_string stdout "-1\n";
          t
        | t, Some x ->
          output_string stdout (Int.to_string x ^ "\n");
          t)
     | [ 3 ] ->
       output_string stdout (Int.to_string (Stack.length t) ^ "\n");
       t
     | [ 4 ] ->
       output_string stdout (Int.to_string (Stack.is_empty t |> Bool.to_int) ^ "\n");
       t
     | [ 5 ] ->
       output_string
         stdout
         (Int.to_string (Stack.top t |> Option.value ~default:(-1)) ^ "\n");
       t
     | _ -> assert false)
    |> process (n - 1)
;;

let () =
  let n = input_line stdin |> int_of_string in
  process n Stack.empty
;;
