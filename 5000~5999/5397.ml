open StdLabels

module type Key_logger = sig
  type t

  val empty : t
  val prev : t -> t
  val next : t -> t
  val insert : char -> t -> t
  val remove : t -> t
  val to_string : t -> string
end

module Key_logger : Key_logger = struct
  type t = char list * char list

  let empty = ([], [])
  let prev (l, r) = match l with [] -> (l, r) | x :: xs -> (xs, x :: r)
  let next (l, r) = match r with [] -> (l, r) | x :: xs -> (x :: l, xs)
  let insert c (l, r) = (c :: l, r)
  let remove (l, r) = match l with [] -> (l, r) | _ :: xs -> (xs, r)

  let to_string (l, r) =
    List.fold_left ~f:(fun acc x -> x :: acc) ~init:r l
    |> List.to_seq |> String.of_seq
end

let log () =
  let rec loop log =
    let open Key_logger in
    match input_char stdin with
    | '\n' -> to_string log
    | '<' -> loop (prev log)
    | '>' -> loop (next log)
    | '-' -> loop (remove log)
    | c -> loop (insert c log)
  in
  loop Key_logger.empty

let () =
  List.init ~len:(read_int ()) ~f:(fun _ -> log ())
  |> List.iter ~f:print_endline
