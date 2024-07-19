open! StdLabels
open! MoreLabels

module Trie = struct
  type t =
    { left : t option
    ; right : t option
    ; count : int
    ; value : int option
    }

  let empty = { left = None; right = None; count = 0; value = None }

  let num_to_bits x =
    let bits = Array.make 31 0 in
    let rec loop x i =
      if i = -1
      then bits
      else (
        bits.(i) <- x land 1;
        loop (x lsr 1) (i - 1))
    in
    loop x 30
  ;;

  let insert t value =
    let bits = num_to_bits value in
    let rec loop t idx =
      if idx = 31
      then { t with value = Some value; count = t.count + 1 }
      else (
        match bits.(idx) with
        | 0 ->
          { t with
            left = Some (loop (Option.value ~default:empty t.left) (idx + 1))
          ; count = t.count + 1
          }
        | 1 ->
          { t with
            right = Some (loop (Option.value ~default:empty t.right) (idx + 1))
          ; count = t.count + 1
          }
        | _ -> assert false)
    in
    loop t 0
  ;;

  let remove t value =
    let sanitize t =
      match t.count with
      | 0 -> None
      | _ -> Some t
    in
    let bits = num_to_bits value in
    let rec loop t idx =
      if idx = 31
      then sanitize { t with count = t.count - 1 }
      else (
        match bits.(idx) with
        | 0 ->
          sanitize
            { t with
              left = loop (Option.value ~default:empty t.left) (idx + 1)
            ; count = t.count - 1
            }
        | 1 ->
          sanitize
            { t with
              right = loop (Option.value ~default:empty t.right) (idx + 1)
            ; count = t.count - 1
            }
        | _ -> assert false)
    in
    loop t 0
  ;;

  let query t value =
    let bits = num_to_bits value in
    let rec loop t idx =
      match t.value with
      | Some v -> v lxor value
      | None ->
        (match t, bits.(idx) with
         | { left = Some left; _ }, 1 -> loop left (idx + 1)
         | { right = Some right; _ }, 0 -> loop right (idx + 1)
         | { left = Some left; _ }, _ -> loop left (idx + 1)
         | { right = Some right; _ }, _ -> loop right (idx + 1)
         | { left = None; right = None; _ }, _ -> assert false)
    in
    loop t 0
  ;;
end

let () =
  let n = input_line stdin |> int_of_string in
  let rec loop trie idx =
    if idx < n
    then (
      match
        input_line stdin |> String.split_on_char ~sep:' ' |> List.map ~f:int_of_string
      with
      | [ 1; x ] -> loop (Trie.insert trie x) (idx + 1)
      | [ 2; x ] ->
        let trie = Trie.remove trie x |> Option.value ~default:Trie.empty in
        loop trie (idx + 1)
      | [ 3; x ] ->
        Trie.query trie x |> string_of_int |> output_string stdout;
        output_char stdout '\n';
        loop trie (idx + 1)
      | _ -> assert false)
  in
  loop (Trie.insert Trie.empty 0) 0
;;
